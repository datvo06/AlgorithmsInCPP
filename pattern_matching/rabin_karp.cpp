#include <iostream>
#include <vector>
#include <cmath>


int hash(std::string t){
	int result = 0;
	int prime = 3;
	int mult = 1;
	for (size_t i = 0; i < t.size(); i++){
		result += (mult * int(t[i]));
		mult *= prime;
	}
	return result;
}

int hashFromOld(int oldHash, int oldChar, int newChar, int prime, int mult){
	return (oldHash - oldChar)/prime + mult*newChar;
}

std::vector<int> matchingIdx(std::string t, std::string p){
	int m = p.size();
	int prime = 3;
	int maxMult = pow(prime, m-1);
	std::vector<int> results;
	int hashP = hash(p);
	std::cout << hashP << std::endl;
	int oldHash = 0;
	// O(mn)
	for (size_t i = 0; i <= t.size() - m; i++){
		if (i == 0) oldHash = hash(t.substr(i, m));
		else oldHash = hashFromOld(oldHash, int(t[i-1]), int(t[i+m-1]), prime, maxMult);
		if (oldHash == hashP)
			if (t.substr(i, m) == p) results.push_back(i);
	}
	return results;
}


int main(int argc, char** argv){
	std::cout << "result: ";
	// for (auto it: matchingIdx("abcgabcfxmxyz", "abc")){
	for (auto it: matchingIdx("abcabcfxmxyz", "abc")){
		std::cout << it << " ";
	}
	std::cout << std::endl;
	return 0;
}
