//TO-DO
/*
    1) the game is basically finished i dont really have any other features in mind
    2) make a decent border (figure out string formatting loser)
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <time.h>

int main() {
	srand(time(0));
    char menuInput;
    time_t tick = 1000;
    time_t snek_speed = 100; //each tick is a millisecond
    int runoverToggle = 1; //tells C that we want the snake to die a gruesome death
    int wallToggle = 1; //tells C that we want the snake to have a flat face

	//set up sizeY x sizeX grid
	int sizeY = 10;
	int sizeX = 10;
	char coords[sizeY][sizeX]; //y-axis -> x-axis
	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			coords[y][x] = ' ';
		}
	}

	//functions
	int spawnApple() {
        int applePosY;
        int applePosX;
        while(1) {
            applePosY = rand() % sizeY;
            applePosX = rand() % sizeX;
            if (coords[applePosY][applePosX] == ' ') {
                coords[applePosY][applePosX] = '@';
                break;
            } else {}
        }
        return applePosY, applePosX;
    }

    int isValidInput(char potInput) {
        if (potInput == 'w' || potInput == 'W') {
            return 1;
        } else if (potInput == 'a' || potInput == 'A') {
            return 1;
        } else if (potInput == 's' || potInput == 'S') {
            return 1;
        } else if (potInput == 'd' || potInput == 'D') {
            return 1;
        } else if (potInput == 'r' || potInput == 'R') {
            return 1;
        } else {
            return 0;
        }
    }

	//menu while loop
	while (1) {
        system("cls");
        printf("welcome to snake\n\n[1] play\n[2] settings\n[3] exit\n");
        scanf("%c", &menuInput);

        //menu if statement
        if (menuInput == '1') {
            int dead = 0; //acts as a boolean (1 == true; 0 == false)
            char input = 'd'; //placeholder
            char oldInput = 'd';
            int cursorY = ceil(sizeY/2);
            int cursorX = ceil(sizeX/2);
            int newCursorY = cursorY;
            int newCursorX = cursorX;

            spawnApple(); //spawn the initial apple

            //set up the tail
            int score = 0;
            int snakeLen = 4;
            int tailInc = 0;
            int tailTab[sizeX*sizeY][2];
            for (int i = 0; i < (sizeX*sizeY); i++) { //we have to set each value of the table to -1 to show it is empty
                tailTab[i][0] = -1;
                tailTab[i][1] = -1;
            }

            //game while loop
            while (dead == 0) {
                //clear screen
                system("cls");

                //handle snake position + tail
                if (input == 'w' || input == 'W') {
                    newCursorY = cursorY - 1;
                    if (newCursorY < 0) {
                        if (wallToggle == 1) {
                            dead = 1;
                        } else if (wallToggle == 0) {
                            newCursorY = sizeY - 1;
                        }
                    }
                } else if (input == 'a' || input == 'A') {
                    newCursorX = cursorX - 1;
                    if (newCursorX < 0) {
                        if (wallToggle == 1) {
                            dead = 1;
                        } else if (wallToggle == 0) {
                            newCursorX = sizeX - 1;
                        }
                    }
                } else if (input == 's' || input == 'S') {
                    newCursorY = cursorY + 1;
                    if (newCursorY > sizeY - 1) {
                        if (wallToggle == 1) {
                            dead = 1;
                        } else if (wallToggle == 0) {
                            newCursorY = 0;
                        }
                    }
                } else if (input == 'd' || input == 'D') {
                    newCursorX = cursorX + 1;
                    if (newCursorX > sizeX - 1) {
                        if (wallToggle == 1) {
                            dead = 1;
                        } else if (wallToggle == 0) {
                            newCursorX = 0;
                        }
                    }
                } else if (input == 'r' || input == 'R') {
                    dead = 1;
                } else {}

                if (coords[newCursorY][newCursorX] == '@') { //increase score, snake length, and spawn a new apple
                    score++;
                    snakeLen++;
                    spawnApple();
                } else if (coords[newCursorY][newCursorX] == 's' && runoverToggle == 1 /* && (tailTab[tailInc][0] != newCursorY && tailTab[tailInc][1] != newCursorX)*/) {
                    dead = 1;
                }

                if (tailTab[snakeLen][0] == -1 && tailTab[snakeLen][1] == -1) { //set the tail positions
                    tailTab[tailInc-1][0] = cursorY;
                    tailTab[tailInc-1][1] = cursorX;
                    if ((tailInc + 1) <= snakeLen && dead == 0) {
                        tailInc++;
                    } else if (dead == 0) {
                        for (int i = 1; i < tailInc; i++) {
                            //erase the lost tail piece
                            coords[tailTab[0][0]][tailTab[0][1]] = ' ';
                            //move the index over to the left
                            tailTab[i-1][0] = tailTab[i][0];
                            tailTab[i-1][1] = tailTab[i][1];
                            //set the new closest tail position
                            tailTab[tailInc-1][0] = cursorY;
                            tailTab[tailInc-1][1] = cursorX;
                        }
                    }
                }

                if (dead == 0) {
                    for (int i = 0; i < tailInc; i++) {
                        int tempY = tailTab[i][0];
                        int tempX = tailTab[i][1];
                        coords[tempY][tempX] = 's';
                    }

                    coords[newCursorY][newCursorX] = 'S';
                    cursorY = newCursorY;
                    cursorX = newCursorX;
                }

                //print coords[] contents
                //lmao this border is so jank rn but idk how else to do it rn so suck it loser
                printf("======================\n     Score:    %d  \n======================\n|", score);
                for (int y = 0; y < sizeY; y++) {
                    for (int x = 0; x < sizeX; x++) {
                        printf("%c ", coords[y][x]);
                        if (x == sizeX - 1) {
                            printf("|\n|");
                            break;
                        }
                    }
                }
                printf("____________________|\npress R to restart");

                if (dead == 1) {
                    if (input == 'r' || input == 'R') {
                        printf("\n\nrestarting\npress any key to continue");
                    } else {
                        printf("\n\nyou ded, rip\npress any key to continue");
                    }
                    while (1) {
                        if (_kbhit()) {
                            break;
                        }
                    }

                    //reset everything
                    for (int y = 0; y < sizeY; y++) {
                        for (int x = 0; x < sizeX; x++) {
                            coords[y][x] = ' ';
                        }
                    }
                }

                //listen for keyboard input
                time_t start = clock();
                while (clock() < start + snek_speed) {
                    if (_kbhit()) {
                        oldInput = input;
                        char getch = _getch();
                        if (isValidInput(getch) == 1) {
                            input = getch;
                        }
                    }
                }
            }
        } else if (menuInput == '2') {
            //while loop for settings menu
            while (1) {
                system("cls");
                printf("wacky settings yo\n\n[1] change snake speed\n[2] runover toggle (%d)\n[3] wall toggle (%d)\n[4] back to main menu\n", runoverToggle, wallToggle);
                scanf("%c", &menuInput);
                //handles settings woahhhhh
                if (menuInput == '1') {
                    printf("enter your desired snake speed (movements per second)\n");
                    time_t tempSpeed;
                    scanf("%d", &tempSpeed);
                    snek_speed = tick/tempSpeed;
                } else if (menuInput == '2') {
                    if (runoverToggle == 1) {
                        runoverToggle = 0;
                    } else {
                        runoverToggle = 1;
                    }
                } else if (menuInput == '3') {
                    if (wallToggle == 1) {
                        wallToggle = 0;
                    } else {
                        wallToggle = 1;
                    }
                } else if (menuInput == '4') {
                    break;
                }
            }
        } else if (menuInput == '3') {
            break;
        }
	}

	return 0;
}
