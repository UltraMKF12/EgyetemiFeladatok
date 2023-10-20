kompakt([], []).
kompakt([H|T], [P|Rest]) :-
    H = [Atom, Count],
    pack([H|T], Atom, Count, P, UjT),
    kompakt(UjT, Rest).

pack([], Atom, Count, [Atom, Count], []).
pack([H|T], Atom, Count, P, Rest) :-
    H = [Atom, AtomCount],
    NCount is Count + AtomCount,
    pack(T, Atom, NCount, P, Rest).
pack([H|T], Atom, Count, [Atom, Count], [H|T]) :-
    H \= [Atom, _].

% NEM MEGY
