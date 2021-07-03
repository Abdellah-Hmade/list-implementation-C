#include "list.h"


char* intToString(Object* object);
int intCompare(Object* obj1,Object* obj2);

char* intToString(Object* object){

    char* str=(char*)malloc(10*sizeof(char));sprintf(str,"%d",*((int*)object));
    return str;

}

int intCompare(Object* obj1,Object* obj2){
    if(*((int*)obj1)==*((int*)obj2)){
        return 0;
    }
    else if(*((int*)obj1)<*((int*)obj2)){
        return -1;
    }
    else if(*((int*)obj1)>*((int*)obj2)){
        return 1;
    }

}

int main(){    
    int obj=0;
    int obj3=3;
    int obj1=1;
    int obj2=2;
    List* list=createList(1,(*intToString),(*intCompare));

    insertEndList(list,&obj);
    insertInOrdre(list,&obj2);
    insertInOrdre(list,&obj1);
    insertInOrdre(list,&obj3);
    listList(list);
    extractTopList(list);
    printf("first element : %s\n",list->toString(list->first->reference));
    printf("last element : %s\n",list->toString(list->last->reference));
    //printf("%d\n",inOrdre(&obj1,&obj2,1,list->compare));
    deleteList(list);
    free(list);
}