#include <tuple>
#include <queue>
#include <vector>
#include <algorithm>
#include <iostream>


using fr_v = int64_t;
using fr = std::tuple<fr_v, fr_v, size_t>;

fr_v getA(fr v) {
	return std::get<0>(v);
}

fr_v getB(fr v) {
	return std::get<1>(v);
}

size_t getI(fr v) {
	return std::get<2>(v);
}

size_t n;
fr_v val;
fr friends[100001];

int main() {
	std::cin >> n >> val;
	size_t m = 0;
	size_t s = 0;
	for (size_t i = 0; i < n; i++) {
		fr_v a, b;
		std::cin >> a >> b;
		fr fr = { a, b, i + 1 };
		if (b >= 0) {
			friends[m] = fr;
			m++;
		}
		else {
			friends[n - 1 - s] = fr;
			s++;
		}
	}

	auto compare1 = [&](fr f1, fr f2) -> bool {return getB(f1) + getA(f1) > getB(f2) + getA(f2);};
	auto compare2 = [&](fr f1, fr f2) -> bool {return getB(f1) > getB(f2);};
	std::priority_queue < fr, std::vector<fr>, decltype(compare2) > q(compare2);

	std::sort(friends, friends + m);
	std::sort(friends + m, friends + n, compare1);

	std::vector<fr> res;
	for (size_t i = 0; i < m; i++) {
		if (val >= getA(friends[i])) {
			res.push_back(friends[i]);
			val += getB(friends[i]);
		}
		else {
			break;
		}
	}
	size_t r = res.size();
	for (size_t i = m; i < n; i++) {
		fr f = friends[i];
		auto a = getA(f);
		q.push(f);
		if (a > val) {
			fr l = q.top();
			val -= getB(l);
			q.pop();
		}
		val += getB(f);
	}
	while (!q.empty()) {
		fr f = q.top();
		res.push_back(f);
		q.pop();
	}
	std::sort(res.begin() + r, res.end(), compare1);
	std::cout << res.size() << '\n';
	for (fr f : res) {
		std::cout << getI(f) << ' ';
	}
	return 0;
}