#include <iostream>
#include <algorithm>
#include <tuple>
#include <queue>
#include <cmath>
#include <iomanip>

using segment = std::tuple<double, size_t, size_t>;

double d(segment s) {
	return std::get<0>(s);
}
size_t i1(segment s) {
	return std::get<1>(s);
}
size_t i2(segment s) {
	return std::get<2>(s);
}

size_t n;
int16_t x[200];
int16_t y[200];
bool v[200];
bool m[200][200];
segment ls[40000];
segment answer[200];
double sum = 0;

double d(size_t i, size_t j) {
	return sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * ((y[i] - y[j])));
}

void reset_v() {
	for (size_t i = 0; i < n; i++) {
		v[i] = false;
	}
}

bool has_path(size_t i, size_t j) {
	std::queue<size_t> q;
	reset_v();
	q.push(i);
	while (!q.empty()) {
		size_t p = q.front();
		if (p == j) return true;
		q.pop();
		v[p] = true;
		for (size_t k = 0; k < n; k++) {
			if (v[k] || !m[p][k]) continue;
			q.push(k);
		}
	}
	return false;
}

void add(segment s, size_t ind) {
	m[i1(s)][i2(s)] = 1;
	m[i2(s)][i1(s)] = 1;
	answer[ind] = s;
	sum += d(s);
}

int main() {
	std::cin >> n;
	for (size_t i = 0; i < n; i++) {
		std::cin >> x[i] >> y[i];
	}
	size_t count = 0;
	for (size_t i = 0; i < n; i++) {
		for (size_t j = i + 1; j < n; j++) {
			ls[count] = { d(i, j), i, j};
			count++;
		}
	}
	std::sort(ls, ls + count);
	size_t c = 0;
	size_t index = 0;
	while (c < n - 1) {
		segment s = ls[index];
		if (!has_path(i1(s), i2(s))) {
			add(s, c);
			c++;
		}
		index++;
	}
	std::cout << std::fixed << std::setprecision(6) << sum << '\n';
	std::cout << c << '\n';
	for (size_t i = 0; i < c; i++) {
		segment s = answer[i];
		std::cout << (i1(s) + 1) << ' ' << (i2(s) + 1) << '\n';
	}
	return 0;
}