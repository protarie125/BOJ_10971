#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

using ll = long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vvl = vector<vl>;
using pii = pair<int, int>;
using vii = vector<pii>;
using pll = pair<ll, ll>;
using vll = vector<pll>;

int n;
vvi cost;

vb used;
int ct;
vi selected;
ll now;
ll ans = numeric_limits<ll>::max();

void solve() {
	if (n == ct) {
		const auto rv = cost[selected.back()][selected.front()];
		if (0 < rv) {
			ans = min(ans, now + rv);
		}

		return;
	}

	for (auto i = 0; i < n; ++i) {
		if (used[i]) {
			continue;
		}

		if (0 == selected.size()) {
			selected.push_back(i);
			used[i] = true;
			++ct;

			solve();

			selected.pop_back();
			used[i] = false;
			--ct;
		}
		else {
			const auto cv = cost[selected.back()][i];

			if (cv <= 0) {
				continue;
			}

			now += cv;
			used[i] = true;
			++ct;
			selected.push_back(i);

			solve();

			selected.pop_back();
			now -= cv;
			used[i] = false;
			--ct;
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	cin >> n;

	cost = vvi(n, vi(n));
	for (auto&& r : cost) {
		for (auto&& x : r) {
			cin >> x;
		}
	}

	used = vb(n, false);
	ct = 0;
	now = 0;
	solve();

	cout << ans;

	return 0;
}