#include <iostream>
#include <vector>
#include <algorithm>

void allQueens(int rows, int cols, std::vector<int>& prevCols){
	if ((int)prevCols.size() == rows){
			std::cout << "found result: " << std::endl;
			for (int queen = 0; queen < cols; queen++){
				std::cout << "(" << queen << ", " << prevCols[queen] << "), ";
			}
			std::cout << std::endl;
	}
	for (int c = 0; c < cols; c++){
		int r = (int) prevCols.size();
		if (std::find(prevCols.begin(), prevCols.end(), c) != prevCols.end()){
			continue;
		}
		bool found = true;
		for (int queen = 0; queen < (int) prevCols.size(); queen++){
			if ((r + c) == (queen + prevCols[queen]) || r - c == queen - prevCols[queen]){
				found = false;
				break;
			}
		}
		if (!found) continue;
		prevCols.push_back(c);
		allQueens(rows, cols, prevCols);
		prevCols.pop_back();
	}
}


int main(int argc, char** argv){
	int rows = 4;
	int cols = 4;
	std::vector<int> results;
	allQueens(rows, cols, results);
	return 0;
}
