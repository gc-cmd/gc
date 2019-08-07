/*
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
    }
};
*/
class Solution {
public:
    TreeNode* KthNode(TreeNode* pRoot, int k)
    {
        if(pRoot == NULL || k < 1)
        {
            return NULL;
        }
        count = k;
        TreeNode* p = NULL;
        inorder(pRoot,p);
        return p;
    }
    void inorder(TreeNode* root,TreeNode*& p)
    {
        if(root)
        {
            inorder(root->left,p);
            count--;
            if(!count)
            {
                p = root;
            }
            inorder(root->right,p);
        }
         
    }
private:
    int count = 0;
};
