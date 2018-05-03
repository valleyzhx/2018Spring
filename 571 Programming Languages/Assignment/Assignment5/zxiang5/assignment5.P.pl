%%
%% Please load this file into SWI-Prolog
%%
%%
%% Considering the following will give some practice
%% in thinking about backtracking.
%%

/** <examples>
?- max([1,3,5,4,2], Res).
?- deleteNTerm(3,f(2,3,4,5,6,7,8),Res).
?- replace_first_k(3, f(2,1,3,1,4,1,5,1,6,1) , Res).
?- position(1, [1,3,1,2,5,1], Res).
*/
length([], 0).
length([H|T], N) :- length(T, N1), N is N1 + 1.


/*---1---*/
max([],Res):- Res is 0.
max([X|XS],Res):-
    max(XS,Res1),(
        X>Res1-> Res is X
        ;Res is Res1
    ).

/*---2---*/
/*
* deleteNTerm(3,f(2,3,4,5,6,7,8),Res).
  Res = f(2,3,5,6,8).
*/
deleteNMList(N,M,[],[]).
deleteNMList(N,1,[X|Xs],Res):- deleteNMTerm(N,N,Xs,Res).
deleteNMList(N,M,[X|Xs],[X|Ys]):- M1 is M-1,deleteNMTerm(N,M1,Xs,Ys).


deleteNList(1,T,[]).
deleteNList(N,L,Res):- deleteNMTerm(N,N,L,Res).

/*----3----*/
/*
 replace_first_k(3, [2,1,3,1,4,1,5,1,6,1] , Res).
 Res = [2,8,3,8,4,8,5,1,6,1].
*/

replace_first_k(K,[],[]).
replace_first_k(0,L,L).
replace_first_k(K,[X|Xs],Res):- (
    X == 1, K1 is K-1,X1 is 8,replace_first_k(K1,Xs,Res1), Res = [X1|Res1];
    replace_first_k(K,Xs,Res1), Res = [X|Res1]
  ).

/*----4-----*/
/*
  position(1, [1,3,1,2,5,1], Res).
  Res = [1,3,6].
*/

position1(X,[],K,[]).
position1(X,[H|T],K,Res):-(
        X==H,Res = [K|Res1],K1 is K+1,position1(X,T,K1,Res1);
        K2 is K+1,position1(X,T,K2,Res)
).
position(X,L,Res):- position1(X,L,1,Res).


