#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <thread>
#include <mutex>
#include <chrono>
#include <fstream>
#include <ctime>

int randomRange(int min, int max);

void fill(int * array, const int N);

int array_sum(const int* a, const int* b, const int N);

void print(const int* array, const int N);

int number_of_odds(const int * array, const int N);


int main()
{
    int a[100], b[100], N;
    do
    {
        std::cout<<"Imput size for Arrays (between o and 100) ";
        std::cin>> N;
    } while(N< 0|| N > 100);

    srand((unsigned int)time(NULL));

    fill(a,N);
    fill(b,N);

    std::cout<<"Number of odd elements in array a"<<number_of_odds(a, N)<<std::endl;
    std::cout<<"Number of odd elements in array b"<<number_of_odds(b, N)<<std::endl;

    return 0;
}

int randomRange(int min, int max)
{
    return (rand()%(max -min + 1)) + min; 
}

void fill(int* array, const int N)
{
    for(int i = 0; i< N; i++)
        array[i] = randomRange(10,50);
}


int array_sum(const int* a, const int* b, const int N)
{
    int sum = 0;
    for(int i = 0; i < N; i++)
        sum +=a[i] + b[i];
    return sum;
}

void print(const int* array, const int N)
{
    for(int i = 0; i < N; i++)
        std::cout<<array[i] << " ";
    std::cout<<std::endl;
}


int number_of_odds(const int* array, const int N)
{
    int number_of_odds = 0;
    for(int i = 0; i < N; i++)
        if(array[i]%2 !=0)
            number_of_odds++;
    return number_of_odds;
}














