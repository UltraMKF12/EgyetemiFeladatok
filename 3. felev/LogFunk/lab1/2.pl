kszor(0, _, []).
kszor(N, Lista, Vissza) :-
    N > 0,
    UjN is N-1,
    kszor(UjN, Lista, UjVissza),
    append(Lista, UjVissza, Vissza).
