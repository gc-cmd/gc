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
    ListNode* EntryNodeOfLoop(ListNode* pHead)
    {
        if(pHead == NULL || pHead->next == NULL)
        {
            return NULL;
        }
        ListNode *pfast = pHead;
        ListNode *pslow = pHead;
        while(pfast != NULL && pfast->next != NULL)
        {
            pfast = pfast->next->next;
            pslow = pslow->next;
            if(pfast == pslow)
            {
                pfast = pHead;
                while(pfast != pslow)
                {
                    pfast = pfast->next;
                    pslow = pslow->next;
                }
                if(pfast == pslow)
                {
                    return pfast;
                }
            }
        }
        return NULL;
    }
};
