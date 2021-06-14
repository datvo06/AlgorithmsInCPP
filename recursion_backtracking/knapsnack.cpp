#include <iostream>
#include <vector>


void helper(std::vector<std::vector<int>>& T, int* vals, int* weights, std::vector<int>& currResult,  int maxWeight, int numVals){
	int currVal = T[numVals-1][maxWeight];
	// check if the max of last row weight without this val equal
	//
	if(maxWeight == 0){
		for (auto it: currResult){
			std::cout << it << ", ";
		}
		std::cout << std::endl;
	}
	if (maxWeight - weights[numVals-1] >= 0){
		if (T[numVals-2][maxWeight - weights[numVals-1]] == currVal - vals[numVals-1]){
				currResult.push_back(numVals-1);
				helper(T, vals, weights, currResult, maxWeight - weights[numVals-1], numVals-1);
				currResult.pop_back();
		}
		else{
			helper(T, vals, weights, currResult, maxWeight, numVals-1);
		}
	}
}


int main(int argc, char** argv){
	int maxWeight = 7;
	int vals[4] = {1, 4, 5, 7};
	int weights[4] = {1, 3, 4, 5};
	std::vector<std::vector<int>> T;
	for (int i = 0; i < 4; i++){
		std::vector<int> row;
		for (int j = 0; j < maxWeight+1; j++){
			row.push_back(0);
		}
		T.push_back(row);
	}
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < maxWeight+1; j++){
			if (j < weights[i]){
				if (i == 0){
					T[i][j] = 0; 
				}
				else{
					T[i][j] = T[i-1][j];
				}
			}
			else{
				if (i == 0) T[i][j] = vals[i];
				else	T[i][j] = std::max(vals[i] + T[i-1][j-weights[i]], T[i-1][j]);
			}
		}
	}
	for (auto itr: T){
		for (auto it: itr){
			std::cout << it << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "Max value: " << T[3][7] << std::endl;
	std::vector<int> currResult;
	helper(T, vals, weights, currResult, maxWeight, 4);
}
