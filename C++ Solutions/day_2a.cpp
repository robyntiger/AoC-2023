#include <iostream>

#include <iostream>
#include <fstream>

#include <string>
#include <regex>

#include <vector>

bool determineIfTooBig(std::string key, std::string value){
    int red = 12;
    int green = 13;
    int blue = 14;

    bool returnVal;

    int val = std::stoi(value);

    if (key == "red" && std::stoi(value) <= red ){
        returnVal=true;
    }
    else if (key == "green" && std::stoi(value) <= green ){
        returnVal=true;
    }
    else if (key == "blue" && std::stoi(value) <= blue ){
        returnVal=true;
    }
    else{
        returnVal=false;
    }

    return returnVal;
}

int main(){
    // Read file
    std::ifstream MyReadFile("day_2.txt");
    std::string line;

    std::vector<std::string> possibleGames;

    // Go through each line in file
    while (std::getline(MyReadFile, line)) {
        // MAP FOR CUBES
        std::vector<std::pair<std::string, std::string>> cubesMap;

        // CODE
        std::regex regexp("([0-9])+");
        std::smatch match;

        // GAME NUMBER
        std::string::const_iterator searchStart(line.cbegin());
        regex_search(searchStart, line.cend(), match, regexp);
        std::string currentGame = match.str(0);

        // CUBES ONLY
        std::string delimiter = ": ";
        std::string cubes = line.substr(0, line.find(delimiter));
        line.erase(0, line.find(delimiter) + delimiter.length());

        // iterate through sub games
        line = line + "; ";
        delimiter = "; ";

        // VALID GAME
        bool validGame = true;

        size_t pos = 0;
        std::string token;
        while ((pos = line.find(delimiter)) != std::string::npos) {
            token = line.substr(0, pos);
            //std::cout << token << std::endl;
            line.erase(0, pos + delimiter.length());

            std::string commaDelim = ", ";

            std::string lineBuffer = token + ", ";

            size_t posVal = 0;
            std::string tokenVal;
             while ((posVal = lineBuffer.find(commaDelim)) != std::string::npos) {
                tokenVal = lineBuffer.substr(0, posVal);
                //std::cout << tokenVal << std::endl;
                lineBuffer.erase(0, posVal + commaDelim.length());

                // split by space
                std::string spaceDelim = " ";
                std::string tokenLineBuffer = tokenVal + " ";

                size_t newPosVal = 0;
                std::string newTokenVal;

                while ((newPosVal = tokenLineBuffer.find(spaceDelim)) != std::string::npos) {
                    newTokenVal = tokenLineBuffer.substr(0, newPosVal);
                    std::string key = newTokenVal;
                    tokenLineBuffer.erase(0, newPosVal + spaceDelim.length());

                    newPosVal = tokenLineBuffer.find(spaceDelim);

                    newTokenVal = tokenLineBuffer.substr(0, newPosVal);
                    std::string value = newTokenVal;
                    tokenLineBuffer.erase(0, newPosVal + spaceDelim.length());

                    cubesMap.push_back(make_pair(key,value));
                }

                for (int i = 0; i < cubesMap.size(); i++){
                    validGame = determineIfTooBig(cubesMap[i].second, cubesMap[i].first);

                    if (validGame == false){
                        break;
                    }
                }

            }
        }

        if (validGame == true){
            possibleGames.push_back(currentGame);
        }
    }

    int finalSum = 0;

    for (int i = 0; i < possibleGames.size(); i++){
        finalSum += std::stoi(possibleGames.at(i));
    }

    std::cout << finalSum;
    

    // Close file
    MyReadFile.close();
}