#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cmath>
#include <iomanip>

using t = uint16_t;
t h;
size_t n;
t xs[100];
t ys[100];
std::vector<size_t> paths[100];
double maxs[100];
double max = -1;

double start(size_t i) {
	return ys[i];
}

double end(size_t i) {
	return h - ys[i];
}

t diff(t a, t b) {
	if (a > b) return a - b;
	else return b - a;
}

bool closest(size_t i, size_t j) {
	return ys[i] >= ys[j];
}

double distance(size_t i, size_t j) {
	return sqrt(diff(xs[i], xs[j]) * diff(xs[i], xs[j]) + diff(ys[i], ys[j]) * diff(ys[i], ys[j]));
}

std::vector<size_t> copy(const std::vector<size_t>& v) {
	std::vector<size_t> res(v.size());
	std::copy(v.begin(), v.end(), res.begin());
	return res;
}

bool has(const std::vector<size_t>& v, size_t val) {
	return std::find(v.begin(), v.end(), val) != v.end();
}

void reset() {
	std::fill(paths, paths + n, std::vector<size_t>{});
	std::fill(maxs, maxs + n, -1);
}

void check(size_t index) {
	std::queue<size_t> q;
	q.push(index);
	reset();
	maxs[index] = start(index);
	paths[index] = { index };
	while (!q.empty()) {
		size_t v = q.front();
		double exit = std::max(maxs[v], end(v));
		if (exit < max || max < 0) {
			max = exit;
		}
		q.pop();
		for (size_t i = 0; i < n; i++) {
			if (has(paths[v], i)) continue;
			double d = distance(i, v);
			double m = std::max(maxs[v], d);
			if (m < maxs[i] || maxs[i] < 0) {
				maxs[i] = m;
				paths[i] = copy(paths[v]);
				paths[i].push_back(i);
				q.push(i);
			}
		}
	}
}

int main() {
	std::cin >> h >> n;
	for (size_t i = 0; i < n; i++) {
		std::cin >> xs[i] >> ys[i];
	}
	for (size_t i = 0; i < n; i++) {
		check(i);
	}
	std::cout << std::fixed << std::setprecision(6) << max;
	return 0;
}