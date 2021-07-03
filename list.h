#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define FALSE   0
#define TRUE   1
typedef int    boolean;

typedef void Object;

#define UORD  0
#define ASC   1
#define DEC 2

// un élément de la List
typedef struct element {
  Object*          reference;   // référence un Object (de l'application)
  struct element* next;     // élément suivant de la List
} Element;

// le type List
typedef struct {
  Element* first; // premier élément de la List
  Element* last; // dernier élément de la List
  Element* current; // élément en cours de traitement (parcours de List)
  int      nbElt;   // nombre d'éléments dans la List
  int      type;    // 0:simple, 1:croissant, 2:décroissant
  char*    (*toString) (Object*);
  int      (*compare) (Object*, Object*);
} List;


Element* createElement();
Element* createElement(Object* Object,Element* next);

boolean emptyElement(Element* element);

Element* createElement(Object* Object);
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

char* intToString(Object* object);
int intCompare(Object* obj1,Object* obj2);
