#pragma once
#include "ListNode.h"
#include <iostream>

class List
{
public:
    List();
    virtual ~List();
    bool Empty();
    unsigned long Size();
    void PushFront(int);
    void PushBack(int);
    int PopFront();
    int PopBack();
    void Clear();

private:
    ListNode* extractPrev(ListNode* node);
private:
    ListNode* m_head;
    ListNode* m_tail;
    unsigned long m_size;
};