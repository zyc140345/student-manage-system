#ifndef DULINKLIST_H
#define DULINKLIST_H

template<typename elementType>
struct node {
    // 双向链表节点
    elementType element;
    struct node<elementType> *next;
    struct node<elementType> *previous;
};

template<typename T>
class DuLinkList {
    // 双向链表类
public:
    typedef node<T> *position;
    DuLinkList() : hd{new node<T>} { ti = hd; hd->next = ti->next = nullptr; }
    DuLinkList(const DuLinkList<T> &rhs);
    ~DuLinkList() { clear(); }
    DuLinkList<T> &operator=(const DuLinkList<T> &rhs);

    void insert(position p, T element);
    void del(position p);
    void clear();
    position head() { return hd; } // 返回头指针
    position tail() { return ti; } // 返回尾指针
protected:
    position hd; // 头指针
    position ti; // 尾指针
};

template<typename T>
DuLinkList<T>::DuLinkList(const DuLinkList<T> &rhs) : hd{new node<T>} {
    // 复制构造函数
    ti = hd;
    hd->next = hd->previous = nullptr;
    for (auto p = rhs.hd->next; p; p = p->next)
        insert(ti, p->element);
}

template<typename T>
DuLinkList<T> &DuLinkList<T>::operator=(const DuLinkList<T> &rhs) {
    // 赋值运算符
    if (this != &rhs) { // 检测自我赋值
        clear();
        for (auto p = rhs.hd->next; p; p = p->next)
            insert(ti, p->element);
    }
    return *this;
}

template<typename T>
void DuLinkList<T>::insert(position p, T element) {
    // 插入
    auto temp = new node<T>;
    temp->element = element;
    if (p == ti) {
        // 在表尾插入需要修改尾指针
        temp->next = p->next;
        temp->previous = p;
        p->next = temp;
        ti = temp;
    } else {
        temp->next = p->next;
        temp->next->previous = temp;
        p->next = temp;
        temp->previous = p;
    }
}

template<typename T>
void DuLinkList<T>::del(position p) {
    // 删除
    if (p == ti) {
        // 在表尾删除需要修改尾指针
        p->previous->next = p->next;
        ti = p->previous;
    } else {
        p->next->previous = p->previous;
        p->previous->next = p->next;
    }
    delete p;
}

template<typename T>
void DuLinkList<T>::clear() {
    // 清空链表
    while (hd != ti)
        del(ti);
}

#endif // DULINKLIST_H
