% T�r�lj�k egy lista minden K-adik elem�t, azaz legyen igaz a torolk([1,2,3,4,5,6,7,8],2,[1,3,5,7]) predik�tum.
torolk(Lista, K, UjLista) :-
    torolk(Lista, K, K, UjLista).

torolk(Lista, EredetiK, K,  UjLista):-
    K > 0,
    UjK is K - 1,
    trolok(Lista, EredetiK, UjK, Lista).

torolk([ListaH | ListaT
