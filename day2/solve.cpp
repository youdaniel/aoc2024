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

int part1() {
  ifstream infile("input.txt");
  string line;
  int safe = 0;
  while (getline(infile, line)) {
    vector<int> nums;
    istringstream iss(line);
    string s;
    while (getline(iss, s, ' ')) {
      nums.push_back(stoi(s));
    }
    bool ok = true;
    for (int i = 1; i < sz(nums); i++) {
      int diff = nums[i] - nums[i - 1];
      if (abs(diff) < 1 || abs(diff) > 3 ||
          ((diff > 0) != ((nums[1] - nums[0]) > 0))) {
        ok = false;
        break;
      }
    }
    safe += ok;
  }
  return safe;
}

ll part2() {
  ifstream infile("input.txt");
  string line;
  int safe = 0;
  while (getline(infile, line)) {
    vector<int> nums;
    istringstream iss(line);
    string s;
    while (getline(iss, s, ' ')) {
      nums.push_back(stoi(s));
    }
    int bad = 0;
    for (int i = 1; i < sz(nums); i++) {
      int diff = nums[i] - nums[i - 1];
      if (abs(diff) < 1 || abs(diff) > 3 ||
          ((diff > 0) != ((nums[1] - nums[0]) > 0))) {
        bad++;
      }
    }
    safe += (bad <= 1);
  }
  return safe;
}

int main() {
  cout << part1() << nl;
  cout << part2() << nl;
}
