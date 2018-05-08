#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i < _; ++i)
#define down(i, x, y) for (int i = (x) - 1, _ = (y); i >= _; --i)
#define bin(x) (1 << (x))
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define SZ(x) (x).size()
//#define LX_JUDGE

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> Vi;

template<typename T> inline void upmax(T &x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T &x, T y) { x > y ? x = y : 0; }

const int mod = 998244353, G = 3;
const int MAX_N = bin(19) + 1;

constexpr int add(int a, int b) { return a + b >= mod ? a + b - mod : a + b; }
constexpr int sub(int a, int b) { return a - b < 0 ? a - b + mod : a - b; }
constexpr ll mul(ll a, ll b) { return a * b % mod; }
inline int qpow(int x, int n) {
	int ans = 1;
	for ( ; n; n /= 2, x = mul(x, x)) if (n & 1) ans = mul(ans, x);
	return ans;
}
inline int mod_inv(int x) { return qpow(x, mod - 2); }

class NTT_WORKER {
private :
	int w[2][2 * MAX_N];
	void fft(int a[], int n, int w[]) {
		for (int i = 0, j = 0; i < n; ++i) {
			if (i < j) swap(a[i], a[j]);
			for (int l = n / 2; (j ^= l) < l; l /= 2);
		}
		int *r = w + 2;
		for (int i = 2, m = 1; i <= n; r += i, m = i, i *= 2) {
			for (int j = 0; j < n; j += i) for (int k = 0; k < m; ++k) {
				int t = mul(a[j + k + m], r[k]);
				a[j + k + m] = sub(a[j + k], t);
				a[j + k] = add(a[j + k], t);
			}
		}
	}
public :
	void init(int n) {
		int a = qpow(G, (mod - 1) / n), b = mod_inv(a);
		w[0][n] = 1; w[1][n] = 1;
		rep (i, n + 1, n + n) {
			w[0][i] = mul(w[0][i - 1], a);
			w[1][i] = mul(w[1][i - 1], b);
		}
		down (i, n, 1) {
			w[0][i] = w[0][i << 1];
			w[1][i] = w[1][i << 1];
		}
	}
	void dft(int a[], int n) {
		fft(a, n, w[0]);
	}
	void idft(int a[], int n) {
		fft(a, n, w[1]);
		int r = mod_inv(n);
		rep (i, 0, n) a[i] = mul(a[i], r);
	}
} my;

void poly_inv(int n, const int a[], int b[]) {
	if (n == 1) {
		b[0] = mod_inv(a[0]);
		return ;
	}
	static int c[MAX_N];
	int m = (n + 1) / 2;
	poly_inv(m, a, b);
	int T = bin(32 - __builtin_clz(n + n));
	memcpy(c, a, n << 2);
	memset(c + n, 0, (T - n) << 2);
	my.dft(c, T);
	memset(b + m, 0, (T - m) << 2);
	my.dft(b, T);
	rep (i, 0, T) b[i] = mul(b[i], sub(2, mul(b[i], c[i])));
	my.idft(b, T);
}
void rev_copy(int n, const int a[], int b[]) {
	rep (i, 0, n) b[i] = a[n - i - 1];
}
void reverse(int n, int a[]) {
	int t;
	rep (i, 0, n / 2) { t = a[i]; a[i] = a[n - i - 1]; a[n - i - 1] = t; }
}
void poly_mul(int n, int m, const int a[], const int b[], int c[]) {
	static int X[MAX_N], Y[MAX_N];
	int T = bin(32 - __builtin_clz(n + m));
	memcpy(X, a, n << 2); memset(X + n, 0, (T - n) << 2);
	my.dft(X, T);
	memcpy(Y, b, m << 2); memset(Y + m, 0, (T - m) << 2);
	my.dft(Y, T);
	rep (i, 0, T) X[i] = mul(X[i], Y[i]);
	my.idft(X, T);
	memcpy(c, X, (n + m - 1) << 2);
}
void poly_div(int n, int m, const int A[], const int B[], int D[], int R[]) {
	while (n and !A[n - 1]) --n;
	while (m and !B[m - 1]) --m;
	if (n < m) {
		if (D) D[0] = 0;
		memcpy(R, A, n << 2);
		memset(R + n, 0, (m - n) << 2);
		return ;
	}

	static int X[MAX_N], Y[MAX_N];
	int t = n - m + 1, Tn = bin(32 - __builtin_clz(t * 2));

	memset(X, 0, Tn << 2); rev_copy(m, B, X);  poly_inv(t, X, Y);
	memset(Y + t, 0, (Tn - t) << 2); my.dft(Y, Tn);
	rev_copy(n, A, X); memset(X + t, 0, (Tn - t) << 2); my.dft(X, Tn);
	rep (i, 0, Tn) X[i] = mul(X[i], Y[i]); my.idft(X, Tn); reverse(t, X);

	if (D) memcpy(D, X, n << 2); if (!R) return ;

	Tn = bin(32 - __builtin_clz(n));
	memset(X + t, 0, (Tn - t) << 2); my.dft(X, Tn);
	memcpy(Y, B, m << 2); memset(Y + m, 0, (Tn - m) << 2); my.dft(Y, Tn);
	rep (i, 0, Tn) X[i] = mul(X[i], Y[i]); my.idft(X, Tn);
	rep (i, 0, m) R[i] = sub(A[i], X[i]);
	while (m and !R[m - 1]) --m;
}

void maintain(Vi &pol) { while (!pol.empty() and !pol.back()) pol.pop_back(); }
Vi operator * (const Vi &a, const Vi &b) {
	Vi c(SZ(a) + SZ(b));
	poly_mul(SZ(a), SZ(b), a.data(), b.data(), c.data());
	maintain(c); return c;
}
Vi operator % (const Vi &a, const Vi &b) {
	Vi c(SZ(b));
	poly_div(SZ(a), SZ(b), a.data(), b.data(), 0, c.data());
	maintain(c); 
	return c;
}
Vi der(const Vi &a) {
	Vi r(SZ(a) - 1);
	rep (i, 1, a.size()) r[i - 1] = mul(a[i], i);
	return r;
}

int a[MAX_N], val[MAX_N];

Vi divide(int l, int r) {
	if (l == r) return Vi{sub(0, a[l]), 1};
	int m = (l + r) / 2;
	return divide(l, m) * divide(m + 1, r);
}

Vi pre[MAX_N * 4];

void prepare(int o, int l, int r) {
	if (l == r) return void(pre[o] = Vi{sub(0, a[l]), 1});
	int m = (l + r) / 2;
	prepare(o << 1, l, m); prepare(o << 1 | 1, m + 1, r);
	pre[o] = pre[o << 1] * pre[o << 1 | 1];
}

void solve(int o, int l, int r, Vi u) {
	u = u % pre[o];
	if (l == r) {
		val[l] = u[0];
		return ;
	}
	int m = (l + r) / 2;
	solve(o << 1, l, m, u); solve(o << 1 | 1, m + 1, r, u);
}

int Solve(int N) {
	Vi dfm = der(divide(0, N - 1));
	prepare(1, 0, N - 1);
	solve(1, 0, N - 1, dfm);
	int ans = 0;
	rep (i, 0, N) {
		int t = mod_inv(val[i]);
		if ((N - i + 1) & 1) t = sub(0, t);
		ans = add(ans, t);
	}
	ans = mul(ans, (mod + 1) / 2);
	return ans;
}

vector<int> g[MAX_N];
int siz[MAX_N];
int N, A, B;
int sta[MAX_N], tot;

bool dfs1(int x, int f) {
	if (x == B) return 1;
	siz[x] = 1;
	bool flag = 0;
	for (auto y : g[x]) {
		if (y == f) continue ;
		if (dfs1(y, x)) {
			flag = 1;
		} else {
			siz[x] += siz[y];
		}
	}
	if (flag) sta[tot++] = x;
	return flag;
}
void dfs2(int x, int f) {
	siz[x] = 1;
	for (auto y : g[x]) {
		if (y == f) continue ;
		dfs2(y, x);
		siz[x] += siz[y];
	}
}

int main() {
#ifdef LX_JUDGE
	freopen(".in", "r", stdin);
#endif
	my.init(bin(19));
	scanf("%d%d%d", &N, &A, &B);

	rep (i, 1, N) {
		int x, y;
		scanf("%d%d", &x, &y);
		g[x].pb(y); g[y].pb(x);
	}

	if (A == B) {
		dfs2(A, 0);
		int r = 1;
		rep (i, 1, N + 1) r = mul(r, siz[i]);
		r = mod_inv(r);
		rep (i, 1, N + 1) r = mul(r, i);
		printf("%d\n", r);
		return 0;
	}

	sta[tot++] = B;
	dfs1(A, 0); dfs2(B, sta[1]); 
	rep (i, 0, tot) sta[i] = siz[sta[i]];

	cerr << tot << endl;

	int p = 1;
	rep (i, 1, N + 1) p = mul(p, siz[i]);
	p = mod_inv(p);
	rep (i, 0, tot) p = mul(p, sta[i]);
	rep (i, 1, N + 1) p = mul(p, i);

	a[0] = 0;
	rep (i, 0, tot) a[i + 1] = a[i] + sta[i];
	int ans = mul(Solve(tot + 1), p);

	printf("%d\n", ans);

	return 0;
}
