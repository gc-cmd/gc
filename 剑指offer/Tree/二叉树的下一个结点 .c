/*
struct TreeLinkNode {
    int val;
    struct TreeLinkNode *left;
    struct TreeLinkNode *right;
    struct TreeLinkNode *next;
    TreeLinkNode(int x) :val(x), left(NULL), right(NULL), next(NULL) {
         
    }
};
*/
class Solution {
public:
    TreeLinkNode* GetNext(TreeLinkNode* pNode)
    {
        if(pNode == NULL)
        {
            return NULL;
        }
        if(pNode->right != NULL)
        {
            TreeLinkNode *cur = pNode->right;
            while(cur->left != NULL)
            {
                cur = cur->left;
            }
            return cur;
        }
        if(pNode->next != NULL)
        {
            TreeLinkNode *cur = pNode;
            TreeLinkNode *parent = pNode->next;
            while(parent != NULL && cur == parent->right)
            {
                 
                cur = parent;
                parent = parent->next;
            }
            return parent;
        }
        return NULL;
    }
};
