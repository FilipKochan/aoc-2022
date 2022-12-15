#include <iostream>
#include <set>
#include <vector>

//#define DEBUG
//#define SAMPLE_INPUT
#define TARGET_Y 2000000
#define BEACON_X_MIN 0
#define BEACON_Y_MIN 0
#define BEACON_X_MAX 4000000
#define BEACON_Y_MAX 4000000
#define FREQUENCY_COEF 4000000

#ifdef SAMPLE_INPUT
#define TARGET_Y 10
#define BEACON_X_MAX 20
#define BEACON_Y_MAX 20
#endif

typedef long long ll;

struct point {
    ll x;
    ll y;

    ll manhattan_dist(point other) const {
        return std::abs(x - other.x) + std::abs(y - other.y);
    }
};

inline bool operator<(const point& l, const point& r)
{
    return l.x < r.x || ((l.x == r.x) && (l.y < r.y));
}

int main() {
    point s = { }, b = { };
    std::set<point> occupied;
    std::vector<std::tuple<point, point>> sensors;

    while (scanf("Sensor at x=%lli, y=%lli: closest beacon is at x=%lli, y=%lli\n", &s.x, &s.y, &b.x, &b.y) == 4) {
#ifdef DEBUG
        std::cout << "[" << s.x << ", " << s.y << "] -> [" << b.x << ", " << b.y << "]" << std::endl;
#endif
        ll d = s.manhattan_dist(b);
        ll d_to_target = 0;
        if ((d_to_target = std::abs(s.y - TARGET_Y)) <= d) {
            for (ll i = -(d - d_to_target); i <= (d - d_to_target); i++) {
                if (s.x + i == b.x && TARGET_Y == b.y) {
                    continue;
                }
                occupied.insert({ s.x + i, TARGET_Y });
            }
        }
        std::tuple<point, point> row = std::make_tuple(s, b);
        sensors.push_back(row);
    }

    std::cout << "part 1: " << occupied.size() << std::endl;
    occupied.clear();
    for (auto t : sensors) {
        s = std::get<0>(t);
        b = std::get<1>(t);
        ll d = b.manhattan_dist(s);
        for (ll i = -d - 1; i <= d + 1; i++) {
            ll off = d + 1 - std::abs(i);
            point p1 = {s.x + i, s.y + off};
            point p2 = {s.x + i, s.y - off};

            if (BEACON_X_MIN <= p1.x && p1.x <= BEACON_X_MAX) {
                bool is_solution_plus_off = true;
                bool is_solution_minus_off = true;

                for (auto tt : sensors) {
                    point ss = std::get<0>(tt);
                    point bb = std::get<1>(tt);

                    if (ss.manhattan_dist(p1) <= ss.manhattan_dist(bb)) {
                        is_solution_plus_off = false;
                    }

                    if (ss.manhattan_dist(p2) <= ss.manhattan_dist(bb)) {
                        is_solution_minus_off = false;
                    }
                }


                if (is_solution_plus_off && BEACON_Y_MIN <= p1.y && p1.y <= BEACON_Y_MAX) {
                    std::cout << "part 2: " << p1.x * FREQUENCY_COEF + p1.y << std::endl;
                    return 0;
                }

                if (is_solution_minus_off && BEACON_Y_MIN <= p2.y && p2.y <= BEACON_Y_MAX) {
                    std::cout << "part 2: " << p2.x * FREQUENCY_COEF + p2.y << std::endl;
                    return 0;
                }
            }
        }
    }

    return 1;
}
