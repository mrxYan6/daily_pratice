//
// Created by mrx on 2022/6/3.
//
//template
#include <cstdio>

namespace Maker {

    typedef unsigned int uit;

    bool __sp;
    uit __x, __y, __z;
    int __type, __k, __m;

    const int L = 1 << 21;
    char buf[L], *front = buf, *end = buf;

    char GetChar() {
        if (front == end) {
            end = buf + fread(front = buf, 1, L, stdin);
            if (front == end) return -1;
        }
        return *(front++);
    }

    template<typename T>
    inline void qr(T &x) {
        char ch = GetChar(), lst = ' ';
        while ((ch > '9') || (ch < '0')) lst = ch, ch = GetChar();
        while ((ch >= '0') && (ch <= '9')) x = (x << 1) + (x << 3) + (ch ^ 48), ch = GetChar();
        if (lst == '-') x = -x;
    }

    template<typename T>
    inline void Begin(const T &x) {
        __type = x % 10;
        qr(__x);
        qr(__y);
        qr(__z);
        qr(__m);
        __sp = (__type == 3) || (__type == 4);
        __type &= 1;
    }

    inline uit __Next_Integer() {
        __x ^= __y << (__z & 31);
        __y ^= __z >> (__x & 31);
        __z ^= __x << (__y & 31);
        __x ^= __x >> 5;
        __y ^= __y << 13;
        __z ^= __z >> 6;
        return __x;
    }

    inline uit Rand() { return __Next_Integer(); }

    template<typename Tx, typename Ty, typename Tz>
    inline void Get_Nextline(Tx &x, Ty &y, Tz &z) {
        if (__m) {
            --__m;
            x = 0;
            y = 0;
            z = 0;
            qr(x);
            qr(y);
            qr(z);
            if (x == 0) ++__k;
        } else {
            x = Rand() & 1;
            y = Rand() & 1;
            if (__k == 0) { x = 0; }
            if (x == 0) {
                ++__k;
                if (__sp) {
                    z = __type;
                } else {
                    z = Rand() & 1;
                }
            } else {
                int dk = __k >> 1;
                if (dk == 0) {
                    z = 1;
                } else {
                    z = Rand() % dk + dk;
                }
            }
        }
    }

}

int n;
const int INF = 0x3f3f3f3f;
struct nod {
    int l = INF, r = INF;
    bool now;
};

#include "deque"

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    scanf("%d", &n);
    Maker::Begin(n);
    long long ch[4] = {0};
    std::deque<nod> q;
    int id = 1;
    for (int x, y, z; n; --n) {
        Maker::Get_Nextline(x, y, z);
        int ans = -1;
        if (x == 0) {
            if (y == 0) {
                if (z == 0) {
                    for (int i = 0; i < q.size(); ++i) {
                        q[i].l = i + 1;
                        if (q[i].now == 0)break;
                    }
                    q.push_front({0, 0, 0});
                } else {
                    q.push_front({INF, std::min(INF, q.front().r + 1), 1});
                }
            } else {
                if (z == 0) {
                    int len = q.size();
                    for (int i = 1; i <= len; ++i) {
                        q[len - i].l = i;
                        if (q[len - i].now == 0)break;
                    }
                    q.push_back({0, 0, 0});
                } else {
                    q.push_back({std::min(INF, q.front().l + 1), INF, 1});
                }
            }
        } else {
            if (y == 0) {
                if (z == 1) {
                    ans = q[0].now;
                } else {
                    if (q[z - 1].r != INF)
                        ans = (q[z - 1].l + 1) % 2;
                    else ans = (z) % 2;
                }
            } else {
                if (z == 1) {
                    ans = q.back().now;
                } else {
                    if (q[q.size() - z + 1].r != INF)
                        ans = (q[q.size() - z + 1].r + 1) % 2;
                    else ans = (z) % 2;
                }
            }
            if (ans == 1)ch[0]++;
            if (ans == 0 && id & 1)ch[1]++;
            if (ans == 1 && id % 2 == 0)ch[2]++;
            if (ans == 0 && id % 1024 == 0)ch[3]++;
        }
        id++;
    }
    printf("%d %d %d %d\n", ch[0], ch[1], ch[2], ch[3]);
    //print your ans here
    return 0;
}
