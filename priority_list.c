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

struct priority_list* priority_add(struct priority_list* list, float item, int value)
{
	struct priority_list_node* new_item = malloc(sizeof(struct priority_list_node));
	new_item->data.heuristic = item;
	new_item->data.value = value;
	//new_item->data.value = num;
	new_item->data.visited = 0;
	if (list->list == NULL)
	{
		new_item->next = NULL;
		list->count = 1;
		list->list = new_item;
		return list;
	}
	if (item < list->list->data.heuristic || list->list->data.heuristic == -1)
	{
		new_item->next = list->list;
		list->list = new_item;
		list->count++;
		return list;
	}
	struct priority_list_node* curr = list->list, * prev = 0;
	for (; curr; curr = curr->next)
	{
		if (item < curr->data.heuristic || curr->data.heuristic == -1)
			break;
		prev = curr;
	}
	prev->next = new_item;
	new_item->next = curr;
	list->count++;
	return list;
}

struct priority_list* remove_list(struct priority_list* list, int value)
{
	struct priority_list_node* curr = list->list, * prev = 0;
	if (curr->data.value == value)
	{
		prev = curr->next;
		free(curr);
		list->list = prev;
		list->count--;
		return list;
	}
	for (; curr; curr = curr->next)
	{
		if (curr->data.value == value)
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
		printf("%f ", list->list->data.heuristic);
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
	//res->weight = list->list->data.weight;
	res->visited = list->list->data.visited;
	res->heuristic = list->list->data.heuristic;
	/*struct board* tmp = malloc(sizeof(struct board));
	int* tmp_b = malloc(sizeof(int) * list->list->data.board->len);
	tmp->board = tmp_b;
	for (int i = 0; i < list->list->data.board->len; i++)
		tmp->board[i] = list->list->data.board->board[i];
	tmp->len = list->list->data.board->len;
	tmp->row_len = list->list->data.board->row_len;
	res->board = tmp;*/
	//res->board= list->list->data.board;
	free(list->list);
	list->list = next;
	list->count--;
	return list;
}
