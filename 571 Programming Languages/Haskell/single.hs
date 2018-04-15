single [] = []
single (x:xs) = [x]: single(xs)
sqroot n = sqroot1 n 1
sqroot1 n k
  |n == k = []
  |k*k == n = [k]
  |otherwise = sqroot1 n (k+1)
