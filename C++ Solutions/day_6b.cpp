#include <iostream>

#include <iostream>
#include <fstream>

#include <string>
#include <vector>
#include <sstream>

#include <numeric>

std::string splitLineToVector(std::string myString) {
    std::string tokens;
    std::stringstream mySstream(myString);
    std::string temp;

    while(std::getline(mySstream, temp, ' ' ) ) {
        if (isdigit(temp[0])){
            tokens = tokens + temp;
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

    long long int timeVals = std::stoll(splitLineToVector(time));
    long long int distanceVals = std::stoll(splitLineToVector(distance));

    std::vector<int> numOfWIns;
    long long int currentRaceWins = 0;
    

    for (int j = 0; j <= timeVals; j++){
        if (j*(timeVals-j) > distanceVals){
            currentRaceWins++;
        }
    }

    std::cout << currentRaceWins;
}