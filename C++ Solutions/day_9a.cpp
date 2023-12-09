#include <iostream>

#include <iostream>
#include <fstream>

#include <string>
#include <vector>

#include <sstream>
#include <numeric>

int interpolate(std::vector<int> inputData)
{
    int add = 0;
    std::vector<int> data = inputData;
    std::vector<int> buffer;

    while (true){
        for (int i = 0; i < data.size()-1; i++){
            buffer.push_back(data[i+1]-data[i]);
        }

        add += buffer[buffer.size()-1];

        bool allZero = true;

        for (int i =0; i < buffer.size(); i++){
            if (buffer[i] != 0){
                allZero = false;
            }
        }

        if (allZero){
            return inputData[inputData.size()-1]+add;
        }
        else{
            data = buffer;
            buffer.clear();
        }
    }
}

std::vector<int> splitLineToVector(std::string myString) {
    std::vector<int> tokens;
    std::stringstream mySstream(myString);
    std::string temp;

    while(std::getline(mySstream, temp, ' ' ) ) {
        tokens.push_back(std::stoi(temp));
    }

    return tokens;
}

int main(){
    std::ifstream MyReadFile("day_9.txt");
    std::string line;

    std::vector<std::vector<int>> sequences;
    
    while (std::getline(MyReadFile, line)) {
        sequences.push_back(splitLineToVector(line));
    }
    
    std::vector<int> results;

    for (int i = 0; i < sequences.size(); i++){
        results.push_back(interpolate(sequences[i]));
    }

    long int sum = std::accumulate(results.begin(), results.end(), 0.0);
    std::cout << sum;
}