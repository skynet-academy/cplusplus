#include <iostream>
#include<string>
#include<vector>
#include<ctime>
#include<numeric>
#include<math.h>

class Warrior{
private:
    int attkMax;
    int blockMax;
public:
    std::string name;
    int health;
    Warrior(std::string name, int health,int attkMax, int blockMax){
        this->name = name;
        this->health = health;
        this->attkMax = attkMax;
        this->blockMax = blockMax;
    }
    int Attack(){
        return std::rand() % this -> attkMax;
    }

    int Block(){
        return std::rand() % this -> blockMax;
    }

};
class Battle{
public:
    static void StartFight(Warrior& warrior1,Warrior& warrior2){
        while(true){
            if(Battle::GetAttackResult(warrior1, warrior2).compare("Game over")==0){
                std::cout<<"Game over\n";
                break;
            }
            if(Battle::GetAttackResult(warrior2, warrior1).compare("Game over")==0){
                std::cout<<"Game over\n";
                break;
            }
        }
    }
    static std::string GetAttackResult(Warrior& warriorA,Warrior& warriorB){
        int warriorAAttkAmt = warriorA.Attack();
        int warriorBBlockAmt = warriorB.Block();
        int damage2WarriorB = ceil(warriorAAttkAmt - warriorBBlockAmt);
        damage2WarriorB = (damage2WarriorB <= 0)? 0: damage2WarriorB;
        warriorB.health = warriorB.health - damage2WarriorB;
        printf("%s attacks %s and deals %d damage\n",
            warriorA.name.c_str(),
            warriorB.name.c_str(),
            damage2WarriorB);
        printf("%s is down to %d health\n",
            warriorB.name.c_str(),
            warriorB.health);
        if(warriorB.health <=0){
            printf("%s has died and %s is victorius\n"
            ,warriorB.name.c_str()
            ,warriorA.name.c_str());
            return "Game over";
        }else{
            return "fight again";
        }
    }
};


int main(){
    Warrior Spiderman("Spiderman", 1200, 12, 30);
    Warrior Hulk("Hulk", 1400, 16, 20);
    Battle::StartFight(Spiderman,Hulk);

}