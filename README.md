# Tatamibari Verifier
Tatamibari Verifier (Verifier2) is used to check whether a Tatamibari configuration is a solution

## Input
Tatamibari Solver input format:
The first line consist of two inputs, _m_ and _n_  where _m,n_ > 0, followed with _m_ lines and each lines have _n_ columns where each cell consist of 2 character (Symbol)(Number) where symbol is either '\+', '-', or '|' and number is 1 <= number <= _mn_.

Input Example:

	4 4
	-1 -1 -1 -1
	-2 -2 |5 |3
	-4 -4 |5 |3
	+6 -7 -7 |3
  
## Output
It will output "Valid" if it is a solution or "Invalid" if not.
 
# Tatamibari Exhaustive
Tatamibari Exhaustive Search (Brute) is used to solve a Tatamibari instance using Exhaustive Search.

## Input
Tatamibari Solver input format:
The first line consist of two inputs, _m_ and _n_  where _m,n_ > 0, followed with _m_ lines and each lines have _n_ columns where each cell consist of 1 character (Symbol) where symbol is either '\+', '-', '|', or '\*' representing empty cell.

Input Example:

	4 4
	* * - *
	* - * |
	- * | *
	+ - * *
  
## Output
It will output the number of solutions and the solution(s).
 
# Tatamibari Empty
Tatamibari Empty (Empty) is used to solve an empty Tatamibari instance using Exhaustive Search.

## Input
Tatamibari Solver input format:
The first line consist of two inputs, _m_ and _n_  where _m,n_ > 0, followed with _m_ lines and each lines have _n_ columns where each cell is '\*'.

Input Example:

	3 3
	* * * 
	* * * 
	* * * 
  
## Output
It will output the number of solutions and the solution(s).

# Requirement
C++

# Additional Info
For comparison between Exhaustive Search and SAT solver using Python: https://github.com/chrisalpha5/TatamibariSolver
