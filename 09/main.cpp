#include <iostream>
#include <set>

#define PIECES 10

struct ps {
     int x;
     int y;

     int dist(ps other) const {
         return xdist(other) + ydist(other);
     }
     bool is_diag(ps other) const {
         return xdist(other) == 1 && ydist(other) == 1;
     }
     int xdist(ps other) const {
         return std::abs(x - other.x);
     }
     int ydist(ps other) const {
         return std::abs(y - other.y);
     }
};

inline bool operator<(const ps& l, const ps& r)
{
    return l.x < r.x || ((l.x == r.x) && (l.y < r.y));
}

int main() {
    char d;
    int off;

    std::set<ps> p;
    std::set<ps> p2;

    ps hpos = { 0, 0 };
    ps tpos = { 0, 0 };

    p.insert(tpos);
    p2.insert(tpos);

    ps tails[PIECES];

    for (auto & tail : tails) {
        tail = { 0, 0 };
    }

    while (scanf("%c %d\n", &d, &off) > 0) {
        int dir = 1;
        switch (d) {
            case 'R':
                hpos.x += off;
                tails[0].x += off;
                break;
            case 'D':
                hpos.y -= off;
                tails[0].y -= off;
                dir = -1;
                break;
            case 'L':
                hpos.x -= off;
                tails[0].x -= off;
                dir = -1;
                break;
            case 'U':
                hpos.y += off;
                tails[0].y += off;
                break;
            default:
                std::cerr << "unknown direction" << std::endl;
                exit(1);
        }

        if (tpos.dist(hpos) <= 1 || tpos.is_diag(hpos)) {
            p.insert(tpos);
        } else if (tpos.dist(hpos) >= 2) {
            if (tpos.xdist(hpos) == 1 || tpos.xdist(hpos) == 0) {
                tpos.x = hpos.x;

                while (tpos.dist(hpos) > 1) {
                    tpos.y += dir;
                    p.insert(tpos);
                }

            } else if (tpos.ydist(hpos) == 1 || tpos.ydist(hpos) == 0){
                tpos.y = hpos.y;
                while (tpos.dist(hpos) > 1) {
                    tpos.x += dir;
                    p.insert(tpos);
                }
            }
            else {
                std::cerr << "unreachable position" << std::endl;
                exit(1);
            }
        }
    }

    std::cout << "part 1: " << p.size() << "\npart 2: " << p2.size() << std::endl;
    return 0;
}
