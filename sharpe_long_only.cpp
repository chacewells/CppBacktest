//
// Created by chace on 5/10/2023.
//

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <numeric>
#include <algorithm>
#include <cmath>
#include "sharpe_long_only.h"

using namespace std;

void sharpe_long_only::backtest_ige() {
    vector<double> adj_close;
    ifstream fspy(IGE_FILE);

    string line;
    int head = 0;
    while (getline(fspy, line)) {
        if (head++ == 0) continue;
        string token;
        stringstream ss(line);
        for (int i = 0; i <= 6; ++i) {
            getline(ss, token, ',');
        }
        adj_close.push_back(stod(token));
    }

    size_t n = adj_close.size();
    vector<double> dailyret(n);

    for (int i = 1; i < n; ++i) {
        dailyret[i] = (adj_close[i] - adj_close[i - 1]) / adj_close[i - 1];
    }

    vector<double> excessret(n);
    transform(dailyret.begin() + 1, dailyret.end(), excessret.begin() + 1,
              [](const double &ret) { return ret - 0.04 / 252; });

    double sum = accumulate(excessret.begin() + 1, excessret.end(), 0.0);
    cout << "excessret sum: " << sum << endl;
    double mean = sum / (n - 1);
    cout << "excessret mean: " << mean << endl;
    double stddev = transform_reduce(excessret.begin() + 1, excessret.end(), 0.0,
                                     [](const double &a, const double &b) { return a + b; }, [&](const double &x) {
                const double delta = x - mean;
                return delta * delta;
            });
    stddev = sqrt(stddev / (n - 1));
    cout << "excessret stddev: " << stddev << endl;

    double sharpe = sqrt(252) * mean / stddev;
    cout << "Sharpe ratio: " << sharpe << endl;

}

