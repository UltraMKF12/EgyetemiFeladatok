torolk([], _, []).
torolk(Lista, K, UjLista) :-
    torolk(Lista, K, K, UjLista).

torolk([], _, _, []).
torolk([_ | T], 1, K, UjLista) :-
    torolk(T, K, K, UjLista).
torolk([H | T], N, K, [H | UjT]) :-
    N > 1,
    N1 is N - 1,
    torolk(T, N1, K, UjT).
