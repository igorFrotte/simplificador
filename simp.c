#include <stdio.h>
#include <stdlib.h>

typedef struct list{
    char info[100];
    struct list *next;
}List;

char toUpperCase(char c){
    if(c <= 'z' && c >= 'a')
        c = (c - 'a') + 'A';
    return c; 
}

int hasChar(char c, char *string){
    int i;
    for(i=0; string[i] != '\0'; i++){
        if(string[i] == c)
            return i;
    }
    return -1;
}

void strCopyByIndex(char *origin, int iOrigin, char *copy, int iCopy){
    do{
        copy[iCopy] = origin[iOrigin];
        iOrigin++;
        iCopy++;
    }while(origin[iOrigin] != '\0');     
    printf("\n\nwwerwe --  %s", origin);  
    printf("\n\nwwerwe --  %s\n\n", copy);
}

List *separator(List *l){
    int i, countParentheses=0;
    for(i=0; l->info[i] != '\0' ;i++){ 
        if(l->info[i] == '(')
            countParentheses++;
        if(l->info[i] == ')')
            countParentheses--;
        if(l->info[i] == '+' && countParentheses == 0){
            List *aux, *new = (List *)malloc(sizeof(List)); 
            l->info[i] = '\0';
            strCopyByIndex(l->info, i+1, new->info, 0);
            aux = l->next;
            l->next = new;
            new->next = aux;
            l->next = separator(l->next);
            break;
        }
    }
    return l;
}

List *createLists(char *exp){
    List *l = (List *)malloc(sizeof(List)); 
    strCopyByIndex(exp, 0, l->info, 0);
    l->next = NULL;
    l = separator(l);
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
    char exp[] = "~(A+B+C)+~((AB)+C)+AB+CA";
    List *list = createLists(exp);
    list = deMorgan(list);
    printf("\n%s", exp);
    printList(list);
    return 1;
}
