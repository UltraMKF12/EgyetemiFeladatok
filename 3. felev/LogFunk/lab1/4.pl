lista_general(N, M, Lista) :-
    findall(X, between(N, M, X), Lista).

invertal(InvertaltLista) :-
    lista_general(1, 18000, Lista),
    reverse(Lista, InvertaltLista).
