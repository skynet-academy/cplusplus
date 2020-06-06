#include<cstdlib>
#include<iostream>
#include<string>
#include<vector>
#include<ctime>
#include<numeric>
#include<cmath>
#include<sstream>
#include<fstream>


int main (){
    std::ofstream writeTofile;
    std::ifstream readFromFile;
    std::string txtToWrite = "";
    std::string txtFromfile = "";
    writeTofile.open("test.txt",std::ios_base::out | std::ios_base::trunc);
    if(writeTofile.is_open()){
        writeTofile << "Beginning of file\n";
        std::cout<<"Enter data to write: ";
        getline(std::cin, txtToWrite);
        writeTofile << txtToWrite;
        writeTofile.close();
    }
    readFromFile.open("test.txt", std::ios_base::in);
    if(readFromFile.is_open()){
        while(readFromFile.good()){
            getline(readFromFile, txtFromfile);
            std::cout<<txtFromfile<<"\n";
        }
        readFromFile.close();
    }
    return 0;
}