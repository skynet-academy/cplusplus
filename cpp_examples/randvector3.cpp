#include<iostream>
#include<cstdlib>
#include<numeric>
#include<sstream>
#include<cmath>

std::vector<int> GenerateRandeVec(int numOfNums, int min, int max);

int main(){
    std::vector<int> vecVals = GenerateRandeVec(10,1,50);
    std::vector<int> vec1 = {1,2,3,4,5,6};
    std::vector<int> vec2 = {1,2,3,4,5,6};
    std::vector<int> vec3(6);
    transform(vec1.begin(),vec1.end(),vec2.begin(),vec3.begin(),
        [](int x, int y){return x * y;});
    for(auto val: vec3)
        std::cout<< val<<"\n";

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
