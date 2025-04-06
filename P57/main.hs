module P57 where

import Data.Ratio

half :: Rational
half = 1 % 2

next :: Rational -> Rational
next x = 1 / (2 + x)

result =
  length
    [ r
      | r <-
          map
            (1 +)
            (take 1000 (iterate next half)),
        ((> (length . show . denominator) r) . length . show . numerator) r
    ]

main = do
  print result
