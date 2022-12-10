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

    p.insert({0, 0});
    p2.insert({ 0, 0});

    ps tails[PIECES];

    for (auto & tail : tails) {
        tail = { 0, 0 };
    }

    while (scanf("%c %d\n", &d, &off) > 0) {
        int xoff = 0, yoff = 0;
        switch (d) {
            case 'R':
                xoff = 1;
                break;
            case 'D':
                yoff = -1;
                break;
            case 'L':
                xoff = -1;
                break;
            case 'U':
                yoff = 1;
                break;
            default:
                std::cerr << "unknown direction" << std::endl;
                exit(1);
        }

        off = std::abs(off);
        while (off--) {
            tails[0].x += xoff;
            tails[0].y += yoff;
            
            for (int i = 1; i < PIECES; i++) {
                ps *h = tails + i - 1;
                ps *t = tails + i;

                if (t->dist(*h) <= 1 || t->is_diag(*h)) {
                    if (i == 1){
                        p.insert(*t);
                    } else if (i + 1 == PIECES) {
                        p2.insert(*t);
                    }
                } else if (t->dist(*h) >= 2) {
                    if (t->xdist(*h) == 1 || t->xdist(*h) == 0) {
                        t->x = h->x;

                        int dir = 1;
                        if (t->y > h->y) {
                            dir = -1;
                        }
                        while (t->dist(*h) > 1) {
                            t->y += dir;
                            if (i == 1){
                                p.insert(*t);
                            } else if (i + 1 == PIECES) {
                                p2.insert(*t);
                            }
                        }

                    } else if (t->ydist(*h) == 1 || t->ydist(*h) == 0){
                        t->y = h->y;
                        int dir = 1;
                        if (t->x > h->x) {
                            dir = -1;
                        }
                        while (t->dist(*h) > 1) {
                            t->x += dir;
                            if (i == 1){
                                p.insert(*t);
                            } else if (i + 1 == PIECES) {
                                p2.insert(*t);
                            }
                        }
                    }
                    else if (t->xdist(*h) == t->ydist(*h)) {
                        int xdiff, ydiff;
                        if (h->x - t->x > 0) { xdiff = 1; } else { xdiff = -1;}
                        if (h->y - t->y > 0) { ydiff = 1; } else { ydiff = -1;}

                        while (!t->is_diag(*h)) {
                            t->x += xdiff;
                            t->y += ydiff;
                            if (i == 1){
                                p.insert(*t);
                            } else if (i + 1 == PIECES) {
                                p2.insert(*t);
                            }
                        }
                    } else {
                        std::cerr << "unreachable position" << std::endl;
                        exit(1);
                    }
                }
            }
        }
    }

    std::cout << "part 1: " << p.size() << "\npart 2: " << p2.size() << std::endl;
    return 0;
}
