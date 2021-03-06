/** Mengdi Wei
  * ID:1538074
  * PA4
  * List.c is the library for the Graph.c
  */


#include<stdio.h>
#include<stdlib.h>

#include "List.h"
// structs
typedef struct NodeObj {
    int item;
    struct NodeObj* pre;
    struct NodeObj* next;
} NodeObj;

typedef NodeObj* Node;

typedef struct ListObj {
    Node front;
    Node back;
    Node cursor;
    int index;
    int lengths;
} ListObj;
    //Constructor of Node
   Node nodes (int item) {
   	Node m = malloc(sizeof(NodeObj));
  	m->pre=m->next=NULL;
  	m->item=item;
  	return m;
  }

void freeNodes(Node* pN) {
    if(pN != NULL && *pN != NULL) {
        free(*pN);
        *pN = NULL;
    }
}
 //Constructor of List
  List newList(void) {
  	List list;
  	list=malloc(sizeof(ListObj));
    (list)->front=(list)->back=NULL;
    (list)->cursor=NULL;
    list->lengths=0;
    list->index=-1;
    return list;
  }
  
void freeList(List* pL) {
    if(pL!=NULL && *pL!=NULL){
    Node m = (*pL)->front;
    while(m!=NULL){
        Node cur = m;
        m = m->next;
        free(cur);
    }
    free(*pL);
    *pL = NULL;
  }
}

  //length of list
  int length(List L) {
  	 if (L==NULL) {
        printf("List Error: calling length() on NULL List reference\n");
        exit(1);
    }
  	return L->lengths;
  }
 
 //index of cursor
  int index(List L) {
  	   if (L==NULL) {
        printf("List Error: calling index() on NULL List reference\n");
        exit(1);
    }
    if(L->front==NULL ){
        //printf("List Error: calling index() on an empty List\n");
        return -1;
        exit(1);
    }
  //  if(L->lengths == 0)
    //    return -1;
  	return L->index;
  }
 //return front element
  int front(List L) {
  	  if (L==NULL) {
        printf("List Error: calling front() on NULL List reference\n");
        exit(1);     
    }
    if(L->front==NULL ){
        printf("List Error: calling front() on an empty List\n");
        exit(1);
    }
  	return L->front->item;
  }
  
  //return back element
  int back(List L) {
  	 if (L==NULL) {
       printf("List Error: calling back() on NULL List reference\n");
       exit(1);
    }
    if(L->front==NULL ){
       printf("List Error: calling back() on an empty List\n");
       exit(1);
    }
  	return L->back->item;
  }
// Returns cursor element (pre: length() > 0).
int get(List L) {
 if (length(L)>0 && index(L)>=0) {
        return (L->cursor)->item;
    }
    return -1;
}

//check if two list equals
  int equals(List A, List B) {
  	   if(A ==NULL || B ==NULL) {
        printf("List error: equals() called on null List reference ");
        printf( "One or more of your Lists may be null.\n");
        exit(1);
    }
  	if (A->lengths!=B->lengths) {
  		  return 0;
  	} 
  	Node m= A->front;
  	Node n= B->front;
  	while (n!=NULL&&m!=NULL) {
  			if (n->item!=m->item) {
    			 return 0;
    	 } else {
    	 	n=n->next;
    	 	m=m->next;
    	 }
    	 	
  	}
  	return 1;
  }

//clear list
void clear(List L) {
    if(L == NULL) {
        printf( "List error: clear() called on null List reference\n");
        exit(1);
    }
    Node m = L->front;
    while(m != NULL) {
        Node cur = m;
        m = m->next;
        free(cur);
    }
    L->front = L->back = L->cursor = NULL;
    L->index = -1;
    L->lengths = 0;
}

  //move the cursor to front
   void moveFront(List L) {
   	  if (L==NULL) {
        printf("List Error: calling moveFront() on NULL List reference\n");
        exit(1);
    }
   		if (length(L)>0) {
    		L->index=0;
    		L->cursor=L->front;
    	} 
     return;
   }
  // move the cursor to back
  void moveBack(List L) {
  	  if (L==NULL) {
        printf("List Error: calling moveBack() on NULL List reference\n");
        exit(1);
    }
      if (length(L)>0) {
    		L->index=L->lengths-1;
    		L->cursor=L->back;
    	}
    	return;
    }
//move cursor previous
void movePrev(List L) {
    if(L == NULL) {
        printf("List error: movePrev() called on null List reference\n");
        exit(1);
    }
    if(L->cursor == L->front) {
        L->cursor = NULL;
        L->index = -1;
    } else {
        L->cursor = L->cursor->pre;
        L->index--;
    }
}
 //move cursor next
void moveNext(List L) {
    if(L == NULL) {
        printf("List error: moveBack() called on null List reference\n");
        exit(1);
    }
    if(L->cursor == L->back) {
        L->cursor = NULL;
        L->index = -1;
    } else {
        L->cursor = L->cursor->next;
        L->index++;
    }
}

     //prepend a element
    void prepend (List L, int item) {
    	 if (L==NULL) {
        printf("List Error: calling prepend() on NULL List reference\n");
        exit(1);
    }
		Node value=nodes(item);
		
		if ((*L).lengths==0) {
			 L->front=L->back=value;
			L->lengths++;
		} else {
			 L->front->pre=value;
			 value->next=L->front;
			 L->front=value;
			 L->lengths++;
			 L->index++;
		}
		return;
	}

  //append an element
	 void append (List L, int data) {
		if(L == NULL) {
		printf("List Error: calling append() on NULL List reference\n");
		exit(1);
	}
	Node node = nodes(data);
	if(length(L) == 0) {
		L->front = node;
		L->back = node;
	} else {
		L->back->next = node;
		node->pre = L->back;
		L->back = node;
	}
	L->lengths++;
	 }

 //insert an element before cursor
	 void insertBefore(List L, int item) {
	 	  if (L==NULL) {
        printf("List Error: calling insertBefore() on NULL List reference\n");
        exit(1);
    }
    if(length(L)==0 ){
        printf("List Error: calling insertBefore() on an empty List\n");
        exit(1);
    }
	 	Node value=nodes(item);
	 	if (L->index==0)
	 	    prepend(L, item);
	 	 else {
	 	 	  value->pre=L->cursor->pre;
	 	 	  value->next=L->cursor;
	 	 	  L->cursor->pre->next=value;
	 	 	  L->cursor->pre=value;
	 	 	  L->lengths++;
	 	 	  L->index++;
	 	 }
	 	 return;
	 }

	 //insert an element after cursor
  void insertAfter (List L, int item) {
  	  if (L==NULL) {
        printf("List Error: calling insertAfter() on NULL List reference\n");
        exit(1);
    }
    if(L->lengths==0 ){
        printf("List Error: calling insertAfter() on an empty List\n");
        exit(1);
    }
	 Node value=nodes(item);
	 	if (L->index==L->lengths-1)
	 	    append(L, item);
	 	 else {
	 	 	  value->next=L->cursor->next;
	 	 	  L->cursor->next=value;
	 	 	  value->pre=L->cursor;
	 	 	  L->cursor=value;
	 	 	  L->lengths++;
	 	 }
	 	  return;
	 }
 //idelete front element
void deleteFront(List L) {
    if(L == NULL) {
        printf( "List error: deleteFront() called on null List reference\n");
        exit(1);
    }
    if(L->lengths <= 0) {
        printf( "List error: deleteFront() called on empty List\n");
        exit(1);
    }
    Node tmp = L->front;
    if(length(L) > 1) {
    	L->front = L->front->next;
    	L->index--;
    }
    else {
    	 L->front = L->back = NULL;
    	 L->index=-1;
    	}
    L->lengths--;
    freeNodes(&tmp);
   
}

	//delete back element
	 void deleteBack(List L) {
	 	  	if(L == NULL) {
		printf("List Error: calling deleteBack() on NULL List reference\n");
		exit(1);
	}
	if(length(L) == 0) {
		printf("List Error: calling deleteBack() on empty List\n");
		exit(1);
	}
	if(L->cursor == L->back) {
		L->cursor = NULL;
		L->index = -1;
	}
	Node N = L->back;
	if(length(L) > 1) {
		L->back = L->back->pre;
	} else {
		L->back = NULL;
		L->front = NULL;
	}
	L->lengths--;
	freeNodes(&N);
	 	}

//delete cursor element
void delete(List L) {
    if(L == NULL) {
        printf("List error: delete() called on null List reference\n");
        exit(1);
    }
    if(L->lengths <= 0) {
        printf( "List error: delete() called on empty List\n");
        exit(1);
    }
    if(L->cursor == NULL) {
        printf( "List error: delete() called on undefined cursor");
        exit(1);
    }
    if(L->cursor == L->back) {
        deleteBack(L);
        return;
    }
    else if(L->cursor == L->front) {
        deleteFront(L);
        return;
    }
    L->cursor->pre->next = L->cursor->next;
    L->cursor->next->pre = L->cursor->pre;
    L->cursor = NULL;
    L->index = -1;
    L->lengths--;
}

  void printList(FILE* out, List L) {
	
	    Node m=L->front;
	    while (m!=NULL) {
	    	fprintf(out, "%d ", m->item);
	    	m=m->next;
	    }
	    return;
	  }
	  
 List copyList(List L) {
      List copyList=newList();
      Node i=L->front;
      while (i!=NULL) {
      	append(copyList, i->item);
      	i=i->next;
      }
      return copyList;
    }