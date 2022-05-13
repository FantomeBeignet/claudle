#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <err.h>
#include <errno.h>
#include <assert.h>
#include "linked_list.h"

element_t* element_create(char* key, char* value) 
{
    element_t* new = malloc(sizeof(element_t));

    unsigned long len = strlen(key);
    char* keyCopy = malloc(len + 1);
    strcpy(keyCopy, key);

    len = strlen(value);
    char* valueCopy = malloc(len + 1);
    strcpy(valueCopy, value);

    new->key = keyCopy;
    new->value = valueCopy;

    return new;
}

node_t* node_create(element_t* value) 
{
    node_t* node = calloc(1, sizeof(node_t));
    node->value = value;

    return node;
}

list_t *list_create()
{
    list_t *new_list =  calloc(1, sizeof(list_t));

    if (new_list == NULL)
    {
        err(ENOMEM, "can't allocate a new list");
    }

    return new_list;
}

void list_destroy(list_t *one_list)
{
    assert(one_list != NULL);

    node_t *curr_node = one_list->head;
    while(curr_node)
    {
        node_t* next_node_pt = curr_node->next;

        free(curr_node->value);
        free(curr_node);

        curr_node = next_node_pt;
    }
}

bool list_is_empty(list_t *one_list)
{
    assert(one_list != NULL);
    return one_list->head == NULL;
}

void list_append(list_t *one_list, char *one_key, int *one_value)
{
    node_t *new_node = node_create(element_create(one_key, one_value));

    if(one_list->head == NULL)
    {
        one_list->head = new_node;
        one_list->last = new_node;
    }

    else
    {
        one_list->last->next = new_node;
        one_list->last = new_node;
    }
}

char* *list_find(list_t *one_list, char *one_key)
{
    node_t *one_node = one_list->head;

    while(one_node->next != NULL)
    {
        if(strcmp(one_node->value->key, one_key) == 1)
        {
            return one_node->value->value;
        }

        one_node = one_node->next;
    }

    // Compare last element
    // Could have used list->last
    if(strcmp(one_node->value->key, one_key) == 1)
    {
        return one_node->value->value;
    }

    return NULL;
}

bool list_contains(list_t *one_list, char *one_key)
{
    node_t *one_node = one_list->head;

    while(one_node->next != NULL)
    {
        if(strcmp(one_node->value->key, one_key) == 1)
        {
            return true;
        }

        one_node = one_node->next;
    }

    // Compare last element
    // Could have used list->last
    if(strcmp(one_node->value->key, one_key) == 1)
    {
        return true;
    }

    return false;
}

char* list_get_key(element_t *one_element)
{
    assert(one_element != NULL);
    return one_element->key;
}

int* list_get_value(element_t *one_element)
{
    assert(one_element != NULL);
    return one_element->value;
}

void list_remove_key(list_t *one_list, char *one_key)
{
    node_t *previous = NULL;
    node_t *current = one_list->head;
    
    while(current->next != NULL)
    {
        if(strcmp(current->value->key, one_key) == 1)
        {
            if(current == one_list->head)
            {
                one_list->head = one_list->head->next;
            }
            else
            {
                previous->next = current->next;
            }
            
            free(current->value);
            free(current);

            break;
        }
        
        previous = current;
        current = current->next;
    }
}