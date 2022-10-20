#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define BUFSIZE  256

struct element {
    char *name;
    struct element *next;
};

struct element *tail;

void init_queue (void);
void enqueue (char *name);
int dequeue (char *name);
void print_queue (void);
void error (char *msg);

int main (int argc, char **argv)
{
	setlocale(LC_ALL, "Rus");
    char buf [BUFSIZE];

    init_queue ();

    while (1) {
        printf ("\n1: Очередь\n2: Удаление из очереди\n3: Вывести очередь\n0: Выход\n\nВыберите: ");
        if (fgets (buf, BUFSIZE, stdin) == NULL)
            break;
        if (buf [0] == '1') {
           // Очередь
           // Ввести элемент
           printf ("Элемент: ");
           if (fgets (buf, BUFSIZE, stdin) == NULL) 
               break;
           int len = strlen (buf);
           if (buf [len - 1] == '\n')
               buf [len - 1] = '\0';
           enqueue (buf);
        } else if (buf [0] == '2') {
           // Удаление элемента
           if (dequeue (buf) != -1)
               printf ("%s Удален из очереди\n", buf);
        } else if (buf [0] == '3')
           print_queue ();
        else if (buf [0] == '0')
           break;
        else
            fprintf (stderr, "Ошибка ввода\n");
    }
    
    exit (0);
}

void init_queue (void)
{
    tail = NULL;
}

void enqueue (char *name)
{
    struct element *ptr;
    char *cp;

    if ((ptr = (struct element *) malloc (sizeof (struct element))) == NULL)
        error ("malloc");
    if ((cp = (char *) malloc (strlen (name) + 1)) == NULL)
        error ("malloc");

    strcpy (cp, name);
    ptr -> name = cp;

    if (tail == NULL) {
        ptr -> next = ptr;
    }
    else
    {
        ptr -> next = tail -> next;
        tail -> next = ptr;
    }
    tail = ptr;
}

int dequeue (char *name) // возвращает -1 при ошибке
{
	setlocale(LC_ALL, "Rus");
    struct element *ptr;
    char *cp;

    if (!tail) {
        fprintf (stderr, "Очередь пустая\n");
        return -1;
    }
    // get the head
    ptr = tail -> next;
    cp = ptr -> name;

    if (ptr == tail)
        tail = NULL;
    else
        tail -> next = ptr -> next;
    free (ptr);
    strcpy (name, cp);
    free (cp);
    return 0;
}

void print_queue (void)
{
	setlocale(LC_ALL, "Rus");
    struct element *ptr, *head;

    if (!tail) {
        fprintf (stderr, "Очередь пустая\n");
        return;
    }

    printf ("Очередь: \n");

    // get the head
    head = ptr = tail -> next;
    int i = 1;

    do {
        printf ("%d. %s\n", i, ptr -> name);
        ptr = ptr -> next;
        i++;
    } while (ptr != head);
}

void error (char *msg)
{
    perror (msg);
    exit (1);
}