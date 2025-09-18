#include <windows.h>
#include <mmsystem.h>
#include <atomic>
#include <thread>
#include <chrono>
#include <cstdio>
#include <cstring>

#pragma comment(lib, "winmm.lib")

// 固定参数（无随机抖动）
static constexpr int SPRINT_MS     = 175; // Shift按下持续时间
static constexpr int POST_GAP_MS   = 0;  // 冲刺后间隔
static constexpr int JUMP_HOLD_MS  = 5;  // 空格保持时间
static constexpr int CYCLE_MS      = 125; // 冷却周期

// 扫描码（US键位布局）
static constexpr USHORT SC_W       = 0x11;
static constexpr USHORT SC_LSHIFT  = 0x2A;
static constexpr USHORT SC_SPACE   = 0x39;

static std::atomic<bool> g_running{ true };
static std::atomic<bool> g_active{ false };
static std::thread g_worker;
static std::atomic<bool> g_graceful{ false };
static std::atomic<int>  g_cycles_to_finish{ 0 };

// 发送键盘扫描码
void SendScan(USHORT sc, bool down) {
    INPUT in = {};
    in.type = INPUT_KEYBOARD;
    in.ki.wVk = 0;
    in.ki.wScan = sc;
    in.ki.dwFlags = KEYEVENTF_SCANCODE | (down ? 0 : KEYEVENTF_KEYUP);
    SendInput(1, &in, sizeof(in));
}

// 安全释放常用键
void ReleaseAllKeys() {
    SendScan(SC_W, false);
    SendScan(SC_LSHIFT, false);
    SendScan(SC_SPACE, false);
}

// 睡眠（毫秒）
inline void SleepMs(int ms) {
    if (ms <= 0) return;
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

// 可中断睡眠：返回 true 表示睡满，false 表示被停止打断
inline bool CancelableSleep(int ms) {
    if (ms <= 0) return true;
    using namespace std::chrono;
    auto deadline = steady_clock::now() + milliseconds(ms);
    while (true) {
        if (!g_running.load(std::memory_order_relaxed) || !g_active.load(std::memory_order_relaxed)) {
            return false;
        }
        if (steady_clock::now() >= deadline) return true;
        std::this_thread::sleep_for(milliseconds(1));
    }
}

// 保持W下压 + 周期跑跳
void WorkerLoop() {
    // 按住W保持前进
    SendScan(SC_W, true);


    while (g_running.load(std::memory_order_relaxed) && g_active.load(std::memory_order_relaxed)) {
        // 冲刺
        SendScan(SC_LSHIFT, true);
        if (!CancelableSleep(SPRINT_MS)) break;
        SendScan(SC_LSHIFT, false);

        if (!g_running || !g_active) break;

        // 冲刺后间隔
        if (!CancelableSleep(POST_GAP_MS)) break;

        if (!g_running || !g_active) break;

        // 跳跃
        SendScan(SC_SPACE, true);
        if (!CancelableSleep(JUMP_HOLD_MS)) break;
        SendScan(SC_SPACE, false);

        if (!g_running || !g_active) break;

        // 冷却周期
        if (!CancelableSleep(CYCLE_MS)) break;

        // 优雅停止：在周期结束时递减并在用尽后退出
        if (g_graceful.load()) {
            int left = g_cycles_to_finish.load();
            if (left > 0) {
                int expected = left;
                if (g_cycles_to_finish.compare_exchange_strong(expected, left - 1)) {
                    if (left - 1 == 0) {
                        g_graceful.store(false);
                        g_active.store(false);
                        break;
                    }
                }
            }
        }
    }

    // 释放所有按键
    ReleaseAllKeys();
}

void Start() {
    if (g_active.exchange(true)) {
        std::printf("[INFO] RUNnING\n");
        return;
    }
    if (g_worker.joinable()) {
        g_worker.join();
    }
    std::printf("[INFO] BHOP READY\n");
    g_graceful.store(false);
    g_cycles_to_finish.store(0);
    g_worker = std::thread(WorkerLoop);
}

void Stop() {
    if (!g_active.exchange(false)) {
        std::printf("[INFO] STOPPED\n");
        return;
    }
    std::printf("[INFO] STOPPING...\n");
    ReleaseAllKeys();
    if (g_worker.joinable()) g_worker.join();
    std::printf("[INFO] STOPPED\n");
}

void SoftStop() {
    if (!g_active.load()) {
        std::printf("[INFO] Not running\n");
        return;
    }
    g_graceful.store(true);
    g_cycles_to_finish.store(2); // finish current + next cycle
    std::printf("[INFO] Graceful stop requested: finish current and next cycle\n");
}

void EmergencyStop() {
    std::printf("[INFO] EMERGENCE!\n");
    g_running = false;
    g_active = false;
    ReleaseAllKeys();
    if (g_worker.joinable()) g_worker.join();
}

bool RegisterHotkeys() {
    // 使用 MOD_NOREPEAT 防止连发
    const UINT MOD_NR = 0x4000; // MOD_NOREPEAT
    bool ok = true;
    ok &= RegisterHotKey(nullptr, 1, MOD_NR, 0x5A);      // Z 启停
    ok &= RegisterHotKey(nullptr, 2, MOD_NR, 0x43);      // C 急停
    ok &= RegisterHotKey(nullptr, 3, MOD_NR, 0x58);      // X 退出
    return ok;
}

void UnregisterHotkeys() {
    UnregisterHotKey(nullptr, 1);
    UnregisterHotKey(nullptr, 2);
    UnregisterHotKey(nullptr, 3);
}

int main() {
    timeBeginPeriod(1);

    std::printf("==== BHOP FOR ESCAPETHEBACKROOMS BY YIN(C++) ====\n");
    std::printf("Z: Begin/Stop  | C: Emergence | X: exit\n");
    std::printf("参数: sprint=%dms, gap=%dms, jump=%dms, cycle=%dms\n",
                SPRINT_MS, POST_GAP_MS, JUMP_HOLD_MS, CYCLE_MS);

    if (!RegisterHotkeys()) {
        std::printf("[WARN] HOt key failed to regist,fall back to cmd\n");
        std::printf("Input start/stop/quit ENTER to control\n");
        char cmd[32];
        while (g_running.load()) {
            if (!std::fgets(cmd, sizeof(cmd), stdin)) break;
            if (std::strncmp(cmd, "start", 5) == 0) Start();
            else if (std::strncmp(cmd, "stop", 4) == 0) Stop();
            else if (std::strncmp(cmd, "quit", 4) == 0) { EmergencyStop(); break; }
        }
        timeEndPeriod(1);
        return 0;
    }

    // 消息循环
    MSG msg;
    while (g_running.load()) {
        BOOL ret = GetMessage(&msg, nullptr, 0, 0);
        if (ret <= 0) break;
        if (msg.message == WM_HOTKEY) {
            switch (msg.wParam) {
            case 1: // Z
                if (g_active.load()) SoftStop(); else Start();
                break;
            case 2: // C
                EmergencyStop();
                break;
            case 3: // X
                EmergencyStop();
                PostQuitMessage(0);
                break;
            default:
                break;
            }
        } else {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    UnregisterHotkeys();

    // 清理与收尾
    if (g_active.load()) Stop();
    timeEndPeriod(1);
    std::printf("[INFO] Exit\n");
    return 0;
}
