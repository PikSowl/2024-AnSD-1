#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::swap;
using std::endl;
using std::vector;
using std::sort;

struct Dot{
    double x;
    double y;

    Dot(double a, double b) {
        x = a;
        y = b;
    }

    Dot operator-(Dot d) const {
        return {x - d.x, y - d.y};
    }

    double operator^(Dot d) const {
        return x * d.y - y * d.x;
    }
};

int main() {
    int n = 0;
    vector<Dot> dots;

    cout << "Input number of dots" << endl;
    cin >> n;

    double a = 0, b = 0;
    for (int i = 0; i < n; i++){
        cout << "Input point number " << i << endl;
        cin >> a >> b;
        dots.emplace_back(a, b);
    }

    Dot d0 = dots[0];
    for (Dot d: dots){
        if (d.x < d0.x || (d.x == d0.x && d.y < d0.y))
            d0 = d;
    }

    for (Dot &d: dots){
        d.x -= d0.x;
        d.y -= d0.y;
    }

    sort(dots.begin(), dots.end(), [&](Dot d1, Dot d2){
        return (d1 ^ d2) > 0 || (d1 ^ d2) == 0 && (d1.x * d1.x + d1.y * d1.y) < (d2.x * d2.x + d2.y * d2.y);
    });

    vector<Dot> hull;

    for (Dot d : dots) {
        while (hull.size() >= 2 && ((d - hull.back()) ^ (hull[hull.size() - 2] - hull.back())) <= 0) {
            hull.pop_back();
        }
        hull.push_back(d);
    }

    for (Dot d : hull) {
        d.x += d0.x;
        d.y += d0.y;
    }

    cout << "Hull for this set of dots:" << endl;
    for (Dot d : hull) {
        cout << "(" << d.x << ", " << d.y << ") ";
    }
    cout << endl;
    return 0;
}

