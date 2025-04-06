module P17 where

numToWord :: Int -> String
numToWord n 
    | n == 1 = "one"
    | n == 2 = "two"
    | n == 3 = "three"
    | n == 4 = "four"
    | n == 5 = "five"
    | n == 6 = "six"
    | n == 7 = "seven"
    | n == 8 = "eight"
    | n == 9 = "nine"
    | n == 10 = "ten"
    | n == 11 = "eleven"
    | n == 12 = "twelve"
    | n == 13 = "thirteen"
    | n == 14 = "fourteen"
    | n == 15 = "fifteen"
    | n == 16 = "sixteen"
    | n == 17 = "seventeen"
    | n == 18 = "eighteen"
    | n == 19 = "nineteen"
    | n == 20 = "twenty"
    | n == 30 = "thirty"
    | n == 40 = "forty"
    | n == 50 = "fifty"
    | n == 60 = "sixty"
    | n == 70 = "seventy"
    | n == 80 = "eighty"
    | n == 90 = "ninety"
    | n `elem` [100,200..900] = numToWord (div n 100) ++ " hundred"
    | n < 100 = numToWord (div n 10 * 10) ++ "-" ++ numToWord (mod n 10)
    | n < 1000 = numToWord (div n 100 * 100) ++ " and " ++ numToWord (mod n 100)
    | n == 1000 = "one thousand"
    | otherwise = "not supported"

result = sum (map (length . filter (`notElem` [' ', '-']) . numToWord) [1..1000])

main = do
    print result
