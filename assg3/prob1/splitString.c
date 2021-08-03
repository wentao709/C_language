/*
* File: splitString.c
* Author: wentao zhou
* Purpose: the program's behavior is to look for dash character '-', and
* prints the portions of the string separated by dashes on separate lines.
*
*/

# include <stdio.h>
# include <stdlib.h>

/*
* main() -- go through all the input string. I replaced the '-' with '\n', and git rid
* of the extra '-' in the strings, and finally use a single print statement to print each string out.
* it assumes the all the strings can't be longer than 255.
*
*/
int main(){
  char str[256];
  int i;
  int j;
  int replace = 0; // check if I have replaced the '-' with '\n'
  int lengthOfString;
  while (scanf("%255s", str) != EOF){
    for (i = 0; str[i] != '\0';i++){
      if (str[i]!='-'){
        replace = 1; // the character is not '-', so when I see '-' i could replace it with '\n'
      }
      if (str[i] == '-' && !replace){
        for (j = i; str[j]!= '\0';j++){
          str[j] = str[j+1];
        }
        replace = 0; // once I see '-', replace it with '\n', then get rid of the extra '-'.
        i--;
      }else if (str[i] == '-' && replace){
        str[i] = '\n'; // replace it with '\n'
        replace = 0;
      }
    }
    for (lengthOfString = 0; str[lengthOfString] != '\0';lengthOfString++){}
    /* in the loop, git rid of the extra '-' by moving each chracter behind the '-'
    * forward one digits.
    */
    if (lengthOfString > 0){
      if (str[lengthOfString-1] == '\n'){
        str[lengthOfString-1] = '\0';
      }
      printf("%s\n",str);
    }
    replace = 0;
  }
  exit(0);
}
