module P53 where

factorial :: Integer -> Integer
factorial x
  | x <= 1 = 1
  | otherwise = x * factorial (x - 1)

choose :: Integer -> Integer -> Integer
choose n r = factorial n `div` (factorial r * factorial (n - r))

result = length [v | v <- [choose n r | n <- [1..100], r <- [0..n]], v > 1_000_000]

main = do
  print result
