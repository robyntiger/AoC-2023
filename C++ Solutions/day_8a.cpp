#include <iostream>

#include <iostream>
#include <fstream>

#include <string>
#include <vector>
#include <sstream>

#include <map>

void binarySearch(int& i, std::string stack, std::map<std::string, std::pair<std::string, std::string>> binaryTree, std::string current){
    if (stack[0] == 'L'){
        current = binaryTree[current].first;
    }
    else{
        current = binaryTree[current].second;
    }
    
    stack.push_back(stack[0]);
    stack.erase(0, 1);

    if (current == "ZZZ"){
        return;
    }
    else{
        i++;
        binarySearch(i, stack, binaryTree, current);
    }

    return;
}

int main(){
    std::ifstream MyReadFile("day_8.txt");
    std::string line;
    
    std::map<std::string, std::pair<std::string, std::string>> binaryTree;
    std::string stack;

    std::string first = "AAA";

    int x = 0;
    
    while (std::getline(MyReadFile, line)) {   
        if (x > 0 && line.size() > 0){
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

    int i = 1;
    binarySearch(i, stack, binaryTree, first);

    std::cout << i;
}