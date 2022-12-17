#include <iostream>
#include <set>

#define POINTS_LEN 5
#define ROCKS_LIMIT_PART1 2022
#define ROCKS_LIMIT_PART2 1000000000000
#define CHAMBER_WIDTH 7

typedef long long ll;
struct point {
    ll x;
    ll y;
};
inline point operator+(const point& l, const point &r) {
    return { .x = l.x + r.x, .y = l.y + r.y };
}
inline bool operator<(const point& l, const point& r)
{
    return l.x < r.x || ((l.x == r.x) && (l.y < r.y));
}
inline bool operator==(const point& l, const point& r)
{
    return l.x == r.x && l.y == r.y;
}

void iterate(const std::set<point> *points, const std::string &pattern, std::set<point> &occupied_pt1, ll *time,
             ll fallen_rocks) {
    ll max_y = -1;
    for (auto p : occupied_pt1) { if (p.y > max_y) max_y = p.y; };
    point pos = {2, max_y + 4};
    std::__1::set<point> current_rock = points[fallen_rocks % POINTS_LEN];

    while (true) {
        point offset = {};
        if (pattern[*time % pattern.size()] == '>') {
            offset = {1, 0};
        } else if (pattern[*time % pattern.size()] == '<'){
            offset = {-1, 0};
        } else { std::cerr << "unknown direction"<<std::endl;exit(1); }
        ++(*time);


        // shift to the side
        bool move = true;
        for (auto p : current_rock) {
            point np = pos + offset + p;
            if (np.x >= CHAMBER_WIDTH || np.x < 0 || occupied_pt1.count(np) > 0) {
                move = false;
                break;
            }
        }
        if (move) {
            pos = pos + offset;
        }

        offset = {0, -1};
        move = true;
        for (auto p : current_rock) {
            point np = pos + offset + p;
            if (np.y < 0 || occupied_pt1.count(np) > 0) {
                move = false;
                break;
            }
        }
        if (move) {
            pos = pos + offset;
        } else {
            for (auto p : current_rock) {
                point np = pos + p;
                occupied_pt1.insert(np);
            }
            break;
        }
    }
}

int main() {
    std::set<point> points[POINTS_LEN] = {
            {{0, 0 }, {1, 0}, {2, 0}, {3, 0}},
            {{1, 2}, {0, 1}, {1, 1}, {2, 1}, {1, 0}},
            {{2, 2}, {2, 1}, {0, 0}, {1, 0}, {2, 0}},
            {{0, 3}, {0, 2}, {0, 1}, {0, 0}},
            {{0, 1}, {1, 1}, {0, 0}, {1, 0}},
    };
    std::string pattern;
    std::cin >> pattern;
    std::set<point> occupied_pt1;
    std::set<point> occupied_pt2;
    ll time = 0;
    ll fallen_rocks = 0;

    for (;fallen_rocks < ROCKS_LIMIT_PART1; fallen_rocks++) {
        iterate(points, pattern, occupied_pt1, &time, fallen_rocks);
    }

    ll top_pt1 = 0;
    for (auto p : occupied_pt1) { if (p.y > top_pt1) { top_pt1 = p.y; }}
    std::cout << "part 1: " << top_pt1 + 1 << std::endl;
    return 0;
}
