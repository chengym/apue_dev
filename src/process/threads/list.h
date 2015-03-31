#ifndef _LINUX_LIST_H
#define _LINUX_LIST_H

#define LIST_POISON1 (NULL)
#define LIST_POISON2 (NULL)

typedef struct _LIST_ {
    struct _LIST_ *next;
    struct _LIST_ *prev;
} list_head;

#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) \
	list_head name = LIST_HEAD_INIT(name)

static inline void INIT_LIST_HEAD(list_head *list)
{
	list->next = list;
	list->prev = list;
}

static inline void __list_add(list_head *new,
			      list_head *prev,
			      list_head *next)
{
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
}

static inline void list_add(list_head *new, list_head *head)
{
	__list_add(new, head, head->next);
}

static inline void list_add_tail(list_head *new, list_head *head)
{
	__list_add(new, head->prev, head);
}

static inline void __list_del(list_head * prev, list_head * next)
{
	next->prev = prev;
	prev->next = next;
}

static inline void list_del(list_head *entry)
{
    if (entry->next == entry) {
        return;
    }

	__list_del(entry->prev, entry->next);
	entry->next = LIST_POISON1;
	entry->prev = LIST_POISON2;
}

#define container_of(ptr, type, member) ({                      \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
        (type *)( (char *)__mptr - offsetof(type,member) );})
/*
 * list_entry - get the struct for this entry
 * @ptr:	the &list_head pointer.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_head within the struct.
 */
#define list_entry(ptr, type, member) \
	container_of(ptr, type, member)

/**
 * list_for_each	-	iterate over a list
 * @pos:	the &list_head to use as a loop cursor.
 * @head:	the head for your list.
 */
#define list_for_each(pos, head) \
	for (pos = (head)->next; pos != (head); pos = pos->next)

/**
 * list_for_each_prev	-	iterate over a list backwards
 * @pos:	the &list_head to use as a loop cursor.
 * @head:	the head for your list.
 */
#define list_for_each_prev(pos, head) \
	for (pos = (head)->prev; pos != (head); pos = pos->prev)

#endif
