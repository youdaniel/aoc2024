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

string line;

ll compute_checksum(const vector<int> &expanded) {
  ll checksum = 0;
  for (int i = 0; i < sz(expanded); i++) {
    if (expanded[i] == -1)
      continue;
    checksum += i * expanded[i];
  }
  return checksum;
}

vector<int> get_expanded() {
  vector<int> expanded;
  int id = 0;
  for (int i = 0; i < sz(line); i += 2) {
    for (int j = 0; j < line[i] - '0'; j++) {
      expanded.push_back(id);
    }

    for (int j = 0; j < line[i + 1] - '0'; j++) {
      expanded.push_back(-1);
    }
    id++;
  }
  return expanded;
}

ll part1() {
  vector<int> expanded = get_expanded();
  int l = 0, r = sz(expanded) - 1;
  while (l < r) {
    while (expanded[l] != -1) {
      l++;
    }

    while (expanded[r] == -1) {
      r--;
    }

    if (l < r)
      swap(expanded[l], expanded[r]);
  }

  return compute_checksum(expanded);
}

ll part2() {
  vector<int> expanded = get_expanded();
  int r = sz(expanded) - 1;
  while (r >= 0) {
    while (r >= 0 && expanded[r] == -1) {
      r--;
    }

    int curr = expanded[r];
    int curr_cnt = 0;
    while (r >= 0 && expanded[r] == curr) {
      r--;
      curr_cnt++;
    }

    // loop through expanded, see if there is a sequence of -1s with to fit curr
    int i = 0;
    while (i < sz(expanded)) {
      while (i < sz(expanded) && expanded[i] != -1) {
        i++;
      }

      if (i >= r)
        break;

      int start_i = i;
      int free_cnt = 0;
      while (i < sz(expanded) && expanded[i] == -1) {
        free_cnt++;
        i++;
      }

      if (free_cnt >= curr_cnt) {
        for (int j = 0; j < curr_cnt; j++) {
          swap(expanded[start_i + j], expanded[r + curr_cnt - j]);
        }
        break;
      }
    }
  }

  return compute_checksum(expanded);
}

int main() {
  ifstream in("input.txt");
  getline(in, line);

  cout << part1() << nl;
  cout << part2() << nl;
}
