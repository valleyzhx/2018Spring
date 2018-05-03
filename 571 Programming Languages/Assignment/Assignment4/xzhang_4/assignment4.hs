--1.union
member a[] = False
member a(b:xs)
    |a == b = True
    |otherwise = member a xs
append []ys = ys
append (x:xs)ys = x:append xs ys
union [] [] = []
union [] (y:ys) = union [y] ys
union (xs) [] = xs
union (x:xs) (y:ys)
    |member x xs = union xs (y:ys)
    |member y (x:xs) = union (x:xs) ys
    |otherwise = union(append (x:xs) [y]) ys
 
--2.delete
deletek k n[] = [] 
deletek 1 n(x:xs) = deletek n n xs
deletek k n(x:xs) = x:deletek (k-1)(n)xs

delete k[] = [] 
delete 1(x:xs) = []
delete k(x:xs) = deletek (k)(k)(x:xs)

--3.data Tree
data Tree = Leaf Int 
            | Node Tree Int Tree

occurs :: Int->Tree->Bool
occurs x (Leaf l)
        | x==l = True
        |otherwise = False
occurs x (Node left l right)
        |x == l = True
        |otherwise = occurs x left || occurs x right

--4.delete_last x lt

delete_last a [] = []
delete_last a (x:xs)
    |a == x && (member a xs == False)  = xs
    |otherwise = x:delete_last a xs

--5.isort lt
insert y [] = [y]
insert y (x:xs)
    |y>x = x:(insert y xs)
    |otherwise = y:(x:xs)

sort_insert :: [Int]->[Int]->[Int]
sort_insert []ls = ls
sort_insert (y:ys)ls = sort_insert ys(insert y ls)

isort (y:ys) = sort_insert (y:ys)[]