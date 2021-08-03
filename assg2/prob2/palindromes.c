/*
* File: palindromes.c
* Author: wentao zhou
* Purpose: the class is to determine if the strings are palindromes
*
*/

# include<stdio.h>
# include <stdlib.h>

void toLower();


/*
* main() - go through all the input string and check if it's a palindromes,
* print 1 if it is and otherwise print 0. It assumes that each word is at
* most 64 char long, and no white space in a wrod.
*/
int main(){
  char str[65];
  int lengthOfString;
  int fromHead;
  int fromTail;
  int isPalindromes;
  while (scanf("%64s", str) != EOF){
    toLower(str);
    isPalindromes = 1;
    for (lengthOfString = 0; str[lengthOfString] != '\0';lengthOfString++){}
    fromHead = 0; // go from the first char in the string
    fromTail = lengthOfString-1; // go from the last char in the string
    while (fromHead <= fromTail){
      if (str[fromHead] != str[fromTail]){
        isPalindromes = 0;
        printf("%d\n",0);
        break;
      } // if it's not a palindromes, stop the loop and go to next input.
      fromHead += 1;
      fromTail -= 1;
    }
    if(isPalindromes){
      printf("%d\n",1);
    }
  }
  exit(0);
}

/* toLower(char []): change all the character to lower cases.
*/
void toLower(char c[65]){
  int i;
  for (i = 0; c[i] != '\0'; ++i){
    if (c[i] >= 'A' && c[i] <= 'Z'){
      c[i] = c[i]-'A'+'a';
    }
  }
  return;
}
