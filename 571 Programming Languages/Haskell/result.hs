--1
maxodd [x]=x
maxodd(x:y:xs)
  |x>(maxodd xs) = x
  |otherwise = maxodd xs

--2
deletefirst x k []=[]
deletefirst x 0 lt = lt
deletefirst x k (y:ys)
  |x==y = deletefirst x (k-1) ys
  |otherwise = y:deletefirst x k ys

--3
sproot m n = [y|x<-[m..n],y<-[1..n],y*y==x]

--4
replace x y [] = []
replace x y (z:xs)
  |x == z = y:replace x y xs
  |otherwise = z:replace x y xs
