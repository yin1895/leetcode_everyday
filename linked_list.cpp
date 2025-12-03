#include<bits/stdc++.h>

using namespace std;

template<class T>struct Node{
    T val;
    *Node next;

    Node(T val):val(val),next(nullptr){}
};

template<class T>class LinkChain{
private:
    *Node head;
    int length;
public:
    LinkChain(vector<T> toInput)
    {
        Node Head = new Node(toInput[0]);
        this->head = &Head;

        Node *current = &Head;
        for(int i = 1;i<toInput.size();++i)
        {
            Node tmp = new Node(toInput[i]);

            current->next = &tmp;

            current = current->next;

            delete tmp;
        }
    }

    
};