#include "snake_map.h"
#include <pthread.h>
#include <iostream>
#include <vector>
#include <utility>
#include <stdlib.h>
#include <time.h>
#include "macros.h"

using namespace std;

SnakeMap::SnakeMap(Snake *snake)
{
    this->snake = snake;
    clear_map(this->map_array);
    srand(time(NULL));
    update_snake_food(true);
		this->cnt = 0;
}

void SnakeMap::redraw(void)
{
    clear_map(this->map_array);
//    for (int i = 0; i < MAP_END; i++)
//    {
//        cout << endl;
//    }
		system("clear");
    update_score();
    vector<pair<int, int>> snake_parts = snake->snake_parts;
    for (int i = 0; i < snake_parts.size(); i++)
    {
        pair<int, int> tmp = snake_parts[i];
        map_array[tmp.first][tmp.second] = SNAKE_CHAR;
    }
    update_snake_head(map_array, snake);
    update_snake_food(false);
    map_array[snake_food.first][snake_food.second] = SNAKE_FOOD_CHAR;
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            cout << map_array[i][j] << " ";
        }
        cout << endl;
    }
}

//bomb, wall
void SnakeMap::update_snake_food(bool force_update)
{
    if (snake->food_eaten || force_update)
    {
        while (true)
        {
            int random_i = rand() % MAP_WIDTH;
            int random_j = rand() % MAP_HEIGHT;
            if (map_array[random_i][random_j] == MAP_CHAR)
            {
                snake_food = make_pair(random_i, random_j);
                snake->set_snake_food(snake_food);
                snake->food_eaten = false;
                break;
            }
        }
    }
}

void clear_map(char map_array[MAP_HEIGHT][MAP_WIDTH])
{
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            map_array[i][j] = MAP_CHAR;
        }
    }
}

//mouth
void SnakeMap::update_snake_head(char map_array[MAP_HEIGHT][MAP_WIDTH], Snake *snake)
{
		char snake_head_char = SNAKE_CHAR;
    enum Direction direction = snake->get_direction();
    if(this->cnt == 0) {
			switch (direction)
	    {
		  case West:
			  snake_head_char = SNAKE_HEAD_WEST;
				break;
		  case North:
			   snake_head_char = SNAKE_HEAD_NORTH;
				 break;
		  case East:
			   snake_head_char = SNAKE_HEAD_EAST;
				 break;
		  case South:
			   snake_head_char = SNAKE_HEAD_SOUTH;
				 break;
			}
			this->cnt = 1;
		} else {
			switch (direction)
			{
			case West:
		    snake_head_char = SNAKE_HEAD_WE;
			  break;
		  case North:
			  snake_head_char = SNAKE_HEAD_NS;
			  break;
			case East:
		    snake_head_char = SNAKE_HEAD_WE;
			  break;
		  case South:
			  snake_head_char = SNAKE_HEAD_NS;
			  break;

			}
			this->cnt = 0;
		}
    pair<int, int> snake_head = snake->snake_head;
    map_array[snake_head.first][snake_head.second] = snake_head_char;
}

void SnakeMap::update_score(void)
{
    cout << "Score:" << snake->length << endl;
}
