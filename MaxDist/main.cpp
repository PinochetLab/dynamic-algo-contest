#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

size_t n, m;
uint16_t d[22];
bool dis[22];
bool w[22][22];
std::vector<size_t> ps[22];

uint16_t distance = 0;
bool ds = false;
std::vector<size_t> answer;

std::vector<size_t> copy(const std::vector<size_t>& v) {
	std::vector<size_t> res(v.size());
	std::copy(v.begin(), v.end(), res.begin());
	return res;
}

bool has(const std::vector<size_t>& v, size_t a) {
	return std::find(v.begin(), v.end(), a) != v.end();
}

void count(size_t j) {
	std::queue<size_t> q;
	for (size_t i = 0; i < n; i++) {
		d[i] = 0;
		dis[i] = false;
		ps[i] = {};
	}
	q.push(j);
	ps[j] = { j };
	dis[j] = true;
	while (!q.empty()) {
		size_t p = q.front();
		if (d[p] > distance || !ds) {
			distance = d[p];
			answer = copy(ps[p]);
			ds = true;
		}
		q.pop();
		for (size_t i = 0; i < n; i++) {
			if (i == j || w[p][i] == 0 || has(ps[p], i)) continue;
			uint16_t dist = d[p] + 1;
			if (dist > d[i] || !dis[i]) {
				dis[i] = true;
				d[i] = dist;
				ps[i] = copy(ps[p]);
				ps[i].push_back(i);
				q.push(i);
			}
		}
	}
}

int main() {
	std::cin >> n >> m;
	for (size_t i = 0; i < m; i++) {
		size_t u, v;
		std::cin >> u >> v;
		if (u == v) {
			continue;
		}
		w[u - 1][v - 1] = true;
	}

	for (size_t i = 0; i < n; i++) {
		count(i);
	}
	std::cout << distance << '\n';
	for (size_t i = 0; i < answer.size(); i++) {
		std::cout << (answer[i] + 1) << ' ';
	}
	return 0;
}