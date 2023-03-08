#include <iostream>
#include <vector>
#include <algorithm>

using floors = std::vector<std::pair<size_t, size_t>>;

size_t n, c, p, t;
floors fls;

floors copy(const floors& v) {
	floors r(v.size());
	std::copy(v.begin(), v.end(), r.begin());
	return r;
}

bool check(size_t count) {
	size_t sum = 0;
	floors fs;
	for (size_t i = 0; i < fls.size(); i++) {
		sum += fls[i].first;
		fs.push_back(fls[i]);
		std::cout << fls[i].second << " - " << sum << std::endl;
		if (sum >= count) break;
	}
	std::cout << "size: " << fs.size() << std::endl;
	size_t time = 0;
	int r = count;
	size_t amount = 0;
	int index = fs.size() - 1;
	while (index >= 0) {
		sum -= fs[index].first;
		fs[index].first += amount;
		amount = 0;
		std::cout << fs[index].second << " - " << fs[index].first << std::endl;
		size_t f = fs[index].second;
		size_t a = fs[index].first;
		size_t mc = std::floor((r - sum) / c) + 1;
		size_t ca = a / c;
		std::cout << "mc: " << mc << "; ca: " << ca << "; sum: " << sum << std::endl;
		size_t co = std::min(ca, mc);
		size_t pe = co * c;
		a -= pe;
		fs[index].first = a;
		std::cout << f << " - r: " << r << "; sum: " << sum << "; time: " << time << "co: " << co << std::endl;
		r -= pe;
		if (r <= 0) return time <= t;
		time += 2 * p * f * co;
		
		if (r < sum) {
			while (r > sum) {
				index--;
				std::cout << "index: " << index;
				if (index < 0) return time <= t;
				sum -= fs[index].first;
			}
		}
		else {
			amount += a;
			if (index >= 1) {
				time += 2 * p * (f - fs[index - 1].second);
			}
			index--;
		}
	}
	std::cout << "time: " << time << std::endl;
	return time <= t;
}

size_t binary_search(size_t left, size_t right) {
	while (right - left > 1) {
		size_t middle = (right + left) / 2;
		if (check(middle)) {
			left = middle;
		}
		else {
			right = middle;
		}
	}
	return left;
}

int main() {
	std::cin >> n >> c >> p >> t;
	size_t sum = 0;
	for (size_t i = 0; i < n; i++) {
		size_t a;
		std::cin >> a;
		sum += a;
		if (a > 0) {
			fls.push_back({a, i + 1});
		}
	}
	//std::cout << binary_search(0, sum);
	std::cout << check(5);
	return 0;
}