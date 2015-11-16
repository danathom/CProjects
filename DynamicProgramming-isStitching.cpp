//  @author Dana Thomas
//  @date 10/4
//

#include <iostream>
#include <string>

using namespace std;

/* 
 Dynamic Programming Question: Given strings A, B, and C, return whether or not C is a stiching of strings 
 A and B. 
 
 Assumptions: A, B, and C have no danger values and are small enough to fit within the classic variable 'String'
 
 Runtime: O((M*N)^2) where M= length of String A, N= length of String B
 */

bool isStiching(string A, string B, string C)
{
    int M = (unsigned int) A.length();
    int N = (unsigned int) B.length();
    
    bool stich[M+1][N+1];
    //memoization: each cell within this 2D array
    //will have a 0/1, which is dependent on whether the
    //corresponding col and/or row both match the potential stich, and
    //its neighboring cells (to demonstrate wheter the previous values
    //of the substrings were also found in the potential stitch)
    //substring A = rows; substring B = cols
    
  
    //initialize all values to False (0)
    for (int a = 0; a < (M+1); a++) {
        for (int b = 0; b < (N+1); b++) {
            stich[a][b] = 0;
        }
    }
    
    //Base Case: if the lengths are unequal, the strings
    //are automatically not a proper stiching
    if ((M+N) != C.length())
        return false;

    for (int i=0; i < (M+1); i++){
        for (int j=0; j< (N+1) ; j++) {
            if (i==0 && j==0) //by default, upper L of array is initialized to T
                stich[i][j] = 1;
            
            // compares all elements of A against the first i-1 elements in C
            else if (j==0 && A[i-1]==C[i-1])
                stich[i][j] = stich[i-1][j];
            
            // same function as ^ but for potential substring B
            else if (i==0 && B[j-1]==C[j-1])
                stich[i][j] = stich[i][j-1];

            // if both the chars you're looking at in the columns and the rows match
            //and either the row above your current OR the row to your left is a 1,
            //put a 1 in your current cell, else put a 0
            else if (A[i-1]==C[i+j-1] && B[j-1]==C[i+j-1])
                stich[i][j]=(stich[i-1][j] || stich[i][j-1]) ;
            
            //compares rows, if the char corresponding to the row you're currently
            //in matches the corresponding char in C (AND IT DOESNT MATCH B),
            //copy the cell up above you into this cell
            else if(A[i-1]==C[i+j-1])
                stich[i][j] = stich[i-1][j];
            
            // same function as ^ but for potential substring B that copies
            //from the cell to its L
            else if (B[j-1]==C[i+j-1])
                stich[i][j] = stich[i][j-1];
            
            //no match
            else stich[i][j] = 0;
        }
    }
    
    //answer will be in lower right of 2D array (0 = no match, 1 = match)
    return stich[M][N];
}

int main()
{
    bool worked = isStiching("XXY", "XXZ", "XXZXXY");
    cout<< "XXY and XXZ make up XXZXXY? " << worked <<endl;
    worked = isStiching("ABC", "123", "AB12C3");
    cout<< "ABC and 123 make up AB12C3? " << worked <<endl;
    worked = isStiching("ABC", "123", "ABA2C3");
    cout<< "ABC and 123 make up ABA2C3? " << worked <<endl;
    worked = isStiching("xxx", "xxx", "xxxxxx");
    cout<< "xxx and xxx make up xxxxxx? " << worked <<endl;
    
    
    return 1;
}