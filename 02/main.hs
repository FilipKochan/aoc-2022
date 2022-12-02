solve :: String -> String
solve rounds = "part 1: " ++ ( show $ sum ( map getPoints (lines rounds) ) ) ++ "\npart 2: " ++ ( show $ sum ( map getPoints2 (lines rounds) ) ) ++ "\n"

getPoints2 :: String -> Int
getPoints2 round = case (words round) of
  [move, "X"] -> getPoints (unwords [move, (getMoveForLose move)])
  [move, "Y"] -> getPoints (unwords [move, (getMoveForDraw move)])
  [move, "Z"] -> getPoints (unwords [move, (getMoveForWin move)])
  _ -> undefined

getMoveForWin :: String -> String
getMoveForWin "A" = "Y"
getMoveForWin "B" = "Z"
getMoveForWin "C" = "X"
getMoveForWin _ = undefined

getMoveForDraw :: String -> String
getMoveForDraw "A" = "X"
getMoveForDraw "B" = "Y"
getMoveForDraw "C" = "Z"
getMoveForDraw _ = undefined

getMoveForLose :: String -> String
getMoveForLose "A" = "Z"
getMoveForLose "B" = "X"
getMoveForLose "C" = "Y"
getMoveForLose _ = undefined

getPoints :: String -> Int
getPoints round = case (words round) of
  ["A", "X"] -> 3 + 1
  ["A", "Y"] -> 6 + 2
  ["A", "Z"] -> 0 + 3
  ["B", "X"] -> 0 + 1
  ["B", "Y"] -> 3 + 2
  ["B", "Z"] -> 6 + 3
  ["C", "X"] -> 6 + 1
  ["C", "Y"] -> 0 + 2
  ["C", "Z"] -> 3 + 3
  _ -> undefined

main :: IO ()
main = interact solve