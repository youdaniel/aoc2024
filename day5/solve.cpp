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

unordered_map<int, set<int>> goes_before;
vector<vector<int>> updates;

bool is_correct(const vector<int> &update) {
  unordered_set<int> seen;
  for (int i = sz(update) - 1; i >= 0; i--) {
    for (int b : goes_before[update[i]]) {
      if (seen.count(b) > 0) {
        return false;
      }
    }
    seen.insert(update[i]);
  }
  return true;
}

vector<int> reorder_update(const vector<int> &update) {
  unordered_set<int> nums(update.begin(), update.end());
  vector<int> res;
  vector<bool> used(update.size(), false);
  unordered_set<int> seen;
  while (res.size() < update.size()) {
    for (int i = 0; i < sz(update); i++) {
      if (used[i]) {
        continue;
      }
      bool can_add = true;
      for (int b : goes_before[update[i]]) {
        if (seen.find(b) == seen.end() && nums.find(b) != nums.end()) {
          can_add = false;
          break;
        }
      }
      if (can_add) {
        res.push_back(update[i]);
        used[i] = true;
        seen.insert(update[i]);
      }
    }
  }
  reverse(res.begin(), res.end());
  return res;
}

int part1() {
  int sum = 0;
  for (const auto &update : updates) {
    if (is_correct(update)) {
      sum += update[update.size() / 2];
    }
  }
  return sum;
}

int part2() {
  int sum = 0;
  for (const auto &update : updates) {
    if (!is_correct(update)) {
      vector<int> reordered = reorder_update(update);
      sum += reordered[reordered.size() / 2];
    }
  }
  return sum;
}

int main() {
  ifstream file("input.txt");
  string line;
  bool saw_blank = false;
  while (getline(file, line)) {
    if (line.empty()) {
      saw_blank = true;
      continue;
    }
    if (!saw_blank) {
      int p1 = stoi(line.substr(0, line.find("|")));
      int p2 = stoi(line.substr(line.find("|") + 1));
      goes_before[p2].insert(p1);
    } else {
      vector<int> update;
      istringstream ss(line);
      string token;
      while (getline(ss, token, ',')) {
        update.push_back(stoi(token));
      }
      updates.push_back(update);
    }
  }

  cout << part1() << nl;
  cout << part2() << nl;
}
