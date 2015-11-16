/*
 author: @danathom
 date: 10/03/2015
 */

#include <iostream>
#include <time.h>
#include <string>

using namespace std;

struct IceCream{
	int value;
	int price;
};


/*
 Classic dynamic programming problem: what is the correct combination of ice creams I can buy in order to maximize 
 my purchased value, all while staying at or below a given budget?
 
 
 Variables: n, length of array ic
            ic, array of all IceCreams the store has available for purchase
 
 Assumptions: n >= 2
              you can only buy one of each "IceCream"
              no "danger values" (ex. IceCream with price of -9) in ic array
 
 Runtime: O(n*budget)
 */
int buyIceCream(int budget, IceCream ic[], int n) {
    int netValue [n+1][budget+1];
    for (int j = 0; j <= budget; j++) {
        for (int i = n; i > -1; i--) {
            int cost = ic[i].price;
            if (j == 0 || i ==n) {
                netValue[i][j] = 0; //BCs:N+1th ice cream has value 0 / if budget ==0
            }
            else if (cost > j && j != budget) {  //BC: if you can't afford the ice cream, value = 0
                netValue[i][j] = 0;
                continue;
            }                          //dont take              //do take
            else { netValue[i][j] = max(netValue[i+1][j],netValue[i+1][j-cost] + ic[i].value);
            }
        }
    }
    
    return netValue[0][budget];
}
