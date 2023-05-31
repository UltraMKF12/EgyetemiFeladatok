//Széri József
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;


struct el;
struct csomopont
{
    int id;
    bool latogatott;
    int x, y;
    vector<el> kifele;
};

struct el
{
    csomopont* kovetkezo;
    double tavolsag;
};

double eukledeszi_tavolsag(double x1, double y1, double x2, double y2) 
{
    return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

void graf_beolvas_hossz_szamitas(vector<csomopont> &csomopontok)
{
    int sorszam, x, y;
    while (cin >> sorszam >> x >> y)
    {
        csomopontok.push_back({sorszam, false, x, y});
    }

    for(int i = 0; i < csomopontok.size(); i++)
    {
        for (int j = 0; j < csomopontok.size(); j++)
        {
            if(i == j) continue;

            csomopontok[i].kifele.push_back({&csomopontok[j], 
            eukledeszi_tavolsag(csomopontok[i].x, csomopontok[i].y, csomopontok[j].x, csomopontok[j].y)});
        }
    }
}

double travelling_greedy(vector<csomopont> &csomopontok, vector<int> &path)
{
    csomopont* current = &csomopontok[0];
    int kezdopont = current->id;
    path.push_back(current->id);
    current->latogatott = true;

    double hossz = 0;

    bool lehet_menni = true;
    while(lehet_menni)
    {
        lehet_menni = false;
        double legkisebb = -1;
        csomopont* uj;
        for (int i = 0; i < current->kifele.size(); i++)
        {
            if ((!current->kifele[i].kovetkezo->latogatott) && (current->kifele[i].tavolsag < legkisebb || legkisebb == -1))
            {
                legkisebb = current->kifele[i].tavolsag;
                uj = current->kifele[i].kovetkezo;
            }
        }
        if(legkisebb != -1)
        {
            current = uj;
            current->latogatott = true;
            path.push_back(current->id);
            lehet_menni = true;
            hossz += legkisebb;
        }   
    }

    //Hozzaadni a vegso path-et.
    for (int i = 0; i < current->kifele.size(); i++)
    {
        if(current->kifele[i].kovetkezo->id == kezdopont)
        {
            hossz += current->kifele[i].tavolsag;
            path.push_back(kezdopont);
        }
    }

    return hossz;
}


void kiir(vector<int> path)
{
    for (int i = 0; i < path.size()-1; i++)
    {
        cout << path[i] << " -> ";
    }
    cout << path[path.size()-1] << endl;
}

int main()
{

    freopen("be.txt", "r", stdin);

    vector<csomopont> csomopontok;
    graf_beolvas_hossz_szamitas(csomopontok);

    vector<int> path;
    double hossz = travelling_greedy(csomopontok, path);

    cout << "Ut hossz: " << hossz << endl;
    kiir(path);
    return 0;
}