#include <iostream>
using namespace std;

//negyzetbol hany y diameter kort lehet kivagni, majd osszegyurni a maradekot es azt nezni.
//Alapotled diameter: ha a kor hatrelevo sor hosszaba meg fer akkor kezdjuk. A sor hosszaig megyunk a diameter rakodassal.
/*
1. Megszerezni legeloszor hany kor fel bere a negyzetbe
2. Kiszamitani a korok teruletet
3. Kivonni az areabol, majd abbol kiszamitani az uj negyzetet. Repeat / for frugal

*/

int main()
{
    freopen("bemenet.txt", "r", stdin);
    const double PI = 3.141592653589793;

    double squareSide;
    cin >> squareSide;

    double circleDiameter;
    cin >> circleDiameter;

    int wasteful = 0;
    int frugal = 0;

    double circleArea = (PI * (circleDiameter/2) * (circleDiameter/2));
    double squareArea = squareSide*squareSide;

    if(squareSide >= circleDiameter)
    {
        double newSide = 0;
        while(newSide <= squareSide)
        {
            newSide += circleDiameter;
        }

        if(newSide > squareSide) newSide -= circleDiameter;

        double newArea = newSide * newSide;
        wasteful = int(newArea / (circleDiameter*circleDiameter));

        
        frugal = int(squareArea / circleArea);

        //int howManyCirclesInArea = squareArea/(circleDiameter*circleDiameter);
        //wasteful = howManyCirclesInArea;
        //frugal = howManyCirclesInArea;


        // while (howManyCirclesInArea > 0)
        // {
        //     squareArea = squareArea - circleArea * howManyCirclesInArea;
        //     howManyCirclesInArea = squareArea/(circleDiameter*circleDiameter);
        //     frugal += howManyCirclesInArea;
        // }

        //squareArea -= (circleArea*howManyCirclesInArea); 
    }

    cout << frugal - wasteful;
}