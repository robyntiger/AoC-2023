#include <iostream>

#include <iostream>
#include <fstream>

#include <string>
#include <list>
#include <vector>
#include <sstream>

#include <algorithm>

std::vector<long long int> splitLineToVector(std::string myString) {
    std::vector<long long int> nums;
    std::istringstream iss(myString);
    std::string s;
    while (std::getline( iss, s, ' ' ) ) {
        nums.push_back(std::stoll(s));
    }

    return nums;
}

int main(){
    // Read file
    std::ifstream MyReadFile("day_5.txt");
    std::string line;

    std::list<std::string> alamac;
    std::vector<long long int> seeds;
    std::vector<long long int> seeds_new;

    std::vector<long long int> lineBuffer;

    // Go through each line in file
    while (std::getline(MyReadFile, line)) {
        alamac.push_back(line);
    }

    std::string lineBuf;
    int currentConversion = 0;

    for (auto const& i : alamac) {
        if (currentConversion == 0){
            lineBuf = i;
            lineBuf.erase(0, 7);
            seeds = splitLineToVector(lineBuf);
            seeds_new = seeds;
            currentConversion++;
        }

        if (i == ""){
            currentConversion++;
            seeds = seeds_new;
        }

        if (isdigit(i[0])){
            lineBuffer =  splitLineToVector(i);
            
            for (int j =0; j < seeds.size(); j++){
                if (seeds.at(j) >= lineBuffer.at(1) && seeds.at(j) < lineBuffer.at(1)+lineBuffer.at(2) ){
                    seeds_new[j] = seeds.at(j)+(lineBuffer.at(0)-lineBuffer.at(1));
                }
            }
        }
    }

    seeds = seeds_new;

    auto min_value = *std::min_element(seeds.begin(),seeds.end());
    std::cout << min_value;
}