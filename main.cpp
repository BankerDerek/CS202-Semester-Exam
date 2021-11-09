#include <iostream>
#include <fstream>

std::string userFile();

void readFile(std::string);

void displayFile(std::string);

int main(){
    
    return 0;
}

std::string userFile(){
    std::string filename;
    std::cout << "Enter the name of your file: ";
    std::cin >> filename;
    return filename;
}
void readFile(std::string file){
    
}

void displayFile(std::string file){
    std::string line;
    std::ifstream dataFile(file);
    while(std::getline(dataFile,line)){
        std::cout << line << std::endl;
    }
}
