/*
* File: sumDigits.c
* Author: wentao zhou
* Purpose: input some integers and for each one calculate the
* sum of its digits.
*
*/

# include<stdio.h>
# include<stdlib.h>


/*
* main()
* take the input integers and calculate their sum of digits.
* it assumes that the input integers are all positive.
*/
int main(){
  int input;
  int digit;
  int checkInput = scanf("%d",&input);
  int gotError = 0; // as a boolean to see if it meets a error
  while(checkInput != -1){
    if (checkInput == 0){ // non-integer input
      fprintf(stderr, "non-integer input\n");
      exit(1);
    }
    if (input <= 0){ // non-positive input
      fprintf(stderr, "invalid input, it should be positive integers\n");
      gotError = 1;
    }else{
      int sum = 0;
      int divide = input;
      while(divide > 0){
        digit = divide%10; // get the last digits
        sum+=digit;
        divide = divide/10; // go to the next digits
      }
      printf("%d\n", sum);
    }
    checkInput = scanf("%d",&input);
  }
  if (gotError){
    exit(1);
  }else{
    exit(0);
  }
}
