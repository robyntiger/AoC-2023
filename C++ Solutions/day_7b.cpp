#include <iostream>

#include <iostream>
#include <fstream>

#include <string>
#include <vector>

#include <sstream>
#include <algorithm>

#include <unordered_map>

std::vector<int> stringToHand(std::string& hand){
    std::unordered_map<char, int> cardValues = {
        {'J', 1}, {'T', 10}, {'Q', 11}, {'K', 12}, {'A', 13}
    };

    std::vector<int> handVec;
    for (char ch : hand) {
        if (cardValues.find(ch) != cardValues.end()) {
            handVec.push_back(cardValues[ch]);
        } else {
            handVec.push_back(ch - '0');
        }
    }

    return handVec;
}

int determineType(const std::vector<int>& handCards) {
    std::vector<int> cardTypes(12, 0);
    std::vector<int> values(6, 0);

    int jokerCount = 0;

    for (int card : handCards) {
        if (card > 1){
            cardTypes[card - 2]++;
        }
        else{
            jokerCount++;
        }
    }

    int maxIndex = max_element(cardTypes.begin(), cardTypes.end()) - cardTypes.begin();
    for (int i = 0; i < jokerCount; i++){
        cardTypes[maxIndex] +=1;
    }

    for (int count : cardTypes) {
        if (count > 0 && count <= 5) {
            values[count]++;
        }
    }

    if (values[5] >= 1) return 7;
    if (values[4] >= 1) return 6;
    if (values[3] >= 1 && values[2] >= 1) return 5;
    if (values[3] >= 1) return 4;
    if (values[2] >= 2) return 3;
    if (values[2] >= 1) return 2;
    if (values[1] >= 5) return 1;

    return 0;
}

int determineBiggerCard(std::string firstCards, std::string secondCards){
    std::vector<int> firstHandCards = stringToHand(firstCards);
    std::vector<int> secondHandCards = stringToHand(secondCards);

    int firstHandValue = determineType(firstHandCards);
    int secondHandValue = determineType(secondHandCards);

    if (firstHandValue > secondHandValue){
        return 0;
    }
    else if (firstHandValue < secondHandValue){
        return 1;
    }

    else{
        for (int i = 0; i < firstHandCards.size(); i++){
            if (firstHandCards[i] > secondHandCards[i]){
                return 0;
            }
            else if (firstHandCards[i] < secondHandCards[i]){
                return 1;
            }
            else{
                continue;
            }
        }
    }
}

std::vector<std::pair<std::string, int>> merge(std::vector<std::pair<std::string, int>>& array, int left, int mid, int right)
{
    int i, j, k;
    int size_left = mid - left + 1;
    int size_right =  right - mid;
    
    std::vector<std::pair<std::string, int>> Left;
    std::vector<std::pair<std::string, int>> Right;

    Left.resize(size_left);
    Right.resize(size_right);
    
    for(i = 0; i < size_left; i++)
    {
        Left[i] = array[left+i];
    }

    for(j = 0; j < size_right; j++)
    {
        Right[j] = array[mid+1+j];
    }
    
    i = 0;
    j = 0;
    k = left;

    while (i < size_left && j < size_right)
    {
        if (determineBiggerCard(Left[i].first, Right[j].first) == 0)
        {
            array[k] = Left[i];
            i++;
        }
        else
        {
            array[k] = Right[j];
            j++;
        }
        k++;
    }
    
    while (i < size_left)
    {
        array[k] = Left[i];
        i++;
        k++;
    }
    
    while (j < size_right)
    {
        array[k] = Right[j];
        j++;
        k++;
    }

    return array;
}

std::vector<std::pair<std::string, int>> mergeSort(std::vector<std::pair<std::string, int>>& array, int left, int right)
{
    if(left < right)
    {
        int mid = (left+right)/2;
        
        array = mergeSort(array, left, mid);
        array = mergeSort(array, mid+1, right);
        
        array = merge(array, left, mid, right);
    }

    return array;
}

int main(){
    // Read file
    std::ifstream MyReadFile("day_7.txt");
    std::string line;

    std::vector<std::string> puzzleInput;

    // Go through each line in file
    while (std::getline(MyReadFile, line)) {
        puzzleInput.push_back(line);
    }

    std::vector<std::pair<std::string, int>> cards;
    std::vector<std::string> tempCard;

    for (int i = 0; i < puzzleInput.size(); i++){
        std::istringstream iss(puzzleInput.at(i));
        std::string s;

        while (std::getline( iss, s, ' ' ) ) {
            tempCard.push_back(s);
        }

        cards.push_back(std::make_pair(tempCard[0], std::stoi(tempCard[1])));

        tempCard.clear();
    }

    cards = mergeSort(cards, 0, cards.size()-1);

    int totalWinnings = 0;

    for (int i = 0; i < cards.size(); i++){
        totalWinnings += cards.at(i).second*(cards.size()-i);
    }

    std::cout << totalWinnings;
}