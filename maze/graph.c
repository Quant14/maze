#include "graph.h"
#include "set.h"

struct astar_node_t* create_astar_node(struct node_t* node)
{
    struct astar_node_t* curr_node_temp = malloc(sizeof(struct astar_node_t));
    if (curr_node_temp == NULL)return 0;
    curr_node_temp->value = node->value;
    struct maze_t* tmp = malloc(sizeof(struct maze_t));
    if (tmp == NULL)return 0;
    int* tmp_b = malloc(sizeof(int) * node->board->width * node->board->height);
    if (tmp_b == NULL)return 0;
    tmp->field = tmp_b;
    for (int i = 0; i < node->board->width * node->board->height; i++)
        tmp->field[i] = node->board->field[i];
    tmp->width = node->board->width;
    tmp->height = node->board->height;
    curr_node_temp->board = tmp;
    curr_node_temp->visited = 0;
    curr_node_temp->heuristic = -1;
    curr_node_temp->weight = -1;
    curr_node_temp->prev_move = NULL;
    curr_node_temp->prev = NULL;
    return curr_node_temp;
}

struct node_t* create_node(struct maze_t* board, int value)
{
    struct node_t* curr_node_temp = malloc(sizeof(struct node_t));
    if (curr_node_temp == NULL)return 0;
    curr_node_temp->value = value;
    struct maze_t* tmp = malloc(sizeof(struct maze_t));
    if (tmp == NULL)return 0;
    int* tmp_b = malloc(sizeof(int) * board->width * board->height);
    if (tmp_b == NULL)return 0;
    tmp->field = tmp_b;
    for (int i = 0; i < board->width * board->height; i++)
        tmp->field[i] = board->field[i];
    tmp->width = board->width;
    tmp->height = board->height;
    curr_node_temp->board = tmp;
    return curr_node_temp;
}

struct node_t* find_node_in_set(struct set_t* set, void* value)
{
    for (struct list_node_t* curr = set->head; curr != NULL; curr = curr->next)
    {
        if (((struct node_t*)curr->value)->value == value) return curr->value;
    }
    return 0;
}

struct node_t* find_node_in_set_board(struct set_t* set, struct maze_t* board)
{
    for (struct list_node_t* curr = set->head; curr != NULL; curr = curr->next)
    {
        int cnt = 0;
        for (int i = 0; i < board->width * board->height; i++)
        {
            if (((struct node_t*)curr->value)->board->field[i] == board->field[i] || (((struct node_t*)curr->value)->board->field[i] > 1 && board->field[i] > 1))cnt++;
        }
        if (cnt == board->width * board->height)
            return curr->value;
        //if (((struct node_t*)curr->value)->board == board) 
         //   return curr->value;
    }
    return 0;
}

struct astar_node_t* astar_find_node_in_set_board(struct set_t* set, struct maze_t* board)
{
    for (struct list_node_t* curr = set->head; curr != NULL; curr = curr->next)
    {
        int cnt = 0;
        for (int i = 0; i < board->width * board->height; i++)
        {
            if (((struct astar_node_t*)curr->value)->board->field[i] == board->field[i] || (((struct astar_node_t*)curr->value)->board->field[i] > 1 && board->field[i] > 1))cnt++;
        }
        if (cnt == board->width * board->height)
            return curr->value;
    }
    return 0;
}

struct connection_t* find_connection_in_set(struct set_t* set, void* value)
{
    for (struct list_node_t* curr = set->head; curr != NULL; curr = curr->next)
    {
        if (((struct connection_t*)curr->value)->a == ((struct connection_t*)value)->a && ((struct connection_t*)curr->value)->b == ((struct connection_t*)value)->b ||
            ((struct connection_t*)curr->value)->a == ((struct connection_t*)value)->b && ((struct connection_t*)curr->value)->b == ((struct connection_t*)value)->a) return curr->value;
    }
    return 0;
}


struct connection_t* connect_nodes(struct graph_t* g, int a, int b, struct maze_t b_a, struct maze_t b_b, struct move m) {
    struct node_t* a_node = find_node_in_set_board(g->nodes, &b_a);
    struct node_t* b_node = find_node_in_set_board(g->nodes, &b_b);
    if (a_node == 0)
    {
        a_node = create_node(&b_a, a);
        add_to_set(g->nodes, a_node);
    }

    if (b_node == 0)
    {
        b_node = create_node(&b_b, b);
        add_to_set(g->nodes, b_node);
    }
    struct connection_t* c = malloc(sizeof(struct connection_t));
    c->a = a_node->value;
    c->b = b_node->value;
    c->move.el_num = m.el_num;
    c->move.direction = m.direction;
    if (find_connection_in_set(g->connections, c) == 0)
        add_to_set(g->connections, c);
    return c;
}
