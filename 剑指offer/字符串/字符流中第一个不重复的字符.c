class Solution
{
public:
  //Insert one char from stringstream
    vector<char>a;
    void Insert(char ch)
    {
         a.push_back(ch);
    }
  //return the first appearence once char in current stringstream
    char FirstAppearingOnce()
    {
        int hash[255] = {0};
        for(int i = 0; i < a.size();++i)
        {
            if(!hash[a[i]])
                hash[a[i]] = 1;
                else
                {
                    hash[a[i]] = 2;
                }
        }
        for(int i = 0; i < a.size(); ++i)
        {
            if(hash[a[i]] == 1)
            {
                return a[i];
            }
        }
        return '#';
    }
 
};
