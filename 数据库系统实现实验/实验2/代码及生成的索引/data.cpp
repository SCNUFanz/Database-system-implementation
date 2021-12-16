#include <bits/stdc++.h>
#define read(x) scanf("%d", &x)
#define readll(x) scanf("%d", &x)
#define readf(x) scanf("%lf", &x)


const int N = 4e7 + 5;
const int mod = (1 << 30);
const int INF = 0x3f3f3f3f;
const long long LINF = 1e18;
const double eps = 1e-8;

std::string str = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXY0123456789";
std::unordered_map<std::string, bool> st;

template<typename T> 
T randint(T l, T r) {
    T res = rand() / (double)RAND_MAX * (r - l + 1) + l;
    while (res < l or res > r) {
        res = rand() / (double)RAND_MAX * (r - l + 1) + l;
    }
    return res;
}
std::string get_str(int l, int r) {
    int sz = randint(l, r);
    std::string name;
    for (int i = 0; i < sz; i++) {
        name += str[randint(0, (int)str.size() - 1)];
    }
    return name;
}
std::string get() {
    int sz = 4;
    std::string name;
    while (1) {
        name = "";
        for (int i = 0; i < sz; i++) {
            name += str[randint(0, (int)str.size() - 1)];
        }
        if (!st[name]) {
            break;
        }
    }
    st[name] = true;
    return name;
}
int main() {
    srand(time(0));
    freopen("data\\testdata1.csv", "w", stdout);
    std::cout << "id" << ',' << "user" << ',' << "password" << '\n';
    for (int i = 1; i <= 1000000; i++) {
        std::cout << get() << ',' << get_str(5, 5) << ',' << get_str(8, 16) << '\n';
    }
    freopen("data\\testdata2.csv", "w", stdout);
    std::cout << "id" << ',' << "user" << ',' << "password" << '\n';
    for (int i = 1; i <= 1000000; i++) {
        std::cout << get() << ',' << get_str(5, 5) << ',' << get_str(8, 16) << '\n';
    }
    freopen("data\\testdata3.csv", "w", stdout);
    std::cout << "id" << ',' << "user" << ',' << "password" << '\n';
    for (int i = 1; i <= 1000000; i++) {
        std::cout << get() << ',' << get_str(5, 5) << ',' << get_str(8, 16) << '\n';
    }
    freopen("data\\testdata4.csv", "w", stdout);
    std::cout << "id" << ',' << "user" << ',' << "password" << '\n';
    for (int i = 1; i <= 1000000; i++) {
        std::cout << get() << ',' << get_str(5, 5) << ',' << get_str(8, 16) << '\n';
    }
    return 0;
}

