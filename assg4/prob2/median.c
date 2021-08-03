#include <stdio.h>
#include <stdlib.h>

int main(){
  int num;
  int input;
  scanf("%d", &num);
  if (num<=0){
    fprintf(stderr, "first input should be a positive integer\n");
    exit(1);
  }
  int *sptr;
  int *eptr;
  int *head;
  int i;
  int swapped = 1;
  head = malloc(num*sizeof(int));
  if (head == NULL){
    fprintf(stderr, "out of memory!\n");
  }
  sptr = head;
  for (i = 0; i < num ;i++){
    int status = scanf("%d",&input);
    if (status == 1){
      fprintf(stderr, "number less than first int!\n");
      exit(1);
    }
    *(sptr+i) = input;
  }
  while (swapped){
    swapped = 0;
    sptr = head;
    eptr = sptr + 1;
    for (i = 0; i < num -1 ;i++){
      if (*sptr > *eptr){
        swapped = 1;
        int temp = *sptr;
        *sptr = *eptr;
        *eptr = temp;
      }
      sptr = eptr;
      eptr += 1;
    }
  }
  if (num%2 == 1){
    float median = *(head+(num-1)/2);
    printf("%.1f\n", median);
  }else if(num%2 == 0){
    float median = (float)(*(head+(num)/2)+*(head+(num)/2-1))/2;
    printf("%.1f\n", median);
  }
  exit(0);
}
