#include <iostream>
#include<string>
#include<vector>
#include<ctime>
#include<numeric>
#include<math.h>

class Laptop{
    private:
        std::string name;
        double height;
        double weight;

        static int numOflaptops;
    public:
        std::string GetName(){return name;}
        void SetName(std::string name){this-> name = name;}
        double GetHeight(){return height;}
        void SetHeight(double height){this-> height = height;}
        double GetWeight(){return weight;}
        void SetWeight(double weight){this -> weight = weight;}

        void SetAll(std::string, double, double);
        Laptop(std::string, double, double);
        Laptop();
        ~Laptop();
        static int GetNumOfLaptops(){return numOflaptops;}
        void ToString();
};
int Laptop::numOflaptops = 0;
void Laptop::SetAll(std::string name, double height, double weight){
    this -> name = name;
    this -> height = height;
    this -> weight = weight;
    Laptop::numOflaptops++;
}
Laptop::Laptop(std::string name, double height, double weight){
    this -> name = name;
    this -> height = height;
    this -> weight = weight;
    Laptop::numOflaptops++;
}

Laptop::Laptop(){
    this -> name = name;
    this -> height = height;
    this -> weight = weight;
    Laptop::numOflaptops++;
}

Laptop::~Laptop(){
    std::cout<<"\nLaptop "<< this-> name<<" Destroyed ";
}

void Laptop::ToString(){
    std::cout<<this->name<<"Name is: "<<this-> height<< "\ncms tall and: "<<
    this-> weight<<"\nKgs in weight: ";
}
int main(){
    Laptop toshiba;
    toshiba.ToString();
    toshiba.SetHeight(80);
    toshiba.SetWeight(3);
    toshiba.SetName("LPX 1298");
    toshiba.ToString();
    Laptop Asus("JSH 328",20, 3);
    Asus.ToString();
    return 0;
}