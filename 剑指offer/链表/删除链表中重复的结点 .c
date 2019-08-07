/*
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};
*/
class Solution {
public:
    ListNode* deleteDuplication(ListNode* pHead)
    {
        if(pHead == NULL)
        {
            return NULL;
        }
        if(pHead != NULL && pHead->next == NULL)
        {
            return pHead;
        }
        ListNode* pPreNode=nullptr;
        ListNode* pNode=pHead;
           
        while(pNode != nullptr)
            {
                ListNode* pNext = pNode->next;
                if(pNext != nullptr && pNode->val == pNext->val)
                {
                    while(pNext!=nullptr && pNode->val == pNext->val)
                    {
                        pNext = pNext->next;
                    }
                    if(pPreNode == nullptr)
                    {
                        pHead = pNext;
                    }
                    else
                    {
                        pPreNode->next = pNext;
                    }
                    pNode = pNext;
                }
                else
                {
                    pPreNode=pNode;
                    pNode=pNext;
                }
        }
        return pHead;
    }
};
