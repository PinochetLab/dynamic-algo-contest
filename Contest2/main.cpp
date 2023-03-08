#include <iostream>
#include <algorithm>
#include <vector>

size_t n;

struct Dwarf {
	size_t index;
	size_t a;
	size_t b;
};

int main() {
	std::cin >> n;
	std::vector<size_t> as = {};
	size_t sum = 0;
	for (size_t i = 0; i < n; i++) {
		size_t a;
		std::cin >> a;
		as.push_back(a);
		sum += a;
	}
	std::vector<size_t> bs = {};
	for (size_t i = 0; i < n; i++) {
		size_t b;
		std::cin >> b;
		bs.push_back(b);
	}
	std::vector<Dwarf> ds = {};
	for (size_t i = 0; i < n; i++) {
		ds.push_back({ i + 1, as[i], bs[i] });
	}
	std::sort(ds.begin(), ds.end(), [](Dwarf d1, Dwarf d2) -> bool {return d1.a + d1.b > d2.a + d2.b; });
	if (ds[0].a + ds[0].b > sum) {
		for (size_t i = 0; i < n; i++) {
			std::cout << ds[i].index << ' ';
		}
	}
	else {
		std::cout << "-1";
	}
}