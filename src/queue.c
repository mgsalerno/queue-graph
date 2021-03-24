#include <stdio.h>
#include "queue.h"

/* ------------------------------------------------------------------------------ */

void queue_append (queue_t **queue, queue_t *elem)
{
  if (!queue)
  {
    fprintf(stderr, "Error: Queue does not exist\n");
    return ;
  }

  if (!elem)
  {
    fprintf(stderr, "Error: Element does not exist\n");
    return ;
  }

  if (elem->next || elem->prev)
  {
    fprintf(stderr, "Error: Element already belongs to another queue\n");
    return ;
  }

  if (*queue) // if the queue is not empty
  {
    queue_t *last = (*queue)->prev;
    elem->next = (*queue);
    (*queue)->prev = elem;
    elem->prev = last;
    last->next = elem;
    return ;
  }
  else
  {
    (*queue) = elem;
    (*queue)->next = (*queue)->prev = elem;
    return ;
  }
}

/* ------------------------------------------------------------------------------ */

queue_t *queue_remove (queue_t **queue, queue_t *elem)
{
  if (!queue)
  {
    fprintf(stderr, "Error: Queue does not exist\n");
    return NULL;
  }

  if (!queue_size(*queue))
  {
    fprintf(stderr, "Error: Empty queue\n");
    return NULL;
  }

  if (!elem)
  {
    fprintf(stderr, "Error: Element does not exist\n");
    return NULL;
  }

  queue_t *aux = (*queue);

  while (aux->next != (*queue) && aux != elem)
    aux = aux->next;

  if (aux != elem)
  {
    fprintf(stderr, "Error: Element does not belong to the queue\n");
    return NULL;
  }

  if (aux == (*queue)) // if it is the beginning of the queue 
    (*queue) = aux->next == aux ? NULL : (*queue)->next; // if it is the only element in the queue

  elem->prev->next = elem->next;
  elem->next->prev = elem->prev;
  elem->next = elem->prev = NULL;
  return elem;
}

/* ------------------------------------------------------------------------------ */

unsigned int queue_size (queue_t *queue)
{
  unsigned int size = 0;

  if (queue)
  {
    queue_t *aux = queue;

    do
      size++;
    while ((aux = aux->next) != queue);
  }

  return size;
}
