class Solution {
public:
    bool hasPath(char* matrix, int rows, int cols, char* str)
    {
        if(matrix == NULL || str == NULL || rows <= 0 || cols <= 0)
        {
            return false;
        }
        bool* isUsed = new bool[rows*cols]();
        for(int i = 0 ; i < rows;++i)
        {
            for(int j = 0 ; j < cols ; ++j)
            {
                if(hsaPathCore(matrix,rows,cols,str,isUsed,i,j))
                {
                    return true;
                }
            }
        }
        return false;
    }
    bool hsaPathCore(char* matrix, int rows, int cols, char* str,bool* isUsed,int i,int j)
    {
        if(*str == '\0')
        {
            return true;
        }
        if(j == cols)
        {
            i++;
            j = 0;
        }
        if(j == -1)
        {
            i--;
            j = cols-1;
        }
        if(i < 0 || i >= rows)
        {
            return false;
        }
        
        if(isUsed[i*cols+j] || *str != matrix[i*cols+j])
        {
            return false;
        }
         isUsed[i*cols+j] = true;
        bool sign = hsaPathCore(matrix,rows,cols,str+1,isUsed,i-1,j)
                    ||hsaPathCore(matrix,rows,cols,str+1,isUsed,i+1,j)
                    ||hsaPathCore(matrix,rows,cols,str+1,isUsed,i,j-1)
                    ||hsaPathCore(matrix,rows,cols,str+1,isUsed,i,j+1);
         isUsed[i*cols+j] = false;
        return sign;
    }
 
};
