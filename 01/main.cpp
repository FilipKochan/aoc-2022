#include <iostream>
#include <cstdlib>
#include <vector>

typedef long long int ll;
int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "usage: " << argv[0] << " <1 | 2>" << std::endl;
        return 1;
    }
    std::string w;
    ll cur = 0;
    ll max_c = 0;
    ll c = 1;
    std::vector<ll> cals = {};
    for (std::string l; std::getline(std::cin, l);){
        if (l.empty()) {
            max_c = std::max(cur, max_c);
            cals.push_back(cur);
            c++;
            cur = 0;
        } else {
            char *end;
            cur += strtoll(&(l[0]), &end, 10);
        }
    }
    max_c = std::max(cur, max_c);
    cals.push_back(cur);

    if (strcmp(argv[1], "1") == 0) {
        std::cout << max_c << std::endl;
    } else {
        std::sort(cals.begin(), cals.end());
        std::cout << (cals[c - 1] + cals[c - 2] + cals[c - 3]) << std::endl;
    }

    return 0;
}
