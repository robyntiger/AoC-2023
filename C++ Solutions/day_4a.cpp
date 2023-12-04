#include <iostream>

#include <iostream>
#include <fstream>

#include <string>
#include <regex>

#include <vector>
#include <sstream>

#include <algorithm>

int main(){
    // Read file
    std::ifstream MyReadFile("day_4.txt");
    std::string line;

    std::vector<int> points;

    // Go through each line in file
    while (std::getline(MyReadFile, line)) {
        std::vector<int> winningVals;

        // CUBES ONLY
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

        int pointValue = 0;

        for (int i = 0; i < winningVals.size(); i++){
            if (i == 0){
                pointValue = 1;
            }
            else{
                pointValue *= 2;
            }
        }

        points.push_back(pointValue);
    }

    int sum = 0;

    for (int i =0 ; i < points.size(); i++){
        sum += points.at(i);
    }

    std::cout << sum;
    

    // Close file
    MyReadFile.close();
}