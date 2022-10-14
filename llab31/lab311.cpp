#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
 
typedef struct _node { // создание списка
    struct _node* next; // это у нас ссылка на следующий указатель
    int val;
} node;
 
typedef struct {
    node* lst; // это у нас ссылка на предыдущий указатель
} pqueue;
 
inline void pqueue_init(pqueue* pq)  { pq->lst = NULL; } // встриваемая функция инициализации для вызова, пред знач pq становится пустым 
inline  int pqueue_top(pqueue* pq)   { return pq->lst->val; } //встраиваемая функция  возвращает 
inline  int pqueue_empty(pqueue* pq) { return (pq->lst == NULL); } // встраиваемая функция для вызова возвращает пред знач pq становится пустым 
 
int  pqueue_push(pqueue* pq, int val); // вызов функции
void pqueue_pop(pqueue* pq); // вызов функции
void pqueue_clear(pqueue* pq); // вызов функции
 
int main(void){
    int    i;
    pqueue pq;
    pqueue_init(&pq);
    for(i = 0; i < 10; ++i)
        pqueue_push(&pq, rand() % 10);
        
    pqueue_push(&pq,  100);
    pqueue_push(&pq, -100); 
 
    while(! pqueue_empty(&pq)){
        printf("%d ", pqueue_top(&pq));
        pqueue_pop(&pq);
    }
    return 0;
}
 
//вставка
int pqueue_push(pqueue* pq, int val){
    node* p, *i, **q = &pq->lst;
    for(i = pq->lst; (i != NULL) && (i->val > val); ){ //пока i не null и прошлое знач val больше val нынешнего выполняется 
        q = &i->next; // q присваивается значения указателя i с прошлого next
        i = i->next; // i присваивается значение указателя i с прошлого next
    }
    // Создали указатель на переменную структуры списка и выделим немного памяти для нее
    p = (node*)malloc(sizeof(node));
    if(p != NULL){ //если список p не пустой, то
        p->val  = val; // p с прошлым val становится новыйм val
        p->next = i; // p следующее становится i
 
        if(pq->lst == NULL) //если пред знач pq не пустая, то
            pq->lst = p; // пред знач pq становится p
        else 
            *q = p; // указатель q становится p
    }
    return (p != NULL);
}
 
//вытолкнуть макс
void pqueue_pop(pqueue* pq){
    node* t;
    if(pq->lst != NULL){ // если пред знач pq не пустое, то
        t = pq->lst; // t становится пред знач pq
        pq->lst = pq->lst->next; //пред знач pq становится след знач pq
        free(t);
    }
}
 
//удаление увсех
void pqueue_clear(pqueue* pq){
    node* t;
    while(pq->lst != NULL){ // пока пред знач pq не пустое
        t = pq->lst; // t становится пред значением pq
        pq->lst = pq->lst->next; // пред знач pq становится след значением pq
        free(t);
    }
}
