#include<stdio.h>
#include "set.h"
#include "graph.h"

enum directions
{
	r=2,d,l,u
};

int maze[30] =
{
	r, 0, 0, 0, 0, 1,
	0, 1, 0, 1, 0, 1,
	0, 1, 0, 1, 0, 1,
	1, 1, 0, 1, 0, 1,
	0, 0, 1, 0, 0, 0
};

/*int maze[9] =
{
    r,1,0,
    0,0,0,
    1,1,0
};
*/
const int row = 6;
const int col = 5;

void print_maze(int *maze,int row,int col)
{
	char print_vals[6] = {' ','#','>','V','<','^'};
	for (int i = 0; i < col; i++)
	{
		for (int j = 0; j < row; j++)
		{
			int coordinate = j + i * row;
			int tmp = maze[coordinate];
			printf("%c", print_vals[tmp]);
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
    int movements[4] = { 1,row,-1,-row };
	while (player_pos != row*col-1)
	{
		print_maze(maze,row,col);
        float tmp_eval = 1.00/eval_pos(maze, col, row);
        printf("%f\n\n", tmp_eval);
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

	print_maze(maze,row,col);
}

int get_player_pos(int* board, int col_len, int row_len)
{
    for (int i = 0; i < col_len * row_len; i++)
    {
        if (board[i] > 1)
        {
            return i;
        }
    }
}

int eval_pos(int* board, int col_len, int row_len)
{
    int empty_xy = col_len*row_len-1;
    int i = get_player_pos(board,col_len,row_len);
    int x = abs(i % row_len - (row_len - 1));
    int y = abs(i / row_len - (col_len - 1));
    float distance = (float)(x + y);
    return distance;
}

struct astar_node_t* astar_find_in_set(struct set_t* set, void* value)
{
    for (struct list_node_t* curr = set->head; curr != NULL; curr = curr->next)
    {
        if (((struct astar_node_t*)curr->value)->value == (int)value) return curr->value;
    }
    return 0;
}

unsigned int values_cnt = 0;

int board_cmp(int* board1, int* board2, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (board1[i] != board2[i])
            return 0;
    }
    return 1;
}

int num_of_moves = 0;

struct list_node_t* print_path(struct set_t* all_nodes, int value, struct list_node_t* res)
{
    struct astar_node_t* v = astar_find_in_set(all_nodes, value);
    if (v == NULL)return;
    if (v->prev == NULL)
    {
        print_maze(v->board->board, v->board->row_len, v->board->col_len);
        return res;
    }
    res = print_path(all_nodes, v->prev->value, res);

    print_maze(v->board->board, v->board->row_len, v->board->col_len);
    return res;
}

struct list_node_t* find_shortest_path_a_star(
    struct board *maze
) {
    int wall_check[4] = { row,-1,-row,1 };
    int movements[4] = { 1,row,-1,-row };

    //init prio list
    struct priority_list* priority_list = NULL;
    priority_list = priority_init(priority_list);

    //init graph
    struct graph_t* graph=malloc(sizeof(struct graph_t));
    graph->nodes = init_set();
    graph->connections=init_set();

    struct node_t* curr_node_temp = create_node(maze,values_cnt++);

    add_to_set(graph->nodes,curr_node_temp);

    priority_add(priority_list, -1, graph->nodes->head->value);

    //make the set with all the nodes and their info:
    struct set_t* all_nodes = init_set();
    struct set_t* visited_boards = init_set();

    for (struct list_node_t* curr = graph->nodes->head; curr != NULL; curr = curr->next) {
        struct astar_node_t* curr_node_temp = create_astar_node(curr->value);
        add_to_set(all_nodes, curr_node_temp);
    }

    //initializing variables and making first element in prio list to be 0:
    struct astar_node_t* curr_node = astar_find_in_set(all_nodes, 0);
    struct astar_node_t* node_temp = malloc(sizeof(struct astar_node_t));
    curr_node->weight = 0;
    curr_node->heuristic = 0;
    curr_node->prev = 0;
    priority_list = remove_list(priority_list, curr_node->value);
    priority_list = priority_add(priority_list, curr_node->heuristic, curr_node->value);
    struct set_t* connections = init_set();

    int end = 0;
    //main cycle:
    while (priority_list->count)
    {
        //remove node from the prio list
        priority_list = pop(priority_list, node_temp);
       
        curr_node = astar_find_in_set(all_nodes, node_temp->value);
        if (curr_node->board->board[maze->row_len * maze->col_len - 1] > 1) //if the player has arrived to end
        {
            end = curr_node->value;
            break; 
        }

        //generating connections:
        connections = init_set();
        for (int i = 0; i < 4; i++)
        {
 
            int player_pos = get_player_pos(curr_node->board->board,maze->col_len,maze->row_len);
            //a connection is generated only when the move is valid and hasn't been visited
            if (validate_move(player_pos + movements[i], player_pos)&&astar_find_node_in_set_board(visited_boards, curr_node->board)==0)
            {
                //IN GRAPH:
                struct node_t* curr_node_temp = create_node(curr_node->board,values_cnt);
                curr_node_temp->board->board[player_pos] = 0;
                curr_node_temp->board->board[player_pos + movements[i]] = i + r;

                struct move m = {.el_num=player_pos,.direction=i+r};
                struct connection_t *c=connect_nodes(graph,curr_node->value, values_cnt++ ,*curr_node->board,*curr_node_temp->board,m);

                //IN PRIO LIST:
                priority_add(priority_list, -1, curr_node_temp->value);

                //IN ALL NODES SET:
                struct astar_node_t* astar_node = create_astar_node(curr_node_temp);
                add_to_set(all_nodes, astar_node);

                //IN CONNECTIONS SET:
                add_to_set(connections, c);
            }
        }

        //looking at all connections of the curr element
        for (struct list_node_t* curr = connections->head; curr != NULL; curr = curr->next) 
        {
            struct connection_t* c = curr->value;
            int other = c->a;
            if (c->a == node_temp->value) other = c->b;
            //taking the other element in the graph
            struct astar_node_t* other_node_temp = astar_find_in_set(all_nodes, other);

            //visiting the element if it hasn't been visited
            if (other_node_temp != 0 && !other_node_temp->visited) {
                //taking new heuristic:
                struct astar_node_t* other_node = astar_find_in_set(all_nodes, other);
                float new_heuristic = curr_node->weight - 1.0/eval_pos(other_node->board->board, other_node->board->col_len, other_node->board->row_len) + 1;
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
        add_to_set(visited_boards,curr_node);
    }
    struct list_node_t* res_list = 0;
    res_list = print_path(all_nodes, end, res_list);
    return res_list;
}


int main()
{
	//print_maze();

	//solve_maze();
    struct board maze_struct;
    maze_struct.board = maze;
    maze_struct.row_len = row;
    maze_struct.col_len = col;
    find_shortest_path_a_star(&maze_struct);
	
	return 0;
}