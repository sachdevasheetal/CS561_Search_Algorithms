# Search_Algorithms
Input file that describes the terrain map, landing site,
target sites, and characteristics of the robot. For each target site, we have to find the optimal
(shortest) safe path from the landing site to that target. A path is composed of a sequence of
elementary moves. Each elementary move consists of moving the rover to one of its 8 neighbors.

ABOUT THE SEARCH ALGORITHMS

Breadth-first search (BFS)
In BFS, each move from one cell to any of its 8 neighbors counts for a unit path cost of 1. You do
not need to worry about elevation differences.

Uniform-cost search (UCS)
When running UCS, you should compute unit path costs in 2D.

A* search (A*).
When running A*, you should compute an approximate integer unit path cost of each move in
3D, by summing the horizontal move distance as in the UCS case (unit cost of 10 when moving
North to South or East to West, and unit cost of 14 when moving diagonally), plus the absolute
difference in elevation between the two cells.

Input: The file input.txt in the current directory of your program will be formatted as follows:

First line: Instruction of which algorithm to use, as a string: BFS, UCS or A*

Second line: Two strictly positive 32-bit integers separated by one space character, for
“W H” the number of columns (width) and rows (height), in cells, of the map.

Third line: Two positive 32-bit integers separated by one space character, for
“X Y” the coordinates (in cells) of the landing site. 

Fourth line: Positive 32-bit integer number for the maximum difference in elevation between
two adjacent cells which the rover can drive over.
The difference in Z between two adjacent cells must be smaller than or equal (£ )
to this value for the rover to be able to travel from one cell to the other.

Fifth line: Strictly positive 32-bit integer N, the number of target sites.
Next N lines: Two positive 32-bit integers separated by one space character, for
“X Y” the coordinates (in cells) of each target site.
Next H lines: W 32-bit integer numbers separated by any numbers of spaces for the elevation
(Z) values of each of the W cells in each row of the map.

Output: The file output.txt which your program creates in the current directory should be
formatted as follows:
N lines: Report the paths in the same order as the targets were given in the input.txt file.
Write out one line per target. Each line should contain a sequence of X,Y pairs
of coordinates of cells visited by the rover to travel from the landing site to the
corresponding target site for that line.
