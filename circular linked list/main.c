//
// Created by lvyzh on 24-3-27.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// #define DEBUG 1
#ifdef DEBUG
#define DEBUG_PRINT(fmt, args...) \
printf(fmt, ##args)
#else
#define DEBUG_PRINT(fmt, args...) \
do { } while (0)
#endif
#define ALIGN8(x) (((x) + 7) & ~7)

struct node
{
    struct node *prev;
    struct node *next;
    unsigned long long size;
    char *data;
};

struct node *head;
unsigned long long count;

void add_node(const char* str)
{
    const unsigned long long size = ALIGN8(sizeof(struct node));
    struct node* temp = (struct node *)malloc(size);
    memset(temp, 0, size);
    temp->prev = temp;
    temp->next = temp;
    const unsigned long long str_size = ALIGN8(strlen(str)+1);
    temp->data = (char *)malloc(str_size);
    temp->size = str_size;
    memset(temp->data, 0, str_size);
    strncpy(temp->data, str, str_size);
    if(head == NULL)
    {
        head = temp;
    }
    else
    {
        temp->prev = head->prev;
        temp->next = head;
        head->prev->next = temp;
        head->prev = temp;
        head = temp;
    }
    ++count;
    DEBUG_PRINT("add node | Now node count: %llu\n", count);
}

struct node *search_node(const char *str)
{
    struct node* now = head;
    unsigned long long temp_count = 0;
    for(; temp_count < count; now=now->next, ++temp_count)
    {
        if(!strncmp(now->data, str, now->size))
        {
            return now;
        }
    }

    return NULL;

}

void remove_node(const char *str)
{
    struct node *temp = search_node(str);
    if(temp == NULL)
    {
        DEBUG_PRINT("remove node | Can't search the string\n");
    }
    else
    {
        if(count == 1)
        {
            head = NULL;
        }
        else
        {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }

        free(temp->data);
        free(temp);
        --count;
        DEBUG_PRINT("remove node | Now node count: %llu\n", count);
    }
}

void list_node()
{
    struct node* now = head;
    unsigned long long temp_count = 0;
    for(; temp_count < count; now=now->next, ++temp_count)
    {
       printf("data: %s\n", now->data);
    }
}

int main()
{

    add_node("test1");
    add_node("test2");
    add_node("test3");
    list_node();
    remove_node("test2");
    list_node();

    return 0;
}
