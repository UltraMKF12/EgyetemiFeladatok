// Széri József - sjim2307
//Kiralynok
/*
Helyezzünk el 𝑛 darab királynőt egy 𝑛 × 𝑛-es sakktáblán minden lehetséges
módon, úgy, hogy ne üssék egymást. Számoljuk meg, hogy hányféleképpen
lehetséges ez és írassuk ki a megadott sorszámú konfigurációkat a lexikografikus
sorrendet tekintve.
*/

#include <iostream>
#include <vector>
using namespace std;

void beolvasas(int &n, int &q, vector<int> &sorrendek)
{
    cin >> n;
    cin >> q;
    sorrendek.resize(q);
    for (int i = 0; i < q; i++)
    {
        cin >> sorrendek[i];
    }
}

void kiralyno_helyfoglalas(vector<vector<int>> &tabla, int n, int pos_x, int pos_y)
{
    //Vertical
    for (int i = 0; i < n; i++)
    {
        tabla[i][pos_y] = 1;
    }

    //Horizontal
    for (int i = 0; i < n; i++)
    {
        tabla[pos_x][i] = 1;
    }
    
    int x = 0;
    int y = 0;

    //Left-up
    x = pos_x;
    y = pos_y;
    while(x >= 0 && y >= 0)
    {
        tabla[x][y] = 1;
        x--;
        y--;
    }

    //Left-down
    x = pos_x;
    y = pos_y;
    while(x >= 0 && y < n)
    {
        tabla[x][y] = 1;
        x--;
        y++;
    }

    //Right-up
    x = pos_x;
    y = pos_y;
    while(x < n && y >= 0)
    {
        tabla[x][y] = 1;
        x++;
        y--;
    }

    //Right-down
    x = pos_x;
    y = pos_y;
    while(x < n && y < n)
    {
        tabla[x][y] = 1;
        x++;
        y++;
    }
    
    tabla[pos_x][pos_y] = 2;
}

void kiralyno_kiir(const vector<vector<int>> &tabla, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if(tabla[i][j] == 2)
            {
                cout << "Q";
            }
            else
            {
                cout << ".";
            }
        }
        cout << endl;
    }
    cout << endl;
}

bool bennevan_e(const vector<int> &tomb, int elem)
{
    int hossz = tomb.size();
    for (int i = 0; i < hossz; i++)
    {
        if(tomb[i] == elem)
        {
            return true;
        }
    }

    return false;
}

void kiralynok(const vector<vector<int>> &tabla, int n, int melyseg, int &q, vector<int> &sorrendek, int &jelenlegi)
{   
    if(melyseg == n)
    {   
        //Kiiratas
        if(q > 0 && bennevan_e(sorrendek, jelenlegi))
        {   
            kiralyno_kiir(tabla, n);
            q--;
        }
        jelenlegi++;
    }
    else
    {   
        //Megnézi a mélység sorban, hogy betudja helyezni e a királynőt.
        for (int i = 0; i < n; i++)
        {
            if(tabla[melyseg][i] == 0)
            {
                vector<vector<int>> uj_tabla(tabla);
                kiralyno_helyfoglalas(uj_tabla, n, melyseg, i);
                kiralynok(uj_tabla, n, melyseg+1, q, sorrendek, jelenlegi);
            }
        }
    }
}

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    int n, q;
    vector<int> sorrendek;
    beolvasas(n, q, sorrendek);

    vector<vector<int>> tabla(n, vector<int>(n, 0));
    int jelenlegi = 1;
    kiralynok(tabla, n, 0, q, sorrendek, jelenlegi);
    cout << jelenlegi-1;

    return 0;
}