#include "graph.h"
#include "set.h"

struct node_t* find_node_in_set(struct set_t* set, void* value)
{
    for (struct list_node_t* curr = set->head; curr != NULL; curr = curr->next)
    {
        if (((struct node_t*)curr->value)->value == value) return curr->value;
    }
    return 0;
}

struct node_t* find_node_in_set_board(struct set_t* set, struct board* board)
{
    for (struct list_node_t* curr = set->head; curr != NULL; curr = curr->next)
    {
        int cnt = 0;
        for (int i = 0; i < board->len; i++)
        {
            if (((struct node_t*)curr->value)->board->board[i] == board->board[i])cnt++;
        }
        if (cnt == board->len)
            return curr->value;
        //if (((struct node_t*)curr->value)->board == board) 
         //   return curr->value;
    }
    return 0;
}

struct astar_node_t* astar_find_node_in_set_board(struct set_t* set, struct board* board)
{
    for (struct list_node_t* curr = set->head; curr != NULL; curr = curr->next)
    {

      /*  char print_vals[6] = {' ','#','>','V','<','^'};
        for (int i = 0; i < board->col_len; i++)
        {
            for (int j = 0; j < board->row_len; j++)
            {
                int coordinate = j + i * board->row_len;
                int tmp = board->board[coordinate];
                //printf("%d ", coordinate);
                printf("%c", print_vals[tmp]);
            }
            printf("\n");
        }
        printf("\n\n\n");

        for (int i = 0; i < board->col_len; i++)
        {
            for (int j = 0; j < board->row_len; j++)
            {
                int coordinate = j + i * board->row_len;
                int tmp = ((struct astar_node_t*)curr->value)->board->board[coordinate];
                //printf("%d ", coordinate);
                printf("%c", print_vals[tmp]);
            }
            printf("\n");
        }
        printf("\n\n\n");
        */

        int cnt = 0;
        for (int i = 0; i < board->len; i++)
        {
            if (((struct astar_node_t*)curr->value)->board->board[i] == board->board[i])cnt++;
        }
        if (cnt == board->len)
            return curr->value;
        //if (((struct node_t*)curr->value)->board == board) 
         //   return curr->value;
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


struct connection_t* connect_nodes(struct graph_t* g, int a, int b, struct board b_a, struct board b_b, struct move m) {
    struct node_t* a_node = find_node_in_set_board(g->nodes, &b_a);
    struct node_t* b_node = find_node_in_set_board(g->nodes, &b_b);
    if (a_node == 0)
    {
        /* a_node = malloc(sizeof(struct node_t));
         a_node->value = a;
         a_node->board = &b_a;
         add_to_set(g->nodes, a_node);*/
        a_node = malloc(sizeof(struct node_t));
        a_node->value = a;
        struct board* tmp = malloc(sizeof(struct board));
        int* tmp_b = malloc(sizeof(int) * b_a.len);
        tmp->board = tmp_b;
        for (int i = 0; i < b_a.len; i++)
            tmp->board[i] = b_a.board[i];
        tmp->len = b_a.len;
        tmp->row_len = b_a.row_len;
        tmp->col_len = b_a.col_len;
        tmp->empty_pos = b_a.empty_pos;
        a_node->board = tmp;
        add_to_set(g->nodes, a_node);
    }

    if (b_node == 0)
    {
        /*b_node = malloc(sizeof(struct node_t));
        b_node->value = b;
        b_node->board = &b_b;
        add_to_set(g->nodes, b_node);*/
        b_node = malloc(sizeof(struct node_t));
        b_node->value = b;
        struct board* tmp = malloc(sizeof(struct board));
        int* tmp_b = malloc(sizeof(int) * b_b.len);
        tmp->board = tmp_b;
        for (int i = 0; i < b_b.len; i++)
            tmp->board[i] = b_b.board[i];
        tmp->len = b_b.len;
        tmp->row_len = b_b.row_len;
        tmp->col_len = b_b.col_len;
        tmp->empty_pos = b_b.empty_pos;
        b_node->board = tmp;
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

void print_graph(struct graph_t* graph) {
    for (struct list_node_t* curr = graph->nodes->head; curr != NULL; curr = curr->next) {
        printf("%d\n", ((struct node_t*)curr->value)->value);
        for (int j = 0; j < ((struct node_t*)curr->value)->board->col_len; j++)
        {
            for (int i = 0; i < ((struct node_t*)curr->value)->board->row_len; i++)
                printf("%d ", ((struct node_t*)curr->value)->board->board[j * ((struct node_t*)curr->value)->board->row_len + i]);
            printf("\n");
        }
    }
    for (struct list_node_t* curr = graph->connections->head; curr != NULL; curr = curr->next) {
        struct connection_t* c = (struct connection_t*)curr->value;
        printf("%d <=> %d\n", c->a, c->b);
    }
}