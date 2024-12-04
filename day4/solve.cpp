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

vector<int> dx8 = {1, 0, -1, 0, 1, 1, -1, -1};
vector<int> dy8 = {0, 1, 0, -1, 1, -1, 1, -1};

vector<int> dx4 = {-1, 1, -1, 1};
vector<int> dy4 = {-1, 1, 1, -1};

vector<vector<char>> grid;

int countXMAS(int x, int y) {
  int count = 0;
  for (int i = 0; i < 8; i++) {
    string s;
    for (int j = 0; j < 4; j++) {
      int nx = x + dx8[i] * j;
      int ny = y + dy8[i] * j;
      if (nx < 0 || nx >= sz(grid) || ny < 0 || ny >= sz(grid[0])) {
        break;
      }
      s += grid[nx][ny];
    }
    if (s == "XMAS") {
      count++;
    }
  }
  return count;
}

bool isMAS(int x, int y) {
  int m_cnt = 0, s_cnt = 0;
  for (int i = 0; i < 4; i++) {
    int nx = x + dx4[i];
    int ny = y + dy4[i];

    if (nx < 0 || nx >= sz(grid) || ny < 0 || ny >= sz(grid[0])) {
      return false;
    }

    if (grid[nx][ny] == 'M') {
      m_cnt++;
    } else if (grid[nx][ny] == 'S') {
      s_cnt++;
    }
  }
  if (m_cnt == 2 && s_cnt == 2) {
    if (grid[x - 1][y - 1] == grid[x + 1][y + 1] ||
        grid[x - 1][y + 1] == grid[x + 1][y - 1]) {
      return false;
    }
    return true;
  }
  return false;
}

int part1() {
  int ans = 0;
  for (int i = 0; i < sz(grid); i++) {
    for (int j = 0; j < sz(grid[0]); j++) {
      if (grid[i][j] == 'X') {
        ans += countXMAS(i, j);
      }
    }
  }
  return ans;
}

int part2() {
  int ans = 0;
  for (int i = 0; i < sz(grid); i++) {
    for (int j = 0; j < sz(grid[0]); j++) {
      if (grid[i][j] == 'A') {
        ans += isMAS(i, j);
      }
    }
  }
  return ans;
}

int main() {
  ifstream file("input.txt");
  string line;
  while (getline(file, line)) {
    grid.push_back(vector<char>(line.begin(), line.end()));
  }

  cout << part1() << nl;
  cout << part2() << nl;
}
