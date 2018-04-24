#include <bits/stdc++.h>
using namespace std;
#define f(x, y, z) for(int x = (y); x <= (z); ++x)
#define g(x, y, z) for(int x = (y); x < (z); ++x)
#define h(x, y, z) for(int x = (y); x >= (z); --x)

const int MAX_N = 6;
const int MAX_M = 667;
const int MAX_Q = 667;
const int MAX_EV = MAX_N * MAX_M * MAX_M / 2;

// #define ENSURE

#ifdef ENSURE
void ensure_impl(bool x, int line, const char *info)
{
	if(x) return;
	printf("line %d: ensure \"%s\" failed!\n", line, info, x);
	exit(1);
}
#define ensure(x) ensure_impl(x, __LINE__, #x)
#else
#define ensure(x) do{x;}while(0)
#endif

struct test_type_expected
{
};
void test_type(test_type_expected foo)
{
}

typedef uint16_t u16;
typedef int32_t s32;
typedef int64_t s64;
typedef __int128_t s128;
void output(s128 x)
{
	if(x == 0)
	{
		putchar('0');
		putchar('\n');
		return;
	}
	char buf[48], *ptr = buf + 47;
	*ptr-- = 0;
	for(; x; x /= 10) *ptr-- = '0' + x % 10;
	puts(ptr + 1);
}

template <class T, class LenT>
struct basic_point
{
	T x, y;
	LenT len2() const
	{
		return *this * *this;
	}
	LenT operator *(const basic_point<T, LenT> &b) const
	{
		return (LenT) x * b.x + (LenT) y * b.y;
	}
	bool operator <(const basic_point<T, LenT> &b) const
	{
		return x != b.x ? (x < b.x) : (y < b.y);
	}
	bool operator ==(const basic_point<T, LenT> &b) const
	{
		return x == b.x && y == b.y;
	}
	template <class T2, class LenT2>
	basic_point<typename common_type<T, T2>::type,
			typename common_type<LenT, LenT2>::type>
	operator +(const basic_point<T2, LenT2> &b) const
	{
		return (basic_point<typename common_type<T, T2>::type,
				typename common_type<LenT, LenT2>::type>) {x + b.x, y + b.y};
	}
	template <class T2, class LenT2>
	basic_point<typename common_type<T, T2>::type,
			typename common_type<LenT, LenT2>::type>
	operator -(const basic_point<T2, LenT2> &b) const
	{
		return (basic_point<typename common_type<T, T2>::type,
				typename common_type<LenT, LenT2>::type>) {x - b.x, y - b.y};
	}
	template <class T2, class LenT2>
	basic_point<T, LenT> &operator +=(const basic_point<T2, LenT2> &b)
	{
		x += b.x; y += b.y; return *this;
	}
};
typedef basic_point<s32, s64> point32;
typedef basic_point<s64, s128> point64;

const point32 INIT_DIR = (point32) {1000000007, -1};

struct event
{
	s32 x, y;
	int i, j1, j2;
	u16 key[2];
	bool operator <(const event &b) const
	{
		s64 l = (s64) y * b.x, r = (s64) b.y * x;
		return l != r ? (l < r) : (i < b.i);
		// return (s64) y * b.x < (s64) b.y * x;
	}
	bool operator ==(const event &b) const
	{
		return (s64) y * b.x == (s64) b.y * x;
	}
	void flip()
	{
		x = -x; y = -y;
	}
};

void sort_events(event *es, int n)
{
	static event aux[MAX_EV];
	static int b[1 << 16];
	g(i, 0, n)
	{
		ensure(es[i].x || es[i].y);
		if(es[i].y < 0 || (es[i].y == 0 && es[i].x < 0)) es[i].flip();
		float k = (long double) es[i].y / es[i].x;
		memcpy(es[i].key, &k, sizeof(es[i].key));
		if(es[i].key[1] & 0x8000)
		{
			es[i].key[0] = ~es[i].key[0];
			es[i].key[1] = ~es[i].key[1] | (u16) 0x8000;
		}
	}
	memset(b, 0, sizeof(b));
	g(i, 0, n) ++b[es[i].key[0]];
	g(i, 1, 1 << 16) b[i] += b[i - 1];
	h(i, n - 1, 0) aux[--b[es[i].key[0]]] = es[i];
	
	memset(b, 0, sizeof(b));
	g(i, 0, n) ++b[aux[i].key[1]];
	g(i, 1, 1 << 16) b[i] += b[i - 1];
	h(i, n - 1, 0) es[--b[aux[i].key[1]]] = aux[i];
	
	int cnt = 0;
	g(i, 1, n) if(es[i] < es[i - 1])
	{
		swap(es[i], es[i - 1]);
		i -= 2;
		++cnt;
	}
	fprintf(stderr, "cnt %d\n", cnt);
}

struct input
{
	int n, m, q;
	point32 a[MAX_N][MAX_M];
	int c[MAX_Q][MAX_N];
	input()
	{
		scanf("%d%d%d", &n, &m, &q);
		g(i, 0, n) g(j, 0, m) scanf("%d", &a[i][j].x);
		g(i, 0, n) g(j, 0, m) scanf("%d", &a[i][j].y);
		g(k, 0, q) g(i, 0, n) scanf("%d", &c[k][i]);
	}
};

int CNT = 0;

struct query
{
	point64 cur;
	point64 last[MAX_N];
	s128 ans;
	bool started;
	query()
	{
		memset(this, 0, sizeof(*this));
	}
	void init(const input &in, int k);
	void start_events()
	{
		ans = cur.len2();
		started = true;
	}
	void recv_notify(int i, const point64 &p)
	{
		++CNT;
		cur = cur - last[i] + p;
		last[i] = p;
		if(started) ans = max(ans, cur.len2());
	}
} queries[MAX_Q];

struct point32_cnt
{
	point32 p; int c;
};
struct point64_cnt
{
	point64 p; int c;
};
struct point_set
{
	point32_cnt p[MAX_M];
	int n, i;
	int rank[MAX_M], inv[MAX_M];
	point64_cnt sp[MAX_M];
	vector<int> listeners[MAX_M];
	int tml[MAX_M], tmr[MAX_M], ctm;
	int que[MAX_M], qn;
	void init(input &in, int i)
	{
		memset(tml, 0, sizeof(tml));
		memset(tmr, 0, sizeof(tmr));
		ctm = 1;
		this->i = i;
		point32 *q = in.a[i];
		sort(q, q + in.m);
		n = 0;
		g(j, 0, in.m) if(j && q[j] == q[j - 1]) ++p[n - 1].c; else
		{
			p[n].p = q[j]; p[n++].c = 1;
		}
	}
	int make_events(event *es, int en)
	{
		g(j1, 0, n) g(j2, j1 + 1, n) es[en++] = (event)
		{
			p[j1].p.y - p[j2].p.y, p[j2].p.x - p[j1].p.x, i, j1, j2
		};
		return en;
	}
	void start_events()
	{
		g(i, 0, n) inv[i] = i;
		sort(inv, inv + n, [this](int j1, int j2)
		{
			return p[j1].p * INIT_DIR > p[j2].p * INIT_DIR;
		});
		g(i, 0, n) rank[inv[i]] = i;
		calc_sp(0, n - 1);
	}
	void calc_sp(int r1, int r2)
	{
		f(i, r1, r2)
		{
			point64_cnt &sum = sp[i];
			sum = i ? sp[i - 1] : (point64_cnt) {(point64) {0, 0}, 0};
			point32_cnt &cur = p[inv[i]];
			g(_, 0, cur.c) notify(++sum.c, sum.p += cur.p);
		}
	}
	void add_listener(int rk, int k)
	{
		listeners[rk].push_back(k);
	}
	void notify(int rk, const point64 &p)
	{
		for(int k: listeners[rk]) queries[k].recv_notify(i, p);
	}
	void recv_events(event *e, event *r)
	{
		++ctm;
		qn = 0;
		for(event *it = e; it != r; ++it)
		{
			ensure(it->i == i);
			int t1 = rank[it->j1], t2 = rank[it->j2];
			if(t1 + 1 == t2)
			{
				tmr[t1] = tml[t2] = ctm;
				que[qn++] = t1;
			}
			if(t2 + 1 == t1)
			{
				tmr[t2] = tml[t1] = ctm;
				que[qn++] = t1;
			}
		}
		int expected = 0;
		g(k, 0, qn)
		{
			int c = que[k];
			if(!tml[c] && !tmr[c]) continue;
			int l = c, r = c;
			while(tml[l] == ctm)
			{
				tml[l--] = 0; tmr[l] = 0;
			}
			while(tmr[r] == ctm)
			{
				tmr[r++] = 0; tml[r] = 0;
			}
			expected += (r - l + 1) * (r - l) / 2;
			int ll = l, rr = r;
			for(; l < r; ++l, --r)
			{
				swap(rank[inv[l]], rank[inv[r]]);
				swap(inv[l], inv[r]);
			}
			calc_sp(ll, rr);
		}
		ensure(expected == r - e);
	}
} point_sets[MAX_N];

void query::init(const input &in, int k)
{
	g(i, 0, in.n) point_sets[i].add_listener(in.c[k][i], k);
}

int main()
{
	static input in;
	
	g(i, 0, in.n) point_sets[i].init(in, i);
	
	static event es[MAX_EV];
	int en = 0;
	g(i, 0, in.n) en = point_sets[i].make_events(es, en);
	sort_events(es, en);
	es[en].i = -1;
	
	g(k, 0, in.q) queries[k].init(in, k);
	
	g(i, 0, in.n) point_sets[i].start_events();
	g(k, 0, in.q) queries[k].start_events();
	
	g(_, 0, 2) for(int i = 0, j; i != en; i = j)
	{
		for(j = i; es[j] == es[i] && es[j].i == es[i].i; ++j);
		point_sets[es[i].i].recv_events(es + i, es + j);
	}
	
	g(k, 0, in.q) output(queries[k].ans);
	fprintf(stderr, "CNT = %d\n", CNT);
	return 0;
}
