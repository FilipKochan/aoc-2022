{-# LANGUAGE OverloadedStrings #-}
import Data.Text (replace, pack, unpack)
import Data.List (sort)

data Packet = Ar [Packet] | N Int deriving (Show,Read)
instance (Eq Packet) where
  p1 == p2 = comparePacket p1 p2 == 0

instance (Ord Packet) where
  compare p1 p2 = if res == 0 then EQ else (if res > 0 then GT else LT) where res = comparePacket p1 p2

solve :: String -> String
solve i = "part 1: " ++ (part1 (lines i)) ++ "\npart 2: " ++ (part2 (lines i)) ++ "\n" 

part1 :: [String] -> String
part1 p =  show $ sum $ map fst $ filter snd $ zip [1 ..] $ decidePackets p

part2 :: [String] -> String
part2 p = show $ foldl1 (*) $ map (\(i, p) -> if p == p1 || p == p2 then i else 1) $ zip [1..] $ sort (p1 : (p2) : map getPacket (filter (/="") p))
  where 
    p1 = getPacket "[[2]]"
    p2 = getPacket "[[6]]"

decidePackets :: [String] -> [Bool]
decidePackets [] = []
decidePackets [""] = []
decidePackets (p1:p2:_:rest) = cp (getPacket p1) (getPacket p2) : decidePackets rest
decidePackets (p1:p2:rest)   = cp (getPacket p1) (getPacket p2) : decidePackets rest

cp :: Packet -> Packet -> Bool
cp p1 p2 = (comparePacket p1 p2) < 0

comparePacket :: Packet -> Packet -> Int
comparePacket (N a) (N b) = a - b
comparePacket (N a) (Ar ar) = comparePacket (Ar [N a]) (Ar ar)
comparePacket (Ar ar) (N a) = comparePacket (Ar ar) (Ar [N a])
comparePacket (Ar []) (Ar []) = 0
comparePacket (Ar []) _ = -1
comparePacket _ (Ar []) = 1
comparePacket (Ar (x:xs)) (Ar (y:ys)) = if res == 0 then comparePacket (Ar xs) (Ar ys) else res 
  where res = comparePacket x y 

getPacket :: String -> Packet
getPacket p = read (getStrRepr p) :: Packet

getStrRepr :: String -> String
getStrRepr p = unpack $ 
  replace ",0" ",N 0" $ 
  replace ",1" ",N 1" $ 
  replace ",2" ",N 2" $ 
  replace ",3" ",N 3" $ 
  replace ",4" ",N 4" $ 
  replace ",5" ",N 5" $ 
  replace ",6" ",N 6" $ 
  replace ",7" ",N 7" $ 
  replace ",8" ",N 8" $ 
  replace ",9" ",N 9" $ 
  replace "[0" "[N 0" $ 
  replace "[1" "[N 1" $ 
  replace "[2" "[N 2" $ 
  replace "[3" "[N 3" $ 
  replace "[4" "[N 4" $ 
  replace "[5" "[N 5" $ 
  replace "[6" "[N 6" $ 
  replace "[7" "[N 7" $ 
  replace "[8" "[N 8" $ 
  replace "[9" "[N 9" $ 
  replace "[" "Ar [" (pack p)

main :: IO ()
main = interact solve