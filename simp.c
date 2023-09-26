#include <stdio.h>
#include <stdlib.h>

typedef struct list{
    char info[20];
    struct list *next;
}List;

char toUpperCase(char c){
    if(c <= 'z' && c >= 'a')
        c = (c - 'a') + 'A';
    return c; 
}

List *createLists(char *exp){
    int i, j=0, countParentheses=0;
    List *l = (List *)malloc(sizeof(List)); 
    List *aux = l;
    l->next = NULL;
    for(i=0; exp[i]!='\0' ;i++){ 
        if(exp[i] == '(')
            countParentheses++;
        if(exp[i] == ')')
            countParentheses--;
        if(exp[i] == '+' && countParentheses == 0){
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

void printList(List *list){
    List *l = list->next;
    printf("\n%s", list->info);
    while(l != NULL){
        printf(" + %s", l->info);
        l = l->next;
    }
    printf("\n\n");
}

int hasChar(char c, char *string){
    int i;
    for(i=0; string[i] != '\0'; i++){
        if(string[i] == c)
            return i;
    }
    return -1;
}

void concStrByInd(char *str, char *newStr, int ind){
    int i;
    for(i=0; newStr[i] != '\0'; i++){
        str[ind] = newStr[i];
        ind++;
    }
}

List *deMorgan(List *l){
    return l;
}

int main(){
    char exp[40] = "~(A+B+C)+~((AB)+C)+AB";
    List *list = createLists(exp);
    list = deMorgan(list);
    printf("\n%s", exp);
    printList(list);
    return 1;
}
