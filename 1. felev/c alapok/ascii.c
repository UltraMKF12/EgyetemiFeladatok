// Széri József - 514
// sjim2307

#include <stdio.h>
#include <stdlib.h>
int main()
{
    //Kiiratni az ascii táblát
        for(int i = 0; i <= 25; i++)
        {
            int value = i;
            while(value <= 255)
            {   
                if(value == 0)
                {
                    printf("|%*d [0x00]:   ", 3, value);
                }
                else if((value > 6 && value < 16) || value == 27 || value == 127)
                {
                    printf("|%*d [%#0*x]:   ", 3, value, 4, value);
                }
                else
                {
                    printf("|%*d [%#0*x]: %c ", 3, value, 4, value, value);
                }
                value += 26;
            }
            printf("\n");
        }
        return 0;
}