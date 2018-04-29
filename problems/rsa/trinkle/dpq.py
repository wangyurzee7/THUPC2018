import gmpy2
def work(n,e1,e2,message1,message2):
        # s & t
        gcd, s, t = gmpy2.gcdext(e1, e2)
        if s < 0:
            s = -s
            message1 = gmpy2.invert(message1, n)
        if t < 0:
            t = -t
            message2 = gmpy2.invert(message2, n)
        plain = gmpy2.powmod(message1, s, n) * gmpy2.powmod(message2, t, n) % n
        print plain
T=int(input())
for __ in range(T):
        s=raw_input().split(' ')
        c1,c2,e1,e2,n=int(s[0]),int(s[1]),int(s[2]),int(s[3]),int(s[4])
        work(n,e1,e2,c1,c2)

