#include <iostream>
using namespace std;

template <class T>
class FifoList
{
    private:
        struct Node
        {
            T data;
            Node* next;
        };

        Node* first;
        Node* last;
        int maxSize;
        int size;

    public:
        FifoList(int);
        ~FifoList();
        void kiir();
        void push(T);
        T pop();
        T& operator[](int index);
        void operator()(T(*f)(T));
};

template<class T>
FifoList<T>::FifoList(int maxSize)
{
    this->maxSize = maxSize;
    first = NULL;
    last = NULL;
    size = 0;
}

template<class T>
FifoList<T>::~FifoList()
{
    while(first != NULL)
    {
        Node* next = first->next;
        delete first;
        first = next;
    }
}

template<class T>
void FifoList<T>::kiir()
{
    Node* current = first;
    while(current != NULL)
    {
        cout << current->data << " ";
        current = current->next;
    }

    cout << endl;
}

template<class T>
void FifoList<T>::push(T data)
{
    if(size < maxSize)
    {
        Node* newNode = new Node{data, NULL};
        if(last != NULL)
        {
            last->next = newNode;
            last = newNode;
        }
        else
        {
            first = newNode;
            last = newNode;
        }
        size++;
    }
    else
    {
        throw "Tulcsordulas";
    }
}

template<class T>
T FifoList<T>::pop()
{
    if(size > 0)
    {
        T data = first->data;

        Node* temp = first;
        first = first->next;
        delete temp;

        size--;
        return data;
    }
    else
    {
        throw "Alulcsordulas";
    }
}

template<class T>
T& FifoList<T>::operator[](int index)
{
    Node* current = first;
    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }

    return current->data;
}

template<class T>
void FifoList<T>::operator()(T(*f)(T))
{
    Node* current = first;
    for (int i = 0; i < size; i++)
    {
        current->data = f(current->data);
        current = current->next;
    }
}

template<typename T>
T duplaz(T ertek)
{
    return ertek * 2;
}

int main()
{
    try
    {
        FifoList<int> teszt(5);
        teszt.push(32);
        teszt.push(66);
        teszt(duplaz<int>);
        teszt.kiir();
        cout << endl;
        // cout << teszt.pop() + 1 << " ";
        // cout << teszt.pop() + 1 << " ";
        teszt[0] = 5;
        teszt.kiir();
        // cout << teszt.pop() + 1;
    }
    catch(const char *e)
    {
        cout << e << endl;
    }
}