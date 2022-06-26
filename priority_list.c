#include <stdio.h>
#include <malloc.h>

#include"priority_list.h"


struct priority_list* priority_init(struct priority_list* list)
{
	list = malloc(sizeof(struct priority_list));
	list->list = 0;
	list->count = 0;
	return list;
}

struct priority_list* priority_add(struct priority_list* list, int item, int weight, int x, int y)
{
	struct priority_list_node* new_item = malloc(sizeof(struct priority_list_node));
	new_item->data.heuristic = item;
	new_item->data.weight = weight;
	new_item->data.value = malloc(sizeof(struct node_t));
	new_item->data.value->x = x;
	new_item->data.value->y = y;
	//new_item->data.value = num;
	new_item->data.visited = 0;
	if (list->list == NULL)
	{
		new_item->next = NULL;
		list->count = 1;
		list->list = new_item;
		return list;
	}
	if (list->list->data.heuristic > item || list->list->data.heuristic == -1)
	{
		new_item->next = list->list;
		list->list = new_item;
		list->count++;
		return list;
	}
	struct priority_list_node* curr = list->list, * prev = 0;
	for (; curr; curr = curr->next)
	{
		if (curr->data.heuristic > item || curr->data.heuristic == -1)
			break;
		prev = curr;
	}
	prev->next = new_item;
	new_item->next = curr;
	list->count++;
	return list;
}

struct priority_list* remove_list(struct priority_list* list, int x, int y)
{
	struct priority_list_node* curr = list->list, * prev = 0;
	if (curr->data.value->x == x && curr->data.value->y == y)
	{
		prev = curr->next;
		free(curr);
		list->list = prev;
		list->count--;
		return list;
	}
	for (; curr; curr = curr->next)
	{
		if (curr->data.value->x == x && curr->data.value->y == y)
		{
			prev->next = curr->next;
			free(curr);
			list->count--;
			return list;
		}
		prev = curr;
	}
	return list;
}

void print_priority_list(struct priority_list* list)
{
	while (list->list)
	{
		printf("%d ", list->list->data.heuristic);
		list->list = list->list->next;
	}
}

struct priority_list* pop(struct priority_list* list, struct astar_node_t* res)
{
	if (list->list == NULL)
	{
		res = 0;
		return 0;
	}
	struct priority_list_node* next = list->list->next;
	//res=&list->list->data;
	res->prev = list->list->data.prev;
	res->value = list->list->data.value;
	res->weight = list->list->data.weight;
	res->visited = list->list->data.visited;
	res->heuristic = list->list->data.heuristic;
	free(list->list);
	list->list = next;
	list->count--;
	return list;
}