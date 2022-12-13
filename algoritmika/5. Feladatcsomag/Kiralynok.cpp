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
#include <climits>
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

void kiirat_sorrend_alapjan(vector<vector<vector<int>>> keresett_tablak, const vector<int> &sorrendek, int n, const vector<int> &keresett_tabla_sorrend_hely)
{   
    for (int i = 0; i < sorrendek.size(); i++)
    {
        for (int j = 0; j < keresett_tabla_sorrend_hely.size(); j++)
        {
            if(sorrendek[i] == keresett_tabla_sorrend_hely[j])
            {
                kiralyno_kiir(keresett_tablak[j], n);
                break;
            }
        }
    }
}

void kiralynok(vector<vector<int>> &tabla, vector<bool> &oszlop, vector<bool> &fo_atlo, vector<bool> &mellek_atlo, int n, int melyseg, int &q, const vector<int> &sorrendek, int &jelenlegi, vector<vector<vector<int>>> &keresett_tablak, vector<int> &keresett_tabla_sorrend_hely)
{   
    if(melyseg == n)
    {   
        //Kiiratas
        if(q > 0 && bennevan_e(sorrendek, jelenlegi))
        {   
            keresett_tablak.push_back(vector<vector<int>>(tabla));
            keresett_tabla_sorrend_hely.push_back(jelenlegi);
            q--;
        }
        jelenlegi++;
    }
    else
    {   
        for (int i = 0; i < n; i++)
        {
            if(oszlop[i] == 0 && fo_atlo[melyseg-i+n-1] == 0 && mellek_atlo[i+melyseg] == 0)
            {   
                oszlop[i] = true;
                fo_atlo[melyseg-i+n-1] = true;
                mellek_atlo[i+melyseg] = true;
                tabla[melyseg][i] = 2;
                kiralynok(tabla, oszlop, fo_atlo, mellek_atlo, n, melyseg+1, q, sorrendek, jelenlegi, keresett_tablak, keresett_tabla_sorrend_hely);
                oszlop[i] = false;
                fo_atlo[melyseg-i+n-1] = false;
                mellek_atlo[i+melyseg] = false;
                tabla[melyseg][i] = 0;
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
    vector<bool> oszlop(n, false);
    vector<bool> fo_atlo(2*n, false);
    vector<bool> mellek_atlo(2*n, false);

    vector<vector<vector<int>>> keresett_tablak;
    vector<int> keresett_tabla_sorrend_hely;

    int jelenlegi = 1;
    kiralynok(tabla, oszlop, fo_atlo, mellek_atlo, n, 0, q, sorrendek, jelenlegi, keresett_tablak, keresett_tabla_sorrend_hely);
    kiirat_sorrend_alapjan(keresett_tablak, sorrendek, n, keresett_tabla_sorrend_hely);
    cout << jelenlegi-1;

    return 0;
}