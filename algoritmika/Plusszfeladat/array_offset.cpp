#include <iostream>
#include <vector>
using namespace std;

int main()
{
    freopen("bemenet.txt", "r", stdin);
    int array_count = 0;
    cin >> array_count;
    vector<vector<int>> tombok(26, vector<int>(102, 0));

    //Tombok beolvasasa
    for (int i = 0; i < array_count; i++)
    {
        char letter;
        cin >> letter;
        int index = letter - 'A';

        char elnyelo;
        cin >> elnyelo;
        
        int lowerRange;
        int higherRange;
        cin >> lowerRange >> elnyelo >> elnyelo >> higherRange >> elnyelo >> elnyelo;

        int offset = 0;
        while (lowerRange > 0)
        {
            lowerRange--;
            higherRange--;
            offset--;
        }
        while (lowerRange < 0)
        {
            lowerRange++;
            higherRange++;
            offset++;
        }

        for (int j = 0; j <= higherRange; j++)
        {
            int szam;
            cin >> szam;
            tombok[index][j+1] = szam;
        }
        tombok[index][0] = offset;
    }
    
    //Keresett elem beolvasas
    char karakter, elnyelo;
    int index;
    cin >> karakter >> elnyelo >> index >> elnyelo;

    int keresett_index = karakter - 'A';
    int offset = tombok[keresett_index][0];
    cout << tombok[keresett_index][offset+index+1];
    return 0;
}