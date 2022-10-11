#ifndef LL_INCLUDED
#define LL_INCLUDED

#include <stdbool.h>
#include <stddef.h>

typedef struct ll_list ll_List;

struct ll_list {
    void *data;
    ll_List *next;
};

void ll_clear(ll_List *l, bool free_data); /* Removes all items from the
                                              list. */
void ll_insert(ll_List **l, void *data);   /* Inserts data at the head
                                              of the list. */
size_t ll_length(ll_List *l);              /* Gets the number of
                                              elements
                                              in the list. */
void ll_print(ll_List *l, char *data_fmt); /* Prints all the elements in
                                              the list with a specific
                                              format (Ex: "%s\n"). */
void ll_remove(ll_List **l, void *data,
        bool free_data);                   /* Removes the first item
                                              from list where both data
                                              are equal. */

#ifdef LL_SHORTEN_NAMES
#define List   ll_List
#define insert ll_insert
#define length ll_length
#define print  ll_print
#define remove ll_remove
#endif

#endif

/* vim: set et sw=4 ts=4 tw=72: */
