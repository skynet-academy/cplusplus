#include<cstdlib>
#include<iostream>
#include<string>
#include<vector>
#include<ctime>
#include<numeric>
#include<cmath>
#include<sstream>
#include<functional>

bool IsItOdd(int num){
    if( num % 2 == 0 ){
        return false;
    }else{
        return true;
    }
}
std::vector<int> ChangeList(std::vector<int> list, std::function<bool(int)>func){
    std::vector<int>oddlist;
    for(auto i: list){
        if(func(i)){
            oddlist.push_back(i);
        }
    }
    return oddlist;
}

int main(){
    std::vector<int> listOfNums {1,2,3,4,5,6,7,8,9};
    std::vector<int> oddlist = ChangeList(listOfNums, IsItOdd);
    std::cout << "list of Odds\n";
    for(auto i: oddlist){
        std::cout<<i<<"\n";
    }
    return 0;
}