class Solution {
public:
    vector<int> maxInWindows(const vector<int>& num, unsigned int size)
    {
        vector<int>res;
        if(num.empty() || num.size() < size || size == 0)
        {
            return res;
        }
        int a = num.size() - size;
        for(int i = 0; i <= a; ++i)
        {
            int max = 0x80000000;
            for(int j = i ; j < i+size; ++j)
            {
                if(num[j] > max)
                {
                    max = num[j];
                }
            }
            res.push_back(max);
        }
        return res;
    }
};
