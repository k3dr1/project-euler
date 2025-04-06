module P19 where

import Data.Time (Day, DayOfWeek (Sunday), dayOfWeek, fromGregorian, toGregorian)
import Data.Time.Calendar.MonthDay (dayOfYearToMonthAndDay)

result =
  ( length
      . filter
        ( \day ->
            let (_, _, dayofmonth) = toGregorian day
             in (dayOfWeek day == Sunday) && dayofmonth == 1
        )
  )
    [(fromGregorian 1901 1 1) .. fromGregorian 2000 12 31]

main = do
  print result
