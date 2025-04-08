module Main where

isPrime :: Int -> Bool
isPrime n
  | n < 2 = False
  | otherwise = null [k | k <- [2 .. ((floor . sqrt . fromIntegral) n)], mod n k == 0]

-- Replaces *s with every possible digit, and
-- counts the number of resulting primes
primeFamilyCount :: [Char] -> Int
primeFamilyCount s
  | '*' `notElem` s = if (isPrime . read) s then 1 else 0
  | otherwise =
      let replace string r = map (\c -> if c == '*' then r else c) s
       in length $ filter id (map (isPrime . read . replace s) (if head s == '*' then ['1' .. '9'] else ['0' .. '9']))

-- Given a string with only 'd' and '*' generates a list of all possible strings where d is replaced by digits
-- "d*" -> ["1*", "2*", "3*",..., "9*"]
generateCandidates :: [Char] -> [[Char]]
generateCandidates [c] = if c == '*' then ["*"] else map (: []) ['1' .. '9']
generateCandidates (c : cs) = [u ++ v | u <- generateCandidates [c], v <- generateCandidates cs]

starsAndDigits :: Int -> [[Char]] -> [[Char]]
starsAndDigits 0 ws = ws
starsAndDigits 1 ws = ["d", "*"]
starsAndDigits i ws = [u : v | u <- ['d', '*'], v <- starsAndDigits (i-1) ws]

numDigits = 6
minPrimeFamilyCount = 8
families = concatMap generateCandidates (starsAndDigits numDigits [])
result = filter ((>=minPrimeFamilyCount) . primeFamilyCount) families

main = do
  let x = head result 
      replace string r = map (\c -> if c == '*' then r else c) string
   in print $ head ( map (replace x) (if head x == '*' then ['1' .. '9'] else ['0' .. '9']))
