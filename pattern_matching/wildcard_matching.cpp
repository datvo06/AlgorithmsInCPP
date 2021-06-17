#include <iostream>
#include <vector>

bool isMatch(std::string s, std::string p){
	std::vector<std::vector<bool>> trackingTable(s.size(), std::vector<bool>(p.size(), false));
	for (size_t is = 0; is < s.size(); is++){
		for (size_t ip = 0; ip < p.size(); ip++){
			if (p[ip] == '?' || s[is] == p[ip]){
				if (is == 0 || ip == 0) trackingTable[is][ip] = true;
				else trackingTable[is][ip] = trackingTable[is-1][ip-1];
			}
			else if (p[ip] == '*'){
				if (is == 0 || ip ==0) trackingTable[is][ip] = true;
				else  trackingTable[is][ip] = trackingTable[is-1][ip] || trackingTable[is][ip-1];
			}
			else trackingTable[is][ip] = false;
		}
	}
	return trackingTable.back().back();
}

int main(int argc, char ** argv){
	std::string str = "xaylmz";
	std::string p = "x?y*z";
	std::cout << isMatch(str, p) << std::endl;
	// TODO: *** -> *: Normalization
	return 0;
}
