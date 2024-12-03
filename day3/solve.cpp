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

ll part1() {
  ifstream file("input.txt");
  ll ans = 0;
  string line;
  regex re("mul\\([0-9]{1,3},[0-9]{1,3}\\)");
  while (getline(file, line)) {
    auto it = sregex_iterator(line.begin(), line.end(), re);
    for (; it != sregex_iterator(); ++it) {
      int comma_idx = it->str().find(',');
      ll n1 = stoll(it->str().substr(4, comma_idx - 4));
      ll n2 = stoll(it->str().substr(comma_idx + 1, it->str().size() - 1));
      ans += n1 * n2;
    }
  }
  return ans;
}

int part2() {
  ifstream file("input.txt");
  ll ans = 0;
  string line;
  regex re("(mul\\([0-9]{1,3},[0-9]{1,3}\\)|do\\(\\)|don't\\(\\))");
  bool enabled = true;
  while (getline(file, line)) {
    auto it = sregex_iterator(line.begin(), line.end(), re);
    for (; it != sregex_iterator(); ++it) {
      if (it->str() == "do()") {
        enabled = true;
      } else if (it->str() == "don't()") {
        enabled = false;
      } else if (enabled) {
        int comma_idx = it->str().find(',');
        ll n1 = stoll(it->str().substr(4, comma_idx - 4));
        ll n2 = stoll(it->str().substr(comma_idx + 1, it->str().size() - 1));
        ans += n1 * n2;
      }
    }
  }
  return ans;
}

int main() {
  cout << part1() << nl;
  cout << part2() << nl;
}
