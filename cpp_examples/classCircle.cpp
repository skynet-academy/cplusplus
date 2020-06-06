#include<cstdlib>
#include<iostream>
#include<string>
#include<vector>
#include<ctime>
#include<numeric>
#include<cmath>
class Shape{
public:
    virtual double Area() = 0;

};
class Circle: public Shape{
protected:
    double width;
public:
    Circle(double w){
        width = w;
    }
    double Area() override{
        return 3.14159 * std::pow((width/2),2);
    }
};
class Rectangle: public Shape{
protected:
    double height, width;
public:
    Rectangle(double h, double w){
        height = h;
        width = w;
    }
    double Area() override final{
        return height * width;
    }
};
void ShowArea(Shape& shape){
    std::cout<<"Area: "<<shape.Area()<<"\n";
}

int main(){
    Rectangle rectangle(23,42);
    Circle circle(30);
    ShowArea(rectangle);
    ShowArea(circle);
    return 0;
}