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
        bool level = true;//单数
        queue<TreeNode*>q;
        q.push(pRoot);
        while(!q.empty())
        {
                vector<int>vec;
                const int size = q.size();
                for(int i = 0; i < size;++i)
                {
                    TreeNode* tmp = q.front();
                    q.pop();
                    vec.push_back(tmp->val);
                    if(tmp->left != NULL)
                    {
                        q.push(tmp->left);
                    }
                    if(tmp->right != NULL)
                    {
                        q.push(tmp->right);
                    }
                }
            if(!level)
            {
                reverse(vec.begin(),vec.end());
            }
                res.push_back(vec);
                level = !level;
        }
        return res;
    }
     
};
