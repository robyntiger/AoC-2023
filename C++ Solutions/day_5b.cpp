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
    std::ifstream MyReadFile("day_5.txt");
    std::string line;

    std::list<std::string> alamac;
    std::vector<long long int> seeds;
    
    std::vector<std::pair<long long int,long long int>> seed_ranges;
    std::pair<long long int,long long int> seed_ranges_Buffer_1;
    std::vector<std::pair<long long int,long long int>> seed_ranges_Buffer_2;
    std::vector<std::pair<long long int,long long int>> seed_ranges_Buffer_3;

    std::vector<long long int> lineBuffer;
    
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

            for (int j = 0; j < seeds.size(); j+=2){
                seed_ranges.push_back(std::make_pair(seeds.at(j), seeds.at(j)+seeds.at(j+1)-1));
            }
            
            currentConversion++;
        }

        if (i == ""){
            if (seed_ranges_Buffer_2.size() > 0){
                seed_ranges.insert(seed_ranges.end(), seed_ranges_Buffer_2.begin(), seed_ranges_Buffer_2.end());
                seed_ranges_Buffer_2.clear();
            }
        }

        if (isdigit(i[0])){
            lineBuffer =  splitLineToVector(i);

            long long int conversionRate = lineBuffer.at(0)-lineBuffer.at(1);
            
            for (int j =0; j < seed_ranges.size(); j++){
                seed_ranges_Buffer_1 = seed_ranges.at(j);
                
                if (std::max(seed_ranges_Buffer_1.first, lineBuffer.at(1)) < std::min(seed_ranges_Buffer_1.second, lineBuffer.at(1)+lineBuffer.at(2))){
                    if(seed_ranges_Buffer_1.first >= lineBuffer.at(1) && seed_ranges_Buffer_1.second < lineBuffer.at(1)+lineBuffer.at(2)){
                        // if range is fully inside
                        
                        seed_ranges_Buffer_2.push_back(std::make_pair(seed_ranges_Buffer_1.first+conversionRate, seed_ranges_Buffer_1.second+conversionRate));
                    }
                    else if(seed_ranges_Buffer_1.first < lineBuffer.at(1) && seed_ranges_Buffer_1.second < lineBuffer.at(1)+lineBuffer.at(2)){
                        // if first part of range is outside

                        seed_ranges_Buffer_2.push_back(std::make_pair(lineBuffer.at(1)+conversionRate,seed_ranges_Buffer_1.second+conversionRate-1));

                        seed_ranges_Buffer_3.push_back(std::make_pair(seed_ranges_Buffer_1.first,lineBuffer.at(1)-1));
                    }
                    else if(seed_ranges_Buffer_1.first >= lineBuffer.at(1) && seed_ranges_Buffer_1.second >= lineBuffer.at(1)+lineBuffer.at(2)){
                        // if second part of range is outside
                        
                        seed_ranges_Buffer_2.push_back(std::make_pair(seed_ranges_Buffer_1.first+conversionRate,lineBuffer.at(1)+lineBuffer.at(2)+conversionRate-1));

                        seed_ranges_Buffer_3.push_back(std::make_pair(lineBuffer.at(1)+lineBuffer.at(2),seed_ranges_Buffer_1.second));
                    }
                    else if(seed_ranges_Buffer_1.first < lineBuffer.at(1) && seed_ranges_Buffer_1.second > lineBuffer.at(1)+lineBuffer.at(2)){
                        // if range is fully inside

                        seed_ranges_Buffer_3.push_back(std::make_pair(seed_ranges_Buffer_1.first,lineBuffer.at(1)-1));
                        seed_ranges_Buffer_3.push_back(std::make_pair(lineBuffer.at(1)+lineBuffer.at(2),seed_ranges_Buffer_1.second));

                        seed_ranges_Buffer_2.push_back(std::make_pair(lineBuffer.at(1)+conversionRate, lineBuffer.at(1)+lineBuffer.at(2)+conversionRate));
                    }
                    else{
                        
                    }
                }
                else{
                    seed_ranges_Buffer_3.push_back(seed_ranges_Buffer_1);
                }
            }
            
            seed_ranges = seed_ranges_Buffer_3;
            seed_ranges_Buffer_3.clear();
        }
    }
    
    seed_ranges.insert(seed_ranges.end(), seed_ranges_Buffer_2.begin(), seed_ranges_Buffer_2.end());

    long long int smallest = seed_ranges.at(0).first;

    for (int i = 0; i < seed_ranges.size(); i++) {
        if (seed_ranges.at(i).first < smallest){
            smallest = seed_ranges.at(i).first;
        }
    }
    
    std::cout << smallest;
}