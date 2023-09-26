#include <stdio.h>
#include <stdlib.h>

typedef struct list{
    char info[80];
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
}

List *separator(List *l){
    int i, countParentheses = 0;
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

List *deMorgan(List *l){
    int iNeg = 0, i, j = 0;
    char newStr[80];
    for(i=0; l->info[i] != '\0'; i++)
        if(l->info[i] == '~' && l->info[i+1] == '(')
            iNeg = i;
    for(i=iNeg+2; l->info[i] != ')'; i++){
        newStr[j] = l->info[i];
        j++;
    }
    newStr[j] = '\0';
    printf("\n\nwefewgfew ---  %s\n\n", newStr);
    return l;
}

List *trigger(List *l){
    if(l != NULL){
        int cont = 0;
        while(cont == 0){
            int i;
            cont = 1;
            for(i=0; l->info[i] != '\0'; i++){
                if(l->info[i] == '~' && l->info[i+1] == '(')
                    l = deMorgan(l);
            }
        }
        l->next = trigger(l->next);
    }
    return l;
}

int main(){
    char exp[] = "~(A+B+C)+~(~(A+B)+~C)+AB+CA";
    List *list = createLists(exp);
    list = trigger(list);
    printf("\n%s", exp);
    printList(list);
    return 1;
}
