module P52 where

import Data.List (sort)

sameDigits :: [Integer] -> Bool
sameDigits a = all (== head s) s where s = map (sort . show) a

result = head [x | x <- [1 ..], sameDigits [x * k | k <- [1 .. 6]]]

main = do
  print result
