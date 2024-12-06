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

vector<int> dx = {-1, 0, 1, 0};
vector<int> dy = {0, 1, 0, -1};

vector<string> grid;

struct Guard {
  int x;
  int y;
  int dir;
};

Guard find_guard() {
  for (int i = 0; i < sz(grid); i++) {
    for (int j = 0; j < sz(grid[i]); j++) {
      if (grid[i][j] == '^') {
        return {i, j, 0};
      }
    }
  }
  return {-1, -1, -1};
}

int part1() {
  Guard g = find_guard();
  vector<vector<bool>> visited(sz(grid), vector<bool>(sz(grid[0]), false));
  int distinct = 0;
  while (g.x >= 0 && g.x < sz(grid) && g.y >= 0 && g.y < sz(grid[0])) {
    if (!visited[g.x][g.y]) {
      distinct++;
      visited[g.x][g.y] = true;
    }
    int nx = g.x + dx[g.dir];
    int ny = g.y + dy[g.dir];
    if (grid[nx][ny] == '#') {
      g.dir = (g.dir + 1) % 4;
    } else {
      g.x = nx;
      g.y = ny;
    }
  }
  return distinct;
}

bool stuckInCycle(Guard g) {
  set<tuple<int, int, int>> turning_points;
  while (g.x >= 0 && g.x < sz(grid) && g.y >= 0 && g.y < sz(grid[0])) {
    int nx = g.x + dx[g.dir];
    int ny = g.y + dy[g.dir];
    if (nx < 0 || nx >= sz(grid) || ny < 0 || ny >= sz(grid[0])) {
      return false;
    }
    if (grid[nx][ny] == '#') {
      g.dir = (g.dir + 1) % 4;
      if (turning_points.find({g.x, g.y, g.dir}) != turning_points.end()) {
        return true;
      }
      turning_points.insert({g.x, g.y, g.dir});
    } else {
      g.x = nx;
      g.y = ny;
    }
  }
  return false;
}

int part2() {
  Guard g = find_guard();
  int ans = 0;
  for (int i = 0; i < sz(grid); i++) {
    for (int j = 0; j < sz(grid[0]); j++) {
      if (grid[i][j] != '.') {
        continue;
      }
      grid[i][j] = '#';
      ans += stuckInCycle(g);
      grid[i][j] = '.';
    }
  }
  return ans;
}

int main() {
  ifstream file("input.txt");
  string line;
  while (getline(file, line)) {
    grid.push_back(line);
  }

  cout << part1() << nl;
  cout << part2() << nl;
}
