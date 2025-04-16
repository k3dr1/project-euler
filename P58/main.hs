module Main where

isPrime :: Int -> Bool
isPrime n
  | n < 2 = False
  | otherwise = null [k | k <- [2 .. ((floor . sqrt . fromIntegral) n)], mod n k == 0]

a :: Int -> Int
a x = (x - 2) ^ 2 + (x - 1)

b :: Int -> Int
b x = (x - 2) ^ 2 + 2 * (x - 1)

c :: Int -> Int
c x = (x - 2) ^ 2 + 3 * (x - 1)

getPrimePercentageAtSideLength x =
  (fromIntegral (sum (map (length . filter isPrime . (\s -> [a s, b s, c s])) [1, 3 .. x])) :: Float)
    / (fromIntegral ((((x + 1) `div` 2) - 1) * 4 + 1) :: Float)

percentages = map (\x -> (x, getPrimePercentageAtSideLength x)) [1009, 1011 ..]

result = head (filter (\(x, y) -> y < 0.10) percentages)

main = do
  putStr "side_length="
  putStr (show (fst result))
  putStr " "
  putStr "percentage="
  putStr (show (snd result))
  putStrLn ""
