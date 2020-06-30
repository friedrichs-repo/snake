#include <curses.h>
#include <iostream>
#include <unistd.h>
#include "vector2.h"
#include <chrono>
#include <thread>
#include <time.h>
#include <vector> 

using namespace std;

int size_y=40;
int size_x=20;
int fps=10;
int initial_length=10;

void draw(vector<Vector2> positions, int length, Vector2 position_prey, WINDOW * window)
{
    int max_y = 0, max_x = 0;
    getmaxyx(window, max_y, max_x);
    wclear(window);
    box(window, 0, 0);
    for (int i = 0; i < length; i++)
    {
        Vector2 pos = positions[i];

        mvwprintw(window,pos.x, pos.y, i == length - 1 ? "#" : "o");
	mvwprintw(window,position_prey.x, position_prey.y,"X");
    }

    wrefresh(window);
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    initscr(); 
    noecho(); 
    curs_set(FALSE); 
    cbreak(); 
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    WINDOW * win = newwin(size_x, size_y, 0, 0);

    int length = initial_length;

    vector<Vector2> positions(length);
    for (int i = 0; i < length; i++)
    {
        positions[i] = {0, i};
    }

    vector<Vector2> directions(4);
    directions[0].y = 1;
    directions[1].x = 1;
    directions[2].y = -1;
    directions[3].x = -1;

    int idx = 0;

    Vector2 position_prey;
    position_prey.x=size_x/2; 
    position_prey.y=size_y/2;
    
    while (true)
    {
        float sleep = 1.0 / fps * 1000;
        this_thread::sleep_for(std::chrono::milliseconds(int(sleep)));
    	int ch;
    	ch = getch();
    	if(ch == KEY_UP){
    	  if(idx != 1)
    	    idx = 3;
    	} else if(ch == KEY_RIGHT){
    	  if(idx != 2)
    	    idx = 0;
    	} else if(ch == KEY_DOWN){
    	  if(idx != 3)
    	    idx = 1;
    	} else if(ch == KEY_LEFT){
    	  if(idx !=0)
    	    idx = 2;
    	}
    	Vector2 dir = directions[idx];
        Vector2 headPos = vector2sum(positions[length - 1], dir);
        headPos.ensureBox(0, 0, size_x, size_y);

        bool isCollided = false;
        for (int i = 0; i < length - 1; i++)
        {
            if (positions[i].equals(headPos))
            {
                isCollided = true;
                break;
            }
        }
        if (isCollided){
            break;
    	}
    	if (headPos.equals(position_prey)){
	    positions.insert(positions.end(),headPos);
	    length++;
	    bool preyUnderSnake = true;
	    while (preyUnderSnake){
	        position_prey.randomInBox(0, 0, size_x, size_y);
		preyUnderSnake = false;
		for (int i = 0; i < length; i++){
		    if (positions[i].equals(position_prey)){
			preyUnderSnake = true;
		        break;
		    }
		}
	    }
    	}
    	else{
    	    for (int i = 0; i < length - 1; i++)
            positions[i] = positions[i + 1];
    	    positions[length - 1] = headPos;
    	}

        draw(positions, length, position_prey, win);
    }
    wclear(win);
    mvwprintw(win,size_x/2, size_y/2, "GAME OVER");
    mvwprintw(win,size_x/2+1, size_y/2, "%d POINTS\n",length-10);
    wrefresh(win);
    this_thread::sleep_for(std::chrono::milliseconds(10000));
    endwin();
    return 0;
}
