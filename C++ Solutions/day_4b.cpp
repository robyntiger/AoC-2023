#include <iostream>

#include <iostream>
#include <fstream>

#include <string>
#include <regex>

#include <vector>
#include <sstream>

#include <algorithm>

int findNumOfWins(std::string line){
    int num = 0;

    std::vector<int> winningVals;
        
    std::string delimiter = ": ";
    line.erase(0, line.find(delimiter) + delimiter.length());

    size_t pos = line.rfind("|");
    std::string myNums = line.substr(0, pos);
    std::string winningNums = line.substr(pos+1, line.length());

    std::stringstream ss(myNums);
    std::vector<std::string> myNumsVector;
    std::string numVal;

    while (getline(ss, numVal, ' ')) {
        if (isdigit(numVal[0])){
            myNumsVector.push_back(numVal);
        }
    }

    std::stringstream ss2(winningNums);
    std::vector<std::string> winningNumsVector;
    std::string numVal2;

    while (getline(ss2, numVal2, ' ')) {
        if (isdigit(numVal2[0])){
            winningNumsVector.push_back(numVal2);
        }
    }

    for (int i = 0; i < myNumsVector.size(); i++){
        if(std::find(winningNumsVector.begin(), winningNumsVector.end(), myNumsVector[i]) != winningNumsVector.end()) {
            winningVals.push_back(std::stoi(myNumsVector[i]));
        }
    }

    num = winningVals.size();

    return num;
}

int main(){
    // Read file
    std::ifstream MyReadFile("day_4.txt");
    std::string line;

    int points = 0;

    std::vector<std::string> scratchcards;

    // Go through each line in file
    while (std::getline(MyReadFile, line)) {
        scratchcards.push_back(line);
    }

    std::vector<int> scratchcardsWins;

    for (int i =0; i < scratchcards.size(); i++){
        scratchcardsWins.push_back(findNumOfWins(scratchcards.at(i)));
    }

    std::vector<int> myMap;

    for (int j = 0; j < scratchcards.size(); j++){
        points++;

        int winValue = scratchcardsWins.at(j);

        for (int i = 0; i < winValue; i++){
            if (j+i+1 < scratchcards.size()){
                myMap.push_back(j+i+1);
            }
            points++;
        }
    }

    while (myMap.size() > 0){
        int winValue = scratchcardsWins.at(myMap.at(0));
        for (int i = 0; i < winValue; i++){
            if (myMap.at(0)+i+1 < scratchcards.size()){
                myMap.push_back(myMap.at(0)+i+1);
            }
            points++;
        }
        
        myMap.erase(myMap.begin());
    }

    std::cout << points;

    // Close file
    MyReadFile.close();
}