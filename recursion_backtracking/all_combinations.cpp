#include <iostream>
#include <map>


void printPermutationString(std::map<char, int> countMap, size_t level, std::string inpStr, std::string currStr){
	std::cout << currStr.substr(0, level) << std::endl;
	for (auto it: countMap){
		char k = it.first;
		if (countMap[k] == 0){
			continue;
		}
		currStr[level] = k;
		countMap[k]--;
		printPermutationString(countMap, level+1, inpStr, currStr);
		countMap[k]++;
	}
}


int main(int argc, char** argv){
	std::string inpStr = "aaAbc";
	std::map<char, int> countMap;
	for (std::size_t i = 0; i < inpStr.length(); i++){
		char c = inpStr[i];
		if (countMap.count(c) == 0){
			countMap[c] = 1;
		}
		else {
			countMap[c]++;
		}
	}
	std::string currStr = inpStr;
	printPermutationString(countMap, 0, inpStr, currStr);
	return 0;
}
