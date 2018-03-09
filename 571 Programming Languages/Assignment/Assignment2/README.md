co-developers:
Wenchen Li: wli100@binghamton.edu
Xiang Zhang: zxiang4@binghamton.edu

TODO:
- [ ] could use Latex to write .pdf

# Assignment 2

## 1
(a(bb)*b)+ # don't consider begin with b
(b*(ab)*(ab)*)+

## 2
(b|c)a?(d+e)*

## 3
- symble table,
- lexical scope
- dynamic scope
```C
#include<stdlib.h>
int a,b;
int p(void){
    int a, p;
    /* point 1 */
    a=0; b =1; p=2;
    return p;
}
void print(void){
    printf("%d\n%d\n", a, b);
}
void q(void){
    int b;
    /* point 2 */
    a = 3; b = 4;
    print();
}
main(){
    /* point 3 */
    a = p();
    q();
}
```
dynamic:
3
4
    point 3:
        a   => int, global
        b   => int, global
        p   => int, function
        print => void, function
        q   => void, function
        main=> void, function
    point 1:
        a   => int, local to p
            -> int, global
        b   => int, global
        p   => int, local to p
            -> int, function
        print => void, function
        q   => void, function
        main=> void, function
    point 2:
        a   => int, global
        b   -> int, local to q
            => int, global
        p   -> int, function
        print => void, function
        q   => void, function
        main=> void, function

static:
output:
3
1
    point 1:
        a   => int, local to p
            -> int, global
        b   => int, global
        p   => int, local to p
            -> int, function
    point 2:
        a   => int, global
        b   => int, local to q
            -> int, global
        p   => int, function
        print=> void, function
        q   -> void, function
    point 3:
        a   => int, global
        b   => int, global
        p   => void, function
        print=> void, function
        q   => void, function
        main=> void, function


## 4
box-and-circle diagrams
```C
#include <stdio.h>
main(){
    int **x;
    int *y;
    int z;
    x = (int **) malloc(sizeof(int*));
    /* one */
    y = (int*) malloc(sizeof(int));
    z = 1;
    *y = 2;
    *x = y;
    **x = z;
    /* two */
    printf("%d\n", *y);
    z = 3;
    printf("%d\n", *y);
    **x = 4;
    /* three */
    printf("%d\n", z);
    return 0;
}
```
output:
1
1
3
/* one */
x => someAddress1
y => 0

/* two */
x => someAddress1 -> someAddress2 -> 1
y => someAddress2 -> 1
z => 1

## 5
call by reference
call by name
```C
int i;
int a[3];

void swap(int x, int y){
    x = x+y;
    y = x-y;
    x = x-y;
}

main(){
    i=1;
    a[0] = 2;
    a[1] = 1;
    a[2] = 0;
    swap(i, a[i]);
    printf("%d %d %d %d\n", i, a[0], a[1], a[2]);
    swap(a[i], a[i]);
    printf("%d %d %d\n", a[0], a[1], a[2]);
    return 0;
}
```
call by reference:
1 2 1 0
2 0 0

call by value:
1 2 1 0
2 1 0

call by name:
0 2 1 2
0 1 2

note: c doesn't have call be reference

## 6
perl program: perl/match.pl
