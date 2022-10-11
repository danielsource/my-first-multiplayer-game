#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#define LL_SHORTEN_NAMES
#include "linked-list.h"

void
clear(List **l, bool free_data) {
    List *node, *aux;
    for (node = *l; node; node = aux) {
        aux = node->next;
        if (free_data)
            free(node->data);
        free(node);
    }
}

void
insert(List **l, void *data) {
    List *node, *aux;
    node = malloc(sizeof (List));
    node->next = NULL;
    node->data = data;
    if (!*l) {
        *l = node;
        return;
    }
    aux = (*l)->next;
    *l = node;
    node->next = aux;

}

size_t
length(List *l) {
    List *node;
    size_t len;
    for (node = l; node; node = node->next)
        len++;
    return len;
}

void
remove(List **l, void *data, bool free_data) {
    List *node, *aux;
    for (node = *l; node; aux = node, node = node->next) {
        if (node->data == data) {
            if (node == *l) {
                *l = (*l)->next;
            } else {
                aux->next = node->next;
            }
            if (free_data)
                free(node->data);
            free(node);
            break;
        }
    }
}

/* vim: set et sw=4 ts=4 tw=72: */
