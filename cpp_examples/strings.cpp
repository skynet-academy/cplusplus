#include<iostream>
#include<cstdlib>
#include<string>

int main (){
    std::vector<std::string>strVec(10);
    std::string str("this is a proof of a string");
    strVec[0] = str;

    std::cout<<str.front()<<" "<< str.back()<<"\n";
    std::cout<< "length "<< str.length()<<"\n";
    std::string str2(str);

    strVec[1] = str2;
    std::string str3(str,4);
    strVec[2] = str3;
    std::string str4(5,'*');
    strVec[3] = str4;
    strVec[4] = str.append(" || algo diferente para agregar|| ");
    str+= "|| otro caso mas para agregar||";
    strVec[5] = str;
    str.erase(13,str.length()-1);
    strVec[6] = str;

    if(str.find("proof")!= std::string::npos)
        std::cout<<"1st index "<<str.find("proof")<<"\n";
    std::cout<< "substring"<<str.substr(7,8)<<"\n";
    reverse(str.begin(),str.end());
    std::cout<<" Reverse "<< str<<"\n";

    transform(str2.begin(), str2.end(),str2.begin(),::toupper);
    std::cout<<" Upper "<<str2<<"\n";
    transform(str2.begin(), str2.end(),str2.begin(),::tolower);
    std::cout<<" Lower "<<str2<<"\n";
    char aChar = 'A';
    int aInt = aChar;
    std::cout<<"A code :"<<(int)'b'<<"\n";
    std::string strNum = std::to_string(1+2);
    std::cout<<"String "<<strNum<<"\n";
    return 0;
}