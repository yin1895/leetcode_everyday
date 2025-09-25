#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    double a, b, C;
    cin >> a >> b >> C;
    const double pi = acos(-1.0);
    double rad = C * pi / 180.0;
    double S = 0.5 * a * b * sin(rad);
    double c = sqrt(a * a + b * b - 2 * a * b * cos(rad));
    double L = a + b + c;
    double h = b * sin(rad);
    cout << fixed << setprecision(4) << S << "\n" << L << "\n" << h << endl;
    return 0;
}

