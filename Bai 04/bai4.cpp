#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
#include <iomanip>
using namespace std;

struct Point {
    double x, y;
};

double dist(const Point& a, const Point& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

double bruteForce(vector<Point>& p, int left, int right) {
    double best = numeric_limits<double>::infinity();
    for (int i = left; i <= right; i++) {
        for (int j = i + 1; j <= right; j++) {
            best = min(best, dist(p[i], p[j]));
        }
    }
    return best;
}

double stripClosest(vector<Point>& strip, double d) {
    double best = d;
    sort(strip.begin(), strip.end(), [](const Point& u, const Point& v) {
        return u.y < v.y;
    });

    for (size_t i = 0; i < strip.size(); i++) {
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < best; j++) {
            best = min(best, dist(strip[i], strip[j]));
        }
    }
    return best;
}

double closestUtil(vector<Point>& p, int left, int right) {
    if (right - left + 1 <= 3) {
        return bruteForce(p, left, right);
    }

    int mid = (left + right) / 2;
    double d = min(closestUtil(p, left, mid),
                   closestUtil(p, mid + 1, right));

    vector<Point> strip;
    for (int i = left; i <= right; i++) {
        if (fabs(p[i].x - p[mid].x) < d) {
            strip.push_back(p[i]);
        }
    }
    return min(d, stripClosest(strip, d));
}

double closestPair(vector<Point> points) {
    sort(points.begin(), points.end(), [](const Point& u, const Point& v) {
        return u.x < v.x;
    });
    return closestUtil(points, 0, (int)points.size() - 1);
}

int main() {
    cout << fixed << setprecision(6);
    cout << "\n===== TIM CAP TRAM BTS GAN NHAU NHAT =====" << endl;

    int n;
    cout << "\nNhap so luong tram BTS (n >= 2): " << flush;
    cin >> n;
    if (n < 2) {
        cout << "Can it nhat 2 tram. Ket qua: 0.000000" << endl;
        return 0;
    }

    vector<Point> points(n);
    cout << "Nhap toa do tung tram (x y):" << endl;
    for (int i = 0; i < n; i++) {
        cout << "  Tram #" << (i + 1) << ": " << flush;
        cin >> points[i].x >> points[i].y;
    }

    double d = closestPair(points);
    cout << "\nKhoang cach nho nhat: " << d << endl;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    return 0;
}
