#include <iostream>

#include "singleton.h"

int main()
{
    Singleton::var1 = 0;
    int var1_1 = Singleton::var1;
    Singleton::var1  = 2;
    int var1_2 = Singleton::var1;


    return 0;
}