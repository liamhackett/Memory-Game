#ifndef graphics_h
#define graphics_h

#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif



// Program initialization NOT OpenGL/GLUT dependent,
// as we haven't created a GLUT window yet
void init();

// Initialize OpenGL Graphics
void InitGL();

// Callback functions for GLUT

// Draw the window - this is where all the GL actions are
void display();

// Trap and process alphanumeric keyboard events
void kbd(unsigned char key, int x, int y);

// Trap and process special keyboard events
void kbdS(int key, int x, int y);

// Handle "mouse cursor moved" events 
void cursor(int x, int y);

// Calls itself after a specified time
void timer(int dummy);

// Timers to make the buttons stay on after being pressed for a half second

void roundTimer(int i);

void greenTimer(int dummy);

void redTimer(int dummy);

void blueTimer(int dummy);

void yellowTimer(int dummy);

void orangeTimer(int dummy);

// Handle mouse button pressed and released events
void mouse(int button, int state, int x, int y);

// Generates random choices for the computer
int randomChoice();

// calls randomChoice() and pushes the random color to the computerChoices vector
void generateGame();

// clears the users choice vector and calls the generateGame() function
void newRound();

// checks if the user vector matches the user vector and if the round is over
int result();



#endif /* graphics_h */
