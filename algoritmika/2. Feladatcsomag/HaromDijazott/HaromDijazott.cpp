// Széri József - sjim2307
// HaromDijazott
// Ismerjük egy osztály tanulóinak neveit (családnév + keresztnév) és év végi átlagait. Állapítsuk meg, hogy egy adott nevű tanuló az első három díjazott között van-e?

#include <iostream>
#include <vector>
#include <limits>
using namespace std;

int search_stringIndex_in_stringVector(string search, const vector<string> &stringVector)
{
    // Searches for a value in stringVector that is equal to search, if found returns the first index where it's found.
    // Returns -1 if not found

    int index = -1;
    int i = 0;
    int size = stringVector.size();

    while ((i < size) && (search != stringVector[i]))
    {
        i++;
    }

    if(i < size)
    {
        index = i;
    }
    
    return index;
}

int main()
{
    freopen("bemenet.txt", "r", stdin);
    freopen("kimenet.txt", "w", stdout);

    int studentCount;
    cin >> studentCount;
    
    // Last and first names are combined together.
    vector<string> lastAndFirstName(studentCount);
    vector<double> studentGrade(studentCount);

    double minimumGrade = numeric_limits<double>::max(); // get the smallest double when reading input.
    for (int i = 0; i < studentCount; i++)
    {
        string firstName, lastName;
        double grade;
        cin >> lastName >> firstName >> grade;

        lastAndFirstName[i] = lastName + " " + firstName;
        studentGrade[i] = grade;

        if(grade < minimumGrade)
        {
            minimumGrade = grade;
        }
    }

    // Get the list with the highest 3 grades (not including same numbers multiple times), by going through studentGrade vector only once.
    // Alternatively we could use "Maximumkiválasztás" 3 times to get the 3 biggest ones.
    vector<double> top3Grades(3, minimumGrade); // Set all elements value to minimumGrade
    for (int i = 0; i < studentCount; i++)
    {
        if(studentGrade[i] > top3Grades[2]) // Grade > 3rd
        {
            if(studentGrade[i] > top3Grades[1]) // Grade > 2nd
            {
                if(studentGrade[i] > top3Grades[0]) // Grade > 1st
                {
                    top3Grades[2] = top3Grades[1]; // 3rd = 2nd
                    top3Grades[1] = top3Grades[0]; // 2nd = 1st
                    top3Grades[0] = studentGrade[i]; // 1st = grade
                }

                else if(top3Grades[0] != studentGrade[i]) // 1st > grade > 2nd - we don't need duplicates
                {
                    top3Grades[2] = top3Grades[1]; // 3rd = 2nd
                    top3Grades[1] = studentGrade[i]; // 2nd = grade
                }
            }

            else if(top3Grades[1] != studentGrade[i]) // 2nd > grade > 3rd - we don't need duplicates
            {
                top3Grades[2] = studentGrade[i];
            }
        }
    }
    
    //Get the index of the student we search for in lastAndFirstName
    string firstName, lastName;
    cin >> lastName >> firstName;

    string searchStudent = lastName + " " + firstName;
    
    // TODO: Meg kell oldani, hogy a legnagyobb elofordulast keresse, ne a legelsot!!!
    int index = search_stringIndex_in_stringVector(searchStudent, lastAndFirstName);

    if((index != -1) && (studentGrade[index] >= top3Grades[2])) // If the searchStudent's grade is in the top 3
    {
        cout << "igen";
    }
    else
    {
        cout << "nem";
    }
    
    return 0;
}