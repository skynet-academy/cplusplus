#include<cstdlib>
#include<iostream>
#include<string>
#include<vector>
#include<ctime>
#include<numeric>
#include<cmath>
#include<sstream>
#include<iterator>
#include<memory>
#include<stdio.h>

class Pizza{
public:
    virtual void MakePizza() = 0;
};
class NYStyleCrust{
public:
    std::string AddIngredient(){
        return "Crust so thin you can see through it\n\n";
    }
};
class DeepDishCrush{
public:
    std::string AddIngredient(){
        return "\nSuper Awesome Chicago Deep dish\n";
    }
};
template < typename T>
class LotsOfMeat: public T{
public:
    std::string AddIngredient(){
        return "\nlots of random meat, " + T::AddIngredient();
    }
};

template < typename T>
class Vegan: public T{
public:
    std::string AddIngredient(){
        return "\nVegan Cheese, Veggies, " + T::AddIngredient();
    }
};
template <typename T>
class MeatNYStyle: public T, public Pizza{
public:
    void MakePizza(){
        std::cout<<"\nMeat NY Style Pizza: "<< T::AddIngredient();
    }
};

template <typename T>
class VeganDeepDish: public T, public Pizza{
public:
    void MakePizza(){
        std::cout<<"\nVegan Deep Dish: \n"<< T::AddIngredient();
    }
};

int main(){
    std::vector<std::unique_ptr<Pizza>>pizzaOrders;
    pizzaOrders.emplace_back(new MeatNYStyle<LotsOfMeat<NYStyleCrust>>());
    pizzaOrders.emplace_back(new VeganDeepDish<Vegan<DeepDishCrush>>());
    for(auto &pizza: pizzaOrders){
        pizza -> MakePizza();
    }

    return 0;
}
