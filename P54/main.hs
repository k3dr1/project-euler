module Main where

import Control.Monad
import Data.List (group, sort, sortBy)
import Data.Maybe (fromJust, isJust)
import Data.Ord
import System.IO

data Rank = Two | Three | Four | Five | Six | Seven | Eight | Nine | Ten | Jack | Queen | King | Ace deriving (Show, Eq, Ord, Enum)

data Suit = Diamonds | Clubs | Hearts | Spades deriving (Show, Eq)

data Card = Card Suit Rank deriving (Show, Eq)

instance Ord Card where
  compare (Card _ r1) (Card _ r2) = compare r1 r2

getRank :: Card -> Rank
getRank (Card _ r) = r

getSuit :: Card -> Suit
getSuit (Card s _) = s

validHand :: [Card] -> Bool
validHand = (== 5) . length

isSameSuit :: [Card] -> Bool
isSameSuit hand =
  all
    ((== (getSuit . head) hand) . getSuit)
    hand

isOnePair :: [Card] -> Maybe Rank
isOnePair hand =
  let pairGroups = filter ((== 2) . length) ((group . sort) (map getRank hand))
   in if not (null pairGroups) then Just (head (last pairGroups)) else Nothing

isTwoPairs :: [Card] -> Maybe Rank
isTwoPairs hand =
  let pairGroups = filter ((== 2) . length) ((group . sort) (map getRank hand))
   in if length pairGroups == 2 then Just (head (last pairGroups)) else Nothing

isThreeOfaKind :: [Card] -> Maybe Rank
isThreeOfaKind hand =
  let treyGroups = filter ((== 3) . length) ((group . sort) (map getRank hand))
   in if not $ null treyGroups then Just $ head $ head treyGroups else Nothing

isStraight :: [Card] -> Maybe Rank
isStraight hand =
  let consecutive = and (zipWith (\x y -> (succ . getRank) x == getRank y) (sort hand) ((tail . sort) hand))
   in if consecutive then Just $ maximum (map getRank hand) else Nothing

isFlush :: [Card] -> Maybe Rank
isFlush hand = if isSameSuit hand then Just $ maximum (map getRank hand) else Nothing

isFullHouse :: [Card] -> Maybe (Rank, Rank)
isFullHouse hand =
  if (&&) (isJust (isThreeOfaKind hand)) (isJust (isOnePair hand))
    then Just (fromJust (isThreeOfaKind hand), fromJust (isOnePair hand))
    else Nothing

isFourOfaKind :: [Card] -> Maybe Rank
isFourOfaKind hand =
  let quadGroups = filter ((== 4) . length) ((group . sort) (map getRank hand))
   in if not $ null quadGroups then Just $ head $ head quadGroups else Nothing

isStraightFlush :: [Card] -> Maybe Rank
isStraightFlush hand =
  if isJust (isFlush hand) && isJust (isStraight hand) then Just $ maximum (map getRank hand) else Nothing

isRoyalFlush :: [Card] -> Bool
isRoyalFlush hand =
  and
    ( zipWith
        (==)
        (map getRank (sort hand))
        [Ten, Jack, Queen, King, Ace]
    )
    && isSameSuit hand

highestCard :: [Card] -> [Card] -> Bool
highestCard first second =
  GT
    == head
      ( filter
          (/= EQ)
          ( zipWith
              compare
              (sortBy (comparing Data.Ord.Down) first)
              (sortBy (comparing Data.Ord.Down) second)
          )
      )

parseCard :: Char -> Char -> Card
parseCard r s = Card suit rank
  where
    suit = case s of
      'D' -> Diamonds
      'C' -> Clubs
      'H' -> Hearts
      'S' -> Spades
    rank = case r of
      '2' -> Two
      '3' -> Three
      '4' -> Four
      '5' -> Five
      '6' -> Six
      '7' -> Seven
      '8' -> Eight
      '9' -> Nine
      'T' -> Ten
      'J' -> Jack
      'Q' -> Queen
      'K' -> King
      'A' -> Ace

parseHand :: String -> [Card]
parseHand s
  | null s = []
  | head s == ' ' = parseHand (tail s)
  | otherwise = card : parseHand (drop 3 s)
  where
    card = parseCard (head s) ((head . tail) s)

parseGame :: [Char] -> ([Card], [Card])
parseGame game = (parseHand (take 14 game), parseHand (drop 15 game))

firstHandWins :: [Card] -> [Card] -> Bool
firstHandWins first second
  -- Royal flush
  | isRoyalFlush first && isRoyalFlush second = False -- should not happen
  | isRoyalFlush first = True
  | isRoyalFlush second = False
  -- Straight flush
  | isJust (isStraightFlush first) && isJust (isStraightFlush second) =
      fromJust (isStraightFlush first) > fromJust (isStraightFlush second)
  | isJust (isStraightFlush first) = True
  | isJust (isStraightFlush second) = False
  -- Four of a kind
  | isJust (isFourOfaKind first) && isJust (isFourOfaKind second) =
      case compare (fromJust (isFourOfaKind first)) (fromJust (isFourOfaKind second)) of
        GT -> True
        LT -> False
        EQ -> highestCard first second
  | isJust (isFourOfaKind first) = True
  | isJust (isFourOfaKind second) = False
  -- Full house
  | isJust (isFullHouse first) && isJust (isFullHouse second) =
      let (f3, f2) = fromJust (isFullHouse first)
          (s3, s2) = fromJust (isFullHouse second)
       in case compare f3 s3 of
            GT -> True
            LT -> False
            EQ -> f2 > s2
  | isJust (isFullHouse first) = True
  | isJust (isFullHouse second) = False
  -- Flush
  | isJust (isFlush first) && isJust (isFlush second) =
      case compare (fromJust (isFlush first)) (fromJust (isFlush second)) of
        GT -> True
        LT -> False
        EQ -> highestCard first second
  | isJust (isFlush first) = True
  | isJust (isFlush second) = False
  -- Straight
  | isJust (isStraight first) && isJust (isStraight second) =
      case compare (fromJust (isStraight first)) (fromJust (isStraight second)) of
        GT -> True
        LT -> False
        EQ -> highestCard first second
  | isJust (isStraight first) = True
  | isJust (isStraight second) = False
  -- Three of a kind
  | isJust (isThreeOfaKind first) && isJust (isThreeOfaKind second) =
      case compare (fromJust (isThreeOfaKind first)) (fromJust (isThreeOfaKind second)) of
        GT -> True
        LT -> False
        EQ -> highestCard first second
  | isJust (isThreeOfaKind first) = True
  | isJust (isThreeOfaKind second) = False
  -- Two pairs
  | isJust (isTwoPairs first) && isJust (isTwoPairs second) =
      case compare (fromJust (isTwoPairs first)) (fromJust (isTwoPairs second)) of
        GT -> True
        LT -> False
        EQ -> highestCard first second
  | isJust (isTwoPairs first) = True
  | isJust (isTwoPairs second) = False
  -- One pair
  | isJust (isOnePair first) && isJust (isOnePair second) =
      case compare (fromJust (isOnePair first)) (fromJust (isOnePair second)) of
        GT -> True
        LT -> False
        EQ -> highestCard first second
  | isJust (isOnePair first) = True
  | isJust (isOnePair second) = False
  | otherwise = highestCard first second

main = do
  handle <- openFile "poker.txt" ReadMode
  contents <- hGetContents handle
  let games = lines contents
  let result = length $ filter id [let (f, s) = parseGame game in firstHandWins f s | game <- games]
  print result
  hClose handle
