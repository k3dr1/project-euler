module Main where

import Data.Bits (xor)
import Data.Char (chr, ord)

keys = [(a, b, c) | a <- [97 .. 122], b <- [97 .. 122], c <- [97 .. 122]]

wordsWhen :: (Char -> Bool) -> String -> [String]
wordsWhen p s = case dropWhile p s of
  "" -> []
  s' -> w : wordsWhen p s''
    where
      (w, s'') = break p s'

charXor :: Char -> Char -> Char
charXor a b = chr (ord a `xor` ord b)

unxor :: (Int, Int, Int) -> ([Char] -> [Char])
unxor (k1, k2, k3) = zipWith charXor (cycle [chr k1, chr k2, chr k3])

f :: [Char] -> [((Int, Int, Int), [Char])]
f text =
  let allDecrypts = zipWith (\k t -> (k, unxor k t)) keys (repeat text)
   in filter (all ((\x -> (32 <= x) && (x <= 122)) . ord) . snd) allDecrypts

main = do
  contents <- readFile "0059_cipher.txt"
  let as_ints = map (takeWhile (/= '\n')) (wordsWhen (== ',') contents)
  let as_chars = map (chr . read) as_ints
  let possibleDecrypts = f as_chars
  print possibleDecrypts
  let correctDecrypt = filter ((== (101, 120, 112)) . fst) possibleDecrypts
  print (sum (map ord (snd $ head correctDecrypt)))
