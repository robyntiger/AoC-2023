#include <iostream>

#include <iostream>
#include <fstream>

#include <string>
#include <regex>

#include <vector>

int main(){
    // Read file
    std::ifstream MyReadFile("day_2.txt");
    std::string line;

    // set of powers
    std::vector<int> powerSet;

    // Go through each line in file
    while (std::getline(MyReadFile, line)) {
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

        // max vals
        int maxRed = 0;
        int maxBlue = 0;
        int maxGreen = 0;

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

                    // max vals
                    if (value == "red" && std::stoi(key) > maxRed){
                        maxRed = std::stoi(key);
                    }

                    if (value == "blue" && std::stoi(key) > maxBlue){
                        maxBlue = std::stoi(key);
                    }

                    if (value == "green" && std::stoi(key) > maxGreen){
                        maxGreen = std::stoi(key);
                    }
                }

            }
        }

        powerSet.push_back(maxRed*maxBlue*maxGreen);
    }
    
    int finalSum = 0;

    for (int i = 0; i < powerSet.size(); i++){
        finalSum += powerSet.at(i);
    }

    std::cout << finalSum;

    // Close file
    MyReadFile.close();
}