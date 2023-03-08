#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <tuple>

using i = uint64_t;
using p = std::tuple<i, i, size_t>;

size_t n;
p ps[100001];
i s;

int main() {
	i sum = 0;
	std::cin >> n;
	for (size_t j = 0; j < n; j++) {
		i h, l;
		std::cin >> h >> l;
		ps[j] = { h, l, j + 1 };
		sum += h;
	}
	std::cin >> s;
	auto comp = [](p p1, p p2) -> bool { return std::get<0>(p1) + std::get<1>(p1) < std::get<0>(p2) + std::get<1>(p2); };
	auto q_comp = [](p p1, p p2) -> bool { return std::get<0>(p1) < std::get<0>(p2); };
	std::sort(ps, ps + n, comp);
	std::priority_queue < p, std::vector<p>, decltype(q_comp)> q(q_comp);
	i height = 0;
	for (size_t j = 0; j < n; j++) {
		i h = std::get<0>(ps[j]);
		i l = std::get<1>(ps[j]);
		if (q.empty()) {
			if (sum + l >= s) {
				q.push(ps[j]);
				sum -= h;
			}
		}else if (sum + l < s) {
			i h2 = std::get<0>(q.top());
			if (h2 > h) {
				sum += h2;
				q.pop();
				q.push(ps[j]);
				sum -= h;
			}
		}
		else {
			sum -= h;
			q.push(ps[j]);
		}
	}
	if (q.empty()) {
		std::cout << 0 << '\n';
		return 0;
	}
	size_t index = 0;
	while (!q.empty()) {
		ps[index] = q.top();
		q.pop();
		index++;
	}
	std::sort(ps, ps + index, comp);
	std::cout << index << '\n';
	for (size_t j = 0; j < index; j++) {
		std::cout << std::get<2>(ps[j]) << ' ';
	}
	return 0;
}