#ifndef FEJ.H
#define FEJ.H
typedef struct IntArray
{
    int *t;
    int meret;
} IntArray;

IntArray* Create(int);
void Destroy(IntArray*);
int GetValue(IntArray*, int);
void SetValue(IntArray*, int, int);

#endif