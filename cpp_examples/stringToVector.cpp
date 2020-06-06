#include<cstdlib>
#include<iostream>
#include<string>
#include<vector>
#include<ctime>
#include<numeric>
#include<cmath>
#include<sstream>
#include<fstream>
std::vector<std::string> StringToVector(std::string, char separator);

int main (){
    std::ofstream writeToFile;
    std::ifstream readFromFile;
    std::string txtToWrite = "";
    std::string txtFromFile = "";
    writeToFile.open("test.txt",std::ios_base::out | std::ios_base::trunc);
    if(writeToFile.is_open()){
        writeToFile << "Beginning of file\n";
        std::cout<<"Enter data to write: ";
        getline(std::cin, txtToWrite);
        writeToFile << txtToWrite;
        writeToFile.close();
    }
    readFromFile.open("test.txt", std::ios_base::in);
    if(readFromFile.is_open()){
        while(readFromFile.good()){
            getline(readFromFile, txtFromFile);
            std::cout<<txtFromFile<<"\n";

            std::vector<std::string> vect = StringToVector(txtFromFile,' ');
            int wordsInline = vect.size();
            std::cout<<"Words in line: "<< wordsInline<<"\n";
            int charCount = 0;
            for(auto word: vect){
                for(auto letter: word){
                    charCount++;
                }
            }
            int avgNumChars = charCount/wordsInline;
            std::cout<< "Avg word length: "<< avgNumChars << "\n";
        }
        readFromFile.close();
    }
    return 0;
}
std::vector<std::string> StringToVector(std::string theString, char separator){
    std::vector<std::string> vecsWords;
    std::stringstream ss(theString);
    std::string sIndivStr;
    while(getline(ss, sIndivStr, separator)){
        vecsWords.push_back(sIndivStr);
    }
    return vecsWords;
}
