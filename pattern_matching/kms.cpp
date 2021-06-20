#include <iostream>
#include <vector>

using std::string;
// Implementation of knuth-morris-pratt 
bool hasSubstr(string text, string pattern){
	size_t i = 0;
	size_t j = 0;
	int k = 0;
	while ( i < text.length() && j < pattern.length()){
		if (text[i] == pattern[j]){
			i++;
			j++;
		} else{
			// Rematch from begining
			j = 0;
			// Increase base by 1
			k++;
			i = k;
		}
	}
	if ( j == pattern.length()){
		return true;
	}
	return false;
}


std::vector<int> computeTemporaryArray(string pattern){
	std::vector<int> lps(pattern.length(), 0);
	int index = 0;
	for (int i = 1; i < pattern.length();){
		if (pattern[i] == pattern[index]){
			lps[i] = index + 1;
			index++;
			i++;
		} else {
			if (index != 0){
				index = lps[index-1];
			} else{
				lps[i] = 0;
				i++;
			}
		}
	}
	return lps;
}

bool kmp(string text, string pattern){
	auto lps = computeTemporaryArray(pattern);
	int i = 0;
	int j = 0;
	while ( i < text.length() && j < pattern.length()){
		if (text[i] == pattern[j]){
			i++;
			j++;
		} else{
			if (j != 0){
				j = lps[j-1];
			} else {
				i++;
			}
		}
	}
	if (j == pattern.length()){
		return true;
	}
	return false;
}

int main(int argc, char** argv){
	string str = "abcxabcdabcdabcy";
	string substr = "abcdabcy";
	std::cout << kmp(str, substr) << std::endl;
	return 0;
}
