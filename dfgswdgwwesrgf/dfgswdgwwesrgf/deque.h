//
//  Nom du fichier : deque.h
//  Description : deque-circulaire
//
//  Auteur : Jean Goulet
//  Date :   2016-12-27
//  Copyleft 2016 UdeS
//
//  Modifié par Vincent Ducharme, Janvier 2018
//

#ifndef _deque_h
#define _deque_h

#include <iostream>
#include <string>
#include <cassert>
#include <stdexcept>

template <typename TYPE>
class deque
{
private:
    TYPE** DEBUT;
    size_t CAP, SIZE, ZERO;
    void reserve(size_t);//augmente la capacite
public:
    deque(size_t = 0);
    ~deque();
    deque(const deque&);
    deque& operator=(const deque&);
    void swap(deque&);

    //selecteurs
    size_t size()const;
    bool empty()const;

    //gestion de la memoire
    void resize(size_t); //change la dimension
    void clear();        //vide la memoire

    //acces aux elements individuels
    TYPE& operator[](size_t);
    TYPE& at(size_t);
    const TYPE& operator[](size_t)const;
    const TYPE& at(size_t)const;
    void push_back(const TYPE&);
    void pop_back();
    void push_front(const TYPE&);
    void pop_front();

    //code de mise au point
    void afficher(std::string = "")const;
};

template <typename TYPE>
deque<TYPE>::deque(size_t D)
{
    SIZE = CAP = D;
    ZERO = 0;
    if (D > 0)
        DEBUT = new TYPE * [CAP];
    else
        DEBUT = nullptr;
    for (size_t i = 0; i < D; ++i)
        DEBUT[i] = new TYPE(TYPE());
}

template <typename TYPE>
deque<TYPE>::~deque()
{
    clear();
}

template <typename TYPE>
deque<TYPE>& deque<TYPE>::operator=(const deque& source)
{
    if (this != &source)
    {
        deque copie(source);
        swap(copie);
    }
    return *this;
}

template <typename TYPE>
void deque<TYPE>::swap(deque& source)
{
    std::swap(DEBUT, source.DEBUT);
    std::swap(CAP, source.CAP);
    std::swap(SIZE, source.SIZE);
    std::swap(ZERO, source.ZERO);
}

template <typename TYPE>
size_t deque<TYPE>::size()const
{
    return SIZE;
}

template <typename TYPE>
bool deque<TYPE>::empty()const
{
    return SIZE == 0;
}

template <typename TYPE>
void deque<TYPE>::clear() {
    for (size_t i = 0; i < SIZE; ++i)
        delete DEBUT[(i + ZERO) % CAP];
    delete[] DEBUT;
    DEBUT = nullptr;
    ZERO = 0;
    CAP = SIZE = 0;
}


/////////////////////////////////////////////////////////////////
//code de mise au point

template <typename TYPE>
void deque<TYPE>::afficher(std::string S)const
{
    using namespace std;
    cout << endl << "---" << S << "------------------------" << endl;
    cout << "DEBUT:" << DEBUT << endl;
    cout << "CAP:  " << CAP << endl;
    cout << "SIZE: " << SIZE << endl;
    cout << "ZERO: " << ZERO << endl;
    cout << "---" << string(S.size(), '-') << "------------------------" << endl;
    size_t i, j;
    for (i = 0; i < CAP; ++i)
    {
        j = (CAP + i - ZERO) % CAP;
        if (j >= SIZE)
            cout << i << "(-)" << endl;
        else
            cout << i << "(" << j << "): " << *DEBUT[i] << endl;
    }
    if (CAP > 0)
        cout << "---" << string(S.size(), '-') << "------------------------" << endl;
}

template <typename TYPE>
std::ostream& operator<<(std::ostream& out, const deque<TYPE>& V)
{
    char delim = '[';
    size_t S = V.size();
    if (S == 0)
        out << delim;
    if (S > 40)
        S = 40;
    for (size_t i = 0; i < S; ++i)
    {
        out << delim << V[i];
        delim = ',';
    }
    out << "]";
    return out;
}

#include "dequeImpl.h"


#endif // deque_h
