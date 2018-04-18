#include <bits/stdc++.h>
using namespace std;
#define f(x, y, z) for(int x = (y); x <= (z); ++x)
#define g(x, y, z) for(int x = (y); x < (z); ++x)
#define h(x, y, z) for(int x = (y); x >= (z); --x)

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

struct Point
{
	s64 x, y;
	s128 len2() const
	{
		return (s128) x * x + (s128) y * y;
	}
};
Point operator +(const Point &a, const Point &b)
{
	return (Point) {a.x + b.x, a.y + b.y};
}

int n, m;
Point a[5][507];
vector<Point> b[5][507];
int c[5];
s128 ans;

void dfsb(int i, int j, int c, const Point &p)
{
	if(j == m)
	{
		b[i][c].push_back(p);
		return;
	}
	dfsb(i, j + 1, c, p);
	dfsb(i, j + 1, c + 1, p + a[i][j]);
}
void dfs(int i, const Point &p)
{
	if(i == n)
	{
		ans = max(ans, p.len2());
		return;
	}
	for(const Point &q: b[i][c[i]]) dfs(i + 1, p + q);
}

int main()
{
	int q;
	scanf("%d%d%d", &n, &m, &q);
	g(i, 0, n) g(j, 0, m) cin >> a[i][j].x;
	g(i, 0, n) g(j, 0, m) cin >> a[i][j].y;
	g(i, 0, n) dfsb(i, 0, 0, (Point) {0, 0});
	while(q--)
	{
		g(i, 0, n) scanf("%d", c + i);
		ans = 0;
		dfs(0, (Point) {0, 0});
		output(ans);
	}
	return 0;
}
