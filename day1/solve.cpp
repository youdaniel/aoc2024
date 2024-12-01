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

pair<vector<int>, vector<int>> read_input() {
  ifstream infile("input.txt");
  vector<int> l1, l2;
  int a, b;
  while (infile >> a >> b) {
    l1.push_back(a);
    l2.push_back(b);
  }
  return {l1, l2};
}

int part1() {
  vector<int> l1, l2;
  tie(l1, l2) = read_input();

  sort(all(l1));
  sort(all(l2));

  int total = 0;
  for (int i = 0; i < sz(l1); i++) {
    total += abs(l1[i] - l2[i]);
  }
  return total;
}

ll part2() {
  vector<int> l1, l2;
  tie(l1, l2) = read_input();

  unordered_map<int, int> freq;
  for (int i : l2) {
    freq[i]++;
  }

  ll similarity = 0;
  for (int i : l1) {
    if (freq.find(i) != freq.end()) {
      similarity += i * freq[i];
    }
  }
  return similarity;
}

int main() {
  cout << part1() << nl;
  cout << part2() << nl;
}
