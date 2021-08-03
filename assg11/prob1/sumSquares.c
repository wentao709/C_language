/*
* File: sumSquares.c
* Author: wentao zhou
* Purpose: define a function to print out all the numbers which can be
* written as the sum of two squares in an interval, [m,n]. m,n is what user
* entered.
*/

# include<stdio.h>
# include <math.h>
# include <stdlib.h>

int isSumSquares(int num);

/*
* main()
* take the inputs m,n  and determine and print out the number which is
* the sum of two squares in the interval [m,n]. It assumes that the m,n
* are positive integers.
*/
int main(){
  int m = 0, n = 0;
  int checkM = scanf("%d",&m);
  int checkN = scanf("%d",&n);
  if (checkM != 1 || checkN != 1 || m<=0 || n<=0){
    fprintf(stderr, "invalid input, it should be positive integers\n");
    exit(1);
  }
  int num;
  for (num = m; num<=n ;num++){
    if (isSumSquares(num)){
      printf("%d\n",num);
    }
  }
  // once we got the number we want, we should stop the loop and start to
  // do the next number.
  exit(0);
}

int isSumSquares(int num){
  float max = sqrt(num); // n and p must be less than max.
  int n;
  for (n = 1; n < max ; n++){
    int p;
    for (p = 1 ; p < max ; p++){
      if (n*n+p*p == num){
        return 1;
      }
    }
    // once we got the number we want, we should stop the loop and start to
    // do the next number.
  }
  return 0;
}
