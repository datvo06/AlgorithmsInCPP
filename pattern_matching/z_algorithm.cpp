#include <iostream>
#include <vector>
#include <numeric>


std::vector<int> calculateZ(std::string str){
	std::vector<int> Z(str.length(), 0);
	int left = 0;
	int right = 0;
	for (int k = 1; k < str.length(); k++){
		if (k > right){
			left = right = k;
			while(right < str.length() && str[right] == str[right -left]){
				right ++;
			}
			Z[k] = right - left;
			right--;
		}
		else {
			// We are operating inside box
			int k1 = k - left;
			// If value does not strestes till right bound then just copy it
			if (Z[k1] < right - k + 1){
				Z[k] = Z[k1];
			} else { // otherwise try to see if there are more matches
				left = k;
				while (right < str.length() && str[right] == str[right -left]){
					right ++;
				}
				Z[k] = right - left;
				right --;
			}
		}
	}
	return Z;
}

std::vector<int> match_pattern(std::string t, std::string p){
	auto idxs = std::vector<int>(t.size() + p.size() + 1, 0);
	std::string newS = p + '$' + t;
	std::vector<int> result;
	std::vector<int> Z = calculateZ(newS);
	for (size_t i = 0; i < Z.size(); i++){
		if (Z[i] == (int)p.length()){
			result.push_back(i - p.length() - 1);
		}
	}
	return result;
}

int main(int argc, char** argv){
	std::string text = "aaabcxyaaaabczaaczabbaaaaaabc";
	std::string pattern = "aaabc";
	std::cout << "Result: ";
	for(auto i: match_pattern(text, pattern)){
		std::cout << i << " ";
	}
	std::cout << std::endl;
	return 0;
}
