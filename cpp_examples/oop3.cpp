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
    this -> name = "";
    this -> height = 50;
    this -> weight = 4;
    Laptop::numOflaptops++;
}

Laptop::Laptop(){
    this -> name = "";
    this -> height = 10;
    this -> weight = 1;
    Laptop::numOflaptops++;
}

Laptop::~Laptop(){
    std::cout<<"\nLaptop "<< this-> name<<" Destroyed ";
}

void Laptop::ToString(){
    std::cout<<this->name<<"Name is: "<<this-> height<< "\ncms tall and: "<<
    this-> weight<<"\nKgs in weight: ";
}

class Tablet: public Laptop{
private:
    std::string color = "green";
public:
    void MakeSound(){
        std::cout<<"The Tablet: "<<this->GetName()<<" is color: "<<
        this->color<<"\n";
    }
    Tablet(std::string, double, double, std::string);
    Tablet():Laptop(){};
    void ToString();
};
Tablet::Tablet(std::string name, double height,
        double weight, std::string color):
        Laptop(name, height,weight){
        this->color = color;
}
void Tablet::ToString(){
    std::cout<<this->GetName()<<"Name is: "      //we need to call "GetName", because "name" is private
    <<this->GetHeight()<< "\ncms tall and: "<<  //we need to call "GetHeight", because "name" is private
    this-> GetWeight()<<"\nKgs in weight and it color is: "<<this->color<<"\n";     //we need to call "GetWeidth", because "name" is private
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
    Tablet advance("Advance", 20, 3, "blue");
    advance.ToString();
    return 0;
}