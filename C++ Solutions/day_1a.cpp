#include <iostream>

#include <iostream>
#include <fstream>

#include <string>

void main2(){
    // Read file
    std::ifstream MyReadFile("day_1.txt");
    std::string line;

    int sum = 0;

    // Go through each line in file
    while (std::getline(MyReadFile, line)) {
        std::string lineNums;

        for (int i = 0; i < line.length(); i++) {
            if (std::isdigit(line[i])){
                lineNums.push_back(line[i]);
            }
        }

        std::string fullNum;
        if (lineNums.length() > 0) fullNum.push_back(lineNums[0]);
        (lineNums.length() > 1) ? fullNum.push_back(lineNums.back()) : fullNum.push_back(lineNums[0]);

        int lineInt = std::stoi(fullNum);

        sum = sum + lineInt;
    }

    std::cout << sum << "\n";

    // Close file
    MyReadFile.close();
}