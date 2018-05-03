sumodd([],0).
sumodd([X],X).
sumodd([X,Y|Ys],Res):-(
    sumodd(Ys,Res1),Res is Res1+X
).


/*2*/




/*4*/
prefix([],L).
prefix([X|Xs],[Y|Ys]):-(
    X==Y,prefix(Xs,Ys)
).
