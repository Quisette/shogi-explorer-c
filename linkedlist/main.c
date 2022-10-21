#include<stdio.h>
#include"linkedlist.h"

int main(){
    List_t *list = initializeList("first");
    char str1[5] = "test";
    char str2[6] = "test2";

    append(str1, list);
    append(str2, list);
    append("fsdaf", list);
    print(*list);
    freeList(list);
    // free(list);
    return 0;
}