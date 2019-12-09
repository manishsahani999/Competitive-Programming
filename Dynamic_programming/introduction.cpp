/*
    Introduction to Dynamic Problems

    * Key to solve DP - Find the problem state and the tansition(relationship) between current problem and there sub problems.
    * Dp is primarily used to solve optimization problems and counting problems 
    * When to use DP - "maximize", "minimize", "count the number of ways to do that"
*/


/*
    Basic DP example - UVA 11450

    Given - Different options for each garments (e.g. 3 shirt model, 2 shoes models, etc) and a limited budget
    TODO  - we want to spend the maximun amount.
*/

#include <bits/stdc++.h>

using namespace std;

#define Max(a, b) (a > b) ? a : b
#define Min(a, b) (a > b) ? b : a
#define pb push_back
#define ALL(A) A.begin(), A.end()
#define FOR(a, b, c) for(int(a) = (b); (a) < (c); (a)++)

#define ll long long
#define ii pair <int, int>
#define vi vector <int>
#define vvi vector <vi>
#define vii vector <ii>

ll N, M, C, res, price[25][25], memo[205][25]; // Number of test cases, Money we have, Number of clothes we want to buy, Number of models

ll shop(ll money, int g) {
    if (money < 0) return -1000000000;  
    if (g == C) return M - money; // actual money that is spent
    if(memo[money][g] != -1) return memo[money][g];
    ll ans = -1;
    FOR(i, 1, price[g][0] + 1) {
        ans = max(ans, shop(money - price[g][i], g + 1));
    }
    return memo[money][g] = ans;
}

ll anotherShop(ll money, int g) {
    if (money < 0) return -1000000000;
    if (g == C) return M - money;
    ll & ans = memo[money][g]; // remembers the memory addresss
    if (ans != -1 ) return ans;
    FOR(i, 1, price[g][0] + 1) {
        ans = max(ans, shop(money - price[g][i], g + 1));
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    cin >> N;

    while(N--) 
    {
        cin >> M >> C;

        FOR(i, 0, C) 
        {
            cin >> price[i][0];
            FOR(j, 1, price[i][0] + 1) cin >> price[i][j];
        }

        // we could try solving this with greedy approach, but the verdict will be (WA)
        // this problem is not solvable with Divide and Conquer because "subproblems are not independent" (WA)
        // Complete search will solve this problem but the verdict will be (TLE) bcz runtime is (20^20)

        /*
            Top-Down Dp

            Prerequisite for DP to be applicable
            * Condition 1 - The problem must have optimal sub-structure 
            * Condition 2 - The problem must have overlapping Sub-structure 
            
            This Problem has following 
            * State               - < Current money, g >
            * Recurrance Relation - shop(money, g) = for k in range(0, 20) max{ shop(money - price[g][k], g + 1) } 
            * Condition 1         - From the recurrance relation we can see that the solution of subproblems are the part of Optimal solution (Condition 1)
            * Condition 2         - The problem has overlapping sub-structure 
            * #Sub-problems       - 201*20 (number of unique combinations of states)
            
            Steps to Implement top-down DP
            * Init Memo Table with dummy values -1 or 0
            * check memo table if not -1 then use answer from memo table otherwise perform the computation and store the computation in memo table.
        */
       
        // step 1 - Init the memo table   
       memset(memo, -1, sizeof memo);

        // step 2 
       res = anotherShop(M, 0);

       if (res < 0) cout << "no solution\n";
       else cout << res << "\n";

    }

    return 0;
}