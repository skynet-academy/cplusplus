#include<iostream>
#include<cstdlib>
#include<string>
#include<vector>
#include<numeric>
#include<sstream>
#include<cmath>

int Factorial(int number);
int main(){
    std::cout<<"Ingresa tu numero: "<<"\n";
    int i = 0 ;
    std::cin>>i;
    std::cout<<"Factorial: "<< Factorial(i);
    return 0;
}

int Factorial(int number){
    if(number==1){
        return 1;
    }else{
        int result = number*Factorial(number-1);
        return result;
    }
}