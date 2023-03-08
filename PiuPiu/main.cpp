#include <iostream>
#include <vector>

uint64_t a[1001];
uint64_t b[1001][1001];
uint64_t mod = 1000000007;
uint64_t n;
uint64_t l;

int main() {
	std::cin >> l >> n;
	if (n % l != 0) {
		std::cout << '0';
		return 0;
	}
	size_t k = n / l;
	a[0] = 1;
	for (size_t i = 0; i < l; i++) {
		b[0][i] = 1;
	}
	for (size_t i = 1; i <= k; i++) {
		b[i][1] = 0;
		for (size_t j = 1; j <= i; j++) {
			b[i][1] = (b[i][1] + 3 * b[j - 1][1] * b[i - j][1]) % mod;
		}
	}
	for (size_t i = 1; i < l; i++) {
		for (size_t j = 2; j <= k; j++) {
			b[i][j] = 0;
			for (size_t s = 0; s <= i; s++) {
				b[i][j] = (b[i][j] + b[s][1] * b[i - s][j]) % mod;
			}
		}
	}
	for (size_t i = 0; i <= k; i++) {
		for (size_t j = 1; j < l; j++) {
			std::cout << i << " " << j << " - " << b[i][j]  << std::endl;
		}
	}
	for (size_t i = 2; i <= k; i++) {
		for (size_t j = 1; j <= i; j++) {
			a[i] = (a[i] + 4 * b[j - 1][l - 1] * a[i - j]) % mod;
			b[i][1] = (b[i][1] + 3 * b[j - 1][l - 1] * b[i - j][1]) % mod;
		}
	}
	std::cout << a[k];
}