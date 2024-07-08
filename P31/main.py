from functools import cache

@cache
def ways(n, coins):
    if (n == 0):
        return 1
    if ((len(coins) == 0) or (n < coins[0])):
        return 0
    representations = 0
    for coin in coins:
        for multiple in range(coin, n+1, coin):
            representations += ways(n - multiple, tuple([x for x in coins if x < coin]))
    return representations

print( f"result = {ways(200, (1,2,5,10,20,50,100,200) )}")
