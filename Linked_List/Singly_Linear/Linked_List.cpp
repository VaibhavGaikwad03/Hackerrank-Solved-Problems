#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::ostream;

class LinkedList;

class Node
{
    int m_iData;
    Node *m_pNext;

public:
    Node();
    ~Node();

    friend class LinkedList;
    friend ostream &operator<<(ostream &, LinkedList &);
};

class LinkedList
{
    int m_iCount;
    Node *m_pHead;

public:
    LinkedList();
    ~LinkedList();
    int count_nodes();
    void display();
    void insert_first(int iNo);
    void insert_last(int iNo);
    void insert_at_position(int iNo, int iPos);
    int delete_first();
    int delete_last();
    int delete_at_position(int iPos);
    int search_first_occurrence(int iKey);
    int search_last_occurrence(int iKey);
    int search_all_occurrences(int iKey);
    void concat_list(LinkedList &pList);
    void concat_at_position(LinkedList &pList, int iPos);
    void physical_reverse();
    void reverse_display();
    void delete_all();

    friend ostream &operator<<(ostream &, LinkedList &);
};

Node::Node()
{
    m_iData = 0;
    m_pNext = NULL;
}

Node::~Node()
{
    m_iData = 0;

    if (m_pNext != NULL)
    {
        delete m_pNext;
        m_pNext = NULL;
    }
}

LinkedList::LinkedList()
{
    m_pHead = NULL;
    m_iCount = 0;
}

LinkedList::~LinkedList()
{
    m_iCount = 0;

    if (m_pHead != NULL)
    {
        delete m_pHead;
        m_pHead = NULL;
    }
}

int LinkedList::count_nodes()
{
    return m_iCount;
}

void LinkedList::display()
{
    Node *pTemp = m_pHead;

    if (pTemp == NULL)
    {
        cout << "\nList is empty.\n";
        return;
    }

    cout << "\nData from the linked list : \n";
    while (pTemp != NULL)
    {
        cout << "|" << pTemp->m_iData << "|->";
        pTemp = pTemp->m_pNext;
    }
    cout << "NULL\n";
}

void LinkedList::insert_first(int iNo)
{
    Node *pNewNode = NULL;

    pNewNode = new Node;

    if (pNewNode == NULL)
    {
        cout << "\nMemory allocation failed.\n";
        return;
    }

    pNewNode->m_iData = iNo;
    pNewNode->m_pNext = m_pHead;
    m_pHead = pNewNode;
    pNewNode = NULL;

    m_iCount++;
}

void LinkedList::insert_last(int iNo)
{
    Node *pTemp = NULL;
    Node *pNewNode = NULL;

    pNewNode = new Node;

    if (pNewNode == NULL)
    {
        cout << "\nMemory allocation failed.\n";
        return;
    }

    pNewNode->m_iData = iNo;
    pNewNode->m_pNext = NULL;

    if (m_pHead == NULL)
    {
        m_pHead = pNewNode;
        pNewNode = NULL;
        m_iCount++;
        return;
    }

    pTemp = m_pHead;

    while (pTemp->m_pNext != NULL)
        pTemp = pTemp->m_pNext;

    pTemp->m_pNext = pNewNode;
    pTemp = pNewNode = NULL;

    m_iCount++;
}

void LinkedList::insert_at_position(int iNo, int iPos)
{
    Node *pTemp = NULL;
    Node *pNewNode = NULL;

    if (iPos < 1 || iPos > m_iCount + 1)
    {
        cout << "\nPosition is invalid.\n";
        return;
    }

    if (iPos == 1)
    {
        insert_first(iNo);
        return;
    }

    pNewNode = new Node;

    if (pNewNode == NULL)
    {
        cout << "\nMemory allocation failed.\n";
        return;
    }

    pNewNode->m_iData = iNo;
    pNewNode->m_pNext = NULL;

    pTemp = m_pHead;

    for (int i = 1; i < iPos - 1; i++)
        pTemp = pTemp->m_pNext;

    pNewNode->m_pNext = pTemp->m_pNext;
    pTemp->m_pNext = pNewNode;

    m_iCount++;
}

int LinkedList::delete_first()
{
    int iDelData = 0;
    Node *pTemp = NULL;

    if (m_pHead == NULL)
        return -1;

    pTemp = m_pHead;
    iDelData = pTemp->m_iData;
    m_pHead = m_pHead->m_pNext;
    pTemp->m_pNext = NULL;
    delete pTemp;
    pTemp = NULL;

    m_iCount--;

    return iDelData;
}

int LinkedList::delete_last()
{
    int iDelData = 0;
    Node *pTemp = NULL;

    if (m_pHead == NULL)
        return -1;

    if (m_pHead->m_pNext == NULL)
    {
        iDelData = m_pHead->m_iData;
        delete m_pHead;
        m_pHead = NULL;
        m_iCount--;
        return iDelData;
    }

    pTemp = m_pHead;

    while (pTemp->m_pNext->m_pNext != NULL)
        pTemp = pTemp->m_pNext;

    iDelData = pTemp->m_pNext->m_iData;
    delete pTemp->m_pNext;
    pTemp->m_pNext = NULL;

    m_iCount--;

    return iDelData;
}

int LinkedList::delete_at_position(int iPos)
{
    int iDelData = 0;
    Node *pTemp = NULL;
    Node *pTempDelete = NULL;

    if (iPos < 1 || iPos > m_iCount)
        return -1;

    if (iPos == 1)
        return delete_first();

    pTemp = m_pHead;

    for (int i = 1; i < iPos - 1; i++)
        pTemp = pTemp->m_pNext;

    pTempDelete = pTemp->m_pNext;
    iDelData = pTempDelete->m_iData;
    pTemp->m_pNext = pTempDelete->m_pNext;
    pTempDelete->m_pNext = NULL;
    delete pTempDelete;
    pTempDelete = NULL;

    m_iCount--;

    return iDelData;
}

int LinkedList::search_first_occurrence(int iKey)
{
    Node *pTemp = NULL;
    int iCountPos = 0;

    pTemp = m_pHead;

    while (pTemp != NULL)
    {
        iCountPos++;
        if (pTemp->m_iData == iKey)
            break;
        pTemp = pTemp->m_pNext;
    }

    if (pTemp == NULL)
        return 0;

    return iCountPos;
}

int LinkedList::search_last_occurrence(int iKey)
{
    Node *pTemp = NULL;
    int iCountPos = 0;
    int iRetCount = 0;

    pTemp = m_pHead;

    while (pTemp != NULL)
    {
        iCountPos++;
        if (pTemp->m_iData == iKey)
            iRetCount = iCountPos;
        pTemp = pTemp->m_pNext;
    }

    return iRetCount;
}

int LinkedList::search_all_occurrences(int iKey)
{
    Node *pTemp = NULL;
    int iCountOcc = 0;

    pTemp = m_pHead;

    while (pTemp != NULL)
    {
        if (pTemp->m_iData == iKey)
            iCountOcc++;
        pTemp = pTemp->m_pNext;
    }
    return iCountOcc;
}

// void LinkedList::concat_list(LinkedList *pList)
// {
//     Node *pTemp = NULL;

//     if (pList->m_pHead == NULL)
//         return;

//     if (m_pHead == NULL)
//     {
//         m_pHead = pList->m_pHead;
//         pList->m_pHead = NULL;
//         return;
//     }

//     pTemp = m_pHead;

//     while (pTemp->m_pNext != NULL)
//         pTemp = pTemp->m_pNext;

//     pTemp->m_pNext = pList->m_pHead;
//     pList->m_pHead = NULL;
//     m_iCount += pList->m_iCount;
//     pList->m_iCount = 0;
// }

void LinkedList::concat_list(LinkedList &pList)
{
    Node *pTemp = NULL;

    if (pList.m_pHead == NULL)
        return;

    if (m_pHead == NULL)
    {
        m_pHead = pList.m_pHead;
        pList.m_pHead = NULL;
        return;
    }

    pTemp = m_pHead;

    while (pTemp->m_pNext != NULL)
        pTemp = pTemp->m_pNext;

    pTemp->m_pNext = pList.m_pHead;
    m_iCount += pList.m_iCount;
    pList.m_pHead = NULL;
    pList.m_iCount = 0;
}

// void LinkedList::concat_at_position(LinkedList *pList, int iPos)
// {
//     Node *pTemp1 = NULL;
//     Node *pTemp2 = NULL;

//     if (iPos < 1 || iPos > m_iCount + 1)
//     {
//         cout << "Position is invalid\n";
//         return;
//     }

//     if (pList->m_pHead == NULL)
//         return;

//     if (iPos == 1)
//     {
//         pList->concat_list(*this);
//         m_pHead = pList->m_pHead;
//         m_iCount += pList->m_iCount;
//         pList->m_iCount = 0;
//         pList->m_pHead = NULL;
//         return;
//     }

//     pTemp1 = m_pHead;

//     for (int i = 1; i < iPos - 1; i++)
//         pTemp1 = pTemp1->m_pNext;

//     pTemp2 = pList->m_pHead;

//     while (pTemp2->m_pNext != NULL)
//         pTemp2 = pTemp2->m_pNext;

//     pTemp2->m_pNext = pTemp1->m_pNext;
//     pTemp1->m_pNext = pList->m_pHead;
//     m_iCount += pList->m_iCount;

//     pList->m_iCount = 0;
//     pTemp1 = pTemp2 = pList->m_pHead = NULL;
// }

void LinkedList::concat_at_position(LinkedList &pList, int iPos)
{
    Node *pTemp1 = NULL;
    Node *pTemp2 = NULL;

    if (iPos < 1 || iPos > m_iCount + 1)
    {
        cout << "Position is invalid\n";
        return;
    }

    if (pList.m_pHead == NULL)
        return;

    if (iPos == 1)
    {
        pList.concat_list(*this);
        m_pHead = pList.m_pHead;
        m_iCount += pList.m_iCount;
        pList.m_iCount = 0;
        pList.m_pHead = NULL;
        return;
    }

    pTemp1 = m_pHead;

    for (int i = 1; i < iPos - 1; i++)
        pTemp1 = pTemp1->m_pNext;

    pTemp2 = pList.m_pHead;

    while (pTemp2->m_pNext != NULL)
        pTemp2 = pTemp2->m_pNext;

    pTemp2->m_pNext = pTemp1->m_pNext;
    pTemp1->m_pNext = pList.m_pHead;
    m_iCount += pList.m_iCount;
    pList.m_iCount = 0;
    pTemp1 = pTemp2 = pList.m_pHead = NULL;
}

void LinkedList::physical_reverse()
{
    Node *pNext = NULL;
    Node *pCurrent = m_pHead;
    Node *pPrev = NULL;

    while (pCurrent != NULL)
    {
        pNext = pCurrent->m_pNext;
        pCurrent->m_pNext = pPrev;
        pPrev = pCurrent;
        pCurrent = pNext;
    }
    m_pHead = pPrev;
}

void LinkedList::reverse_display()
{
    if (m_pHead == NULL)
        return;

    physical_reverse();
    display();
    physical_reverse();
}

void LinkedList::delete_all()
{
    Node *pTemp = NULL;
    pTemp = m_pHead;

    while (pTemp != NULL)
    {
        m_pHead = m_pHead->m_pNext;
        pTemp->m_pNext = NULL;
        delete pTemp;
        pTemp = m_pHead;
    }
    pTemp = NULL;
}

ostream &operator << (ostream &out, LinkedList &refObj)
{
    Node *pTemp = refObj.m_pHead;

    if (pTemp == NULL)
        return;

    while (pTemp != NULL)
    {
        cout << "|" << pTemp->m_iData << "|->";
        pTemp = pTemp->m_pNext;
    }

    cout << "NULL";
    return out;
}

int main()
{
    LinkedList list1;
    int iChoice = 0, iData = 0, iPos = 0, iCount = 0, iCheckData = 0, iDeletedData = 0, iOccurrence = 0, iPosition = 0;

    while (1)
    {
    out:
        cout << "\nHello, Welcome...\nPlease choose from the below options : \n\n";
        cout << "1. Insert First\n2. Insert Last\n3. Insert At Position\n4. Delete First\n5. Delete Last\n6. Delete At Position\n7. Search First Occurrence\n8. Search Last Occurrence\n9. Search All Occurrences\n10. Count Nodes\n11. Concat List\n12. Concat At Position\n13. Physical Reverse\n14. Reverse Display\n15. Exit\n>_";
        cin >> iChoice;

        switch (iChoice)
        {
        case 1:
            cout << "Enter the data : \n";
            cin >> iData;

            list1.insert_first(iData);
            cout << "Data from the linked list : " << list1 << endl;

            break;

        case 2:
            cout << "Enter the data : \n";
            
            iCheckData = scanf("%d", &iData);
            if (iCheckData != 0)
            {
                insertLast(&pFirst, iData);
                display(pFirst);
            }
            else
            {
                printf("\nPlease enter only integer values. Non-integer values will cause errors in the program.\n");
            }
            break;

        case 3:
            printf("Enter the Position : \n");
            scanf("%d", &iPos);
            iCount = countNodes(pFirst);
            if (iPos < 1 || iPos > iCount + 1)
            {
                printf("\nERROR: Position is invalid.\n");
            }
            else
            {
                printf("Enter the data : \n");
                iCheckData = scanf("%d", &iData);
                if (iCheckData != 0)
                {
                    insertAtPosition(&pFirst, iData, iPos);
                    display(pFirst);
                }
                else
                {
                    printf("\nPlease enter only integer values. Non-integer values will cause errors in the program.\n");
                }
            }
            break;

        case 4:
            if (pFirst == NULL)
            {
                printf("\nList is empty.\n");
            }
            else
            {
                iDeletedData = deleteFirst(&pFirst);
                display(pFirst);
                printf("Deleted data is : %d\n", iDeletedData);
            }
            break;

        case 5:
            if (pFirst == NULL)
            {
                printf("\nList is empty.\n");
            }
            else
            {
                iDeletedData = deleteLast(&pFirst);
                display(pFirst);
                printf("Deleted data is : %d\n", iDeletedData);
            }
            break;

        case 6:
            if (pFirst == NULL)
            {
                printf("\nList is empty.\n");
            }
            else
            {
                printf("Enter the position : \n");
                scanf("%d", &iPos);
                iCount = countNodes(pFirst);
                if (iPos < 1 || iPos > iCount)
                {
                    printf("\nERROR: Position is invalid.\n");
                }
                else
                {
                    iDeletedData = deleteAtPosition(&pFirst, iPos);
                    display(pFirst);
                    printf("Deleted data is : %d\n", iDeletedData);
                }
            }
            break;

        case 7:
            if (pFirst == NULL)
            {
                printf("\nList is empty.\n");
            }
            else
            {
                printf("\nPlease enter the data that you would like to search for :\n");
                iCheckData = scanf("%d", &iData);

                if (iCheckData != 0)
                {
                    iOccurrence = searchFirstOccurrence(pFirst, iData);

                    if (iOccurrence != 0)
                    {
                        printf("\nFirst occurrence of %d is at position %d.\n", iData, iOccurrence);
                    }
                    else
                    {
                        printf("\n%d not found.\n", iData);
                    }
                }
                else
                {
                    printf("\nPlease enter only integer values. Non-integer values will cause errors in the program.\n");
                }
            }
            break;

        case 8:
            if (pFirst == NULL)
            {
                printf("\nList is empty.\n");
            }
            else
            {
                printf("\nPlease enter the data that you would like to search for :\n");
                iCheckData = scanf("%d", &iData);

                if (iCheckData != 0)
                {
                    iOccurrence = searchLastOccurrence(pFirst, iData);

                    if (iOccurrence != 0)
                    {
                        printf("\nLast occurrence of %d is at position %d\n", iData, iOccurrence);
                    }
                    else
                    {
                        printf("\n%d not found.\n", iData);
                    }
                }
                else
                {
                    printf("\nPlease enter only integer values. Non-integer values will cause errors in the program.\n");
                }
            }
            break;

        case 9:
            if (pFirst == NULL)
            {
                printf("\nList is empty.\n");
            }
            else
            {
                printf("\nPlease enter the data that you would like to search for :\n");
                iCheckData = scanf("%d", &iData);

                if (iCheckData != 0)
                {
                    iOccurrence = searchAllOccurrences(pFirst, iData);

                    printf("\n%d Occurred %d times\n", iData, iOccurrence);
                }
                else
                {
                    printf("\nPlease enter only integer values. Non-integer values will cause errors in the program.\n");
                }
            }
            break;

        case 10:
            iCount = countNodes(pFirst);
            printf("\nCount of nodes is : %d\n", iCount);
            break;

        case 11:
            while (1)
            {
                fflush(stdin);
                printf("\n1. Insert First\n2. Insert Last\n3. Insert At Position\n4. Delete At Position\n5. Back\n");
                printf(">_");
                iCheckData = scanf("%d", &iChoice);

                if (iCheckData != 0)
                {
                    switch (iChoice)
                    {
                    case 1:
                        printf("Enter the data : \n");
                        iCheckData = scanf("%d", &iData);
                        if (iCheckData != 0)
                        {
                            insertFirst(&pSecond, iData);
                            display(pSecond);
                        }
                        else
                        {
                            printf("\nPlease enter only integer values. Non-integer values will cause errors in the program.\n");
                        }
                        break;

                    case 2:
                        printf("Enter the data : \n");
                        iCheckData = scanf("%d", &iData);
                        if (iCheckData != 0)
                        {
                            insertLast(&pSecond, iData);
                            display(pSecond);
                        }
                        else
                        {
                            printf("\nPlease enter only integer values. Non-integer values will cause errors in the program.\n");
                        }
                        break;

                    case 3:
                        iPos = 0;
                        printf("Enter the Position : \n");
                        scanf("%d", &iPos);
                        iCount = countNodes(pSecond);
                        if (iPos < 1 || iPos > iCount + 1)
                        {
                            printf("\nERROR: Position is invalid.\n");
                        }
                        else
                        {
                            printf("Enter the data : \n");
                            iCheckData = scanf("%d", &iData);
                            if (iCheckData != 0)
                            {
                                insertAtPosition(&pSecond, iData, iPos);
                                display(pSecond);
                            }
                            else
                            {
                                printf("\nPlease enter only integer values. Non-integer values will cause errors in the program.\n");
                            }
                        }
                        break;

                    case 4:
                        if (pSecond == NULL)
                        {
                            printf("\nList is empty.\n");
                        }
                        else
                        {
                            printf("Enter the position : \n");
                            scanf("%d", &iPos);
                            iCount = countNodes(pSecond);
                            if (iPos < 1 || iPos > iCount)
                            {
                                printf("\nERROR: Position is invalid.\n");
                            }
                            else
                            {
                                iDeletedData = deleteAtPosition(&pSecond, iPos);
                                display(pSecond);
                                printf("Deleted data is : %d\n", iDeletedData);
                            }
                        }
                        break;

                    case 5:
                        concatList(&pFirst, &pSecond);
                        display(pFirst);
                        goto out;
                        break;

                    default:
                        printf("\nERROR: Invalid option selected.\n");
                        break;
                    }
                }
                else
                {
                    printf("\nPlease enter only integer values. Non-integer values will cause errors in the program.\n");
                }
            }
            break;

        case 12:
            iCount = countNodes(pFirst);
            printf("Enter the Position : \n");
            scanf("%d", &iPos);

            if (iPos < 1 || iPos > iCount + 1)
            {
                printf("\nERROR: Position is invalid.\n");
            }
            else
            {
                while (1)
                {
                    fflush(stdin);
                    printf("\n1. Insert First\n2. Insert Last\n3. Insert At Position\n4. Delete At Position\n5. Back\n");
                    printf(">_");
                    iCheckData = scanf("%d", &iChoice);

                    if (iCheckData != 0)
                    {
                        switch (iChoice)
                        {
                        case 1:
                            printf("Enter the data : \n");
                            iCheckData = scanf("%d", &iData);
                            if (iCheckData != 0)
                            {
                                insertFirst(&pSecond, iData);
                                display(pSecond);
                            }
                            else
                            {
                                printf("\nPlease enter only integer values. Non-integer values will cause errors in the program.\n");
                            }
                            break;

                        case 2:
                            printf("Enter the data : \n");
                            iCheckData = scanf("%d", &iData);
                            if (iCheckData != 0)
                            {
                                insertLast(&pSecond, iData);
                                display(pSecond);
                            }
                            else
                            {
                                printf("\nPlease enter only integer values. Non-integer values will cause errors in the program.\n");
                            }
                            break;

                        case 3:
                            printf("Enter the Position : \n");
                            scanf("%d", &iPosition);
                            iCount = countNodes(pSecond);
                            if (iPosition < 1 || iPosition > iCount + 1)
                            {
                                printf("\nERROR: Position is invalid.\n");
                            }
                            else
                            {
                                printf("Enter the data : \n");
                                iCheckData = scanf("%d", &iData);
                                if (iCheckData != 0)
                                {
                                    insertAtPosition(&pSecond, iData, iPosition);
                                    display(pSecond);
                                }
                                else
                                {
                                    printf("\nPlease enter only integer values. Non-integer values will cause errors in the program.\n");
                                }
                            }
                            break;

                        case 4:
                            if (pSecond == NULL)
                            {
                                printf("\nList is empty.\n");
                            }
                            else
                            {
                                printf("Enter the position : \n");
                                scanf("%d", &iPosition);
                                iCount = countNodes(pSecond);
                                if (iPosition < 1 || iPosition > iCount)
                                {
                                    printf("\nERROR: Position is invalid.\n");
                                }
                                else
                                {
                                    iDeletedData = deleteAtPosition(&pSecond, iPosition);
                                    display(pSecond);
                                    printf("Deleted data is : %d\n", iDeletedData);
                                }
                            }
                            break;

                        case 5:
                            concatAtPosition(&pFirst, &pSecond, iPos);
                            display(pFirst);
                            goto out;
                            break;

                        default:
                            printf("\nERROR: Invalid option selected.\n");
                            break;
                        }
                    }
                    else
                    {
                        printf("\nPlease enter only integer values. Non-integer values will cause errors in the program.\n");
                    }
                }
            }
            break;

        case 13:
            if (pFirst == NULL)
            {
                printf("\nList is empty.\n");
            }
            else
            {
                physicalReverse(&pFirst);
                display(pFirst);
            }
            break;

        case 14:
            if (pFirst == NULL)
            {
                printf("\nList is empty.\n");
            }
            else
            {
                reverseDisplay(pFirst);
            }
            break;

        case 15:
            deleteAll(&pFirst);
            pFirst = NULL;
            printf("\nThank You for using our application !\n");
            exit(0);
            break;

        default:
            printf("\nERROR: Invalid option selected.\n");
            break;
        }
    }
    return 0;
}