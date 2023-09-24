#include <stdio.h>
#include <stdlib.h>

typedef struct list{
    char info[20];
    struct list *next;
}List;

List *createLists(char *exp){
    int i, j=0;
    List *l = (List *)malloc(sizeof(List)); 
    l->next = NULL;
    List *aux = l;
    for(i=0; exp[i]!='\0' ;i++){ 
        if(exp[i] == '+'){
            aux->info[j] =  '\0';
            j = -1;
            List *new = (List *)malloc(sizeof(List));
            aux->next = new;
            aux = aux->next; 
        }else
            aux->info[j] =  exp[i];
        j++;
    }
    return l;
}

char deMorgan(char o){
    return o;
}

void printList(List *l){
    List *aux = l->next;
    printf("%s", l->info);
    while(aux != NULL){
        printf(" + %s", aux->info);
        aux = aux->next;
    }
}

int main(){
    char exp[20] = "'(AB)+'(A)B";
    List *list = createLists(exp);
    printList(list);
    return 1;
}
