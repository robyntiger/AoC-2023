#include <iostream>

#include <iostream>
#include <fstream>

#include <string>
#include <vector>
#include <sstream>

#include <map>

#include <numeric>

long long int gcd(long long int a, long long int b) 
{ 
  if (b == 0) 
    return a; 
  return gcd(b, a % b); 
} 

long long int lcm(long long int a, long long int b){
    return (a / gcd(a, b)) * b; 
}

void binarySearch(std::vector<int>& LCM, int& x, std::string stack, std::map<std::string, std::pair<std::string, std::string>> binaryTree, std::vector<std::string> current){
    while(true){
        x++;

        for (int i =0; i < current.size(); i++){
            if (stack[0] == 'L'){
                current[i] = binaryTree[current[i]].first;
            }
            else{
                current[i] = binaryTree[current[i]].second;
            }
        }
        
        stack.push_back(stack[0]);
        stack.erase(0, 1);

        std::vector<std::string> currentTemp;
        
        for (int j = 0; j < current.size(); j++){
            if (current[j][2] == 'Z'){
                LCM.push_back(x);
            }
            else{
                currentTemp.push_back(current[j]);
            }
        }

        current = currentTemp;

        if (current.size() > 0){
        }
        else{
            return;
        }
    }
}

int main(){
    std::ifstream MyReadFile("day_8.txt");
    std::string line;
    
    std::map<std::string, std::pair<std::string, std::string>> binaryTree;
    std::string stack;

    std::vector<std::string> first;

    int x = 0;
    
    while (std::getline(MyReadFile, line)) {   
        if (x > 0 && line.size() > 0){
            if (line[2] == 'A'){
                first.push_back(line.substr(0, 3));
            }
            binaryTree[line.substr(0, 3)] = std::make_pair(line.substr(7, 3),line.substr(12, 3));
        }
        else if (x == 0){
            stack = line;
            x++;
        }
        else{
            continue;
        }
    }

    std::vector<int> LCM;

    int i = 0;

    binarySearch(LCM, i, stack, binaryTree, first);

    long long int result = LCM[0];

    for (int i = 1; i < LCM.size(); ++i) {
        result = lcm(result, LCM[i]);
    }

    std::cout << result;
    return 0;
}