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

array<unordered_map<ll, ll>, 76> dp;

ll values_after_blink(ll initial, ll blink) {
  if (dp[blink].count(initial)) {
    return dp[blink][initial];
  }

  if (blink == 0) {
    return 1;
  }

  ll total = 0;
  if (initial == 0) {
    total += values_after_blink(1, blink - 1);
  } else {
    string vstr = to_string(initial);
    if (vstr.length() % 2 == 0) {
      ll h1 = stoll(vstr.substr(0, vstr.length() / 2));
      ll h2 = stoll(vstr.substr(vstr.length() / 2));
      total += values_after_blink(h1, blink - 1);
      total += values_after_blink(h2, blink - 1);
    } else {
      total += values_after_blink(initial * 2024, blink - 1);
    }
  }
  dp[blink][initial] = total;

  return total;
}

int part1() {
  istringstream ss(line);
  ll total = 0;
  for (int x; ss >> x;) {
    total += values_after_blink(x, 25);
  }
  return total;
}

ll part2() {
  istringstream ss(line);
  ll total = 0;
  for (int x; ss >> x;) {
    total += values_after_blink(x, 75);
  }
  return total;
}

int main() {
  ifstream in("input.txt");
  getline(in, line);

  cout << part1() << nl;
  cout << part2() << nl;
}
