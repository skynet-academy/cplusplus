#include<iostream>
#include<cstdlib>
#include<string>
#include<vector>
#include<numeric>
#include<sstream>
#include<cmath>

std::vector<int> Range(int start, int max, int step);

int main()
{
    srand(time(NULL));
    int secretNumber = std::rand() % 20;
    int myNumber = 0;
    while(true){
        std::cout<<"enter your number: ";
        std::cin>> myNumber;
        if(myNumber > secretNumber) std::cout<<"Too big\n";
        if(myNumber < secretNumber) std::cout<<"Too small\n";
        if(myNumber == secretNumber) break;
    }
    std::cout<<"You guessed it\n";

    return 0;
}
std::vector<int> Range(int start, int max, int step){
    int i = start;
}