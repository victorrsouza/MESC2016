#include <stdio.h>
#include <stdlib.h>

typedef struct list List;

struct list {
    int value;
    List * prev;
    List * next;
};

void initList(List **);
int addValue(List **, int);
void printList(List *);
void printPrevAndNext(List *, int);
int getLength(List *);
List * getNth(List *, int);

void xorSwap(int *, int *);
void nodeSwap (List **, List **);

void callBubbleSort(List *);
void callInsertionSort(List *);
void callSelectionSort(List *);
void callShellSort(List *);
void callMergeSort(List * l);

int main() {
    List * newList;

    initList(&newList);
    addValue(&newList, 1);
    addValue(&newList, 2);
    addValue(&newList, 3);
    addValue(&newList, 4);
    addValue(&newList, 5);
    addValue(&newList, 6);
    addValue(&newList, 7);
    addValue(&newList, 8);

    printf("Original list\n");
    printList(newList);

    //alteram a lista original porque fazer alteracao no valor do nos ponteiros do no.
    //TODO: chamar um metodo por execucao.
    //callBubbleSort(newList);
  	//callInsertionSort(newList);
  	//callSelectionSort(newList);
  	callShellSort(newList);

    return 0;
}

void initList(List ** l){
    *l = NULL;
}

int addValue(List ** l, int v) {
    List * lt = (List *) malloc(sizeof(List));
    if (lt == NULL) return 0;

    lt->value = v;
    lt->next = *l;
    lt->prev = NULL;
    if (*l != NULL) (*l)->prev = lt;

    *l = lt;
    return 1;
}

void printList(List * l) {
    for (l; l != NULL; l = l->next) {
        printf("| %d |", l->value);
    }
    printf(".\n");
}

void printPrevAndNext(List * l, int v) {
    for (l; l != NULL; l = l->next) {
        if (l->value == v) {
            int vPrev = l->prev != NULL ? l->prev->value : 0;
            int vNext = l->next != NULL ? l->next->value : 0;
            printf("\n\nThe list value is: %d \nPrevious value is: %d \nNext value is: %d\n", l->value, vPrev, vNext);
        }
    }
}

int getLength(List * l) {
    int i = 0;
    for (l=l; l!=NULL; l=l->next) i++;
    return i;
}

List * getNth(List * l, int index) {
    int i = 0;

    for (l; l != NULL; l = l->next) {
        if (i == index) return l;
        i++;
    }

    return NULL;
}

void xorSwap (int *a , int *b) {
  	if (*a != *b) *a ^= *b ^= *a ^= *b;
}

void nodeSwap (List ** head, List ** current) {
    List * after = (*current)->next;
  	List * afterNext = after->next;
    List * beforeCurrent = (*current)->prev;

    (*current)->next = after->next;
    (*current)->prev = after;

    after->next = (*current);
    after->prev = beforeCurrent;

    if (beforeCurrent) beforeCurrent->next = after;
    else *head = after;
    if (afterNext) afterNext->prev = (*current);

    (*current) = after;
}

void callBubbleSort(List * l) {
    int done = 0;
    List * copy = l;

    printf("Ordering by BubbleSort\n");
    while (!done) {
        done = 1;
        l = copy;
        while (l->next) {
            if (l->value > l->next->value) {
                done = 0;
				//xorSwap(&(l->value), &(l->next->value));
              	nodeSwap(&copy, &l);
              	printList(copy);
            }
            l = l->next;
        }
    }
}

void callInsertionSort(List * l) {
  	List *copy = l;
    List *temp;

  	printf("Ordering by InsertionSort\n");
    while (l->next) {
      temp = l;
      while (temp->next) {
        temp = temp->next;
        if (l->value > temp->value) {
          xorSwap(&(l->value), &(temp->value));
          printList(copy);
        }
      }
      l = l->next;
    }
}

void callSelectionSort(List * l) {
  	int *smaller;
    List *copy = l;
    List *local;

  	printf("Ordering by SelectionSort\n");
    while (l->next) {
      local = l;
      smaller = &(local->value);
      while (local->next) {
		local = local->next;
        if (local->value < *smaller) smaller = &(local->value);
      }
      xorSwap(&(l->value), smaller);
      printList(copy);
      l = l->next;
    }
}

void callShellSort(List * l) {
    int size = getLength(l), i = 0, done = 0, index = 0;
    List * head = l, * temp;

    printf("Ordering by ShellSort\n");
    index = size / 2;
    while (!done) {
        if (index > 1) {
            printf("index size: %d\n", index);
            for(i = 0; i < (size-index); i++) {
                temp = getNth(head, (i + index));
                if (l->value > temp->value) {
                    xorSwap(&(l->value), &(temp->value));
                    printList(head);
                }
                l = l->next;
            }
            index = index / 2;
            l = head;
        }
        else {
            done = 1;
            callInsertionSort(l);
        }
    }
}

void callMergeSort(List * l) {

}
