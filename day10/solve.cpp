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

int n, m;
vector<string> grid;

vector<int> dx = {0, -1, 0, 1};
vector<int> dy = {-1, 0, 1, 0};

int compute_score(int initial_x, int initial_y) {
  vector<vector<bool>> vis(n, vector<bool>(m));
  queue<pair<int, int>> q;
  q.emplace(initial_x, initial_y);
  int score = 0;
  while (!q.empty()) {
    auto [x, y] = q.front();
    q.pop();

    if (vis[x][y]) {
      continue;
    }

    vis[x][y] = true;

    if (grid[x][y] == '9') {
      score++;
      continue;
    }

    for (int i = 0; i < 4; i++) {
      int nx = x + dx[i];
      int ny = y + dy[i];
      if (nx < 0 || nx >= n || ny < 0 || ny >= m || vis[nx][ny] ||
          (grid[nx][ny] - '0') - 1 != (grid[x][y] - '0')) {
        continue;
      }

      q.emplace(nx, ny);
    }
  }

  return score;
}

int part1() {
  int total = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (grid[i][j] == '0') {
        total += compute_score(i, j);
      }
    }
  }
  return total;
}

int compute_rating(int initial_x, int initial_y) {
  vector<vector<bool>> vis(n, vector<bool>(m));
  queue<pair<int, int>> q;
  q.emplace(initial_x, initial_y);
  int score = 0;
  while (!q.empty()) {
    auto [x, y] = q.front();
    q.pop();

    vis[x][y] = true;

    if (grid[x][y] == '9') {
      score++;
      continue;
    }

    for (int i = 0; i < 4; i++) {
      int nx = x + dx[i];
      int ny = y + dy[i];
      if (nx < 0 || nx >= n || ny < 0 || ny >= m || vis[nx][ny] ||
          (grid[nx][ny] - '0') - 1 != (grid[x][y] - '0')) {
        continue;
      }

      q.emplace(nx, ny);
    }
  }

  return score;
}

int part2() {
  int total = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (grid[i][j] == '0') {
        total += compute_rating(i, j);
      }
    }
  }
  return total;
}

int main() {
  ifstream in("input.txt");
  string line;
  while (getline(in, line)) {
    grid.push_back(line);
  }
  n = grid.size();
  m = grid[0].size();

  cout << part1() << nl;
  cout << part2() << nl;
}
