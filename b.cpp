// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx")
// #pragma GCC optimize("unroll-loops")

#include "bits/stdc++.h"
#include "ext/pb_ds/assoc_container.hpp"
#include "ext/pb_ds/tree_policy.hpp"
//#include <ext/rope>

using namespace __gnu_pbds;
// using namespace __gnu_cxx;
using namespace std;

using ll = long long;

// #define int long long
#define unordered_map gp_hash_table
#define cauto const auto

template <typename T>
void ignore_unused(const T &) {}
#ifdef DEBUG
#define debug(args...)                               \
    {                                                \
        std::string _s = #args;                      \
        replace(_s.begin(), _s.end(), ',', ' ');     \
        std::stringstream _ss(_s);                   \
        std::istream_iterator<std::string> _it(_ss); \
        err(_it, args);                              \
    }
#define print_container(v)          \
    {                               \
        bool first = true;          \
        os << "[";                  \
        for (auto x : v) {          \
            if (!first) os << ", "; \
            os << x;                \
            first = false;          \
        }                           \
        return os << "]";           \
    }
void err(std::istream_iterator<std::string> it) { ignore_unused(it); }
template <typename T, typename... Args>
void err(std::istream_iterator<std::string> it, T a, Args... args) {
    std::cerr << *it << " = " << a << std::endl;
    err(++it, args...);
}

// clang-format off

template <typename T1, typename T2> inline std::ostream& operator << (std::ostream& os, const std::pair<T1, T2>& p) { return os << "(" << p.first << ", " << p.second << ")"; }
template <typename T> inline std::ostream &operator << (std::ostream & os, const std::vector<T>& v) { print_container(v); }
template <typename T> inline std::ostream &operator << (std::ostream & os, const std::set<T>& v) { print_container(v); }
template <typename T1, typename T2> inline std::ostream &operator << (std::ostream & os, const std::map<T1, T2>& v) { print_container(v); }
template <typename T1, typename T2, class C> inline std::ostream &operator << (std::ostream & os, const unordered_map<T1, T2, C>& v) { print_container(v); }
template <typename T, class C> inline std::ostream &operator << (std::ostream & os, const unordered_set<T, C>& v) { print_container(v); }
template <typename T1, typename T2> inline std::ostream &operator << (std::ostream & os, const std::multimap<T1, T2>& v) { print_container(v); }
template <typename T> inline std::ostream &operator << (std::ostream & os, const std::multiset<T>& v) { print_container(v); }
#else
#define debug(args...) 0
#endif

template <typename X, typename Y> X &remin(X &x, const Y &y) { return x = (y < x) ? y : x; }
template <typename X, typename Y> X &remax(X &x, const Y &y) { return x = (x < y) ? y : x; }
template <typename X, typename Y> [[nodiscard]] bool ckmin(X &x, const Y &y) { return (y < x) ? (x = y, 1) : 0; }
template <typename X, typename Y> [[nodiscard]] bool ckmax(X &x, const Y &y) { return (x < y) ? (x = y, 1) : 0; }
template <typename T> inline T sq(T a) { return a * a; }
template <typename T> inline T sq_dist(pair<T, T> &a, pair<T, T> &b) { return sq(a.first - b.first) + sq(a.second - b.second); }
template <typename T> inline long double dist(pair<T, T> &a, pair<T, T> &b) { return sqrtl(sq_dist(a, b)); }
inline long long isqrt(long long n) {
    long long sq = (long long)sqrtl((long double)n) - 2;
    sq = max(sq, 0LL);
    while (sq * sq < n) sq++;
    if ((sq * sq) == n) return sq;
    return sq - 1;
}
inline bool is_sq(int n) { int w = (int)isqrt(n); return w * w == n; }

struct custom_hash {
    // http://xorshift.di.unimi.it/splitmix64.c
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

struct pair_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
    size_t operator()(pair<int, int> p) const {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(p.first * 31 + p.second + FIXED_RANDOM);
    }
};

void setIO(string name = "") {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout << setprecision(10) << fixed;
    if (name.size() == 0) return;
    FILE *fin = freopen((name + ".in").c_str(), "r", stdin);
    FILE *fout = freopen((name + ".out").c_str(), "w", stdout);
    ignore_unused(fin);
    ignore_unused(fout);
}

// clang-format on

// constexpr int mod = 998244353;
constexpr int mod = 1e9 + 7;
constexpr int64_t linf = 3e18;
constexpr long double pi = acosl(-1.0);
constexpr long double eps = 1e-9;

[[nodiscard]] int64_t pwr_mod(int64_t a, int64_t n, int mod = ::mod) {
    int64_t ans = 1;
    while (n) {
        if (n & 1) ans = (ans * a) % mod;
        a = (a * a) % mod;
        n >>= 1;
    }
    return ans;
}

// when using integers, keep overflow in mind
template <typename T>
T pwr(T a, int64_t n) {
    T ans(1);
    while (n) {
        if (n & 1) ans *= a;
        if (n > 1) a *= a;
        n >>= 1;
    }
    return ans;
}

void precompute() {}

struct Street {
    int B, E;
    string name;
    int idx;
    int L;
    long double score = 0;
};

struct Cars {
    vector<int> path_indices;
    bool works = true;
    int idx;
};

int D, I, S, V, F;

vector<vector<int>> outgoing, incoming;
vector<Street> streets;
vector<Cars> cars;
unordered_map<string, int> string_index;

void get_input();

void print_stats();

void solve(int) {
    
    get_input();

    int id = -1, mx = -1;
    for (int i = 0; i < I; ++i) {
        if (ckmax(mx, (int)incoming[i].size())) {
            id = i;
        }
    }
    vector<vector<pair<int, int>>> output(I);  // pair of street index and time duration
    int cnt = 0;
    for (int i = 0; i < I; ++i) {
        if (i == id) {
            for (auto index : incoming[i]) {
                output[id].emplace_back(index, 1);
            }
        } else {
            for (auto index : incoming[i]) {
                if (streets[index].E == id) {
                    output[i].emplace_back(index, 10);
                } else {
                    output[i].emplace_back(index, 1);
                }
            }
        }
        cnt += output[i].size() != 0;
    }

    cout << cnt << '\n';
    for (int i = 0; i < I; ++i) {
        if (output[i].empty()) continue;
        cout << i << '\n';
        cout << output[i].size() << '\n';
        for (auto [index, score] : output[i]) {
            cout << streets[index].name << ' ' << score << '\n';
        }
    }
}

void change_cars() {
    long long best = 0;
    vector<int> remaining_time;
    remaining_time.reserve(V);
    for (auto &car : cars) {
        long long total_time = 0;
        for (auto i : car.path_indices) total_time += streets[i].L;
        car.works = (total_time * 4 <= D * 3);  // TODO: change later on
        remaining_time.push_back(D - total_time);
        best += F + D - total_time;
    }
    // cerr << "best poss " << best << '\n';
    sort(begin(remaining_time), end(remaining_time));
    // cerr << "D " << D << endl;
    // cerr << "quantiles\n";
    // cerr << remaining_time.front() << ' '
    //      << remaining_time[remaining_time.size() / 4] << ' '
    //      << remaining_time[remaining_time.size() / 2] << ' '
    //      << remaining_time[remaining_time.size() * 3 / 4] << ' '
    //      << remaining_time.back() << endl;

    sort(begin(cars), end(cars), [](const Cars &i, const Cars &j) {
        if (i.works == j.works) return i.idx < j.idx;
        return i.works;
    });

    while (cars.size() > 0 && !cars.back().works) cars.pop_back();
}

void print_stats() {
    // avg path length
    // S / I - avg degree
    
    get_input();
    
    long double x = 0;
    for (auto &c : cars) {
        x += c.path_indices.size();
    }

    long long best = 0;
    vector<int> remaining_time;
    remaining_time.reserve(V);

    for (auto &car : cars) {
        long long total_time = 0;
        for (auto i : car.path_indices) total_time += streets[i].L;
        car.works = (total_time * 4 <= D * 3);  // TODO: change later on
        remaining_time.push_back(D - total_time);
        best += F + max(D - total_time, 0LL);
    }

    cerr << "best poss " << best << '\n';

    sort(begin(remaining_time), end(remaining_time));

    cerr << "D " << D << endl;
    cerr << "quantiles\n";
    cerr << remaining_time.front() << ' '
         << remaining_time[remaining_time.size() / 4] << ' '
         << remaining_time[remaining_time.size() / 2] << ' '
         << remaining_time[remaining_time.size() * 3 / 4] << ' '
         << remaining_time.back() << endl;

    sort(begin(cars), end(cars), [](const Cars &i, const Cars &j) {
        if (i.works == j.works) return i.idx < j.idx;
        return i.works;
    });

    while (cars.size() > 0 && !cars.back().works) cars.pop_back();

    cerr << "working cars " << cars.size() << endl;

    cerr << "total cars " << V << endl;

    // TODO
    auto score = [&]() { return 0; };

    cerr << "avg path len " << x / cars.size() << endl;
    cerr << "avg degree " << 1.0 * S / I << endl;
}

void get_input() {
    cin >> D >> I >> S >> V >> F;

    assert(1 <= D && D <= 10'000);
    assert(2 <= I && I <= 100'000);
    assert(2 <= S && S <= 100'000);
    assert(1 <= V && V <= 1'000);
    assert(1 <= F && F <= 1'000);

    outgoing.resize(I);
    incoming.resize(I);
    streets.resize(S);
    cars.resize(V);

    for (int i = 0; i < S; ++i) {
        streets[i].idx = i;
        cin >> streets[i].B >> streets[i].E;
        cin >> streets[i].name;
        string_index[streets[i].name] = i;
        cin >> streets[i].L;
        incoming[streets[i].E].push_back(i);
        outgoing[streets[i].B].push_back(i);
    }

    int car_no = 0;
    for (auto &x : cars) {
        int path_length;
        cin >> path_length;
        x.path_indices.resize(path_length);
        for (auto &y : x.path_indices) {
            string s;
            cin >> s;
            y = string_index[s];
        }
        x.idx = car_no++;
    }

    assert(car_no == V);
}
void brute(int) {}

signed main() {
    setIO();
    precompute();
    int t = 1;
    // cin >> t;
    for (int _t = 1; _t <= t; _t++) {
        // cout << "Case #" << _t << ": ";
        solve(_t);
        // print_stats();
        // brute(_t);
    }
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n = 1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */

