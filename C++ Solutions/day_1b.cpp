#include <iostream>

#include <iostream>
#include <fstream>

#include <map>
#include <string>

#include <regex>

#include <sstream>


int main() {
    std::ifstream MyReadFile("day_1.txt");
    std::string line;

    std::map<std::string, int> wordNums{ {"one", 1},{"two", 2}, {"three", 3}, {"four", 4},{"five", 5}, {"six", 6}, {"seven", 7},{"eight", 8}, {"nine", 9} };

    int sum = 0;

    while (std::getline(MyReadFile, line)) {
        std::regex regexp("[1-9]|one|two|three|four|five|six|seven|eight|nine");
        std::smatch match;

        std::string lineNums;

        std::string::const_iterator searchStart(line.cbegin());
        while (regex_search(searchStart, line.cend(), match, regexp))
        {
            std::string matchString = match.str(0);
            std::istringstream ss(matchString);
            std::string word;

            while (ss >> word) {
                if (word.length() == 1) {
                    lineNums.push_back(word[0]);
                }

                else {
                    lineNums = lineNums + std::to_string(wordNums.at(word));
                }
            }

            searchStart++;
        }

        std::string fullNum;

        if (lineNums.length() > 0) fullNum.push_back(lineNums[0]);
        (lineNums.length() > 1) ? fullNum.push_back(lineNums.back()) : fullNum.push_back(lineNums[0]);

        int lineInt = std::stoi(fullNum);

        sum = sum + lineInt;
    }

    std::cout << sum;

    MyReadFile.close();
}