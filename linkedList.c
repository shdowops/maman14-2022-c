#include "linkedList.h"
void *search_linked_list(LinkedList *linked_list, void *data, IsEqual is_equal)
{

    int i;
    struct Node *current = linked_list->start;
    for (i = 0; i < linked_list->size; i++)
    {
        if (is_equal(current->data, data))
            return current->data;
    }
    return NULL;
}

bool add_value(LinkedList *linked_list, void *data)
{
    Node *newNode;
    if (NULL == linked_list)
    {
        return false;
    }

    newNode = malloc(sizeof(struct Node));
    if (NULL == newNode)
    {
        return false;
    }
    newNode->data = data;
    newNode->next = NULL;

    /**Checking if linked list is empty. If true place the new node in the start of the list*/
    if (linked_list->start == NULL)
    {
        /**Adding the new Node to the list*/
        linked_list->start = newNode;
    }
    else /**If the linked list is not empty then */
    {
        /**Adding the new Node to the list*/
        newNode->next = linked_list->start;
        linked_list->start = newNode;
    }
    linked_list->size += 1;
    return true;
}

void delete_linked_list(LinkedList *linked_list)
{

    /**Creating the pointers we will use in the function to delete the lists elements */
    struct Node *current = linked_list->start;
    struct Node *next;
    /**Loop for freeing the memory taken by the nodes, in other words, deleting the elements in the list*/
    while (current != NULL)
    {
        /**storing the pointer to the next element*/
        next = current->next;
        /**freeing the space for the current element*/
        free(current);
        /**resetting the pointer for the loop condition */
        current = next;
    }
    /**freeing the memory where the linked list struct is stored*/
    free(linked_list);
}

LinkedList *create_linked_list()
{
    LinkedList *result = malloc(sizeof(LinkedList));
    result->size = 0;
    return result;
}

/**Deletes a Node from the linked list*/
int deleteNode(LinkedList *linked_list, void *key)
{
     
    /** Store first node*/
    Node* temp = linked_list->start;
    Node* prev = NULL;
     
    /** If head node itself holds the key to be deleted*/
    if (temp != NULL && temp->data == key)
    {
        linked_list->start = temp->next; /* Changed head*/
        free(temp);            /* free old head*/
        return 1;
    }
    /*Else Search for the node to be deleted, 
     while keeping track of the previous node as we
     need to change 'prev->next' */
      else
        {
         while (temp != NULL && temp->data != key)
            {
                prev = temp;
                temp = temp->next;
            }
 
             /* If key was not present in linked list*/
              if (temp == NULL)
        return 0;
    /** Unlink the node from linked list*/
    prev->next = temp->next;
 
    /** Free memory*/
    free (temp);
    return 1;
    }
}