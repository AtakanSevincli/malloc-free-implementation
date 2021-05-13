#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node
{
    int *ptr;
    struct Node *next;
    int size;
} Node;

typedef struct Block
{
    struct Node *head;
    int sizeOfRegion;
} Block;

Block *block;
int totalMemCap;

int Mem_Init(int sizeOfRegion);
void *TEDU_alloc(int size);
int TEDU_Free(void *ptr);
int Mem_IsValid(void *ptr);
int Mem_GetSize(void *ptr);
int TEDU_GetStats();

int Mem_Init(int sizeOfRegion)
{
    block = (Block *)malloc(sizeof(Block *));
    if (block == NULL)
    {
        return 0;
    }

    block->sizeOfRegion = sizeOfRegion;
    totalMemCap = sizeOfRegion;
    block->head = NULL;
    return 1;
}

void *TEDU_alloc(int size)
{

    if (size <= block->sizeOfRegion)
    {
        Node *node = (Node *)malloc(sizeof(Node *));
        node->ptr = (int *)malloc(sizeof(size));
        node->size = size;
        node->next = NULL;
        if (block->head == NULL)
        {
            block->head = node;
        }
        else
        {
            Node *temp = block->head;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = node;
        }
        block->sizeOfRegion -= size;
        return node->ptr;
    }

    else
    {
        return NULL;
    }
}

int Mem_GetSize(void *ptr)
{
    if (Mem_IsValid(ptr))
    {
        Node *temp = block->head;
        while (temp != NULL)
        {
            if (temp->ptr == ptr)
            {
                return temp->size;
            }
            temp = temp->next;
        }
    }

    return -1;
}
int Mem_IsValid(void *ptr)
{
    Node *temp = block->head;
    while (temp != NULL)
    {
        if (temp->ptr == ptr)
        {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

int TEDU_Free(void *ptr)
{
    if (ptr == NULL)
    {
        return -1;
    }
    else
    {
        if (ptr == block->head->ptr)
        {
            Node *temp = block->head->next;
            block->sizeOfRegion += block->head->size;
            free(block->head);
            block->head = NULL;
            block->head = temp;
        }
        else
        {
            Node *temp = block->head;
            Node *deleted;
            while (temp->next != NULL)
            {
                if (temp->next->ptr == ptr)
                {
                    deleted = temp->next;
                    block->sizeOfRegion += deleted->size;
                    temp->next = deleted->next;
                    free(deleted);
                    deleted = NULL;
                    break;
                }

                temp = temp->next;
            }
        }
    }
    return 0;
}
int TEDU_GetStats()
{
    int num_of_fragment = 0;
    double averageFragment = 0;
    int largestFragment = 0;
    double percentUsedmem = 0;
    if (!block)
    {
        return 0;
    }
    Node *temp = block->head;
    while (temp != NULL)
    {
        if (temp == block->head)
        {
            largestFragment = temp->size;
        }
        if (temp->size > largestFragment)
        {
            largestFragment = temp->size;
        }

        averageFragment += temp->size;
        num_of_fragment++;
        temp = temp->next;
    }

    percentUsedmem = (averageFragment / totalMemCap) * 100;
    averageFragment = averageFragment / num_of_fragment;

    printf("\nthe percent of used memory: %%%.2f \n", percentUsedmem);
    printf("the number of empty fragments: %d\n", num_of_fragment);
    printf("average fragment size: %.2f\n", averageFragment);
    printf("the largest empty fragment size in bytes: %d\n\n", largestFragment);
    return 1;
}
