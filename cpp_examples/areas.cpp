#include<iostream>
#include<cstdlib>
#include<numeric>
#include<sstream>
#include<cmath>

double Area(int radius);
double Area(int heidth, int width);

int main(){
    std::cout<<"enter (c) to calculate area of a circle or (r) for a rectangle:  ";
    char Letter;
    std::cin>>Letter;
    switch(Letter){
        case 'c':
            std::cout<<"Enter radius: ";
            double radius;
            std::cin>>radius;
            std::cout<<"Area circle: "<< Area(radius);
            break;
        case 'r':
            double heidth, width;
            std::cout<<"Enter heidth: ";
            std::cin>>heidth;
            std::cout<<"Enter width: ";
            std::cin>>width;
            std::cout<<"Area Rectangle: "<<Area(heidth, width);
            break;
        default: std::cout<<"Please enter 'c' or 'r'";
    }
    return 0;
}


double Area(int radius){
    return 3.1415 *(std::pow(radius, 2));
}
double Area(int heidth, int width){
    return heidth*width;
}