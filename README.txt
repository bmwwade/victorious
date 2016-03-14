week1 progress:
commit first change to git
basic minimax and heuristic algorithms

week2:
improveHeuristic: altered algorithm so base score is changed additively. More
effective and more balanced for the case of positive and negative scores.
Added differences in weight to spots adjacent to corner.

getBestMove: added so that code becomes more readable, and less work needs to
be done in the big function

deepMiniMax: first attempt at alpha-beta pruning algorithm. Very incorrect, and
may do more harm than good. Although it does have depth first search logic, that
is about all it has going for it.

minimax: shorted so that it is now only used for testing purposes. Also does not
utilize heuristic function