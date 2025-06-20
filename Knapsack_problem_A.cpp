// Created by olivi on 2025-06-18.
/*
problem description:
Implement a solution to the classic knapsack problem. You are given a knapsack that can hold up to a certain weight
(its capacity), and several items you may choose to put in the knapsack. Each item has a weight and a value. Choose a
subset of the items (which could be all of them, or none of them) having the greatest value that fit into the knapsack
(i.e. the sum of the weights of the items you choose must be less than or equal to the knapsack capacity).

Input
The input consists of between 1 and 30 test cases. Each test case begins with an integer 1 ≤ C ≤ 2000, giving the
capacity of the knapsack, and an integer 1 ≤ n ≤ 2000, giving the number of objects. Then follow n lines, each giving
the value and weight of the n objects. Both values and weights are integers between 1 and 10,000.

Output
For each test case, output a line containing the number of items chosen, followed by a line containing the indices of
the chosen items (the first item has index 0, the second index 1, and so on). The indices can be given in any order.
*/

/*
my notes:
- is a combinatorial optimization (*which is a subfield of mathematical optimization) problem. Aims to find an optimal
object from a finite set of objects.

- brute force search will not be feasible here, must create a customized search algorithm for the problem at hand

- the knapsack problem:
"Given a set of items, each with a weight and a value, determine which items to include in the collection so that the
total weight is less than or equal to a given limit and the total value is as large as possible."

- the knapsack problem is np-complete (*non-deterministic polynomial time), i.e. :
 - you can verify the solution in polynomial time (*i.e. quickly)
 - but finding a solution to the problem takes time

- it is possible to solve the knapsack problem in pseudo polynomial time using dynamic programming (*i.e. algorithmic
 technique for solving problems by breaking them down into smaller subproblems, solving each subproblem once,
and saving the results to avoid redundant work.)
*/
#include <ios>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr); // this and the above line is for faster I/O

    // keep reading until end of file (multiple test cases)
    int capacityOfKnapsack;
    int numOfObjects;

    while (std::cin >> capacityOfKnapsack >> numOfObjects) {
        // need four variables, two arrays/vectors for storing the values (will have n as index for both weight and value),
        // one int for number of objects, and one int for the capacity of the knapsack
        std::vector<int> weights(numOfObjects);
        std::vector<int> values(numOfObjects);
        std::vector<int> dp(capacityOfKnapsack + 1, 0); //dynamic programming array, initialized as max capacity + 1 with values 0
        std::vector<vector<bool>> taken(numOfObjects, vector<bool>(capacityOfKnapsack + 1, false));

        for (int i = 0; i < numOfObjects; i++) {
            std::cin >> values[i] >> weights[i]; // value first, then weight
        }

        for (int i = 0; i < numOfObjects; i++) {
            for (int j = capacityOfKnapsack; j >= weights[i]; j--) {
                if (dp[j] < dp[j - weights[i]] + values[i]) {
                    dp[j] = dp[j - weights[i]] + values[i]; // to determine if we can get a higher max by including the current item or the next
                    taken[i][j] = true;
                }
            }
        }

        std::vector<int> result;
        int j = capacityOfKnapsack;
        for (int i = numOfObjects - 1; i >= 0; i--) {
            if (taken[i][j]) {
                result.push_back(i); // item was chosen. Put at the end of the vector
                j -= weights[i]; // reduce knapsack capacity by chosen item's weight
            }
        }

        cout << result.size() << '\n';
        for (int i = result.size() - 1; i >= 0; --i) {
            cout << result[i] << (i == 0 ? '\n' : ' ');
        }
    }

    return 0;
}


