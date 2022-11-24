#include "graphics.h"
#include "Button.h"
#include <iostream>
#include <time.h>
#include <vector>

using namespace std;
enum screens{
    startScreen, playScreen, endScreen, rules};
screens screen = startScreen;

GLdouble width, height;
int wd;

// buttons that change the screens
Button play({.85, .85, .85}, {320, 400}, 100, 50, "Play");
Button rule({.85, .85, .85}, {425, 400}, 100, 50, "Rules");
Button menu({.85, .85, .85}, {320, 400}, 100, 50, "Home");
Button restart({.85, .85, .85}, {320, 400}, 100, 50, "Restart");

// buttons for the play screen
Button green({0, 1, 0}, {115, 200}, 100, 250, "");
Button red({1, 0, 0}, {220, 200}, 100, 250, "");
Button blue({0, 0, 1}, {325, 200}, 100, 250, "");
Button yellow({1, 1, 0}, {430, 200}, 100, 250, "");
Button orange({1, .64, 0}, {535, 200}, 100, 250, "");

// buttons for the start screen background
Button green1({0, 1, 0}, {115, 200}, 100, 250, "");
Button red1({1, 0, 0}, {220, 200}, 100, 250, "");
Button blue1({0, 0, 1}, {325, 200}, 100, 250, "");
Button yellow1({1, 1, 0}, {430, 200}, 100, 250, "");
Button orange1({1, .64, 0}, {535, 200}, 100, 250, "");

Button bg1({0,0,0}, {315, 218}, 200, 20, "");
Button bg2({0,0,0}, {315, 245}, 180, 20, "");

vector<int> computerChoices;
vector<int> userChoices;

int round = 1;

int passed = 1;

void init() {
    width = 650;
    height = 500;
    srand(time(NULL));
    green1.pressDown();
    red1.pressDown();
    blue1.pressDown();
    yellow1.pressDown();
    orange1.pressDown();
}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
    // creates the startScreen
    if (screen == startScreen){
        // Tell OpenGL to use the whole window for drawing
        glViewport(0, 0, width, height); // DO NOT CHANGE THIS LINE (unless you're on a Mac running Catalina)

        // Do an orthographic parallel projection with the coordinate
        // system set to first quadrant, limited by screen/window size
        glMatrixMode(GL_PROJECTION); // DO NOT CHANGE THIS LINE
        glLoadIdentity(); // DO NOT CHANGE THIS LINE
        glOrtho(0.0, width, height, 0.0, -1.f, 1.f); // DO NOT CHANGE THIS LINE

        // Clear the color buffer with current clearing color
        glClear(GL_COLOR_BUFFER_BIT); // DO NOT CHANGE THIS LINE
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // DO NOT CHANGE THIS LINE

        // draw the buttons behind the welcome message in the home screen
        green1.draw();
        red1.draw();
        blue1.draw();
        yellow1.draw();
        orange1.draw();

        // draw black quads behind the text
        bg1.draw();
        bg2.draw();

        string welcome = "Welcome to Memory Game";
        glColor3f(1, 1, 1);
        glRasterPos2i(230, 220);
        for (const char &letter : welcome) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
        string phrase = "Press Play to Start ";
        glColor3f(1, 1, 1);
        glRasterPos2i(240, 250);
        for (const char &letter : phrase) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }

        // draw play and rules buttons
        play.draw();
        rule.draw();
        glFlush();

    }
    if (screen == rules){
        // Tell OpenGL to use the whole window for drawing
        glViewport(0, 0, width, height); // DO NOT CHANGE THIS LINE (unless you're on a Mac running Catalina)

        // Do an orthographic parallel projection with the coordinate
        // system set to first quadrant, limited by screen/window size
        glMatrixMode(GL_PROJECTION); // DO NOT CHANGE THIS LINE
        glLoadIdentity(); // DO NOT CHANGE THIS LINE
        glOrtho(0.0, width, height, 0.0, -1.f, 1.f); // DO NOT CHANGE THIS LINE

        // Clear the color buffer with current clearing color
        glClear(GL_COLOR_BUFFER_BIT); // DO NOT CHANGE THIS LINE

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // DO NOT CHANGE THIS LINE

        // draw the rules
        string start = "Press Play to start the game";
        glColor3f(1, 1, 1);
        glRasterPos2i(220, 220);
        for (const char &letter : start) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }

        string phrase = "Click the buttons that flash on the screen in the order they flash";//add parts to click 1 for the rules,
        glColor3f(1, 1, 1);
        glRasterPos2i(70, 250);
        for (const char &letter : phrase) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
        string line = "If you press the buttons in the incorrect order you lose.";
        glColor3f(1, 1, 1);
        glRasterPos2i(110, 280);
        for (const char &letter : line) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }

        // draw the menu button
        menu.draw();

        glFlush();

    }
    if (screen == playScreen) {
        // tell OpenGL to use the whole window for drawing
        glViewport(0, 0, width, height);

        // do an orthographic parallel projection with the coordinate
        // system set to first quadrant, limited by screen/window size
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.0, width, height, 0.0, -1.f, 1.f);

        glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        // draw the buttons
        green.draw();
        red.draw();
        blue.draw();
        yellow.draw();
        orange.draw();

        // draw the round number
        string phrase = "Round " + to_string(computerChoices.size());
        glColor3f(1, 1, 1);
        glRasterPos2i(300, 400);
        for (const char &letter : phrase) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }

        glFlush();  // Render now
    }
    // creates the endScreen
    if (screen == endScreen){
        // Tell OpenGL to use the whole window for drawing
        glViewport(0, 0, width, height); // DO NOT CHANGE THIS LINE (unless you're on a Mac running Catalina)

        // Do an orthographic parallel projection with the coordinate
        // system set to first quadrant, limited by screen/window size
        glMatrixMode(GL_PROJECTION); // DO NOT CHANGE THIS LINE
        glLoadIdentity(); // DO NOT CHANGE THIS LINE
        glOrtho(0.0, width, height, 0.0, -1.f, 1.f); // DO NOT CHANGE THIS LINE

        // Clear the color buffer with current clearing color
        glClear(GL_COLOR_BUFFER_BIT); // DO NOT CHANGE THIS LINE

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // DO NOT CHANGE THIS LINE

        // Draws the phrase and the restart button
        string phrase = "Sorry You Lost the Memory Game on Round " + to_string(round);
        glColor3f(1, 1, 1);
        glRasterPos2i(140, 250);
        for (const char &letter : phrase) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
        restart.draw();
        glFlush();

    }
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y) {
    // escape
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    }
    
    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_DOWN:
            if (screen != startScreen)

            break;
        case GLUT_KEY_LEFT:
            if (screen != startScreen)

            break;
        case GLUT_KEY_RIGHT:
            if (screen != startScreen)

            break;
        case GLUT_KEY_UP:
            if (screen != startScreen)

            break;
    }
    
    glutPostRedisplay();
}

void cursor(int x, int y) {
    // if the mouse is hovering over any of the buttons they change to the hover fill otherwise they are released
    if (play.isOverlapping(x, y)){
        play.hover();
    }
    if (rule.isOverlapping(x, y)){
        rule.hover();
    }
    if (menu.isOverlapping(x, y)){
        menu.hover();
    }
    if (restart.isOverlapping(x, y)){
        restart.hover();
    }
    if (green.isOverlapping(x, y) || red.isOverlapping(x, y) || blue.isOverlapping(x, y) || yellow.isOverlapping(x, y)
                                    || orange.isOverlapping(x, y)){
        if (green.isOverlapping(x, y)){
            green.hover();

            red.release();
            blue.release();
            yellow.release();
            orange.release();
        }
        else if(red.isOverlapping(x, y)){
            red.hover();

            green.release();
            blue.release();
            yellow.release();
            orange.release();
        }
        else if (blue.isOverlapping(x, y)){
            blue.hover();

            green.release();
            red.release();
            yellow.release();
            orange.release();
        }
        else if (yellow.isOverlapping(x, y)){
            yellow.hover();

            green.release();
            red.release();
            blue.release();
            orange.release();
        }
        else if(orange.isOverlapping(x, y)){
            orange.hover();

            green.release();
            red.release();
            blue.release();
            yellow.release();
        }

    }
    if (!play.isOverlapping(x, y)){
        play.release();
    }
    if (!rule.isOverlapping(x, y)){
        rule.release();
    }
    if (!menu.isOverlapping(x, y)){
        menu.release();
    }
    if (!restart.isOverlapping(x, y)){
        restart.release();
    }
    else{

        green.release();
        red.release();
        blue.release();
        yellow.release();
        orange.release();
    }
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (play.isOverlapping(x, y) && screen == startScreen){
            play.pressDown();
            screen = playScreen;
            newRound();
        }
        if (rule.isOverlapping(x, y) && screen == startScreen){
            rule.pressDown();
            screen = rules;
        }
        if (menu.isOverlapping(x, y) && screen == rules){
            menu.pressDown();
            screen = startScreen;
        }
        else if (restart.isOverlapping(x, y) && screen == endScreen){
            restart.pressDown();
            screen = startScreen;
            while(computerChoices.size()!= 0){
                computerChoices.erase(computerChoices.begin());
            }
        }
        else if (green.isOverlapping(x, y)) {
            green.pressDown();
            userChoices.push_back(1);
            glutTimerFunc(500, greenTimer, 0);
            int hasWon = result();
            if (hasWon == 1){
                newRound();
            }
            else if(hasWon == 0){
                screen = endScreen;
            }

        } else if (red.isOverlapping(x, y)) {
            red.pressDown();
            userChoices.push_back(2);
            glutTimerFunc(500, redTimer, 1);
            int hasWon = result();
            if (hasWon == 1){
                newRound();
            }
            else if(hasWon == 0){
                screen = endScreen;
            }

        } else if (blue.isOverlapping(x, y)) {
            blue.pressDown();
            userChoices.push_back(3);
            glutTimerFunc(500, blueTimer, 0);
            int hasWon = result();
            if (hasWon == 1){
                newRound();
            }
            else if(hasWon == 0){
                screen = endScreen;
            }

        } else if (yellow.isOverlapping(x, y)) {
            yellow.pressDown();
            userChoices.push_back(4);
            glutTimerFunc(500, yellowTimer, 0);
            int hasWon = result();
            if (hasWon == 1){
                newRound();
            }
            else if(hasWon == 0){
                screen = endScreen;
            }

        } else if (orange.isOverlapping(x, y)) {
            orange.pressDown();
            userChoices.push_back(5);
            glutTimerFunc(500, orangeTimer, 0);
            int hasWon = result();
            if (hasWon == 1){
                newRound();
            }
            else if(hasWon == 0){
                screen = endScreen;
            }
        }
    }
    else {
        play.release();
        restart.release();
    }
    glutPostRedisplay();
}

int result() {
    passed = 1;
    if (userChoices.size() == computerChoices.size()) {
        for (int i = 0; i < userChoices.size(); ++i) {
            if (userChoices[i] != computerChoices[i]) {
                passed = 0;
            }
        }
        return passed;
    } else if (userChoices.size() != computerChoices.size()){
            for (int i = 0; i < userChoices.size(); ++i) {
                if (userChoices[i] != computerChoices[i]) {
                    passed = 0;
                }
            }
            if (passed == 1)
                passed = 2;
            return passed;
        }
}

int randomChoice(){
    return rand() % 5 + 1;
}

void generateGame(){
    int randChoice = randomChoice();
    computerChoices.push_back(randChoice);
    round = computerChoices.size();
}

void newRound(){
    while(userChoices.size()!= 0){
        userChoices.erase(userChoices.begin());
    }
    generateGame();
    glutTimerFunc(1250, roundTimer, 0);
}

void roundTimer(int i){
    if (computerChoices[i] == 1) {
        green.pressDown();
        glutTimerFunc(350, greenTimer, 0);
    } if (computerChoices[i] == 2) {
        red.pressDown();
        glutTimerFunc(350, redTimer, 0);
    } if (computerChoices[i] == 3) {
        blue.pressDown();
        glutTimerFunc(350, blueTimer, 0);
    } if (computerChoices[i] == 4) {
        yellow.pressDown();
        glutTimerFunc(350, yellowTimer, 0);
    } if (computerChoices[i] == 5) {
        orange.pressDown();
        glutTimerFunc(350, orangeTimer, 0);
    }
    glutPostRedisplay();
    ++i;
    if (i < computerChoices.size()){
        glutTimerFunc(750, roundTimer, i);//set i to the next number in the sequence and recursively call the timer again
    }
    else if (i == computerChoices.size() && computerChoices.size() == userChoices.size()){
        glutTimerFunc(1250, roundTimer, 0); // reset the i value to 0 and have a longer pause between rounds
    }
}

void greenTimer(int dummy){
    green.release();
    glutPostRedisplay();
}

void redTimer(int dummy){
    red.release();
    glutPostRedisplay();
}

void blueTimer(int dummy){
    blue.release();
    glutPostRedisplay();
}

void yellowTimer(int dummy){
    yellow.release();
    glutPostRedisplay();
}

void orangeTimer(int dummy){
    orange.release();
    glutPostRedisplay();
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
    
    init();
    
    glutInit(&argc, argv);          // Initialize GLUT
    
    glutInitDisplayMode(GLUT_RGBA);
    
    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(100, 200); // Position the window's initial top-left corner


    /* create the window and store the handle to it */
    wd = glutCreateWindow("Memory Game!" /* title */ );
    
    // Register callback handler for window re-paint event
    glutDisplayFunc(display);
    
    // Our own OpenGL initialization
    initGL();
    
    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);
    
    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);
    
    // handles mouse movement
    glutPassiveMotionFunc(cursor);
    
    // handles mouse click
    glutMouseFunc(mouse);

    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}
