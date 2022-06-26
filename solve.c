#include<stdio.h>
#include "set.h"
#include "graph.h"
#include "maze_generator.h"

enum directions
{
	r=2,d,l,u
};

/*int maze[30] =
{
	r, 0, 0, 0, 0, 1,
	0, 1, 0, 1, 0, 1,
	0, 1, 0, 1, 0, 1,
	1, 1, 0, 1, 0, 1,
	0, 0, 1, 0, 0, 0
};
*/
/*int maze[9] =
{
    r,1,0,
    0,0,0,
    1,1,0
};
*/
//const int row = 6;
//const int col = 5;

void print_maze(struct maze_t *maze)
{
	char print_vals[6] = {' ','#','>','V','<','^'};
	for (int i = 0; i < maze->height; i++)
	{
		for (int j = 0; j < maze->width; j++)
		{
			int coordinate = j + i * maze->width;
			int tmp = maze->field[coordinate];
			printf("%c", print_vals[tmp]);
		}
		printf("\n");
	}
	printf("\n\n\n");
}

int validate_move(int new_pos,int prev_pos,struct maze_t *maze)
{
	if (maze->field[new_pos] == 1)
		return 0;
	if (new_pos < 0)
		return 0;
	if (prev_pos - new_pos ==1&& prev_pos % maze->height == 0)
		return 0;
	if (new_pos - prev_pos ==1&& new_pos % maze->height == 0)
		return 0;
	if (new_pos > maze->height * maze->width - 1)
		return 0;
	return 1;
}

void solve_maze(struct maze_t *maze)
{
	int player_pos = 0;
	
    int wall_check[4] = { maze->width,-1,-maze->width,1 };
    int movements[4] = { 1,maze->width,-1,-maze->width };
	while (player_pos != maze->width*maze->height-1)
	{
		print_maze(maze);
       // float tmp_eval = 1.00/eval_pos(maze);
        //printf("%f\n\n", tmp_eval);
		int direction = maze->field[player_pos];
		maze->field[player_pos] = 0;
		
		if (validate_move(player_pos + wall_check[direction - r],player_pos,maze) == 0)
		{
			while (validate_move(player_pos + movements[direction - r],player_pos,maze) == 0)
			{
				if (direction > r)
					direction--;
				else
					direction = u;
			}
			player_pos += movements[direction-r];
			maze->field[player_pos] = direction;
		}
		else
		{
			player_pos += wall_check[direction-r];
			maze->field[player_pos] = direction + 1;
			if (maze->field[player_pos] == u + 1)maze->field[player_pos] = 2;
		}
	}

	print_maze(maze);
}

int get_player_pos(int* board, int height, int width)
{
    for (int i = 0; i < height * width; i++)
    {
        if (board[i] > 1)
        {
            return i;
        }
    }
}

int eval_pos(int* board, int height, int width)
{
    int empty_xy = height*width-1;
    int i = get_player_pos(board,height,width);
    int x = abs(i % width - (width - 1));
    int y = abs(i / width - (height - 1));
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

int board_cmp(int* board1, int* board2, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (board1[i] != board2[i])
            return 0;
    }
    return 1;
}

struct list_node_t* print_path(struct set_t* all_nodes, int value, struct list_node_t* res)
{
    struct astar_node_t* v = astar_find_in_set(all_nodes, value);
    if (v == NULL)return;
    if (v->prev == NULL)
    {
        print_maze(v->board);
        return res;
    }
    res = print_path(all_nodes, v->prev->value, res);

    print_maze(v->board);
    return res;
}

struct list_node_t* find_shortest_path_a_star(
    struct maze_t *maze
) {
    unsigned int values_cnt = 0;
    printf("\nIn a*\n");
    print_maze(maze);
    int wall_check[4] = { maze->width,-1,-maze->width,1 };
    int movements[4] = { 1,maze->width,-1,-maze->width };

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
        if (curr_node == 0)
        {
            //means that the maze isnt solvable
            return 0;
        }
        if (curr_node->board->field[maze->width * maze->height - 1] > 1) //if the player has arrived to end
        {
            end = curr_node->value;
            break; 
        }

        //generating connections:
        connections = init_set();
        for (int i = 0; i < 4; i++)
        {
 
            int player_pos = get_player_pos(curr_node->board->field,maze->height,maze->width);
            //a connection is generated only when the move is valid and hasn't been visited

            if (validate_move(player_pos + movements[i], player_pos,maze) && astar_find_node_in_set_board(visited_boards, curr_node->board) == 0)
            {
                int just_for_test = 0;
                if (values_cnt == 58)
                {
                    just_for_test++;
                    
                }
                //IN GRAPH:
                struct node_t* curr_node_temp = create_node(curr_node->board,values_cnt);
                curr_node_temp->board->field[player_pos] = 0;
                curr_node_temp->board->field[player_pos + movements[i]] = i + r;
                //if values are different but the boards are the same we should just take the same value
                struct astar_node_t* ctrl = astar_find_node_in_set_board(all_nodes, curr_node_temp->board);
                if (ctrl != 0)
                {
                    curr_node_temp->value = ctrl->value;
                    //if the board already existed it is probable that it is visited
                    if (astar_find_node_in_set_board(visited_boards, ctrl->board))
                        continue;
                }
                
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
                float new_heuristic = curr_node->weight - 1.0/eval_pos(other_node->board->field, other_node->board->height, other_node->board->width) + 1;
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
    int height = 10, width = 10, seed =-1;

    if (seed == -1) // we do not have seed to do not need it
        srand((unsigned int)time((time_t*)NULL));
    else
        srand(seed);

    struct maze_t res = generate(height, width);

    res.field[0] = r;

    find_shortest_path_a_star(&res);
    //solve_maze(&res);
	return 0;
}