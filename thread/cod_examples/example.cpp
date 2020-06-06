#include<iostream>
#include<stdio.h>
#include<vector>
#include<algorithm>

//void Insert(){
    
//}


int main(){
    std::vector<int>myvec;
    for(int i = 0; i < 10; i++){
        myvec.push_back(i);
    }
    for(auto& i : myvec)
        std::cout<<i<<"\n";
    return 0;
}
