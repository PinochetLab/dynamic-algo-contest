#include <iostream>
#include <algorithm>

size_t n;
int64_t s;
int64_t v[31];
int64_t k[10001];

int main() {
	std::cin >> n >> s;
	for (size_t i = 0; i < n; i++) {
		std::cin >> v[i];
	}
	std::sort(v, v + n, std::greater<int64_t>());
	int64_t c = 0;
	size_t i = 0;
	size_t ind = 0;
	while (c < s) {
		int64_t r = s - c;
		if (r / v[i] > 0) {
			c += v[i];
			k[ind] = v[i];
			ind++;
		}
		else {
			i++;
		}
	}
	std::cout << ind << '\n';
	for (size_t m = 0; m < ind; m++) {
		std::cout << k[m] << ' ';
	}
	return 0;
}