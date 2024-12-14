#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/home/daniel/Documents/CP/debug.h"
#define DEBUG(...) debug(#__VA_ARGS__, __VA_ARGS__)
#else
#define DEBUG(...) 6
#endif

#define all(x) begin(x), end(x)
#define sz(x) int((x).size())

using ll = long long;
const char nl = '\n';

vector<pair<int, int>> A, B, prizes;

ll find_min_cost(pair<ll, ll> a, pair<ll, ll> b, pair<ll, ll> prize) {
  ll numB = (a.second * prize.first - a.first * prize.second) /
            (a.second * b.first - a.first * b.second);
  ll numA = (prize.first - b.first * numB) / a.first;
  if (a.first * numA + b.first * numB != prize.first ||
      a.second * numA + b.second * numB != prize.second) {
    return 0;
  }
  return 3 * numA + numB;
}

int part1() {
  int total = 0;
  for (int i = 0; i < sz(A); i++) {
    total += find_min_cost(A[i], B[i], prizes[i]);
  }
  return total;
}

ll part2() {
  ll total = 0;
  ll additional = 10000000000000;
  for (int i = 0; i < sz(A); i++) {
    total += find_min_cost(
        A[i], B[i],
        {prizes[i].first + additional, prizes[i].second + additional});
  }
  return total;
}

int main() {
  ifstream in("input.txt");
  string line;
  pair<ll, ll> a, b, p;
  int lines = 0;
  while (getline(in, line)) {
    if (line.size() == 0) {
      continue;
    }

    if (lines % 3 == 0) {
      a.first = stoi(line.substr(line.find("X+") + 2, line.find(",")));
      a.second = stoi(line.substr(line.find("Y+") + 2));
      A.push_back(a);
    } else if (lines % 3 == 1) {
      b.first = stoi(line.substr(line.find("X+") + 2, line.find(",")));
      b.second = stoi(line.substr(line.find("Y+") + 2));
      B.push_back(b);
    } else {
      p.first = stoi(line.substr(line.find("X=") + 2, line.find(",")));
      p.second = stoi(line.substr(line.find("Y=") + 2));
      prizes.push_back(p);
    }
    lines++;
  }

  cout << part1() << nl;
  cout << part2() << nl;
}
