#include <stdio.h>
#include <stdlib.h>

typedef struct list{
    char info[20];
    struct list *next;
}List;

List *createLists(char *exp){
    int i, j=0, countParentheses=0;
    List *l = (List *)malloc(sizeof(List)); 
    l->next = NULL;
    List *aux = l;
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
    if(l != NULL){
        int i;
        for(i=0; l->info[i]!='\0'; i++){
            if(l->info[i] == '~' && l->info[i+3] != ')'){
                int ind = hasChar('+', l->info), index = ind;
                if(ind != -1){
                    char new[20] = "~(";
                    int j = 2; 
                    ind++;
                    do{
                        new[j] = l->info[ind];
                        ind++;
                        j++;
                    }while(l->info[ind] != '\0');
                    l->info[index] = ')';
                    concStrByInd(l->info, new, index+1);
                } else {
                    List *aux = (List *)malloc(sizeof(List));
                    aux->info[0] = '~';
                    aux->info[1] = '(';
                    int j, k=2;
                    for(j= i+3 ; l->info[j] != '\0' ; j++){
                        aux->info[k] = l->info[j];
                        k++;
                    }
                    l->info[i+3] = ')';
                    l->info[i+4] = '\0';
                    aux->info[k] = '\0';
                    aux->next = l->next;
                    l->next = aux;
                }
            }
        }
        l->next = deMorgan(l->next);
    }
    return l;
}

int main(){
    char exp[20] = "~(A+B)+~(AB)+AB";
    List *list = createLists(exp);
    list = deMorgan(list);
    printf("\n%s", exp);
    printList(list);
    return 1;
}
