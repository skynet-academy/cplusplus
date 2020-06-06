#include<iostream>
#include<cstdlib>
#include<numeric>
#include<sstream>
#include<cmath>

std::vector<int> GenerateRandeVec(int numOfNums, int min, int max);

int main(){
    std::vector<int> vecVals = GenerateRandeVec(10,1,50);
    int divisor;
    std::vector<int> doubleVector;
    std::for_each(vecVals.begin(),vecVals.end(),[&](int x){doubleVector.push_back(x * 2) ;});
    for(auto val: doubleVector)
        std::cout<<val<<"\n";

    return 0;
}

std::vector<int> GenerateRandeVec(int numOfNums, int min, int max){
    std::vector<int> vecValues;
    srand(time(NULL));
    int i = 0, randVal = 0;
    while(i < numOfNums){
        randVal = min + std::rand()%((max + 1) -min);
        vecValues.push_back(randVal);
        i++;
    }
    return vecValues;
}