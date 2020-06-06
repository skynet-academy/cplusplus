#include<iostream>
#include<cstdlib>
#include<string>
#include<vector>
#include<numeric>
#include<sstream>
#include<cmath>
int main(){

    std::string normalStr, secretStr = "";
    std::cout<< "Enter your string : ";
    std::cin>>normalStr;

    for(char x: normalStr)
        secretStr+=std::to_string((int)x);

    std::cout<<"Secret: "<<secretStr<<"\n";
    normalStr = "";

    for(int i = 0; i < secretStr.length();i +=2){
        std::string sCharCode="";
        sCharCode+= secretStr[i];
        sCharCode+= secretStr[i+1];

        int nCharCode = std::stoi(sCharCode);
        char chCharcode = nCharCode;
        normalStr += chCharcode;
    }

    std::cout<<"Original: "<<normalStr<<"\n";

    return 0;
}