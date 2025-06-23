//
// Created by olivi on 2025-06-23.
//

/*
problem description:
*We say that an integer sequence is increasing if the numbers in the sequence increase (rather than decrease or stay
*the same). For example, the following is an increasing sequence of length 7:
(15, 27, 39, 56, 60, 80, 96)
A subsequence of a sequence uses some of the same members, in the same order, but may leave some out. For example,
if we have the following (non-increasing) sequence of length 7:
(3, 11, 53, 21, 41, 61, 23)
then (11, 53, 61) is a subsequence of length 3. And this subsequence also happens to be increasing. However, for this
example there are longer increasing subsequences; what is the longest you can find?
Write a program that, given a sequence of integers, finds a subsequence that is increasing and is as long as possible.

Input
The input consists of between 1 and 64 test cases. Each test case has two lines. The first line has a positive integer
n ≤ 100000, indicating the length of a sequence. Then follows a line containing a sequence of n integers, each in the
range [-2^31, 2^31). Input ends at end of file.

Output
For each test case, output a line containing the length of the longest increasing subsequence, followed by a line
containing the indices of the elements in one such subsequence (the first element has index 0, the second index 1,
and so on). The indices should be given in ascending order. If multiple increasing subsequences have maximal length,
report any one of them.
 */

/*
my notes:
 * the subsequence has to be in order, from left to right
 * has to be ascending
 * first print the number of items in the subsequence on one row, then print the indices of the subsequence on the other
 * row
 * solve it using dynamic programming in order to achieve the best time complexity - bottom-up tabulation
 * has to be solved in O(nlogn) time - this one has quadratic time complexity. I gave up.
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

 int numOfItems;
 while (std::cin >> numOfItems) {

  std::vector<int> arrayOfItems(numOfItems);
  for (int i = 0; i < numOfItems; i++) {
   cin >> arrayOfItems[i]; //put input as items into array
  }

  std::vector<int> lis(numOfItems, 1); // lis - longest increasing sequence
  std::vector<int> prevIndex(numOfItems, -1); // previous index of lis ending at i. Using this for reconstructing the indexes of lis

  int maxLength = 1;
  int lastIndex = 0;

  //bottom up
  for (int i = 0; i < numOfItems; i++) {
   for (int prev = 0; prev < i; prev++) {
      if (arrayOfItems[i] > arrayOfItems[prev] && lis[i] < lis[prev] + 1) {
       lis[i] = lis[prev]+1;
       prevIndex[i] = prev;
      }
   }
   if (lis[i] > maxLength) {
    maxLength = lis[i];
    lastIndex = i; //is then the longest lis, gets updated with current value
   }
  }

  vector<int> resultIndices; //reconstruct indices of lis
  for (int i = lastIndex; i != -1; i = prevIndex[i]) {
   resultIndices.push_back(i);
  }

  reverse(resultIndices.begin(), resultIndices.end());

  cout << maxLength << '\n';
  for (size_t i = 0; i < resultIndices.size(); i++) {
   cout << resultIndices[i];
   if (i != resultIndices.size() - 1)
    cout << ' ';
  }
  cout << '\n';
 }
 return 0;
}

