#include<stdio.h>
#include "set.h"
#include "graph.h"

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
};*/

int maze[9] =
{
    r,1,0,
    0,0,0,
    1,1,0
};

const int row = 3;
const int col = 3;

void print_maze(int *maze,int row,int col)
{
	char print_vals[6] = {' ','#','>','V','<','^'};
	for (int i = 0; i < col; i++)
	{
		for (int j = 0; j < row; j++)
		{
			int coordinate = j + i * row;
			int tmp = maze[coordinate];
			//printf("%d ", coordinate);
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
    //float res= 1.0 / distance;
    //return res;
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
 //   print_maze(v->board->board, v->board->row_len, v->board->col_len);
    if (v == NULL)return;
    if (v->prev == NULL)
    {
        //printf("%d %d\n", value->x,value->y);
       // printf("%d %c\n", v->prev_move->el_num, v->prev_move->direction);
        //res = add_to_end_of_list(res, v->prev_move);
        print_maze(v->board->board, v->board->row_len, v->board->col_len);
        return res;
    }
    res = print_path(all_nodes, v->prev->value, res);
    //struct node_t tmp = {.value=value,.board=v->board};

    //res = add_to_end_of_list(res, v->prev_move);

 /*   if (((struct move*)v->prev_move)->direction == u)
        printf("%d %d UP\n\n", num_of_moves++, ((struct move*)v->prev_move)->el_num, ((struct move*)v->prev_move)->direction);
    else if (((struct move*)v->prev_move)->direction == d)
        printf("%d %d DOWN\n\n", num_of_moves++, ((struct move*)v->prev_move)->el_num, ((struct move*)v->prev_move)->direction);
    else if (((struct move*)v->prev_move)->direction == l)
        printf("%d %d LEFT\n\n", num_of_moves++, ((struct move*)v->prev_move)->el_num, ((struct move*)v->prev_move)->direction);
    else if (((struct move*)v->prev_move)->direction == r)
        printf("%d %d RIGHT\n\n", num_of_moves++, ((struct move*)v->prev_move)->el_num, ((struct move*)v->prev_move)->direction);
        
    for (int j = 0; j < v->board->col_len; j++)
    {
        for (int i = 0; i < v->board->row_len; i++)
            printf("%d ", v->board->board[j * v->board->row_len + i]);
        printf("\n");
    }
    printf("\n");
    */

    print_maze(v->board->board, v->board->row_len, v->board->col_len);
    // printf("%d %c\n", v->prev_move->el_num, v->prev_move->direction);
    return res;
    //printf("%d %d\n", value->x,value->y);
}

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
    int wall_check[4] = { row,-1,-row,1 };
    int movements[4] = { 1,row,-1,-row };

    //make the priority list with just -1(infinity):
    struct priority_list* priority_list = NULL;
    priority_list = priority_init(priority_list);
    struct graph_t* graph=malloc(sizeof(struct graph_t));
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
    tmp->row_len = rows;
    tmp->col_len = cols;
    //MAYBE ERROR!!!!!


    curr_node_temp->board = tmp;
    
    add_to_set(graph->nodes,curr_node_temp);

    priority_add(priority_list, -1, graph->nodes->head->value);

 /*   for (struct list_node_t* curr = graph->nodes->head; curr != NULL; curr = curr->next) {
        priority_add(priority_list, -1, curr->value);
    }*/

    //make the set with all the nodes and their info:
    struct set_t* all_nodes = init_set();
    struct set_t* visited_boards = init_set();

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

       // add_to_set(visited_boards, curr_node_temp);
    }

    //initializing variables and making first element in prio list to be 0:
    struct astar_node_t* curr_node = astar_find_in_set(all_nodes, 0);
    struct astar_node_t* node_temp = malloc(sizeof(struct astar_node_t));
   // struct astar_node_t* end_node = astar_find_in_set(all_nodes, end);
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
        if (curr_node->board->board[rows * cols - 1] > 1) 
        {
          //  print_maze(curr_node->board->board, curr_node->board->row_len, curr_node->board->col_len);
            end = curr_node->value;
            break; 
        }

       // print_maze(curr_node->board->board, curr_node->board->row_len, curr_node->board->col_len);
       /* //taking all connections and putting them in a set
        for (struct list_node_t* curr = graph->connections->head; curr != NULL; curr = curr->next) {
            struct connection_t* c = curr->value;
            if (((c->a == node_temp->value) || (c->b == node_temp->value)))
                add_to_set(connections, c);
        }*/

        //generating connections:
        connections = init_set();
        for (int i = 0; i < 4; i++)
        {
            //IN GRAPH:
            int player_pos = get_player_pos(curr_node->board->board,cols,rows);
            if (validate_move(player_pos + movements[i], player_pos)&&astar_find_node_in_set_board(visited_boards, curr_node->board)==0)
            {
                struct node_t* curr_node_temp = malloc(sizeof(struct node_t));
                curr_node_temp->value = values_cnt;
                struct board* tmp = malloc(sizeof(struct board));
                int* tmp_b = malloc(sizeof(int) * rows * cols);
                tmp->board = tmp_b;
                for (int i = 0; i < rows * cols; i++)
                    tmp->board[i] = curr_node->board->board[i];
                tmp->len = rows * cols;


                //MAYBE ERROR!!!!!
                tmp->row_len = rows;
                tmp->col_len = cols;
                //MAYBE ERROR!!!!

                tmp->board[player_pos] = 0;
                tmp->board[player_pos + movements[i]] = i + r;
                curr_node_temp->board = tmp;

             //   print_maze(curr_node_temp->board->board, curr_node_temp->board->row_len, curr_node_temp->board->col_len);

                struct move m = {.el_num=player_pos,.direction=i+r};
                struct connection_t *c=connect_nodes(graph,curr_node->value, values_cnt++ ,*curr_node->board,*curr_node_temp->board,m);

                //IN PRIO LIST:
                priority_add(priority_list, -1, curr_node_temp->value);

                //IN ALL NODES SET:
                struct astar_node_t* astar_node=malloc(sizeof(struct astar_node_t));
                astar_node->value = curr_node_temp->value;
                astar_node->board = tmp;
                //curr_node_temp->value = ((struct node_t*)curr->value)->value;
                astar_node->visited = 0;
                astar_node->heuristic = -1;
                astar_node->weight = -1;
                astar_node->prev_move = NULL;
                astar_node->prev = NULL;
                add_to_set(all_nodes, astar_node);

                //IN CONNECTIONS SET:
                add_to_set(connections, c);
            }
        }

        //looking at all connections:
        for (struct list_node_t* curr = connections->head; curr != NULL; curr = curr->next) {
            struct connection_t* c = curr->value;
            int other = c->a;
            if (c->a == node_temp->value) other = c->b;

            struct astar_node_t* other_node_temp = astar_find_in_set(all_nodes, other);
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
       // print_maze(curr_node->board->board, curr_node->board->row_len, curr_node->board->col_len);
    }
    
  //  struct astar_node_t* res = astar_find_in_set(all_nodes, end);
    //printf("end weight: %f\n",end_node->weight);
    // printf("%d\n", res->weight);
    struct list_node_t* res_list = 0;
    //add_to_list(res_list,res);
    res_list = print_path(all_nodes, end, res_list);
    return res_list;
   // return;
}


int main()
{
	//print_maze();

	//solve_maze();

    find_shortest_path_a_star(maze,row,col);
	
	return 0;
}