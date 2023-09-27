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

int firstChar(char c, char *string, int indInit){
    int i;
    for(i=indInit; string[i] != '\0'; i++){
        if(string[i] == c)
            return i;
    }
    return -1;
}

int lastChar(char c, char *string){
    int i, j = -1;
    for(i=0; string[i] != '\0'; i++){
        if(string[i] == c)
            j = i;
    }
    return j;
}

void strCopyPart(char *origin, int originInit, int originFinal, char *copy, int copyInit){
    while(origin[originInit] != '\0' && originInit <= originFinal){
        copy[copyInit] = origin[originInit];
        originInit++;
        copyInit++;
    }
    copy[copyInit] = '\0';
}

int backTrack(char *string, int ind){
    if(ind != 0)
        ind--;
    for(ind; (string[ind] <= 'Z' && string[ind] >= 'A' && ind != 0) ||  string[ind] == '~'; ind--){}
    return ind+1;
}

int afterTrack(char *string, int ind){
    if(string[ind] != '\0')
        ind++;
    for(ind; string[ind] <= 'Z' && string[ind] >= 'A' && string[ind] != '\0'; ind++){}
    return ind-1;
}

//tirar
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

void deMorgan(char *str){
    printf("\nAplicando DeMorgan em: %s", str);
    int ind = firstChar('+', str, 0);
    char new[80];
    if(ind == -1){
        for(ind=0; str[ind] < 'A' || str[ind] > 'Z'; ind++){}
        strCopyPart(str, 0, ind, new, 0);
        new[ind+1] = ')';
        new[ind+2] = '+';
        new[ind+3] = '~';
        new[ind+4] = '(';
        strCopyPart(str, ind+1, 99, new, ind+5); 
    } else {
        strCopyPart(str, 0, ind-1, new, 0);
        new[ind] = ')';
        new[ind+1] = '~';
        new[ind+2] = '(';
        strCopyPart(str, ind+1, 99, new, ind+3); 
    }
    
    strCopyPart(new, 0, 99, str, 0);
    printf("\nResultado DeMorgan: %s", str);
}

void *trigger(char *str){
        int cont = 0;
        while(cont == 0){
            int i;
            cont = 1;
            for(i=0; str[i] != '\0'; i++){
                if(str[i] == '~' && str[i+1] == '('){
                    deMorgan(str);
                    break;
                }
            }
        }
}

List *deeper(List *l){
    if(l != NULL){
        int phaInternOpen = lastChar('(', l->info);
        if(phaInternOpen != -1){
            int phaInternClose = firstChar(')', l->info, phaInternOpen);
            char str[80];
            int init = backTrack(l->info, phaInternOpen);
            int final = afterTrack(l->info, phaInternClose);
            strCopyPart(l->info, init, final, str, 0);
            printf("\n\nstring: %s\n\n", str);
            trigger(str);
        } else {
            printf("\n\nstring: %s\n\n", l->info);
            trigger(l->info);
        }
        l->next=deeper(l->next);
    }
    return l;
}

int main(){
    char exp[] = "~(A+B+C)+~(AC(A+B)B+~C)+~(ABC)+CA";
    List *list = createLists(exp);
    list = deeper(list);
    printf("\n%s", exp);
    printList(list);
    return 1;
}
