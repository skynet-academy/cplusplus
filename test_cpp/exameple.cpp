#include <iostream>
#include <algorithm>
#include <stdlib.h>


double sqr(double arg)
{
    return arg*arg;
}

int main()
{
    double mysqr = sqr(4);
    std::cout<< mysqr << "\n";
}
