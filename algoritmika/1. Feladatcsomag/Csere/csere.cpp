// Széri József - sjim2307
// Csere
// Hasonlitsuk ossze ket egesz tıpusu valtozo cserejenek sebesseget harom kulonbozo modszerrel
#include <iostream>
#include <time.h>
using namespace std;

void csereSegedValtozo(unsigned int &elso, unsigned int &masodik, long long hanyszor)
{
    for (int i = 0; i < hanyszor; i++)
    {
        int temp = elso;
        elso = masodik;
        masodik = temp;
    }
}

void csereOsszeadasKivonas(unsigned int &elso, unsigned int &masodik, long long hanyszor)
{
    for (int i = 0; i < hanyszor; i++)
    {
        // 5 + 7
        elso = elso + masodik; // 5 + 7 = 12
        masodik = elso - masodik; // 12 - 7 = 5
        elso = elso - masodik; // 12 - 5 = 7
    }
}

void csereXor(unsigned int &elso, unsigned int &masodik, long long hanyszor)
{
    for (int i = 0; i < hanyszor; i++)
    {
        // 0101 + 0111 (5 + 7) - nem működik két hasonló számra, mert 0111 ^ 0111 = 0000 (0)
        elso = elso ^ masodik; // 0101 ^ 0111 = 0010 (2)
        masodik = elso ^ masodik; // 0010 ^ 0111 = 0101 (5)
        elso = elso ^ masodik; // 0010 ^ 0101 = 0111 (7)
    }
}

void futasiIdoSzamitas(int index, unsigned int elso, unsigned int masodik, long long hanyszor)
{
    clock_t start = clock();

    switch (index)
    {
    case 1:
        cerr << "Seged valtozo csere ";
        start = clock(); // Hogy legyen picit pontosabb, mert nemtudom a cerr mennyi időbe kerül.
        csereSegedValtozo(elso, masodik, hanyszor);
        break;
    
    case 2:
        cerr << "Osszeadas kivonas csere ";
        start = clock();
        csereOsszeadasKivonas(elso, masodik, hanyszor);
        break;

    case 3:
        cerr << "Xor csere ";
        start = clock();
        csereXor(elso, masodik, hanyszor);
        break;
    }

    clock_t end = clock();
    double elapsed = double(end - start)/CLOCKS_PER_SEC;

    cerr << "futasi ido: " << elapsed << endl;
}

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    unsigned int elso, masodik;
    cin >> elso >> masodik;

    futasiIdoSzamitas(1, elso, masodik, 10000000);
    futasiIdoSzamitas(2, elso, masodik, 10000000);
    futasiIdoSzamitas(3, elso, masodik, 10000000);

    csereSegedValtozo(elso, masodik, 1);
    cout << elso << " " << masodik;
    return 0;
}