#include<cstdlib>
#include<iostream>
#include<string>
#include<vector>
#include<ctime>
#include<numeric>
#include<cmath>
#include<sstream>
#include<iterator>


template<typename T>
T Add(T val, T val2){
    return val + val2;
}
template<typename T>
T Max(T val, T val2){
    return(val < val2) ? val2 : val;
}
int main(){
    std::cout << "5 + 4 = "<< Add(10,6)<<"\n";
    std::cout << "15.2 + 15.8 = "<< Add(15.2,15.8)<<"\n";
    std::cout << "A < B? = "<< Max('A','B')<<"\n";
    std::cout << "Dog < Cat? = "<< Max("Dog","Cat")<<"\n";
    return 0;
}