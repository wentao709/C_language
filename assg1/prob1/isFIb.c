/*
* File: isFib.c
* Author: wentao zhou
* Purpose: define a function to determine if all the numbers
* are Fibonacci number
*
*/


# include<stdio.h>
# include <stdlib.h>

/*
* main() -- go through the all the input integers and determine and print out
* the fib number. it assumes that the input integers are all positive and not
* too large to fit into a type int.
*/
int main(){
  int firstFib, secondFib,sumFib;
//  int input;
  int checkInput = scanf("%d",&input);
  int gotError = 0; // as a boolean to see if it meets a error
  while(checkInput != EOF) {
      if (checkInput == 0){ // non-integer input
        fprintf(stderr, "non-integer input\n");
        exit(1);
      }
      if (input <= 0){ // non-positive input
        fprintf(stderr, "invalid input, it should be positive integers\n");
        gotError = 1;
      }else{
      firstFib = 1;
      secondFib = 1;
      sumFib = firstFib + secondFib;
      // check the initial value
      if (input == firstFib || input == secondFib || input == sumFib){
        printf("%d is fib\n", input);
      }else{
        while(sumFib <= input){
          if (input == firstFib || input == secondFib || input == sumFib){
            printf("%d is fib\n", input);
            break;
          }else{ // go to next
            firstFib = secondFib;
            secondFib = sumFib;
            sumFib = firstFib + secondFib;
            }
          }
        }
        // checkfirstFib, secondFib, sumFib
        if(!(input == firstFib || input == secondFib || input == sumFib)){
          printf("%d is not fib\n", input);
        }
      }
      checkInput = scanf("%d",&input);
    }
  if (gotError){
    exit(1);
  }else{
    exit(0);
  }
}
