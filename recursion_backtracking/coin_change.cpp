#include <iostream>
#include <vector>
#include <map>

int minimumCoinTopDown(int total, std::vector<int> coins, std::map<int, int>& totToNum){
	if (total == 0) return 0;
	if (totToNum.find(total) != totToNum.end()) return totToNum[total];
	int min = INT32_MAX;
	for ( int i = 0; i < coins.size(); i++){
		if (coins[i] > total) continue;
		int val = minimumCoinTopDown(total - coins[i], coins, totToNum);
		if (val < min) min = val;
	}
	min = (min == INT32_MAX ? min: min+1);
	totToNum[total] = min;
	return min;
}


int main(int argc, char** argv){
	std::vector<int> coins;
	coins.push_back(1);
	coins.push_back(2);
	coins.push_back(3);
	std::map<int, int> totToNum;
	for (auto it: coins){
		totToNum[it] = 1;
	}
	for (int i = 1; i < 15; i++){
		std::cout << "Minimum coin toss for " << i << " is " << minimumCoinTopDown(i, coins, totToNum) << std::endl;
	}
	return 0;
}
