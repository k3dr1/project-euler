module P56 where
import Data.List (sort)

digitSum :: Integer -> Integer
digitSum x
    | x < 10 = x
    | otherwise = mod x 10 + digitSum (div x 10)

result = maximum [digitSum (a^b) | a <- [1..99], b <- [1..99]]

main = do
  print result
