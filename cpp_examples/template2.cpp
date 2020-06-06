#include<cstdlib>
#include<iostream>
#include<string>
#include<vector>
#include<ctime>
#include<numeric>
#include<cmath>
#include<sstream>
#include<iterator>

template<typename T, typename U>
class Person{
    public:
        T height;
        U weidht;
        static int numOfPeople;
        Person(T h, U w){
            height = h, weidht = w;
            numOfPeople++;
        }
        void GetData(){
            std::cout<< "Height: "<< height << " and weight "<<weidht<<"\n";
        }
};
template<typename T, typename U> int Person<T,U>::numOfPeople;

int main(){
    Person<double,int> nicolas(1.70, 90);
    nicolas.GetData();
    std::cout<<"Number of people: "<< nicolas.numOfPeople<<"\n";
    return 0;
}