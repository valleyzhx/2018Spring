/*
sumodd([],0).
sumodd([X],X).
sumodd([X,Y|Ys],Res):-(
    sumodd(Ys,Res1),Res is Res1+X
).
*/
sumodd([X],X).
sumodd([X,Y|Xs],Res):-
  sumodd(Xs,Res1),Res is X + Res1.


/*2*/
my_member(H, [H|_T]).
my_member(X, [H|T]) :- my_member(X,T).



/*4*/
prefix([],L).
prefix([X|Xs],[Y|Ys]):-(
    X==Y,prefix(Xs,Ys)
).

rev([],[]).
rev([H|T],Res) :-
  rev(T,Res1),
  Res = [Res1|[H]].

  Res = [Res1|H].


mylast([X],X).
mylast([A,H|T],X) :- mylast(H|T,X).


max([X],X).
max([X,Y|Ys],Res):-
    (X>=Y-> max([X|Ys],Res);
      max([Y|Ys],Res)
    ).

