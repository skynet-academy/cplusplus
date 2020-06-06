#include<iostream>
#include<cstdlib>

int Fibo(int number);

int main(){
    int number;
    std::cout<<"Enter your number: ";
    std::cin>> number;
    printf("The index Fibo(%d) = %d ", number, Fibo(number));
    return 0;

}

int Fibo(int number){
    if(number < 2){
        return 2;
    }else{
        return Fibo(number-1) + Fibo(number-2);
    }
}