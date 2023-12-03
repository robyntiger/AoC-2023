#include <iostream>

#include <iostream>
#include <fstream>

#include <string>
#include <vector>

bool checkIfNumber(char value){
    if (isdigit(value)){
        return true;
    }
    else{
        return false;
    }
}

int recursiveFindNum(std::string theString, int gridNum){
    std::string s;

    std::vector<int> vals;

    for (int i = gridNum-1; i > gridNum-3; i--){
        if (s.length() < 3){
            if (i >= 0 && i < theString.length()){
            if (checkIfNumber(theString[i])){
                s = theString[i]+s;
            }
            else{
                break;
            }
        }
        }
    }

    s.push_back(theString[gridNum]);

    for (int i = gridNum+1; i < gridNum+3; i++){
        if (s.length() < 3){
            if (i >= 0 && i < theString.length()){
            if (checkIfNumber(theString[i])){
                s.push_back(theString[i]);
            }
            else{
                break;
            }
        }
        }
    }

    return std::stoi(s);
}

int main(){
    // Read file
    std::ifstream MyReadFile("day_3.txt");
    std::vector<std::string> grid;
    
    std::string line;

    // all vals
    std::vector<int> allVals;
    std::vector<int> gearVals;

    // Go through each line in file
    while (std::getline(MyReadFile, line)) {
        grid.push_back(line);
    }

    for (int i =0; i < grid.size(); i++){
        //std::cout << grid.at(i) << std::endl;

        for (int j =0; j < grid.at(i).length(); j++){
            //std::cout << grid.at(i)[j];
            if (grid.at(i)[j] == *"*"){
                if (i > 0){
                    if (j > 0){
                        if (checkIfNumber(grid.at(i-1)[j-1])){
                            allVals.push_back(recursiveFindNum(grid.at(i-1), j-1));
                        }
                    }
                    if (j < line.length()){
                        if (checkIfNumber(grid.at(i-1)[j+1])){
                            if (allVals.back() != recursiveFindNum(grid.at(i-1), j+1)){
                                allVals.push_back(recursiveFindNum(grid.at(i-1), j+1));
                            }
                        }
                    }

                    if (checkIfNumber(grid.at(i-1)[j])){
                        if (allVals.back() != recursiveFindNum(grid.at(i-1), j)){
                                allVals.push_back(recursiveFindNum(grid.at(i-1), j));
                            }
                        }
                }

                if (j > 0){
                    if (checkIfNumber(grid.at(i)[j-1])){
                        allVals.push_back(recursiveFindNum(grid.at(i), j-1));
                        }
                }

                if (j < line.length()-1){
                    if (checkIfNumber(grid.at(i)[j+1])){
                        allVals.push_back(recursiveFindNum(grid.at(i), j+1));
                        }
                }

                if (i < grid.size()){
                    if (j > 0){
                        if (checkIfNumber(grid.at(i+1)[j-1])){
                            allVals.push_back(recursiveFindNum(grid.at(i+1), j-1));
                        }
                    }
                    if (j < line.length()){
                        if (checkIfNumber(grid.at(i+1)[j+1])){
                            if (allVals.back() != recursiveFindNum(grid.at(i+1), j+1)){
                            allVals.push_back(recursiveFindNum(grid.at(i+1), j+1));
                        }
                        }
                    }

                    if (checkIfNumber(grid.at(i+1)[j])){
                        if (allVals.back() != recursiveFindNum(grid.at(i+1), j)){
                            allVals.push_back(recursiveFindNum(grid.at(i+1), j));
                        }
                    }
                }
            }

            if (allVals.size() == 2){
            gearVals.push_back(allVals.at(0)*allVals.at(1));
            }

            allVals.clear();
            }
    }

    int sum = 0;

    for (int i =0; i < gearVals.size(); i++){
        sum += gearVals.at(i);
    }

    std::cout << sum;

    // Close file
    MyReadFile.close();
}