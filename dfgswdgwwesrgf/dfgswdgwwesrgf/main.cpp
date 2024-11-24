#include "deque.h"

int
main()
{
    deque<int> monDeck(3);
    monDeck.push_back(65535);
    monDeck.push_back(0);
    monDeck.push_back(-127);
    monDeck.pop_back();
    monDeck.push_front(420);
    monDeck.push_front(69);
    monDeck.pop_front();

    //420
    //0
    //0
    //0
    //65535
    //0



    monDeck.afficher();

	return 0;
}