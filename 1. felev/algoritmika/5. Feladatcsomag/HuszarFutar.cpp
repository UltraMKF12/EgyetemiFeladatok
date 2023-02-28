// Széri József - sjim2307
//HuszarFutar
/*Egy 𝑛 × 𝑛 méretű sakktáblán az (𝑥, 𝑦) pozíción található egy futár és az
(𝑥0, 𝑦0) pozíción egy ló. A lónak el kell jutnia erről a helyről az (𝑥1, 𝑦1) pozícióra,
anélkül, hogy egy bizonyos négyzetre többször lépne illetve, hogy olyan helyen
állna meg, ahonnan a futár kiütheti. Írjuk ki, hogy hányféleképpen lehetséges ez!
*/

#include <iostream> 
#include <vector>
using namespace std;

struct Pozicio
{
    int x;
    int y;
};

void futar_bejeloles(Pozicio futar, vector<vector<bool>> &tabla)
{
    int x = futar.x;
    int y = futar.y;

    //Fotalo
    while(x > 0 && y > 0)
    {
        x--;
        y--;
    }
    while(x < tabla.size() && y < tabla.size())
    {
        tabla[x][y] = true;
        x++;
        y++;
    }

    //Mellekatlo
    x = futar.x;
    y = futar.y;
    while(y < tabla.size() && x > 0)
    {
        y++;
        x--;
    }
    while(y > 0 && x < tabla.size())
    {
        tabla[x][y] = true;
        y--;
        x++;
    }
}

void huszar_futar(vector<vector<bool>> &tabla, Pozicio jelenlegi, Pozicio cel, const vector<Pozicio> &huszar_mozgas, int &darab)
{
    if(jelenlegi.x == cel.x && jelenlegi.y == cel.y)
    {
        darab++;
    }

    else
    {
        for (int i = 0; i < 8; i++)
        {
            Pozicio uj;
            uj.x = jelenlegi.x + huszar_mozgas[i].x;
            uj.y = jelenlegi.y + huszar_mozgas[i].y;

            if(
                uj.x >= 0 && uj.x < tabla.size() &&
                uj.y >= 0 && uj.y < tabla.size() &&
                !tabla[uj.x][uj.y]
              )
            {
                tabla[uj.x][uj.y] = true;
                huszar_futar(tabla, uj, cel, huszar_mozgas, darab);
                tabla[uj.x][uj.y] = false;
            }
        }
        
    }
}

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    //Beolvasas
    int n;
    cin >> n;

    Pozicio futar, lo_kezdo, lo_cel;
    cin >> futar.x >> futar.y;
    cin >> lo_kezdo.x >> lo_kezdo.y;
    cin >> lo_cel.x >> lo_cel.y;

    //Igy a kezdőindex 0
    futar.x--;
    futar.y--;
    lo_kezdo.x--;
    lo_kezdo.y--;
    lo_cel.x--;
    lo_cel.y--;

    //Huszar lehetseges lepesei X,Y
    vector<Pozicio> huszar_mozgas =
    {
        {-1, -2},
        { 1, -2},
        { 2, -1},
        { 2,  1},
        { 1,  2},
        {-1,  2},
        {-2,  1},
        {-2, -1},
    };

    vector<vector<bool>> tabla(n, vector<bool>(n, false));
    futar_bejeloles(futar, tabla);

    int darab = 0;
    tabla[lo_kezdo.x][lo_kezdo.y] = true;
    huszar_futar(tabla, lo_kezdo, lo_cel, huszar_mozgas, darab);
    cout << darab;

    return 0;
}