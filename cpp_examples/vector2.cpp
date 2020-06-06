#include<cstdlib>
#include<iostream>
#include<string>
#include<vector>
#include<ctime>
#include<numeric>
#include<cmath>
#include<sstream>
#include<functional>
std::vector<char> GetHAndTList(std::vector<char> possibleValues,
                                int numberValuesToGenerate){
    srand(time(NULL));
    std::vector<char> hAndTList;
    for(int x = 0; x < numberValuesToGenerate; ++x){
        int randIndex = rand() % 2;
        hAndTList.push_back(possibleValues[randIndex]);
    }
    return hAndTList;
}

int GetNumberOfMatches(std::vector<char> list, char valueToFind){
    int numOfMatches = 0;
    for(char c: list){
        if(c == valueToFind){
            numOfMatches++;
        }
    }
    return numOfMatches;

}
int main(){
    std::vector<char> possibleValues{'H','T'};
    std::vector<char> hAndTList = GetHAndTList(possibleValues, 100);
    std::cout<<"Number of heads: "<< GetNumberOfMatches(hAndTList, 'H')<<"\n";
    std::cout<<"Number of Tails: "<< GetNumberOfMatches(hAndTList, 'T')<<"\n";
    return 0;
}