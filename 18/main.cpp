#include <iostream>
#include <set>
#include <vector>

typedef long long ll;
struct point {
    ll x;
    ll y;
    ll z;

    bool touches(point other) const {
        return (std::abs(x + other.x) + std::abs(y + other.y) + std::abs(z + other.z)) == 1;
    }

    void generate_possible(std::vector<point> *res) {
        res->push_back({x + 1, y, z});
        res->push_back({x - 1, y, z});
        res->push_back({x, y + 1, z});
        res->push_back({x, y - 1, z});
        res->push_back({x, y, z + 1});
        res->push_back({x, y, z - 1});
    }
};

inline bool operator<(const point& l, const point& r)
{
    return l.x < r.x || ((l.x == r.x) && (l.y < r.y)) || ((l.x == r.x) && (l.y == r.y) && l.z < r.z);
}

int main() {
    ll x, y, z;
    ll surface = 0;
    std::set<point> points;
    std::vector<point> possible;
    while (scanf("%llu,%llu,%llu\n", &x, &y, &z) == 3) {
        point current = {x, y, z};
        current.generate_possible(&possible);
        ll touching = 0;
        for (auto p : possible) {
            touching += points.count(p);
        }
        surface += 6 - touching * 2;
        points.insert(current);
        possible.clear();
    }

    std::cout << "part 1: " << surface << std::endl;
    return 0;
}
