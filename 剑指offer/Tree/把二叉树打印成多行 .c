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
        vector<vector<int> > Print(TreeNode* pRoot) {
            vector<vector<int>>res;
            if(pRoot == NULL)
            {
                return res;
            }
            core(res,pRoot,0);
            return res;
        }
        void core(vector<vector<int>>& res, TreeNode* node, int level)
        {
            if(node == NULL)
            {
                return;
            }
            if(res.size() <= level)
            {
                res.push_back(vector<int>());
            }
            res[level].push_back(node->val);
            core(res,node->left,level+1);
            core(res,node->right,level+1);
        }
     
};
