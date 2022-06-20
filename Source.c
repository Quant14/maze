#include<stdio.h>
#include "set.h"
#include "graph.h"

enum directions
{
	r=2,d,l,u
};

int maze[25] =
{
	r, 0, 0, 0, 0,
	0, 1, 0, 1, 0,
	0, 1, 0, 1, 0,
	1, 1, 0, 1, 0,
	0, 0, 1, 0, 0
};

int row = 5;
int col = 5;

void print_maze()
{
	char print_vals[6] = {' ','#','>','V','<','^'};
	for (int i = 0; i < col; i++)
	{
		for (int j = 0; j < row; j++)
		{
			int coordinate = j + i * row;
			int tmp = maze[coordinate];
			//printf("%d ", coordinate);
			printf("%c ", print_vals[tmp]);
		}
		printf("\n");
	}
	printf("\n\n\n");
}

int validate_move(int new_pos,int prev_pos)
{
	if (maze[new_pos] == 1)
		return 0;
	if (new_pos < 0)
		return 0;
	if (prev_pos - new_pos ==1&& prev_pos % col == 0)
		return 0;
	if (new_pos - prev_pos ==1&& new_pos % col == 0)
		return 0;
	if (new_pos > col * row - 1)
		return 0;
	return 1;
}

void solve_maze()
{
	int player_pos = 0;
	int wall_check[4] = { row,-1,-row,1 };
	int movements[4] = {1,row,-1,-row};

	while (player_pos != row*col-1)
	{
		print_maze();
		int direction = maze[player_pos];
		maze[player_pos] = 0;
		
		if (validate_move(player_pos + wall_check[direction - r],player_pos) == 0)
		{
			while (validate_move(player_pos + movements[direction - r],player_pos) == 0)
			{
				if (direction > r)
					direction--;
				else
					direction = u;
			}
			player_pos += movements[direction-r];
			maze[player_pos] = direction;
		}
		else
		{
			player_pos += wall_check[direction-r];
			maze[player_pos] = direction + 1;
			if (maze[player_pos] == u + 1)maze[player_pos] = 2;
		}
	}

	print_maze();
}
/*
unsigned int values_cnt = 0;

struct list_node_t* find_shortest_path_a_star(
    //struct graph_t* graph,
    //int start,
    //int end,
    //int empty_x,
    //int empty_y
    int* board,
    int rows,
    int cols
) {

    //make the priority list with just -1(infinity):
    struct priority_list* priority_list = NULL;
    priority_list = priority_init(priority_list);
    struct graph_t* graph;
    graph->nodes = init_set();
    graph->connections=init_set();

    struct node_t* curr_node_temp = malloc(sizeof(struct node_t));
    curr_node_temp->value = values_cnt++;
    struct board* tmp = malloc(sizeof(struct board));
    int* tmp_b = malloc(sizeof(int) * rows*cols);
    tmp->board = tmp_b;
    for (int i = 0; i < rows*cols; i++)
        tmp->board[i] = board[i];
    tmp->len = rows*cols;


    //MAYBE ERROR!!!!!
    tmp->row_len = cols;
    tmp->col_len = rows;
    //MAYBE ERROR!!!!!


    curr_node_temp->board = tmp;
    //curr_node_temp->value = ((struct node_t*)curr->value)->value;
    curr_node_temp->visited = 0;
    curr_node_temp->heuristic = -1;
    curr_node_temp->weight = -1;
    curr_node_temp->prev_move = NULL;
    curr_node_temp->prev = NULL;
    
    add_to_set(graph->nodes,curr_node_temp);

 /*   for (struct list_node_t* curr = graph->nodes->head; curr != NULL; curr = curr->next) {
        priority_add(priority_list, -1, curr->value);
    }

    //make the set with all the nodes and their info:
    struct set_t* all_nodes = init_set();
    for (struct list_node_t* curr = graph->nodes->head; curr != NULL; curr = curr->next) {
        struct astar_node_t* curr_node_temp = malloc(sizeof(struct astar_node_t));
        curr_node_temp->value = ((struct node_t*)curr->value)->value;
        struct board* tmp = malloc(sizeof(struct board));
        int* tmp_b = malloc(sizeof(int) * ((struct node_t*)curr->value)->board->len);
        tmp->board = tmp_b;
        for (int i = 0; i < ((struct node_t*)curr->value)->board->len; i++)
            tmp->board[i] = ((struct node_t*)curr->value)->board->board[i];
        tmp->len = ((struct node_t*)curr->value)->board->len;
        tmp->row_len = ((struct node_t*)curr->value)->board->row_len;
        tmp->col_len = ((struct node_t*)curr->value)->board->col_len;
        curr_node_temp->board = tmp;
        //curr_node_temp->value = ((struct node_t*)curr->value)->value;
        curr_node_temp->visited = 0;
        curr_node_temp->heuristic = -1;
        curr_node_temp->weight = -1;
        curr_node_temp->prev_move = NULL;
        curr_node_temp->prev = NULL;
        add_to_set(all_nodes, curr_node_temp);
    }

    //initializing variables and making first element in prio list to be 0:
    struct astar_node_t* curr_node = astar_find_in_set(all_nodes, start);
    struct astar_node_t* node_temp = malloc(sizeof(struct astar_node_t));
    struct astar_node_t* end_node = astar_find_in_set(all_nodes, end);
    curr_node->weight = 0;
    curr_node->heuristic = 0;
    curr_node->prev = 0;
    priority_list = remove_list(priority_list, curr_node->value);
    priority_list = priority_add(priority_list, curr_node->heuristic, curr_node->value);
    struct set_t* connections = init_set();

    //main cycle:
    while (priority_list->count)
    {
        //remove node from the prio list
        priority_list = pop(priority_list, node_temp);
        if (node_temp->value == end)break;
        curr_node = astar_find_in_set(all_nodes, node_temp->value);

        //taking all connections and putting them in a set
        for (struct list_node_t* curr = graph->connections->head; curr != NULL; curr = curr->next) {
            struct connection_t* c = curr->value;
            if (((c->a == node_temp->value) || (c->b == node_temp->value)))
                add_to_set(connections, c);
        }

        //looking at all connections:
        for (struct list_node_t* curr = connections->head; curr != NULL; curr = curr->next) {
            struct connection_t* c = curr->value;
            struct node_t* other = c->a;
            if (c->a == node_temp->value) other = c->b;

            struct astar_node_t* other_node_temp = astar_find_in_set(all_nodes, other);
            if (other_node_temp != 0 && !other_node_temp->visited) {
                //taking new heuristic:
                struct astar_node_t* other_node = astar_find_in_set(all_nodes, other);
                float new_heuristic = curr_node->weight - eval_pos(other_node->board->board, other_node->board->len, other_node->board->row_len, empty_x, empty_y) + 1;
                //if new heuristic is lower than the old one we replace them:
                if (other_node_temp->heuristic == -1 || new_heuristic < other_node_temp->heuristic) {
                    other_node->prev = curr_node;
                    other_node->prev_move = &c->move;
                    other_node->weight = curr_node->weight + 1;
                    other_node->heuristic = new_heuristic;
                    priority_list = remove_list(priority_list, other_node_temp->value);
                    priority_list = priority_add(priority_list, new_heuristic, other_node_temp->value);
                }
            }
        }
        //marking element as visited:
        curr_node->visited = 1;
        node_temp->visited = 1;
    }
    struct astar_node_t* res = astar_find_in_set(all_nodes, end);
    //printf("end weight: %f\n",end_node->weight);
    // printf("%d\n", res->weight);
    struct list_node_t* res_list = 0;
    res_list = print_path(all_nodes, end, res_list);
    return res_list;
}

*/
int main()
{
	//print_maze();
	solve_maze();
	
	return 0;
}