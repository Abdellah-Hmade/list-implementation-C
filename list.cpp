#include "list.h"


Element* createElement();
Element* createElement(Object* Object,Element* next);

boolean emptyElement(Element* element);

Element* createElement(Object* object);
void copyElement(Element* element1,Element* element2);

static boolean inOrdre (Object* objet1, Object* objet2, boolean ordreCroissant, 
                 int (*comparer) (Object*, Object*)); 

void     initList              (List* li, int type, char* (*toString) (Object*),
				 int (*compare) (Object*, Object*) );
void     initList              (List* li);

void     initList              (List* li,int type);

//
List*   createList             (int type, char* (*toString) (Object*), 
				 int (*compare) (Object*, Object*) );
List*   createList             (int type);
List*   createList             ();
int      nbElements              (List* li);
//
boolean     insertTopList   (List* li, Object* object);
boolean     insertEndList    (List* li, Object* Object);
boolean insertAfter(List *li,Object* object,Object* object1);
boolean insertAfterCurrent(List *li,Object* object);

// parcours de Liste
boolean  emptyList              (List* li);
void     openList            (List* li);
boolean  endList               (List* li);
Object*   currentObject           (List* li);
//
void nextElement(List* li);
void nextElement(List* list,int numberEle);
void     listList            (List* li);
void     listList            (List* li, void (*f) (Object*));
Object*   searchObject        (List* li, Object* searchedObject);

// extract from list

Object*   extractTopList  (List* li);
Object*   extractEndList   (List* li);
Object*  extractAnObject        (List* li, Object* Object);
void     deleteList          (List* li);
void     copyList          (List* l1, List* l2);
boolean     insertInOrdre         (List* li, Object* Object);




void initList(List* li, int type, char* (*toString) (Object*),int (*compare) (Object*, Object*) ){
            li->first=NULL;
            li->current=NULL;
            li->last=NULL;
            li->nbElt=0;
            li->type=type;
            li->compare=compare;
            li->toString=toString;
                 }

void initList(List* li){

    initList(li,UORD,NULL,NULL);

    }


void initList(List* li,int type){

    initList(li,type,NULL,NULL);
    }

List* createList(int type, char* (*toString) (Object*), int (*compare) (Object*, Object*) ){
    List* list;
    
    list=(List*)malloc(sizeof(List));
    initList(list,type,toString,compare);

    return list;
}

List* createList(int type){
    List* list;
    list=(List*)malloc(sizeof(List));
    initList(list,type);

    return list;
}

List* createList(){
    List* list;

    list=(List*)malloc(sizeof(List));
    initList(list);
    
    return list;
}

Element* createElement(Object* object,Element* next){

    Element* element0=(Element*)malloc(sizeof(Element));
    element0->reference=object;
    element0->next=next;
    return element0;

}

Element* createElement(Object* object){


    return createElement(object,NULL);

}

Element* createElement(){

    return (Element*)malloc(sizeof(Element));
    
}


boolean emptyElement(Element* element){

if (element==NULL || element->reference==NULL){
    return TRUE;
}
return FALSE;


}
void copyElement(Element* element1,Element* element2){
    if(!emptyElement(element1)){
        element1->reference=(Object*)element2->reference;
        element1->next=(Element*)element2->next;
    }
    else{
        if (element2==NULL)
        {
            element1=NULL;
        }
        else{
            element1->reference=element2->reference;
            element1->next=element2->next;
        }
    }
}


boolean  emptyList(List* li){

if (li==NULL  || li->nbElt==0){
    return TRUE;
}
return FALSE;

}


int nbElements(List* li){

return (int)li->nbElt;

}

boolean insertTopList(List* li, Object* object){

if(li->first==NULL){
    Element* New=createElement(object); 
    li->first=New;
    if(li->last==NULL){
    li->last=New;
}

}
else{
    Element* New=createElement(object,li->first);
    li->first=New;
    if(li->last==NULL){
    li->last=New;
}

}



li->nbElt++;
return TRUE;

}
boolean insertEndList(List* list,Object* object){

 
if(!emptyList(list)){
Element* New=createElement(object);
list->last->next=(Element*)New;

list->last=New;
list->nbElt++;
}

else{
    insertTopList(list,object);
}


return TRUE;

}

boolean insertAfterCurrent(List* list,Object* object){

if(!emptyList(list)){

    
        if(list->current==list->last || list->current==NULL){
            insertEndList(list,object);
            return TRUE;
        }

        else{
            Element* newEl=createElement(object);
            newEl->next=list->current->next;
            list->current->next=newEl;
            list->nbElt++;
            return TRUE;
        }
    
}

return FALSE;


}

boolean insertAfter(List* list,Object* object,Object* object1){

if(!emptyList(list)){

    if(searchObject(list,object)==object){

        if(list->current==list->last){
            insertEndList(list,object1);
            
            return TRUE;
        }

        else{
            Element* newEl=createElement(object1);
            newEl->next=list->current->next;
            list->current->next=newEl;
            list->nbElt++;
            return TRUE;
        }
    }

    else{
        return FALSE;
    }
}

return FALSE;

}


void openList(List* list){

    list->current=list->first;
}

boolean endList(List* list){

    return (list->current==NULL)? TRUE:FALSE;

}

Object* currentObject(List* list){

    return (Object*)list->current->reference;

}

void nextElement(List* list){

    list->current=list->current->next;
}


void nextElement(List* list,int numberEle){

    for(int i=0;i<numberEle;i++){
        list->current=list->current->next;
    }

}

void listList(List* list){

if(! emptyList(list) && list->toString!=NULL){
    openList(list);
    int i=0;
    printf("\n\t\t\t\t Listing Objects of the list :\n");
    while(! endList(list)){
        printf("[ Element %d ]\t %s \n",i+1,list->toString((Object *)list->current->reference));
        nextElement(list);
        i++;   
    }
}

}

void listList(List* list, void (*f) (Object*)){

if(! emptyList(list) && list->toString!=NULL){
    openList(list);
    printf("\n\t\t\t\t Listing Objects of the list :\n");
    while(! endList(list)){
    
            f((Object*)list->current->reference);
            nextElement(list);    
    
        }
    }

}

Object* searchObject(List *list,Object* object){

if(! emptyList(list)){
    openList(list);
    while(! endList(list)){
        if(list->compare(list->current->reference,object)==0){
            return (Object*)list->current->reference;
            }
        nextElement(list);
        }
    return NULL;
    }
else{
    return NULL;
    }

}

Object* extractTopList(List* list){
if(! emptyList(list)){
Element* extracted=list->first;
openList(list);
    if(list->nbElt >1){
    list->first=list->first->next;
    list->nbElt--;
        }
    else{
        list->first=NULL;
        list->last=NULL;
        list->nbElt--;
    }
    return (Object*)extracted->reference;

}
else{
    return NULL;
}
}

Object* extractEndList(List* list){

Element* extracted=list->last;
openList(list);

if( (! emptyList(list)) && list->last!=NULL){
    if(list->nbElt >1){

        nextElement(list,list->nbElt-1);
        list->last=list->current;
        list->last->next=NULL;
        }
    else{
        list->first=NULL;
        list->last=NULL;
    }
    return (Object*)extracted->reference;

}
else{
    return NULL;
}



}

Object *extractAnObject(List* list, Object* object){

if(! emptyList(list)){

    openList(list);

    if(list->compare(list->first->reference,object)==0){

        extractTopList(list);
        return object;

    }
    else if(list->compare(list->last->reference,object)==0){

        extractEndList(list);
        return object;

    }
    else{

    while(! endList(list)){

        if(list->current->next!=NULL && list->current->next->next!=NULL && list->current->next->reference!=NULL && list->compare(list->current->next->reference,object)==0){
            list->current->next=list->current->next->next;
            return object;
            }
        nextElement(list);
        }
    return NULL;
    
        }

}
   
else{
    return NULL;
    }
}

void deleteList(List* list){
 
 openList(list);
  while (!endList(list)) {
    Element* ptc =list->current;
    nextElement(list);
    //free (ptc->reference);  // si on veut détruire les objets de la liste
    free (ptc);
  }
initList(list);

}

void copyList(List* list1,List* list2){

    deleteList(list1);

    if(!emptyList(list2)){
    
        initList(list1,list2->type,list2->toString,list2->compare);
    
        list1->nbElt=list2->nbElt;

        if(list2->first!=NULL){
        
            list1->first=list2->first;
        
        }
        if(list2->last!=NULL){
        
            list1->last=list2->last;
        
        }
        list1->current=list1->first;
    }
    else{
        if(list2==NULL){list1=NULL;}
        
        else{
            initList(list1,list2->type,list2->toString,list2->compare);
        }
    }
}

static boolean inOrdre (Object* objet1, Object* objet2, boolean ordreCroissant, 
                 int (*comparer) (Object*, Object*)) {
  boolean ordre = comparer (objet1, objet2) < 0;
  if (!ordreCroissant) ordre = !ordre;
  return ordre;
}

boolean insertInOrdre(List* list,Object* object){

    if(emptyList(list) || inOrdre(object, list->first->reference, list->type==1, list->compare)==1){
    
    return insertTopList(list,object);
    
    }

    else{
     
            boolean  isFound = FALSE;
            openList(list);
            //Element* ele=list->first;
            while (!endList(list)) {
                
                if (list->current->next!=NULL && inOrdre(object, list->current->next->reference, list->type==1, list->compare)){
                    break;
                    }
                nextElement(list);
                }
          // insertion en milieu de liste ou fin de liste
 
            return insertAfterCurrent(list,object);
            


}
}
