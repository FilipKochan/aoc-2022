import Data.Set (fromList, size)

main :: IO ()
main = interact solve

solve :: String -> String
solve buf = "part 1: " ++ (solveForN 4) ++ "\npart 2: " ++ (solveForN 14) ++ "\n"
  where
    solveForN n = show $ fst . head  $  dropWhile ( (<n) . snd ) $ zip [0..] $ Prelude.map (Data.Set.size  . fromList) $ scanl (curry $ Prelude.take n . (uncurry $ flip (:))) [] buf
