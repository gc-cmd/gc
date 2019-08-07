class Solution {
public:
    int movingCount(int threshold, int rows, int cols)
    {
        int res = 0;
        vector<int>visit(rows*cols,0);
        helper(threshold,0,0,rows,cols,res,visit);
        return res;
    }
    void helper(int threshold, int i,int j,int rows, int cols,int& res,vector<int>& visit)
    {
        if(i < 0 || j < 0 || i >= rows || j >= cols || visit[i*cols+j] == 1 || sum(i,j) > threshold)
        {
            return;
        }
        res++;
        visit[i*cols+j] = 1;
        helper(threshold,i-1,j,rows,cols,res,visit);
        helper(threshold,i+1,j,rows,cols,res,visit);
        helper(threshold,i,j-1,rows,cols,res,visit);
        helper(threshold,i,j+1,rows,cols,res,visit);
    }
    int sum(int x,int y)
    {
        int sum = 0;
        while(x)
        {
            int bit = x%10;
            sum += bit;
            x = x/10;
                 
        }
        while(y)
        {
            int bit = y%10;
            sum+=bit;
            y = y/10;
        }
        return sum;
    }
};
