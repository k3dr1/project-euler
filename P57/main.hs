module P57 where

import Data.Ratio

result =
  length
    [ r
      | r <-
          map
            (1 +)
            ( take
                1000
                ( iterate ((1 /) . (+ 2)) (1 % 2)
                )
            ),
        ( ( >
              (length . show . denominator)
                r
          )
            . length
            . show
            . numerator
        )
          r
    ]

main = do
  print result
