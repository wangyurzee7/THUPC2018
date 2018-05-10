#include <bits/stdc++.h>

using namespace std ;

int n ; 

const int MAXN = 1000010 ;

char s[MAXN] ; 

bool f[MAXN] ; 

int p[MAXN] ; 

int main() {
		int T ; 
		scanf("%d", &T) ; 
		while (T --) { 
				scanf("%s", s + 1) ;

				n = strlen(s + 1) ; 
				p[1] = 1 ; 
				int rp = 1, lp = 1; 
				s[n + 1] = 0, s[0] = 199 ;

				for (int i = 2; i <= n; i ++) { 
						if (i <= rp) { 
								p[i] = min(rp - i + 1, p[2 * lp - i]) ;
						}
						else p[i] = 1; 
						while (s[i + p[i]] == s[i - p[i]]) p[i] ++ ; 
						if (i + p[i] > rp) rp = i + p[i] - 1, lp = i ; 
				}
				for (int i = n; i; i --) { 
						f[i] = 0 ; 
						if (i + p[i] - 1 == n) f[i] = 1;  
						else {
								if (p[i] == i && f[i + p[i] - 1]) f[i] = 1 ; 
						}
				}
				for (int i = 1; i <= n; i ++) {
						if (f[i]) 
						printf("%d ", i) ; 
				}
				putchar(10);  
		}
}

							


