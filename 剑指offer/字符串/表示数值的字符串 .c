class Solution {
public:
    bool isNumeric(char* string)
    {
        bool sign = false,decimal = false, hase = false;
        for(int i = 0;i < strlen(string);++i)
        {
            if(string[i] == 'e' || string[i] == 'E')
            {
                if(hase)
                {
                    return false;
                }
                if(i == strlen(string)-1)
                {
                    return false;
                }
                hase = true;
            }
            else if(string[i] == '+' || string[i] == '-')
            {
                if(sign && string[i-1] != 'e' && string[i-1] != 'E')
                {
                    return false;
                }
                if(!sign && i > 0 && string[i-1] != 'e' && string[i-1] != 'E')
                {
                    return false;
                }
                sign = true;
            }
            else if(string[i] == '.')
            {
                if(decimal || hase)
                {
                    return false;
                }
                decimal = true;
            }
            else if(string[i] < '0'||string[i]> '9')
            {
                return false;
            }
             
        }
        return true;
    }
 
};
