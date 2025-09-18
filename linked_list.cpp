#include<iostream>

using namespace std;

// 链表节点类定义
template <typename T>
class ListNode {
    T data;
    ListNode* next;

    ListNode(const T& data)
    {
        data = data;
        next = NULL;
    };
};

// 链表类定义
template <typename T>
class LinkedList {
private:
    // 头节点
    ListNode<T>* head;
    // 链表长度
    int length;

public:
    // 构造函数
    LinkedList(T& val[])
    {
        while (val != Null)
        {
            ListNode<T>* node = new ListNode<T>(val);
            if (head == NULL)
            {
                head = node;
            }
            else
            {
                ListNode<T>* temp = head;
                while (temp->next != NULL)
                {
                    temp = temp->next;
                }
                temp->next = node;
            }
            val++;
        }
    }

    // 析构函数
    ~LinkedList()
    {
        ListNode<T>* temp = head;
        while (temp != NULL)
        {
            ListNode<T>* next = temp->next;
            delete temp;
            temp = next;
        }
        head = NULL;
        cout << "链表已析构" << endl;
    }

    // 获取链表长度
    int getLength() const
    {
        return length;
    };

    // 判断链表是否为空
    bool isEmpty() const
    {
        return(length == 0);
    };

    // 在链表头部插入元素
    void insertAtBeginning(const T& element)
    {
        ListNode<T>* tmp;
        tmp = new ListNode<T>(elsement);
        ListNode<T>* temp = head;
        while (temp->next != Null)
        {
            temp = temp->next;
        }
        head = tmp;
    };

    // 在链表尾部插入元素
    void insertAtEnd(const T& element)
    {
        ListNode<T>* newnode = new ListNode<T>(element);
        ListNode<T>* tmp = head;
        while (tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        tmp->next = newnode;
    };

    // 在指定位置插入元素
    bool insertAt(int index, const T& element)
    {
        ListNode<T>* node = new ListNode<T>(element);

        ListNode<T>* tmp = head;

        if (index < 0 || index > length)
        {
            return false;
        }

        if (index == 0)
        {
            node->next = head;
            head = node;
            return true;
        }

        for (int i = 0; i < index - 1; i++)
        {
            tmp = tmp->next;
        }
        ListNode<T>* demo = tmp->next;
        tmp ->next = node;
        node->next = demo;
        return true;
    };

    // 删除链表头部的元素
    bool removeFirst()
    {
        delete head;
        head = head->next;
        return true;
    };

    // 删除链表尾部的元素
    bool removeLast()
    {
        ListNode<T>* tmp = head;
        while (tmp->next->next != NULL)
        {
            tmp = tmp->next;
        }
        delete tmp->next;
        tmp->next = NULL;
        return true;
    }

    // 删除指定位置的元素
    bool removeAt(int index){
        ListNode<T> *tmp = head;
        if(index<0 || index >=length)
        {
            return 0;
        }
        if(index == 0)
        {
            head = head->next;
            delete tmp;
            return 1;
        }
        for(int i =0;i<index-1;++i)
        {
            tmp = tmp->next;
        }
        ListNode<T>*demo = tmp->next;
        delete tmp->next;
        tmp->next = demo->next;
    }

    // 查找指定位置的元素
    T& get(int index)
    {
        ListNode<T> *it = head;
        if(index<0 || index >= length)
        {
            cout<<"索引不合法"<<endl;
            return NULL;
        }
        for(int i = 0;i<index;++i)
        {
            it = it->next;
        }
        return it->data;
    }

    // 查找元素
    ListNode<T>* find(const T& element) const;

    // 打印链表
    void print() const
    {
        ListNode<T>* tmp = head;
        while (tmp != NULL)
        {
            cout << tmp->data << " ";
            tmp = tmp->next;
        }
        cout << endl;
    }
};


