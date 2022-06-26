#include<stdio.h>
#include "solve.h"
#include "set.h"
#include "graph.h"
#include "maze_generator.h"

void print_maze(struct maze_t *maze)
{
	char print_vals[7] = {' ','#','>','V','<','^','S'};
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
		//print_maze(maze);
		int direction = maze->field[player_pos];
		maze->field[player_pos] = 6;
		
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

int get_player_pos(struct maze_t*maze)
{
    for (int i = 0; i < maze->height * maze->width; i++)
    {
        if (maze->field[i] > 1)
        {
            return i;
        }
    }
}

int eval_pos(struct maze_t*maze)
{
    int empty_xy = maze->height*maze->width-1;
    int i = get_player_pos(maze);
    int x = abs(i % maze->width - (maze->width - 1));
    int y = abs(i / maze->width - (maze->height - 1));
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

void print_path(struct set_t* all_nodes, int value,struct maze_t*maze)
{
    struct astar_node_t* v = astar_find_in_set(all_nodes, value);
    if (v == NULL)return;
    if (v->prev == NULL)
    {
        maze->field[get_player_pos(v->board)]=6;
        return;
    }
    print_path(all_nodes, v->prev->value,maze);

    maze->field[get_player_pos(v->board)]=6;
    return;
}

int find_shortest_path_a_star(
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
 
            int player_pos = get_player_pos(curr_node->board);
            //a connection is generated only when the move is valid and hasn't been visited

            if (validate_move(player_pos + movements[i], player_pos,maze) && astar_find_node_in_set_board(visited_boards, curr_node->board) == 0)
            {
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
                float new_heuristic = curr_node->weight - 1.0/eval_pos(other_node->board) + 1;
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
    print_path(all_nodes, end,maze);
    return 1;
}


int main()
{
	//print_maze();

	//solve_maze();
    int height = 20, width = 20, seed =5;

    if (seed == -1) // we do not have seed to do not need it
        srand((unsigned int)time((time_t*)NULL));
    else
        srand(seed);

    struct maze_t res = generate(height, width);

    res.field[0] = r;

    if (find_shortest_path_a_star(&res))printf("SOLVABLE\n");
    else printf("NOT SOLVABLE\n");
   // solve_maze(&res);

    print_maze(&res);
    //solve_maze(&res);
	return 0;
}