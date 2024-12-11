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

vector<string> grid;

int part1() {
  unordered_map<char, vector<pair<int, int>>> locations;
  set<pair<int, int>> antinodes;
  for (int i = 0; i < sz(grid); i++) {
    for (int j = 0; j < sz(grid[i]); j++) {
      if (grid[i][j] != '.') {
        locations[grid[i][j]].push_back({i, j});
      }
    }
  }

  for (const auto &[c, locs] : locations) {
    if (sz(locs) < 2) {
      continue;
    }

    for (int i = 0; i < sz(locs); i++) {
      for (int j = i + 1; j < sz(locs); j++) {
        auto p1 = locs[i];
        auto p2 = locs[j];
        auto diff = make_pair(p2.first - p1.first, p2.second - p1.second);
        auto node1 = make_pair(p1.first - diff.first, p1.second - diff.second);
        auto node2 = make_pair(p2.first + diff.first, p2.second + diff.second);
        if (node1.first >= 0 && node1.first < sz(grid) && node1.second >= 0 &&
            node1.second < sz(grid[0])) {
          antinodes.insert(node1);
        }

        if (node2.first >= 0 && node2.first < sz(grid) && node2.second >= 0 &&
            node2.second < sz(grid[0])) {
          antinodes.insert(node2);
        }
      }
    }
  }

  return antinodes.size();
}

int part2() {
  unordered_map<char, vector<pair<int, int>>> locations;
  set<pair<int, int>> antinodes;
  for (int i = 0; i < sz(grid); i++) {
    for (int j = 0; j < sz(grid[i]); j++) {
      if (grid[i][j] != '.') {
        locations[grid[i][j]].push_back({i, j});
        antinodes.insert({i, j});
      }
    }
  }

  for (const auto &[c, locs] : locations) {
    if (sz(locs) < 2) {
      continue;
    }

    for (int i = 0; i < sz(locs); i++) {
      for (int j = i + 1; j < sz(locs); j++) {
        auto p1 = locs[i];
        auto p2 = locs[j];
        auto diff = make_pair(p2.first - p1.first, p2.second - p1.second);
        while (true) {
          auto node1 =
              make_pair(p1.first - diff.first, p1.second - diff.second);
          auto node2 =
              make_pair(p2.first + diff.first, p2.second + diff.second);
          bool node1_in_bounds = node1.first >= 0 && node1.first < sz(grid) &&
                                 node1.second >= 0 &&
                                 node1.second < sz(grid[0]);
          bool node2_in_bounds = node2.first >= 0 && node2.first < sz(grid) &&
                                 node2.second >= 0 &&
                                 node2.second < sz(grid[0]);
          if (node1_in_bounds) {
            antinodes.insert(node1);
          }

          if (node2_in_bounds) {
            antinodes.insert(node2);
          }

          if (!node1_in_bounds && !node2_in_bounds) {
            break;
          }

          diff.first += p2.first - p1.first;
          diff.second += p2.second - p1.second;
        }
      }
    }
  }

  return antinodes.size();
}

int main() {
  ifstream in("input.txt");
  string line;
  while (getline(in, line)) {
    grid.push_back(line);
  }

  cout << part1() << nl;
  cout << part2() << nl;
}
