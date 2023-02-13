#include <iostream>
#include <map>
#include <algorithm>

template<typename A, typename B>
std::pair<B, A> flip_pair(const std::pair<A, B>& p)
{
	return std::pair<B, A>(p.second, p.first);
}

template<typename A, typename B>
std::multimap<B, A> flip_map(const std::map<A, B>& src)
{
	std::multimap<B, A> dst;
	std::transform(src.begin(), src.end(), std::inserter(dst, dst.begin()),
		flip_pair<A, B>);
	return dst;
}



int main()
{

	std::string s = "Hello world!!";
	//std::cin >> s;
	std::map<char, int> m;
	for (char const& c : s) {
		if (m.find(c) == m.end()) {
			m[c] = 1;
		}
		else {
			m[c]++;
		}
	}

	std::multimap<int, char> rm = flip_map(m);

	for (auto iter = rm.rbegin(); iter != rm.rend(); ++iter) {
		std::cout << iter->second << ": " << iter->first << std::endl;
	}


	return 0;
}
