-- 1.
findodds [] = []
findodds (x:[]) = [x]
findodds (x:y:[]) = [x]
findodds (x:y:ys) = x:findodds ys

maxone (x:[]) = x
maxone (x:xs)
    |x >= maxone xs = x
    |otherwise = maxone xs

maxodd ls = maxone (findodds ls)

-- 2. deletefirst 1 3 [2,1,3,1,4,1,5,1,6] = [2,3,4,5,1,6]

deletefirst x k [] = []
deletefirst x k (y:ys)
    |k == 0 = ys
    |x == y = deletefirst x (k-1) ys
    |otherwise = y:deletefirst x k ys

-- 3. sproot 2 10 = [2,3]
sproot n m = [y|x<-[n..m],y<-[1..m], y*y==x]

