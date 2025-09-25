#ifndef SEQUENCE_LIST_H
#define SEQUENCE_LIST_H

#include <iostream>
#include <stdexcept>

// 顺序表类定义
template <typename T>
class SequenceList {
private:
    // 存储元素的数组
    T* data;
    // 当前元素个数
    int length;
    // 顺序表的最大容量
    int capacity;

public:
    // 构造函数
    SequenceList(int capacity);

    // 析构函数
    ~SequenceList();

    // 获取顺序表长度
    int getLength() const;

    // 获取顺序表容量
    int getCapacity() const;

    // 判断顺序表是否为空
    bool isEmpty() const;

    // 判断顺序表是否已满
    bool isFull() const;

    // 在指定位置插入元素
    bool insert(int index, const T& element);

    // 在末尾添加元素
    bool append(const T& element);

    // 删除指定位置的元素
    bool remove(int index);

    // 获取指定位置的元素
    T& get(int index);

    // 查找元素
    int indexOf(const T& element) const;

    // 打印顺序表
    void print() const;
};

#endif // SEQUENCE_LIST_H
