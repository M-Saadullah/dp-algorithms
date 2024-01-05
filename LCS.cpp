#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


int LCS_rec(string A, string B, int i, int j)
{
   // Base case: if either of the strings is exhausted, return 0
   if (i == A.size() || j == B.size())
       return 0;

   // If the current characters in both strings match, increment the LCS length and move to the next characters
   if (A[i] == B[j])
       return 1 + LCS_rec(A, B, i + 1, j + 1);

   // If the current characters do not match, consider two possibilities
   return max(LCS_rec(A, B, i + 1, j), LCS_rec(A, B, i, j + 1));
}


int LCS_DP(string A, string B)
{
   int n = A.size();
   int m = B.size();

   // Create a 2D array dp to store the length of LCS for each pair of substrings
   vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

   //dp array using a bottom-up approach
   for (int i = 1; i <= n; i++)
       for (int j = 1; j <= m; j++)
           // If the characters at the current positions match, extend the LCS length
           dp[i][j] = A[i - 1] == B[j - 1] ? 1 + dp[i - 1][j - 1] : max(dp[i - 1][j], dp[i][j - 1]);


   return dp[n][m];
}


int main()
{
	string s1,s2;
	cout << "Enter the first string: ";
    // using cin because there cannot be any white space in strings.
	cin >> s1;
	cout << "Enter the second string: ";
	cin >> s2;
	cout << "Answer Using Recursion: " << LCS_rec(s1, s2, 0, 0) << endl;
	cout << "Answer Using DP: " << LCS_DP(s1, s2) << endl;
}