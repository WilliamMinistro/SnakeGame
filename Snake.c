//William Ministro
//CS 355 Final Project



#include <stdio.h>
#include <curses.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <fcntl.h>
#include <termios.h>


#define HEAD 'O'
#define BODY '.'
#define BLANK ' '


int blankSpaceDet(int, int);
int placeTrophy(void);
int checkTimer(void);


int moveCount = 0, bodyC = 3, denominator = 10;                                                 //Keeps track of the amount of times the snake has moved, the snake's body count, 
                                                                                                //and a portion of the snake's speed respectively

float snakeSpeed = (1000000/10);                                                                //Variable that controls the snake speed
int y;
int x;
int trophyNum, storedTrophyVal, tillExpireTime;                                                 //Keeps track of the trophy number, the value of that trophy, and how long until it expires respectively
int trophyExists = 0;                                                                           //Tells the program if there is currently a trophy on the field or not
int randomCoordX, randomCoordY;                                                                 //Random coordinate variable to hold the trophy's location
time_t currentTime, newTime;                                                                    //Keeps track of the time a trophy was placed and the newest time, respectively

int main(void)
{
    srand(time(NULL));
    int coordTrackX[99999];		                                                                //Sets up array that keeps track of coordinates for X at any given spot
    int coordTrackY[99999];		                                                                //Sets up array that keeps track of coordinates for Y at any given spot   
    initscr();
    nodelay(stdscr, TRUE);
    noecho();
    curs_set(0);                                                                                //Turns off the blinking cursor
    keypad(stdscr, TRUE);
    y = LINES/2, x = COLS/2;	                                                                //Starts the snake at middle of the window and holds X and Y coordinates after
    int Perimeter = (LINES*2) + (COLS*2);
    int cont = 1, getOut = 1, count = 0;                                                        // cont holds the value for the while loop to continue, getOut holds the value of the while loop continuing for each of the arrow key presses
    int tempdir;
    int dir;                                                                                    //Holds the character for the arrow key presses (Up, down, left, right)
    char Direction;
    
    
    

    while(cont)
    {
        border('*','*','*','*','*','*','*','*');                                                //Creates the border on the sides of the terminal window
        mvaddch(y, x, HEAD);                                                                    //Adds the initial head character that starts at X and Y
        move(y,x);  
        refresh();

        if(trophyExists == 0)
        {
            placeTrophy();
        }
        int randomnumber;                                                                       //This series of code decides, using a random number, which direction the snake will go first
        randomnumber = rand() % 4;
        if(randomnumber == 0)
        {
            tempdir = KEY_RIGHT;
        }
        if(randomnumber == 1)
        {
            tempdir = KEY_LEFT;
        }
        if(randomnumber == 2)
        {
            tempdir = KEY_UP;
        }
        if(randomnumber == 3)
        {
            tempdir = KEY_DOWN;
        }
        if(count == 0)                                                                          //Starts the first moving going right, which is a requirement for the first deliverable
        {
        dir = tempdir;    
        }
        checkTimer();

        switch(dir)
        {
            case KEY_UP:                                                                        //Switch statement is used to tell what happens for each key press **Each key press is pretty much the same in terms of code**
                getOut=1;                                                                       //Sets getOut to 1, which continues the loop
                while(getOut)
                {
                if ((y > 0 && blankSpaceDet(y - 1, x)))                                         //Uses blankSpaceDet to see if the snake is able to move down
                    {

                        mvaddch(y-1, x, HEAD);                                                  //Keeps the head moving in this direction
                        int c = getch();                                                        //Gets another key press if the player wants to move directions

                        if(c == KEY_DOWN)                                                       //In this case if a person presses down, getOut escapes the while loop and the direction is set to down
                        {
                            getOut = 0;
                            dir = KEY_DOWN;
                        }

                        if(c == KEY_LEFT)
                        {
                            getOut = 0;
                            dir = KEY_LEFT;
                        }

                        if(c == KEY_RIGHT)
                        {
                            getOut = 0;
                            dir = KEY_RIGHT;
                        }

                        moveCount++;                                                            //Increments moveCount, which keeps track of how many moves are made
                        mvaddch(y, x, BODY);                                                    //Adds the body behind the head when moving
                        coordTrackX[moveCount] = x;                                             //Tracks the x and y coordinates at each move
                        coordTrackY[moveCount] = y;
                        y = y - 1; 

                        if(moveCount>bodyC)                                                     //Adds a blank space bodyC amount of spaces behind the snake to make it look like it's moving fluidly
                        {
                            mvaddch(coordTrackY[(moveCount-bodyC)],coordTrackX[(moveCount-bodyC)] , BLANK); 
                        }     

                        refresh();
                        usleep(snakeSpeed);        
                    }

                    else                                                                        //If blankSpaceDet sees that the snake is going to run into an object, the game ends
                    {
                        clear();
                        printf("Game Over!!");
                        endwin();
                        exit(0);

                    }

                    if(trophyExists == 0)
                    {
                        placeTrophy();
                    }

                    if(bodyC==(Perimeter/2))
                    {
                        clear();
                        endwin();
                        printf("CONGRATULATIONS! YOU WIN!");
                    }
                    checkTimer();

                }
                break;

            case KEY_DOWN:
                getOut=1;
                while(getOut)
                {
                if ((y > 0 && blankSpaceDet(y + 1, x))) 
                {
                        mvaddch(y+1, x, HEAD);
                        int c = getch();

                        if(c == KEY_RIGHT)
                        {
                            getOut = 0;
                            dir = KEY_RIGHT;
                        }

                        if(c == KEY_LEFT)
                        {
                            getOut = 0;
                            dir = KEY_LEFT;
                        }

                        if(c == KEY_UP)
                        {
                            getOut = 0;
                            dir = KEY_UP;
                        }

                        moveCount++;
                        mvaddch(y, x, BODY);
                        coordTrackX[moveCount] = x;
                        coordTrackY[moveCount] = y;
                        y = y + 1;

                        if(moveCount>bodyC)
                        {
                            mvaddch(coordTrackY[(moveCount-bodyC)],coordTrackX[(moveCount-bodyC)] , BLANK);
                        }      

                        refresh();   
                        usleep(snakeSpeed);
                    } 

                    else
                    {
                        clear();
                        printf("Game Over!!");
                        endwin();
                        exit(0);
                        
                    }

                    if(trophyExists == 0)
                    {
                        placeTrophy();
                    }
                    if(bodyC==(Perimeter/2))
                    {
                        clear();
                        endwin();
                        exit(0);
                        printf("CONGRATULATIONS! YOU WIN!");
                    }
                    checkTimer();
                }
                break;

            case KEY_LEFT:
                getOut=1;

                while(getOut)
                {
                    mvaddch(y, x, HEAD);
                    move(y,x);
                    refresh();

                    if ((y > 0 && blankSpaceDet(y, x-1))) 
                    {
                        mvaddch(y, x-1, HEAD);
                        int c = getch();

                        if(c == KEY_DOWN)
                        {
                            getOut = 0;
                            dir = KEY_DOWN;
                        }

                        if(c == KEY_RIGHT)
                        {
                            getOut = 0;
                            dir = KEY_RIGHT;
                        }

                        if(c == KEY_UP)
                        {
                            getOut = 0;
                            dir = KEY_UP;
                        }

                        moveCount++;
                        mvaddch(y, x, BODY);
                        coordTrackX[moveCount] = x;
                        coordTrackY[moveCount] = y;
                        x = x - 1;
                        refresh();

                        if(moveCount>bodyC)
                        {
                            mvaddch(coordTrackY[(moveCount-bodyC)],coordTrackX[(moveCount-bodyC)] , BLANK);
                        } 

                        refresh();   
                        usleep(snakeSpeed);
                    } 

                    else
                    {
                        clear();
                        printf("Game Over!!");
                        endwin();
                        exit(0);

                    } 

                    if(trophyExists == 0)
                    {
                        placeTrophy();
                    }
                    if(bodyC==(Perimeter/2))
                    {
                        clear();
                        endwin();
                        exit(0);
                        printf("CONGRATULATIONS! YOU WIN!");
                    }
                    checkTimer();
                } 
                break;

            case KEY_RIGHT:
                getOut=1;

                while(getOut)
                {
                    if ((y > 0 && blankSpaceDet(y, x+1))) 
                    {
                        mvaddch(y, x+1, HEAD);
                        int c = getch();

                        if(c == KEY_DOWN)
                        {
                            getOut = 0;
                            dir = KEY_DOWN;
                        }

                        if(c == KEY_LEFT)
                        {
                            getOut = 0;
                            dir = KEY_LEFT;
                        }

                        if(c == KEY_UP)
                        {
                            getOut = 0;
                            dir = KEY_UP;
                        }

                        moveCount++;
                        mvaddch(y, x, BODY);
                        coordTrackX[moveCount] = x;
                        coordTrackY[moveCount] = y;
                        x = x + 1;

                        if(moveCount>bodyC)
                        {
                            mvaddch(coordTrackY[(moveCount-bodyC)],coordTrackX[(moveCount-bodyC)] , BLANK);
                        } 

                        refresh();  
                        usleep(snakeSpeed);     
                    } 
                    else
                    {
                        system("clear");
                        printf("Game Over!!");
                        endwin();
                        exit(0);

                    }
                    if(trophyExists == 0)
                    {
                        placeTrophy();
                    }
                    if(bodyC==(Perimeter/2))
                    {
                        clear();           
                        system("clear");
                        endwin();
                        printf("CONGRATULATIONS! YOU WIN!");
                    }
                    checkTimer();
                }
                break;
        }
        count++;
    }
}


/*
    Uses the function mvinch to test if the character in front of the snake is blank or not. If it is, the snake can continue to move.
    Also, this function is also responsible for the snake growing. If the function sees a trophy in front of the player, the snake eats it.
    The function then sets 'trophyExists' to 0, which allows the program to place another trophy somewhere. Also, the snake grows by the corresponding
    number that the trophy had. The snake's speed also increases depending on the body count.
*/

int blankSpaceDet(int y, int x) 
{
  int testch;
  testch = mvinch(y, x);
  if(testch == trophyNum)
  {
      trophyExists = 0;
      bodyC = bodyC + storedTrophyVal;
      denominator = denominator+(bodyC/10);
      snakeSpeed = (1000000/denominator);
  }
  return ((testch == BLANK) || testch == trophyNum);
}

/*
    placeTrophy takes a random set of coordinates (that aren't the border), and places a trophy. It uses the function 'blankSpaceDet' to see if
    the space the trophy is going to be placed is clear or not (Ex. not being placed on the snake's body). If the random variable isn't blank,
    the function is recursively called until a blank space is found. When it's found, the trophy is placed.
*/

int placeTrophy(void)
{
    randomCoordX = rand() % (COLS-2) + 1;
    randomCoordY = rand() % (LINES-2) + 1;
    if(blankSpaceDet(randomCoordY,randomCoordX))
    {
        trophyNum = (rand() % 9) + 1;
        storedTrophyVal = trophyNum;
        trophyNum = trophyNum + '0';
        int expireTime = rand() % 10;
        mvaddch(randomCoordY,randomCoordX , trophyNum);
        trophyExists=1;
        tillExpireTime = (rand() % 9) + 1;
        currentTime = time(NULL);
    }
    else 
    {
        placeTrophy();
    }
    return 0;
}

/*  
    This function, checkTimer, takes the time of whenever a trophy was placed (currentTime), and uses newTime to take the difference of the most
    recent time to the time when a trophy was placed. If the difference in these times is equal to the random number generated (trophy expire time),
    then the trophy is replaced with a blank space and the variable 'trophyExists', which allows the program to call placeTrophy again.
*/

int checkTimer(void)
{
  newTime = time(NULL);
  if ((newTime - currentTime) == tillExpireTime) {
    mvaddch(randomCoordY, randomCoordX, BLANK);
    trophyExists = 0;
  }
    return 0;
}