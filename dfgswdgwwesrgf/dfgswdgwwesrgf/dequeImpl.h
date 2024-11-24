//
//  Nom du fichier dequeImpl.h
//  Description : deque-circulaire
//
//  Auteur : Jean Goulet
//  Date :   2016-12-27
//  Copyleft 2016 UdeS
//
//  Modifié par : Vincent Ducharme, Janvier 2018
//
// =============================================
//
//  Nom de l'étudiant : Nicolas Lambert 20091393
//  Nom de l'étudiant : Philippe Clavière 20089468
//
// =============================================

#ifndef _dequeImpl_h
#define _dequeImpl_h

/////////////////////////////////////////////////////////////////
// code a completer pour le devoir

template<typename TYPE>
deque<TYPE>::deque(const deque& source)
{
    deque<TYPE> copie(source.size());        // crée nouveau deque de taille equivalente
    for(size_t i = 0; i < source.size(); ++i)
        copie.*DEBUT[i] = source.*DEBUT[i];        // copie les valeurs du vieux deque
    swap(copie);                                   // le vieux deque deviens le nouveau
}

template<typename TYPE>
void
deque<TYPE>::resize(size_t nSIZE)
{
    // si taille depasse la capacité on double la capacité
    if(nSIZE > CAP)
        reserve(2 * nSIZE);        // pour O(1) ammorti
    SIZE = nSIZE;
}

template<typename TYPE>
void
deque<TYPE>::reserve(size_t nCAP)
{
    // seulement si on augmente la capacité
    if(nCAP > CAP)
    {
        TYPE** nDEB = new TYPE*[nCAP];        // crée nouveau tableau primitif

        for(size_t i = ZERO; i < ZERO + SIZE; i++)
        {
            nDEB[i - ZERO] =
              DEBUT[i % CAP];        // copie les pointeurs vers les données du vieux deque
        }

        ZERO        = 0;
        CAP         = nCAP;
        TYPE** TEMP = DEBUT;        // temp pour suppression plus tard
        DEBUT       = nDEB;         // le vieux deque deviens le nouveau
        delete[] TEMP;              // supprime le vieux deque
    }
}

template<typename TYPE>
TYPE& deque<TYPE>::operator[](size_t i)
{
    return **DEBUT[(CAP + i + ZERO)
                   % CAP];        // puisque deque circulaire on module par la capacité
}

template<typename TYPE>
TYPE&
deque<TYPE>::at(size_t i)
{
    if(i >= size())
    {
        throw std::exception("out of range");
    }
    return **DEBUT[(CAP + i + ZERO) % CAP];
}

template<typename TYPE>
const TYPE& deque<TYPE>::operator[](size_t i) const
{
    return **DEBUT[(CAP + i + ZERO) % CAP];
}

template<typename TYPE>
const TYPE&
deque<TYPE>::at(size_t i) const
{
    if(i >= size())
    {
        throw std::exception("out of range");
    }
    return **DEBUT[(CAP + i + ZERO) % CAP];
}

template<typename TYPE>
void
deque<TYPE>::push_back(const TYPE& VAL)
{
    // vérifie si la dimension dépasse la capacité
    if(SIZE >= CAP)
        reserve(CAP * 2);        // change la taille a un de plus, reserve callé en meme temps
                                 // pour 2x capacité
    // crée une nouvelle case mémoire et sauvegarde son pointeur dans DEBUT
    DEBUT[(SIZE++ + ZERO) % CAP] = new TYPE(VAL);
}

template<typename TYPE>
void
deque<TYPE>::pop_back()
{    
    delete DEBUT[(--SIZE + ZERO) % CAP];        // supprime la case memoire indiqué par ce pointeur
}

template<typename TYPE>
void
deque<TYPE>::push_front(const TYPE& VAL)
{
    // vérifie si la dimension dépasse la capacité
    if(SIZE >= CAP)
        reserve(2 * CAP);        // change la taille a un de plus, reserve callé en meme temps pour
                                 // 2x capacité
    DEBUT[(--ZERO) % CAP] = new TYPE(VAL);        // nouvelle case mémoire
    SIZE++;
}

template<typename TYPE>
void
deque<TYPE>::pop_front()
{
    delete DEBUT[(ZERO++) % CAP];        // supprime la case memoire indiqué par ce pointeur
    SIZE--;
}


#endif        // dequeImpl_h
