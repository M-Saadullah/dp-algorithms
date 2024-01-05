using namespace std;
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>



int coinChangeUsingGreedy(vector<int>& coins, int amount)
{
    // Sorting the coin denominations in descending order 
    sort(coins.begin(), coins.end(), [](const auto& a, const auto& b) {return a > b; });
    int ans = 0;
    int i = 0;
    // coin denomination until the target amount is reached
    while (i < coins.size() && amount > 0)
    {
        while(coins[i] <= amount)
        {
            amount -= coins[i];  
            ans++;
        }
        i++;  // Move to the next coin denomination if the current one is too large
    }

    // Check if the exact change for the target amount was achieved
    return amount == 0 ? ans : -1;
}


int coinChangeUsingDP(vector<int>& coins, int total_amount)
{
    int c = coins.size(); // Number of coin denominations

    // Create a vector to store minimum number of coins needed for each amount from 0 to total_amount
    vector<int> dp(total_amount + 1, INT_MAX);
    dp[0] = 0; // Base case: 0 coins needed to make change for 0 amount

    // Iterate over each coin denomination
    for (int i = 0; i < c; i++)
    {
        // Iterate over each amount from 1 to total_amount
        for (int amount = 1; amount <= total_amount; amount++)
        {
            // If the current coin denomination is greater than the current amount, skip to the next iteration
            if (coins[i] > amount)
                continue;
            // Check if using the current coin denomination reduces the number of coins needed
            if (dp[amount - coins[i]] != INT_MAX && dp[amount - coins[i]] + 1 < dp[amount])
                dp[amount] = dp[amount - coins[i]] + 1;
        }
    }
    // Return the minimum number of coins needed for the total_amount,
    // or -1 if it is not possible to make exact change using the provided denominations.
    return dp[total_amount] == INT_MAX ? -1 : dp[total_amount];
}



// check if coins are multiple of each other.

bool checkDenomination(vector<int>& coins) {
    if (coins.empty()) {
        return false;
    }
    for (int i = 1; i < coins.size(); i++) {
        if (coins[i] % coins[i-1] != 0) {
            return false;
        }
    }
    
    return true;
}


int main()
{
    string currTitle, currSymbol;
    int numDenominations;
    vector<int> coins;

    // Read input from the text file
    ifstream inputFile("file.txt");
    if (inputFile.is_open())
    {
        inputFile >> currTitle >> currSymbol >> numDenominations;
        for (int i = 0; i < numDenominations; i++)
        {
            string temp;
            int value;
            inputFile >> temp >> value;
            coins.push_back(value);
        }
        inputFile.close();
    }
    else
    {
        cout << "Unable to open file";
        return 0;
    }
    // Check if it is possible to run the greedy algorithm
    int amount;
    cout << "Enter the total sum required: ";
    cin >> amount;
    if (checkDenomination(coins))
    {
		cout << "Number of coins used: " << coinChangeUsingGreedy(coins , amount) << endl;
    }
    else
    {   
        cout << "Greedy algorithm is not possible with the given denominations" << endl;
        cout << "Minumum Coins Using DP: ";
        cout << coinChangeUsingDP(coins, amount) << endl;
    }
    return 0;
}