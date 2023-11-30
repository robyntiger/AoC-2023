#include <iostream>

#include <iostream>
#include <fstream>

#include <string>
#include <vector>

std::vector<std::string> puzzleInput() {
    // Read file
    std::ifstream MyReadFile("input.txt");
    std::string line;

    // Create vector to store data
    std::vector<std::string> inputData;
    
    // Go through each line in file
    while (std::getline(MyReadFile, line)) {
        inputData.push_back(line);
    }

    // Close file
    MyReadFile.close();

    return inputData;
}

int dayOne(std::vector<std::string> inputData) {
    int result = 0;
    return result;
}

int main()
{
    // Each puzzle requires data
    std::vector<std::string> inputData = puzzleInput();

    // test puzzleInput() works as intended
    for (int i = 0; i < inputData.size(); i++) std::cout << inputData.at(i) << std::endl;

    // Results
    std::cout << "day 1 result: " << dayOne(inputData) << std::endl;
}