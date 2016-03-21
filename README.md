# horse-river-cross
This is a c program to solve the problem of a horse crossing a river over a set of stones.

The rules of the game are :-
1. The horse can only move like the knight on a chess board.
2. It can start at any stone.
3. It can step on any stone only once (With the exception of the first stone). The stone it steps on breaks and falls in the river.
4. It has to step over all the stones and back to the starting stone.
5. If the horse is back at the starting stone following the above rule, the game is won
6. If the horse finds its path blocked, the game is lost.

This program tries to find all possible paths for the horse to cross the river.

Here is the stone layout:-

Legends:-
H   = Horse
[n] = Stones
--- = river banks


---------------------------------------
		  	[ 0]	[ 1]	[ 2]
	[3]		[ 4]	[ 5]	[ 6]
	[7]		[ 8]	[ 9]	[10]
			  [11]	[12]	[13]
---------------------------------------
			         H


This code can be optimized further.

