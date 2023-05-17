//Széri József - 514/2 - sjim2307
#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
using namespace std;

struct el;
struct csomopont
{
    int id;
    int hossz;

    int legkorabbi_kezdopont;
    int legkorabbi_vegpont;

    int legkesobbi_kezdopont;
    int legkesobbi_vegpont;

    vector<csomopont*> kifele;
    vector<csomopont*> befele;
};

void graf_beolvas(vector<csomopont> &csomopontok)
{
    int elso, masodik;
    while (cin >> elso >> masodik)
    {
        csomopontok[elso].kifele.push_back(&csomopontok[masodik]);
        csomopontok[masodik].befele.push_back(&csomopontok[elso]);
    }
}

void cpm(vector<csomopont>& csomopontok)
{
    csomopontok[1].legkorabbi_kezdopont = 0;
    csomopontok[1].legkorabbi_vegpont = csomopontok[1].hossz;
    for (int i = 2; i < csomopontok.size(); i++)
    {
        for (int j = 0; j < csomopontok[i].befele.size(); j++)
        {
            if(csomopontok[i].legkorabbi_kezdopont < csomopontok[i].befele[j]->legkorabbi_vegpont)
            {
                csomopontok[i].legkorabbi_kezdopont = csomopontok[i].befele[j]->legkorabbi_vegpont;
            }
        }
        csomopontok[i].legkorabbi_vegpont = csomopontok[i].legkorabbi_kezdopont + csomopontok[i].hossz;
    }

    csomopontok.back().legkesobbi_vegpont = csomopontok.back().legkorabbi_vegpont;
    csomopontok.back().legkesobbi_kezdopont = csomopontok.back().legkesobbi_vegpont - csomopontok.back().hossz;

    for (int i = csomopontok.size()-2; i > 0; i--)
    {
        for (int j = 0; j < csomopontok[i].kifele.size(); j++)
        {
            if(csomopontok[i].legkesobbi_vegpont > csomopontok[i].kifele[j]->legkesobbi_kezdopont)
            {
                csomopontok[i].legkesobbi_vegpont = csomopontok[i].kifele[j]->legkesobbi_kezdopont;
            }
        }
        csomopontok[i].legkesobbi_kezdopont = csomopontok[i].legkesobbi_vegpont - csomopontok[i].hossz;
    }
}

int main()
{
    freopen("3_be.txt", "r", stdin);
    freopen("3_ki.txt", "w", stdout);
    int n;
    cin >> n;

    vector<csomopont> csomopontok(n+1);
    for (int i = 1; i < csomopontok.size(); i++)
    {
        int hossz;
        cin >> hossz;
        csomopontok[i] = {i, hossz, 0, 0, INT_MAX, INT_MAX};
    }
    graf_beolvas(csomopontok);

    cpm(csomopontok);

    cout << "Kritikus ut: ";
    csomopont* jelenlegi = &csomopontok[1];
    cout << jelenlegi->id << " ";
    while(jelenlegi->id != csomopontok.size()-1)
    {
        for (int i = 0; i < jelenlegi->kifele.size(); i++)
        {
            csomopont* kovetkezo = jelenlegi->kifele[i];
            if(kovetkezo->legkorabbi_kezdopont == kovetkezo->legkesobbi_kezdopont &&
               kovetkezo->legkorabbi_vegpont   == kovetkezo->legkesobbi_vegpont)
            {
                cout << kovetkezo->id << " ";
                jelenlegi = kovetkezo;
                break;
            }
        }
    }

    cout << endl << endl;

    for (int i = 1; i < csomopontok.size(); i++)
    {
        cout << "----------[" << csomopontok[i].id << "]----------" << endl;
        cout << "Hossz: " << csomopontok[i].hossz << endl;
        cout << "Legkorabbi elkezdes: " << csomopontok[i].legkorabbi_kezdopont << endl;
        cout << "Legkorabbi befejezes: " << csomopontok[i].legkorabbi_vegpont << endl;
        cout << "Legkesobbi elkezdes: " << csomopontok[i].legkesobbi_kezdopont << endl;
        cout << "Legkesobbi befejezes: " << csomopontok[i].legkesobbi_vegpont << endl;
        cout << endl;
    }
    
    return 0;
}