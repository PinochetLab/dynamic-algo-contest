#include <algorithm>
#include <iostream>
#include <string>


bool increment(std::string& s) {
    bool carry = 1;

    for (uint64_t i = 0; carry && i < s.size(); ++i) {
        s[i] = (s[i] - 'a' + 1) % 4 + 'a';
        carry = s[i] == 'a';
    }

    return carry;
}

bool check(std::string s, uint64_t L) {
    uint64_t c = 0;
    char cc = '\0';

    for (uint64_t i = 0; i < s.size(); ++i) {
        if (s[i] == cc) {
            ++c;
        }
        else {
            cc = s[i];
            c = 1;
        }

        if (c == L) {
            s.erase(i - L + 1, L);

            c = 0;
            cc = '\0';
            i = -1;
        }
    }

    return s.empty();
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint64_t L, N;
    std::cin >> L >> N;

    uint64_t c = 0;
    uint64_t c2 = 0;
    std::string s(N, 'a');
    do {
        if (check(s, L)) {
            std::cerr << s << '\n';
            if (s[0] != 'a' && s[s.length() - 1] != 'a') {
                c2++;
            }
            ++c;
            c %= 1000000007;
        }
    } while (!increment(s));

    std::cout << c << ' ' << c2 << '\n';;
}
