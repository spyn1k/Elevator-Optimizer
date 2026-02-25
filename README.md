# ELEVATE.C

*The elevate program is a command line tool for optimizing elevator efficiency.*

*It calculates the optimal floors for an elevator to stop at to minimize the total walking cost (stairs) for all passengers.*

• **`--mode=`** _Selects the algorithm(solution)_ **:** recurse, brute, memoize, or dp

• **`--debug`** _Enables debug printing (displays the DP cost table)_

                                                               COMPILE WITH

gcc -Os -c -Wall -Wextra -Werror -pedantic elevate.c

gcc -Os -c -Wall -Wextra -Werror -pedantic recurse.c

gcc -Os -c -Wall -Wextra -Werror -pedantic brute.c

gcc -Os -c -Wall -Wextra -Werror -pedantic memoize.c

gcc -Os -c -Wall -Wextra -Werror -pedantic dp.c

gcc -Os -o elevate recurse.o brute.o memoize.o dp.o elevate.o

                                                              COMMAND GUIDE

Default Run
-

./elevate input.txt

*Runs the optimized __Dynamic Programming solution__ (default).*

Recursive Method
-
./elevate input.txt --mode=recurse

*Recursive implementation. **Recommended only for small inputs**.*

Brute Force Method
-
./elevate input.txt --mode=brute

*Generates all possible combinations. __Useful for verification__.*

Memoization Method
-
./elevate input.txt --mode=memoize

*Recursive approach with caching. __Faster than standard recursion__.*

Debug Mode
-
./elevate input.txt --mode=dp --debug

*Prints the internal cost table used to make the decision.*

                                                               INPUT FORMAT

***The program expects an input file formatted as follows:***

    <numPeople> <numStops>
    <dest_1> <dest_2> ... <dest_N>

**Example (5 people, 2 stops):**

    5 2
    11 2 7 13 7

## PRODUCTION CHOICE
***Why Dynamic Programming (DP) is the default:***

After comparing the performance of all four methods with the time command , **Dynamic Programming (Bottom-Up)** was selected as the default solution.

* **Performance**: While the `recurse` and `brute` modes suffer from severe performance degradation on larger inputs the DP mode provides a solution in reasonable time O(N*M).
* **Stability:** Unlike `memoize` which relies on recursion and can lead to **Stack Overflow** in case of very large inputs the DP method is much better.
* **Efficiency:** It works systematically from the ground up making sure no work is repeated and making the program run as fast as possible.

                                                           FORMULA TRANSLATION
***Implementing the mathematical formula to C Code***

The assignment provided the following recursive relation for finding the minimum cost:

    M(i, j) = min { M(i-1, k) - fw(k, inf) + fw(k, j) + fw(j, inf) }

This was translated directly into the `solve_dp` and `solve_recurse` functions as follows:

**1. The Cost Function:**
The term `fw(a, b)` (Floors Walked) was implemented as the helper function
`count_walking_cost(a, b, dests, numPeople)`

**2. The Recurrence:**
Inside our loops (iterating `k` from 0 to `j`) the formula becomes

    long long current_val = m_prev - fw_k_inf + fw_k_j + fw_j_inf;

* **m_prev:** The optimal cost of the previous state (i-1 stops ending at k)
* **fw_k_inf:** Cost subtracted for passengers previously walking from k to inf
* **fw_k_j + fw_j_inf:** New cost for passengers now walking from k to j and j to inf

### SOURCES

***[1]*** ___[Wikipedia – Recursion](https://en.wikipedia.org/wiki/Recursion_(computer_science))___

***[2]*** ___[Wikipedia – Brute-force search](https://en.wikipedia.org/wiki/Brute-force_search)___

***[3]*** ___[Wikipedia – Memoization](https://en.wikipedia.org/wiki/Memoization)___

***[4]*** ___[Wikipedia – Dynamic Programming](https://en.wikipedia.org/wiki/Dynamic_programming)___

***[5]*** ___[Wikipedia – Recursion](https://en.wikipedia.org/wiki/Recursion_(computer_science))___

***[6]*** ___[GeeksforGeeks – Tabulation (Bottom-Up)](https://www.geeksforgeeks.org/tabulation-vs-memoization/)___



