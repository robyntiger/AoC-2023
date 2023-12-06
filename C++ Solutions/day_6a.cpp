#include <iostream>

#include <iostream>
#include <fstream>

#include <string>
#include <vector>
#include <sstream>

#include <numeric>

std::vector<int> splitLineToVector(std::string myString) {
    std::vector<int> tokens;
    std::stringstream mySstream(myString);
    std::string temp;

    while(std::getline(mySstream, temp, ' ' ) ) {
        if (isdigit(temp[0])){
            tokens.push_back(std::stoi(temp));
        }
    }

    return tokens;
}

int main(){
    std::ifstream MyReadFile("day_6.txt");
    std::string line;

    std::vector<std::string> puzzleInput;
    
    while (std::getline(MyReadFile, line)) {
        puzzleInput.push_back(line);
    }

    std::string time = puzzleInput.at(0).erase(0, 5);
    std::string distance = puzzleInput.at(1).erase(0, 9);

    std::vector<int> timeVals = splitLineToVector(time);
    std::vector<int> distanceVals = splitLineToVector(distance);

    std::vector<int> numOfWIns;
    int currentRaceWins = 0;
    
    for (int i = 0 ; i < timeVals.size(); i++){
        for (int j = 0; j <= timeVals.at(i); j++){
            if (j*(timeVals.at(i)-j) > distanceVals.at(i)){
                currentRaceWins++;
            }
        }

        numOfWIns.push_back(currentRaceWins);
        currentRaceWins = 0;
    }

    int num = 0;
    
    for (int i =0; i < numOfWIns.size(); i++){
        if (num == 0){
            num = numOfWIns.at(i);
        }
        else{
            num *= numOfWIns.at(i);
        }
    }

    std::cout << num;
}