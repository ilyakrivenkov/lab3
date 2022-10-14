#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
 
typedef struct _node { // �������� ������
    struct _node* next; // ��� � ��� ������ �� ��������� ���������
    int val;
} node;
 
typedef struct {
    node* lst; // ��� � ��� ������ �� ���������� ���������
} pqueue;
 
inline void pqueue_init(pqueue* pq)  { pq->lst = NULL; } // ����������� ������� ������������� ��� ������, ���� ���� pq ���������� ������ 
inline  int pqueue_top(pqueue* pq)   { return pq->lst->val; } //������������ �������  ���������� 
inline  int pqueue_empty(pqueue* pq) { return (pq->lst == NULL); } // ������������ ������� ��� ������ ���������� ���� ���� pq ���������� ������ 
 
int  pqueue_push(pqueue* pq, int val); // ����� �������
void pqueue_pop(pqueue* pq); // ����� �������
void pqueue_clear(pqueue* pq); // ����� �������
 
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
 
//�������
int pqueue_push(pqueue* pq, int val){
    node* p, *i, **q = &pq->lst;
    for(i = pq->lst; (i != NULL) && (i->val > val); ){ //���� i �� null � ������� ���� val ������ val ��������� ����������� 
        q = &i->next; // q ������������� �������� ��������� i � �������� next
        i = i->next; // i ������������� �������� ��������� i � �������� next
    }
    // ������� ��������� �� ���������� ��������� ������ � ������� ������� ������ ��� ���
    p = (node*)malloc(sizeof(node));
    if(p != NULL){ //���� ������ p �� ������, ��
        p->val  = val; // p � ������� val ���������� ������ val
        p->next = i; // p ��������� ���������� i
 
        if(pq->lst == NULL) //���� ���� ���� pq �� ������, ��
            pq->lst = p; // ���� ���� pq ���������� p
        else 
            *q = p; // ��������� q ���������� p
    }
    return (p != NULL);
}
 
//���������� ����
void pqueue_pop(pqueue* pq){
    node* t;
    if(pq->lst != NULL){ // ���� ���� ���� pq �� ������, ��
        t = pq->lst; // t ���������� ���� ���� pq
        pq->lst = pq->lst->next; //���� ���� pq ���������� ���� ���� pq
        free(t);
    }
}
 
//�������� �����
void pqueue_clear(pqueue* pq){
    node* t;
    while(pq->lst != NULL){ // ���� ���� ���� pq �� ������
        t = pq->lst; // t ���������� ���� ��������� pq
        pq->lst = pq->lst->next; // ���� ���� pq ���������� ���� ��������� pq
        free(t);
    }
}
