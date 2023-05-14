#include <iostream>
#include "Lista.h"
using namespace std;

Lista::Lista()
{
    eleje = NULL;
    vege = NULL;
    rendezett = 0;
}

Lista::~Lista()
{
    if (eleje != NULL)
    {
        delete eleje;
    }
}

void Lista::Kiir()
{
    Elem *kovetkezo = eleje;
    while (kovetkezo != NULL)
    {
        kovetkezo->Kiir();
        cout << endl;
        kovetkezo = kovetkezo->GetKov();
    }
}

void Lista::Beszuras_sor(string nevecske, double atlagocska)
{
    rendezett = 0;
    Elem *uj = new Elem(nevecske, atlagocska);
    // if(vege == eleje && vege != NULL && eleje != NULL)
    // {
    //     vege = uj;
    //     eleje->SetKov(uj);
    // }
    if(vege != NULL)
    {
        vege->SetKov(uj);
        vege = uj;
    }
    else
    {
        eleje = uj;
        vege = uj;
        eleje->SetKov(vege);
    }
}

void Lista::Beszuras_verem(string nevecske, double atlagocska)
{
    rendezett = 0;
    Elem *uj = new Elem(nevecske, atlagocska);
    // if(eleje == vege && vege != NULL && eleje != NULL)
    // {
    //     eleje = uj;
    //     uj->SetKov(vege);
    // }
    if(eleje != NULL)
    {
        uj->SetKov(eleje);
        eleje = uj;
    }
    else
    {
        eleje = uj;
        vege = uj;
        eleje->SetKov(vege);
    }
}

bool kisebb_e(int ertek, Elem* elso, Elem* masodik)
{
    if(ertek == 1)
    {
        return elso->GetNev() < masodik->GetNev();
    }
    else if(ertek == 2)
    {
        return elso->GetAtlag() < masodik->GetAtlag();
    }

    return false;
}

void Lista::Beszuras_rendezett(string name, double value)
{
    if (rendezett == 1 || rendezett == 2)
    {
        Elem *newElem = new Elem(name, value);
        if (eleje == NULL || kisebb_e(rendezett, newElem, eleje))
        {
            // insert at the beginning of the list
            newElem->SetKov(eleje);
            eleje = newElem;
        }
        else
        {
            // find the position to insert
            Elem *curr = eleje;
            while (curr->GetKov() != NULL && !kisebb_e(rendezett, newElem, curr->GetKov()))
            {
                curr = curr->GetKov();
            }
            // insert after curr
            newElem->SetKov(curr->GetKov());
            curr->SetKov(newElem);
        }
    }
    else
    {
        Beszuras_sor(name, value);
    }
}

void Lista::Rendezes(int ertek)
{
    if(rendezett == ertek)
    {
        return;
    }
    if (eleje == NULL || eleje->GetKov() == NULL || ertek < 1 || ertek > 2)
    {
        return;
    }
    bool swapped;
    do
    {
        swapped = false;
        Elem *curr = eleje;
        Elem *prev = NULL;
        while (curr->GetKov() != NULL)
        {
            if(kisebb_e(ertek, curr->GetKov(), curr))
            {
                Elem *nextNode = curr->GetKov();
                curr->SetKov(nextNode->GetKov());
                nextNode->SetKov(curr);
                if (prev != NULL)
                {
                    prev->SetKov(nextNode);
                }
                else
                {
                    eleje = nextNode;
                }
                prev = nextNode;
                swapped = true;
            }
            else
            {
                prev = curr;
                curr = curr->GetKov();
            }
        }
    } while (swapped);

    rendezett = ertek;
}