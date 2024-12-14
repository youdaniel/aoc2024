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

vector<int> dx = {1, 0, -1, 0};
vector<int> dy = {0, -1, 0, 1};

int compute_price(int start_r, int start_c, vector<vector<bool>> &vis) {
  queue<pair<int, int>> q;
  q.emplace(start_r, start_c);
  int area = 0;
  int perimeter = 0;
  while (!q.empty()) {
    auto [r, c] = q.front();
    q.pop();

    if (vis[r][c]) {
      continue;
    }

    vis[r][c] = true;
    area++;

    for (int i = 0; i < 4; i++) {
      int nr = r + dx[i];
      int nc = c + dy[i];

      if (nr < 0 || nr >= n || nc < 0 || nc >= n ||
          grid[nr][nc] != grid[start_r][start_c]) {
        perimeter++;
        continue;
      }

      q.emplace(nr, nc);
    }
  }
  return area * perimeter;
}

int part1() {
  int price = 0;
  vector<vector<bool>> vis(n, vector<bool>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (!vis[i][j]) {
        price += compute_price(i, j, vis);
      }
    }
  }
  return price;
}

int compute_price_with_sides(int start_r, int start_c,
                             vector<vector<bool>> &vis) {
  queue<pair<int, int>> q;
  q.emplace(start_r, start_c);
  int area = 0;
  set<tuple<int, int, int, int>> edges;
  while (!q.empty()) {
    auto [r, c] = q.front();
    q.pop();

    if (vis[r][c]) {
      continue;
    }

    vis[r][c] = true;
    area++;

    for (int i = 0; i < 4; i++) {
      int nr = r + dx[i];
      int nc = c + dy[i];

      if (nr < 0 || nr >= n || nc < 0 || nc >= n ||
          grid[nr][nc] != grid[start_r][start_c]) {
        edges.insert({dx[i], dy[i], nr, nc});
        continue;
      }

      q.emplace(nr, nc);
    }
  }

  int total_sides = 0;
  set<tuple<int, int, int, int>> seen_edges;
  for (auto &edge : edges) {
    if (seen_edges.count(edge)) {
      continue;
    }

    total_sides++;

    stack<tuple<int, int, int, int>> s;
    s.push(edge);
    while (!s.empty()) {
      auto [dxi, dyi, r, c] = s.top();
      s.pop();

      if (seen_edges.count({dxi, dyi, r, c})) {
        continue;
      }

      seen_edges.insert({dxi, dyi, r, c});

      for (int i = 0; i <= 2; i += 2) {
        int nr = r + dyi * (i - 1);
        int nc = c + dxi * (i - 1);

        if (edges.count({dxi, dyi, nr, nc}) &&
            !seen_edges.count({dxi, dyi, nr, nc})) {
          s.emplace(dxi, dyi, nr, nc);
        }
      }
    }
  }

  return area * total_sides;
}

int part2() {
  int price = 0;
  vector<vector<bool>> vis(n, vector<bool>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (!vis[i][j]) {
        price += compute_price_with_sides(i, j, vis);
      }
    }
  }
  return price;
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
