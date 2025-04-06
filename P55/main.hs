module P55 where

isPalindrome :: Integer -> Bool
isPalindrome x = show x == (reverse . show) x

isLychrel x n
    | isPalindrome x = False
    | n == 0 = not (isPalindrome x)
    | otherwise = isLychrel (x + (read . reverse . show) x) (n-1)

result = length [v | v <- [1..10_000], isLychrel (v + (read . reverse . show) v) 50]

main = do
  print result
