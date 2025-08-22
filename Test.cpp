#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include "json.hpp"   // nlohmann JSON header

using namespace std;
using json = nlohmann::json;

double evaluateAtZero(const vector<int> &xs, const vector<long long> &ys) {
    int n = xs.size();
    double result = 0.0;

    for (int i = 0; i < n; i++) {
        double term = ys[i];
        for (int j = 0; j < n; j++) {
            if (i != j) {
                term *= (0.0 - xs[j]) / (xs[i] - xs[j]);
            }
        }
        result += term;
    }

    return result;
}

void printPolynomial(const map<int, long long> &points) {
    int n = points.size();
    vector<int> xs;
    vector<long long> ys;

    for (auto &p : points) {
        xs.push_back(p.first);
        ys.push_back(p.second);
    }

    cout << "P(x) = ";
    for (int i = 0; i < n; i++) {
        cout << "(" << ys[i] << ")";
        cout << " * [";
        bool firstTerm = true;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                if (!firstTerm) cout << " * ";
                cout << "(x - " << xs[j] << ")/(" << xs[i] << " - " << xs[j] << ")";
                firstTerm = false;
            }
        }
        cout << "]";
        if (i != n - 1) cout << " + ";
    }
    cout << "\n";

    // Constant term (P(0))
    double constant = evaluateAtZero(xs, ys);
    cout << "Constant term (P(0)) = " << constant << "\n";
}

int main() {
    ifstream file("FirstTestCase.json");
    if (!file.is_open()) {
        cerr << "Error: Could not open FirstTestCase.json\n";
        return 1;
    }

    json j;
    file >> j;

    map<int, long long> roots;
    for (auto& [key, value] : j.items()) {
        if (key == "keys") continue;

        int x = stoi(key);
        int base = stoi(value["base"].get<string>());
        string encoded = value["value"];
        long long y = stoll(encoded, nullptr, base);
        roots[x] = y;
    }

    printPolynomial(roots);

    return 0;
}
