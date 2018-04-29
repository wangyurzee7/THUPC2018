#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#define rep(i, x, y) for (int i = (x), _ = (y); i < _; ++i)
#define down(i, x, y) for (int i = (x) - 1, _ = (y); i >= _; --i)
#define bin(x) (1 << (x))
#define len(x) ((int) (x).size())
namespace __banban__ {
	const int MAX_N = 1 << 19 | 1;
	const int mod = 998244353, G = 3;
	using ll = long long;
	
	typedef std::vector<int> Poly;
	constexpr int add(int a, int b) { return a + b >= mod ? a + b - mod : a + b; }
	constexpr int sub(int a, int b) { return a - b < 0 ? a - b + mod : a - b; }
	constexpr int mul(int a, int b) { return (ll) a * b % mod; }
	inline int qpow(int x, int n) { int r = 1; for ( ; n; n /= 2, x = mul(x, x)) if (n & 1) r = mul(r, x); return r; }
	inline int mod_inv(int x) { return qpow(x, mod - 2); }
	
	int N, A, B, path[MAX_N], n_path, sum[MAX_N], cur_root, down;
	bool v[MAX_N];
	struct Adj{int to; Adj *nxt;} *fir[MAX_N], mem[MAX_N * 2], *tot = mem;
	
	bool dfs_chain(int i) {
		v[i] = 1;
		if(i == A) return (path[++n_path] = i);
		for(Adj *k = fir[i]; k; k = k->nxt)
			if(!v[k->to] && dfs_chain(k->to))
				return (path[++n_path] = i);
		return 0;
	}
	int dfs_size(int i) {
		v[i] = 1;
		int cnt = 1;
		for(Adj *k = fir[i]; k; k = k->nxt)
			if(!v[k->to]) cnt += dfs_size(k->to);
		v[i] = 0;
		if(i != cur_root) down = mul(down, cnt);
		return cnt;
	}
	
	class BGG_NTT_WORKER {
	private :
		int init_n;
		int w[2][2 * MAX_N];
		void fft(int a[], int n, int w[]) {
			init(n);
			for (int i = 0, j = 0; i < n; ++i) {
				if (i < j) std::swap(a[i], a[j]);
				for (int l = n / 2; (j ^= l) < l; l /= 2);
			}
			int *r = w + 1;
			for (int i = 2, m = 1; i <= n; r += m, m = i, i *= 2) {
				for (int j = 0; j < n; j += i) 
				{
					int *a_j_m = a + j + m, *a_j = a + j, t;
					for (int k = 0; k < m; ++k) {
						t 			= mul(a_j_m[k], r[k]);
						a_j_m[k] 	= sub(a_j[k], t);
						a_j[k] 		= add(a_j[k], t);
					}
				}
			}
		}
		void fft(int a[], int b[], int n, int w[]) {
			init(n);
			for (int i = 0, j = 0; i < n; ++i) {
				if (i < j) {std::swap(a[i], a[j]); std::swap(b[i], b[j]);}
				for (int l = n / 2; (j ^= l) < l; l /= 2);
			}
			int *r = w + 1;
			for (int i = 2, m = 1; i <= n; r += m, m = i, i *= 2) {
				for (int j = 0; j < n; j += i) 
				{
					int *a_j_m = a + j + m, *a_j = a + j, ta;
					int *b_j_m = b + j + m, *b_j = b + j, tb;
					for (int k = 0; k < m; ++k) {
						ta 			= mul(a_j_m[k], r[k]);
						a_j_m[k] 	= sub(a_j[k], ta);
						a_j[k] 		= add(a_j[k], ta);
						tb 			= mul(b_j_m[k], r[k]);
						b_j_m[k] 	= sub(b_j[k], tb);
						b_j[k] 		= add(b_j[k], tb);
					}
				}
			}
		}
	public :
		void init(int n) {
			if(n <= init_n) return; init_n = n;
			int a = qpow(G, (mod - 1) / n), b = mod_inv(a), h = n >> 1;
			w[0][h] = 1; w[1][h] = 1;
			rep (i, h + 1, n) {
				w[0][i] = mul(w[0][i - 1], a);
				w[1][i] = mul(w[1][i - 1], b);
			}
			down (i, h, 1) {
				w[0][i] = w[0][i << 1];
				w[1][i] = w[1][i << 1];
			}
		}
		void dft(int a[], int n) {
			fft(a, n, w[0]);
		}
		void dft(int a[], int b[], int n) {
			fft(a, b, n, w[0]);
		}
		void idft(int a[], int n) {
			fft(a, n, w[1]);
			int r = mod_inv(n);
			rep (i, 0, n) a[i] = mul(a[i], r);
		}
		void idft(int a[], int b[], int n) {
			fft(a, b, n, w[1]);
			int r = mod_inv(n);
			rep (i, 0, n) {a[i] = mul(a[i], r); b[i] = mul(b[i], r);}
		}
		void poly_mul(int n_a, int n_b, int a[], int b[], int c[])
		{
			int n = bin(32 - __builtin_clz(n_a + n_b - 1));
			fft(a, b, n, w[0]);
			rep (i, 0, n) c[i] = mul(a[i], b[i]);
			idft(c, n);
		}
	}	my;
	
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

	void maintain(Poly &pol) { while (!pol.empty() and !pol.back()) pol.pop_back(); }
	Poly operator * (const Poly &a, const Poly &b) {
		Poly c(len(a) + len(b));
		poly_mul(len(a), len(b), a.data(), b.data(), c.data());
		maintain(c); return c;
	}
	Poly operator % (const Poly &a, const Poly &b) {
		Poly c(len(b));
		poly_div(len(a), len(b), a.data(), b.data(), 0, c.data());
		maintain(c); 
		return c;
	}
	
	constexpr int polish(int n) {return (n == 1) ? 1 : bin(32 - __builtin_clz(n - 1));}
	Poly pre[MAX_N << 1];
	void divide(int o, int l, int r, Poly &P, Poly &Q) {
		if(l == r) {
			P = move(Poly{1});
			Q = move(Poly{sub(0, sum[l]), 1});
		} else {
			int m = (l + r) >> 1;
			Poly PL, QL;	divide(o << 1, l, m, PL, QL);
			Poly PR, QR;	divide(o << 1 | 1, m + 1, r, PR, QR);
			int t = polish(QL.size() + QR.size() - 1);
			PL.resize(t); PR.resize(t); my.dft(PL.data(), PR.data(), t);
			QL.resize(t); QR.resize(t); my.dft(QL.data(), QR.data(), t);
			P.resize(t); Q.resize(t);
			rep (i, 0, t) {
				P[i] = add(mul(PL[i], ((r ^ m) & 1) ? sub(0, QR[i]) : QR[i]), mul(QL[i], PR[i]));
				Q[i] = mul(QL[i], QR[i]);
			}
			my.idft(P.data(), Q.data(), t); maintain(P); maintain(Q);
		}
		pre[o] = Q;
	}
	int out[MAX_N];
	void solve(int o, int l, int r, Poly P) {
		P = P % pre[o];
		if(l == r) {out[l] = P[0]; return; }
		int m = (l + r) >> 1;
		solve(o << 1, l, m, P);
		solve(o << 1 | 1, m + 1, r, move(P));
	}
	
	void __main__() {
		std::ios::sync_with_stdio(0);
		std::cin.tie(0); std::cout.tie(0);
		std::cin >> N >> A >> B;
		for(int i = 2, x, y; i <= N; ++i) {
			std::cin >> x >> y;
			*++tot = (Adj) {y, fir[x]}; fir[x] = tot;
			*++tot = (Adj) {x, fir[y]}; fir[y] = tot;
		}
		dfs_chain(B);
		memset(v + 1, 0, N);
		down = 2;
		for(int i = 1; i <= n_path; ++i) {
			v[path[i - 1]] = v[path[i + 1]] = 1;
			sum[i] = sum[i - 1] + dfs_size(cur_root = path[i]);
			v[path[i - 1]] = v[path[i + 1]] = 0;
		}
		down = mod_inv(down);
		Poly P;
		if(true) { Poly Q; divide(1, 0, n_path, P, Q); }
		solve(1, 0, n_path, P);
		int ans = 0;
		for(int i = 0; i <= n_path; ++i)
			ans = add(ans, mod_inv(out[i]));
		ans = mul(ans, down); 
		for(int i = 1; i <= N; ++i) ans = mul(ans, i);
		std::cout << ans << std::endl;
	}
}
int main() {
	__banban__::__main__();	
}