#include<iostream>
#include<cstdlib>
#include<numeric>
#include<sstream>
#include<cmath>

std::vector<int> GenerateRandeVec(int numOfNums, int min, int max);

int main(){
    std::vector<int> vecVals = GenerateRandeVec(10,1,50);
    for(auto x: vecVals)
        std::cout<<x<<"\n";
    std::cout<<" "<<"\n\n";
    std::sort(vecVals.begin(), vecVals.end(), [](int x, int y){return x<y;});
    for(auto x: vecVals)
        std::cout<<x<<"\n";
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