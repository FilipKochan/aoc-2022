#include <iostream>
#include <set>
#include <vector>

typedef long long ll;
struct point {
    ll x;
    ll y;
    ll z;
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
bool traverse(point current, std::set<point> *traversed, std::set<point> *points,
              ll minx, ll miny, ll minz, ll maxx, ll maxy, ll maxz);
int main() {
    ll x, y, z, minx = LLONG_MAX, miny = LLONG_MAX, minz = LLONG_MAX, maxx = LLONG_MIN, maxy = LLONG_MIN, maxz = LLONG_MIN;

    ll surface = 0;
    std::set<point> points;
    std::vector<point> possible;
    while (scanf("%llu,%llu,%llu\n", &x, &y, &z) == 3) {
        minx = std::min(minx, x); miny = std::min(miny, y); minz = std::min(minz, z);
        maxx = std::max(maxx, x); maxy = std::max(maxy, y); maxz = std::max(maxz, z);

        point current = {x, y, z};
        current.generate_possible(&possible);
        ll touching = 0;
        for (auto p : possible) { touching += (ll)points.count(p); }
        surface += 6 - touching * 2;
        points.insert(current);
        possible.clear();
    }
    std::cout << "part 1: " << surface << std::endl;

    std::set<point> visited;
    std::vector<point> gaps;
    std::set<point> traversed;
    for (ll i = minx + 1; i < maxx; i++) {
        for (ll j = miny + 1; j < maxy; j++) {
            for (ll k = minz + 1; k < maxz; k++) {
                point current = {i, j, k};
                if (visited.count(current) || points.count(current)) {
                    continue;
                }
                bool res = traverse(current, &traversed, &points, minx, miny, minz, maxx, maxy, maxz);
                for (auto  pp : traversed) {
                    if (res) { gaps.push_back(pp); }
                    visited.insert(pp);
                }
                traversed.clear();
            }
        }
    }

    for (auto current : gaps) {
        current.generate_possible(&possible);
        ll touching = 0;
        for (auto p : possible) {
            touching += (ll)points.count(p);
        }
        surface += 6 - touching * 2;
        points.insert(current);
        possible.clear();
    }

    std::cout << "part 2: " << surface << std::endl;
    return 0;
}


bool
traverse(point current, std::set<point> *traversed, std::set<point> *points, ll minx, ll miny,
         ll minz, ll maxx, ll maxy, ll maxz) {
    if (traversed->count(current) || points->count(current)) {
        return true;
    }
    if (current.x <= minx || current.x >= maxx || current.y <= miny ||
        current.y >= maxy || current.z <= minz || current.z >= maxz) {
        return false;
    }
    traversed->insert(current);
    std::vector<point> options = {};
    current.generate_possible(&options);
    return std::all_of(options.begin(), options.end(),
                       [&traversed, &points, &minx, &miny, &minz, &maxx, &maxy, &maxz] (point p) {
        return traverse(p, traversed, points, minx, miny, minz, maxx, maxy, maxz);
    });
}
