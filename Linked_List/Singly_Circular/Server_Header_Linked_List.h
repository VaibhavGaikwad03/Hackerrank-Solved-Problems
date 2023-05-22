#ifndef HEADER_LINKED_LIST
#define HEADER_LINKED_LIST

#include <iostream>
#include "Server_Header_Node.h"
using std::ostream;

class Node;

class LinkedList
{
    int m_iCount;
    Node *m_pHead;
    Node *m_pTail;

public:
    LinkedList();
    ~LinkedList();
    int count_nodes();
    void display();
    bool is_empty();
    void insert_first(int iNo);
    void insert_last(int iNo);
    void insert_at_position(int iNo, int iPos);
    int delete_first();
    int delete_last();
    int delete_at_position(int iPos);
    int search_first_occurrence(int iKey);
    int search_last_occurrence(int iKey);
    int search_all_occurrences(int iKey);
    void concat_list(LinkedList *pList);
    void concat_at_position(LinkedList *pList, int iPos);
    void concat_list(LinkedList &refList);
    void concat_at_position(LinkedList &refList, int iPos);
    void physical_reverse();
    void reverse_display();
    void delete_all();

    friend ostream &operator<<(ostream &, LinkedList &);
};

#endif // HEADER_LINKED_LIST