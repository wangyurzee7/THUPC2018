#include <bits/stdc++.h>
using namespace std;
#define f(x, y, z) for(int x = (y); x <= (z); ++x)
#define g(x, y, z) for(int x = (y); x < (z); ++x)
#define h(x, y, z) for(int x = (y); x >= (z); --x)

const int MAX_N = 6;
const int MAX_M = 667;
const int MAX_Q = 667;

const double PI = acos(-1);

mt19937_64 rng;

int r(int x)
{
	return rng() % x;
}
double rr()
{
	return (double) rng() / rng.max();
}

struct Point
{
	int x, y;
};

struct Data
{
	int n, m, q;
	Data(int n, int m, int q): n(n), m(m), q(q)
	{
	}
	Point p[MAX_N][MAX_M];
	void dump(const string &fn) const
	{
		printf("%s\n", fn.c_str());
		FILE *fout = fopen((fn + ".in").c_str(), "w");
		fprintf(fout, "%d %d %d\n", n, m, q);
		g(i, 0, n) g(j, 0, m) fprintf(fout, "%d%c", p[i][j].x, " \n"[j + 1 == m]);
		g(i, 0, n) g(j, 0, m) fprintf(fout, "%d%c", p[i][j].y, " \n"[j + 1 == m]);
		g(_, 0, q) g(i, 0, n) fprintf(fout, "%d%c", r(m + 1), " \n"[i + 1 == n]);
		fclose(fout);
		system(("time ./std < " + fn + ".in > " + fn + ".ans").c_str());
	}
};

void o(const Data &d)
{
	static int id = 0;
	d.dump("data/" + to_string(++id));
}

Data randomSq(int n, int m, int q, int u)
{
	Data d(n, m, q);
	g(i, 0, n) g(j, 0, m)
	{
		d.p[i][j].x = r(2 * u + 1) - u;
		d.p[i][j].y = r(2 * u + 1) - u;
	}
	return d;
}

Data randomSin(int n, int m, int q, int u)
{
	Data d(n, m, q);
	g(i, 0, n)
	{
		int xl = u * sin(rr() * PI), yl = u * sin(rr() * PI);
		double th = rr() * PI;
		double cos_th = cos(th), sin_th = sin(th);
		g(j, 0, m)
		{
			double x = r(2 * xl + 1) - xl;
			double y = r(2 * yl + 1) - yl;
			d.p[i][j].x = (x * cos_th - y * sin_th) / sqrt(2);
			d.p[i][j].y = (x * sin_th + y * cos_th) / sqrt(2);
		}
	}
	return d;
}

Data add0(double p0, Data d)
{
	g(i, 0, d.n) g(j, 0, d.m) if(rr() < p0) d.p[i][j].x = d.p[i][j].y = 0;
	return d;
}

Data cp(int t, Data d)
{
	while(t--)
	{
		int i = r(d.n), j1 = r(d.m), j2 = r(d.m);
		d.p[i][j1] = d.p[i][j2];
	}
	return d;
}

Data tcp(int t, Data d)
{
	while(t--)
	{
		int i = r(d.n), j1 = r(d.m), j2 = r(d.m);
		d.p[i][j1] = d.p[i][j2];
		d.p[i][j1].x += r(3) - 1;
		d.p[i][j1].y += r(3) - 1;
	}
	return d;
}

int main()
{
	// randomSq(6, 666, 666, 1000000000).dump("down/2");
	o(randomSq(6, 663, 666, 1000000000));
	o(add0(.01, randomSq(6, 666, 662, 1000000000)));
	o(cp(1 << 11, add0(.01, randomSq(6, 666, 662, 1000000000))));
	o(cp(1 << 15, add0(.01, randomSq(6, 666, 662, 1000000000))));
	o(cp(1 << 18, add0(.01, randomSq(6, 666, 662, 1000000000))));
	o(cp(1 << 20, add0(.01, randomSq(6, 666, 662, 1000000000))));
	o(cp(1 << 21, add0(.01, randomSq(6, 666, 662, 1000000000))));
	o(tcp(1 << 11, add0(.01, randomSq(6, 666, 662, 1000000000))));
	o(tcp(1 << 15, add0(.01, randomSq(6, 666, 662, 1000000000))));
	o(tcp(1 << 18, add0(.01, randomSq(6, 666, 662, 1000000000))));
	o(tcp(1 << 20, add0(.01, randomSq(6, 666, 662, 1000000000))));
	o(tcp(1 << 21, add0(.01, randomSq(6, 666, 662, 1000000000))));
	o(randomSin(6, 666, 664, 1000000000));
	o(add0(.01, randomSin(6, 665, 666, 1000000000)));
	o(cp(1 << 11, add0(.01, randomSin(6, 665, 666, 1000000000))));
	o(cp(1 << 15, add0(.01, randomSin(6, 665, 666, 1000000000))));
	o(cp(1 << 18, add0(.01, randomSin(6, 665, 666, 1000000000))));
	o(cp(1 << 20, add0(.01, randomSin(6, 665, 666, 1000000000))));
	o(cp(1 << 21, add0(.01, randomSin(6, 665, 666, 1000000000))));
	o(tcp(1 << 11, add0(.01, randomSin(6, 665, 666, 1000000000))));
	o(tcp(1 << 15, add0(.01, randomSin(6, 665, 666, 1000000000))));
	o(tcp(1 << 18, add0(.01, randomSin(6, 665, 666, 1000000000))));
	o(tcp(1 << 20, add0(.01, randomSin(6, 665, 666, 1000000000))));
	o(tcp(1 << 21, add0(.01, randomSin(6, 665, 666, 1000000000))));
	o(randomSq(1, 1, 666, 0));
	o(randomSq(6, 1, 666, 0));
	o(randomSq(1, 66, 666, 0));
	o(randomSq(6, 666, 666, 0));
	o(randomSq(6, 666, 666, 1));
	o(randomSq(6, 666, 666, 10));
	o(randomSq(6, 666, 666, 100));
}
