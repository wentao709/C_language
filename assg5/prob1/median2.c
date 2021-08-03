# include <stdio.h>
# include <stdlib.h>

void sort_list();

struct s{
  int num;
  struct s *next;
};

struct s *list_hd = NULL;

int main(){
  int input;
  while(scanf("%d",&input)!= EOF){
    struct s *tmpnode;
    tmpnode = malloc(sizeof(struct s));
    if (tmpnode == NULL){
      fprintf(stderr, "out of memory\n");
      exit(1);
    }
    tmpnode -> num = input;
    tmpnode -> next = list_hd;
    list_hd = tmpnode;
  }
  struct s *list = list_hd;
  while(list->next!=NULL){
    printf("%d\n", list->num);
    list = list->next;
  }
  sort_list();
  int count = 1;
  struct s *tmp = list_hd;
  while(tmp -> next != NULL){
    tmp = tmp -> next;
    count += 1;
  }
  int i;
  tmp = list_hd;
  if (count%2 == 1){
    for (i = 0; i<(count-1)/2 ;i++){
      tmp = tmp -> next;
    }
    float median = tmp -> num;
    printf("%.1f\n", median);
  }else if(count%2 == 0){
    for (i = 0; i<(count-2)/2 ;i++){
      tmp = tmp -> next;
    }
    int first = tmp -> num;
    int second = tmp -> next -> num;
    float median = (float)(first+second)/2;
    printf("%.1f\n", median);
  }
  exit(0);
}

void sort_list(){
  struct s *ptr1, *ptr2;
  int swapped = 1;
  while (swapped){
    swapped = 0;
    for (ptr1 = list_hd; ptr1!=NULL; ptr1 = ptr1->next)
      for (ptr2 = ptr1->next ; ptr2 != NULL; ptr2 = ptr2->next){
        if (ptr1->num > ptr2->num){
          swapped = 1;
          int temp = ptr1->num;
          ptr1->num = ptr2->num;
          ptr2->num = temp;
        }
      }
  }
}
