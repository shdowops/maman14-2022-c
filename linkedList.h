#ifndef LINKED_LIST_H /*!!!!!!!!!!!!!*/
#define LINKED_LIST_H /*!!!!!!!!!!!!!*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef bool *IsEqual(void *data, void *parameter);

typedef struct Node
{
    void *data;
    struct Node *next;
} Node;

typedef struct LinkedList
{
    Node *start;
    int size;
} LinkedList;

/**
 * Creates a new linked list
 */
LinkedList *create_linked_list();

/**
 * deletes a given linked list
 *
 */
void delete_linked_list(LinkedList *linked_list);

/**
 * adds a new value to the linked list
 * params:
 *  @linked_list: The target linked list
 *  @data: The data to insert
 */
bool add_value_linked(LinkedList *linked_list, void *data);

/**Searches if the data already exists in the linked list*/
void *search_linked_list(LinkedList *linked_list, void *data, IsEqual is_equal);
#endif


/**Deletes a Node from the linked list
 * params:
 *  @linked_list: The target linked list
 *  @data: The data to delete
*/
int deleteNode(LinkedList *linked_list, void *key);