#include<cstdlib>
#include<iostream>
#include<string>
#include<vector>
#include<ctime>
#include<numeric>
#include<cmath>
#include<sstream>
#include<thread>
#include<chrono>
#include<ctime>
#include<mutex>

int GetRandom(int max){
    srand(time(NULL));
    return rand()%max;
}
std::string GetTime(){
    auto nowTime = std::chrono::system_clock::now();
    std::time_t sleepTime = std::chrono::system_clock::to_time_t(nowTime);
    return std::ctime(&sleepTime);
}
double acctBalance = 180;
std::mutex acctLock;
void GetMoney(int id, double withdrawal){
    std::lock_guard<std::mutex> lock(acctLock);
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout<<id<< " Tries to withdrawal $"<< withdrawal<< "on" <<GetTime()<<"\n";
    if((acctBalance - withdrawal) >= 0){
        acctBalance -=withdrawal;
        std::cout<< " New account balance is $: "<< acctBalance<<"\n";
    } else{
        std::cout<<" not enough money in account\n";
        std::cout<<" current balance is $ "<< acctBalance<<"\n";
    }
}
int main(){
    std::thread threads[10];
    for(int i = 0; i < 10; ++i){
        threads[i] = std::thread(GetMoney,i,25);
    }
    for(int i = 0; i < 10; ++i){
        threads[i].join();
    }
    return 0;
}