%Széri József, 524/2

utolso([H], H).
utolso([_ | Tail], E):-
	utolso(Tail, E).