#include <conio.h>
#include <stdio.h>
 
struct list // создание списка
{
    int el;
    list *next;
};
 
struct queue // создание очереди
{
    list *beg, *end;
};
 
void putToQueue(queue *q, int iEl)   //добавить в очередь
{
    list *tmp; // шаблон класса контейнеров последовательностей
    tmp = new list; 
    tmp->next = NULL; // след элемент tmp пустой
    tmp->el = iEl;  
    if(q->end != NULL) // если послед элем q не пустой, то
        q->end->next = tmp; // q с указателем на next присваивается значение tmp
    else
        q->beg = tmp; // q с указателем на beg становится tmp
    q->end = tmp; // q с указателем на end становится tmp
}
 
int takeFromQueue(queue *q, int *iEl) // взять из очереди
{
    if(q->beg == NULL) // если q с указателем на beg пустое, то
		return 0; 
    list *tmp;
    tmp = q->beg;
    *iEl = tmp->el;
    q->beg = tmp->next;
    delete tmp;
    if(q->beg == NULL)
		q->end = NULL;
    return 1;
}
 
queue *CreateQueue()            //создать очередь
{
    queue *q;
    q = new queue;
    q->beg = NULL;
    q->end = NULL;
    return q;
}
 
int isQueueEmpty(queue *q)      //проверка очереди на пустоту
{
    if(q->beg == NULL) 
		return 1;
    return 0;
}
 
int ClearQueue(queue *q)        //очистка очереди
{
    if(q->beg == NULL)
		return 0;
    list *tmp, *t;
    tmp = q->beg;
    while(tmp->next != NULL)
    {
        t = tmp;
        tmp = t->next;
        delete t;
    }
    q->beg = NULL;
    q->end = NULL;
    return 1;
}
 
void PrintQueue(queue *q)       //вывестии очередь на экран
{
    printf("\n");
    queue *tmp = CreateQueue(); 
    int iEl;
    while(!isQueueEmpty(q))
    {
        takeFromQueue(q, &iEl);
        printf("%d ", iEl);
        putToQueue(tmp, iEl);
    }
    while(!isQueueEmpty(tmp))
    {
        takeFromQueue(tmp, &iEl);
        putToQueue(q, iEl);
    }
}
void main()
{
    int i;
    queue *q = CreateQueue();
    printf(".......Put Elems..............");
    for(i=30; i<40; i++)
    {
        putToQueue(q, i);
        PrintQueue(q);
    }
    printf("\n......Take Elems...............");
    while(!isQueueEmpty(q))
    {
        takeFromQueue(q, &i);
        PrintQueue(q);
    }
    printf("\n........Put Elems.............");
    for(i=30; i<35; i++)
    {
        putToQueue(q, i);
        PrintQueue(q);
    }
    printf("\n........Clear queue.............");
    ClearQueue(q);
    PrintQueue(q);
 
    _getch();
}