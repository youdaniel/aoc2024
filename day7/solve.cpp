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

unordered_map<ll, vector<ll>> equations;

bool is_valid(const vector<ll> &equation, ll idx, ll total, ll curr) {
  if (idx >= sz(equation)) {
    return curr == total;
  }
  ll sum = curr + equation[idx];
  ll product = curr * equation[idx];
  return is_valid(equation, idx + 1, total, sum) ||
         is_valid(equation, idx + 1, total, product);
}

ll part1() {
  ll total = 0;
  for (const auto &[tot, nums] : equations) {
    if (is_valid(nums, 1, tot, nums[0])) {
      total += tot;
    }
  }
  return total;
}

bool is_valid_p2(const vector<ll> &equation, ll idx, ll total, ll curr) {
  if (idx >= sz(equation)) {
    return curr == total;
  }
  ll sum = curr + equation[idx];
  ll product = curr * equation[idx];
  ll concat = stoll(to_string(curr) + to_string(equation[idx]));
  return is_valid_p2(equation, idx + 1, total, sum) ||
         is_valid_p2(equation, idx + 1, total, product) ||
         is_valid_p2(equation, idx + 1, total, concat);
}

ll part2() {
  ll total = 0;
  for (const auto &[tot, nums] : equations) {
    if (is_valid_p2(nums, 1, tot, nums[0])) {
      total += tot;
    }
  }
  return total;
}

int main() {
  ifstream in("input.txt");
  string line;
  while (getline(in, line)) {
    string total = line.substr(0, line.find(":"));

    vector<ll> nums;
    string num = "";
    for (int i = line.find(":") + 2; i < sz(line); i++) {
      if (line[i] == ' ') {
        nums.push_back(stoll(num));
        num = "";
      } else {
        num += line[i];
      }
    }
    nums.push_back(stoll(num));

    equations[stoll(total)] = nums;
  }

  cout << part1() << nl;
  cout << part2() << nl;
}
