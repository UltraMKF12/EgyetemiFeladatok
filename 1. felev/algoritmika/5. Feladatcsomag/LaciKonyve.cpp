// Széri József - sjim2307
//LaciKonyve
/*
Adva van egy 𝑛 személyből álló csoport. Minden személynek van legalább 𝑛/2
barátja a csoporton belül. Lacinak van egy könyve, amelyet a csoport minden
tagja el szeretne olvasni. Írjátok ki, hogyan vándorol a könyv egyik személytől
a másikig úgy, hogy mindenkihez csak egyszer kerül, és egy személy csak egy
barátjának kölcsönzi a könyvet, amíg az visszatér Lacihoz. Az összes lehetséges
megoldást keressük, a megoldásokat tetszőleges sorrendben ki lehet íratni.
*/

#include <iostream> 
#include <vector>
using namespace std;

struct Szemely
{
    string nev;
    bool volt_mar = false;
    vector<string> baratok;
};

int szemely_kereses(vector<Szemely> emberek, string nev)
{
    for (int i = 0; i < emberek.size(); i++)
    {
        if(emberek[i].nev == nev)
        {
            return i;
        }
    }

    return -1;
}

void konyv_barat_bejaras(vector<Szemely> &emberek, vector<string> nevsor, Szemely jelenlegi ,int melyseg)
{
    if(melyseg == emberek.size() && jelenlegi.nev == "Laci")
    {
        nevsor[melyseg] = "Laci";
        for (int i = 0; i <= melyseg; i++)
        {
            cout << nevsor[i] << " ";
        }
        cout << endl;
    }
    else
    {
        for (int i = 0; i < jelenlegi.baratok.size(); i++)
        {
            if(!emberek[szemely_kereses(emberek, jelenlegi.baratok[i])].volt_mar)
            {
                emberek[szemely_kereses(emberek, jelenlegi.baratok[i])].volt_mar = true;
                nevsor[melyseg] = jelenlegi.nev;
                konyv_barat_bejaras(emberek, nevsor, emberek[szemely_kereses(emberek, jelenlegi.baratok[i])], melyseg+1);
                emberek[szemely_kereses(emberek, jelenlegi.baratok[i])].volt_mar = false;
            }
        }
        
    }
}

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    //Beolvasas
    int szemelyek_szama;
    int barat_parosok_szama;
    cin >> szemelyek_szama >> barat_parosok_szama;

    vector<Szemely> szemelyek;

    for (int i = 0; i < barat_parosok_szama; i++)
    {
        string nev_elso, nev_masodik;
        cin >> nev_elso >> nev_masodik;

        int nev_elso_index = szemely_kereses(szemelyek, nev_elso);
        int nev_masodik_index = szemely_kereses(szemelyek, nev_masodik);

        //Ha nem léteznek létrehozzuk őket
        if(nev_elso_index == -1)
        {
            Szemely uj;
            uj.nev = nev_elso;
            szemelyek.push_back(uj);
            nev_elso_index = szemelyek.size()-1;
        }
        if(nev_masodik_index == -1)
        {
            Szemely uj;
            uj.nev = nev_masodik;
            szemelyek.push_back(uj);
            nev_masodik_index = szemelyek.size()-1;
        }

        szemelyek[nev_elso_index].baratok.push_back(szemelyek[nev_masodik_index].nev);
        szemelyek[nev_masodik_index].baratok.push_back(szemelyek[nev_elso_index].nev);
    }

    vector<string> nevsor(szemelyek.size()+1);
    konyv_barat_bejaras(szemelyek, nevsor, szemelyek[szemely_kereses(szemelyek, "Laci")], 0);

    return 0;
}