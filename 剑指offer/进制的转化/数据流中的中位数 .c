class Solution {
public:
    priority_queue<int,vector<int>,less<int>>p;//增大
    priority_queue<int,vector<int>,greater<int>>q;//减小
    void Insert(int num)
    {
        if(p.empty() || num <= p.top())
        {
            p.push(num);
        }
        else
        {
            q.push(num);
        }
        if(p.size() == q.size() + 2)
        {
            q.push(p.top());
            p.pop();
        }
        if(p.size() + 1 == q.size())
        {
            p.push(q.top());
            q.pop();
        }
    }
 
    double GetMedian()
    { 
        return p.size() == q.size() ? (p.top()+ q.top())/2.0 : p.top();
    }
 
};
