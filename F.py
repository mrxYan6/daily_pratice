import math
t = int(input())

for tt in range(t):
    n, k = map(int,input().split(' '))
    # print(n,k)
    # # print(type(k))
    # cur = input()
    # print(type(cur))
    # print(cur[0:3])
    k += 1
    x = n % k
    aver  = n // k
    now = input()

    def dfs (l, cur, len, cnt):
        if cnt == k :
            if(l  == n):
                return cur
            else :
                return math.inf
        else:
            if(l + len - 1 > n):return int(now)

            res = math.inf

            if (l + len <= n):
                res = min(res, dfs(l + len, cur + int(now[l,l+len]), len, cnt + 1))
            if (l + len - 1 <= n and l + len - 1 > l):
                res = min(res, dfs(l + len - 1, cur + int(now[l,l+len-1]),len-1,cnt+1))
            if (l + len + 1 <= n):
                res = min(res, dfs(l + len + 1, cur + int(now[l,l+len+1]),len+1,cnt+1))

            return res
    print(dfs(0, 0, aver, 0))

