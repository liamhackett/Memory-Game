#include "Button.h"
#include "graphics.h"
#include <ctime>
using namespace std;

Button::Button(color fill, point center, unsigned int width, unsigned int height, std::string label) : Quad(fill, center, width, height) {
    this->label = label;
    originalFill = {0.6,  0.6, 0.6};
    hoverFill = {0.75,  0.75, 0.75};
    pressFill = fill;
}

void Button::draw() const {
    Quad::draw();
    glColor3f(0, 0, 0);
    glRasterPos2i(center.x - (4 * label.length()), center.y + 7);
    for (const char &letter : label) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
    }
}

/* Returns true if the coordinate is inside the box */
bool Button::isOverlapping(int x, int y) const {
    if (this->getRightX() < x || x < this->getLeftX())
        return false;
    // 2. when one is above the other
    if (this->getTopY() > y || y > this->getBottomY())
        return false;
    return true;
}

/* Change color of the box when the user is hovering over it */
void Button::hover() {
    setColor(hoverFill);
}

/* Change color of the box when the user is clicking on it */
void Button::pressDown() {
    setColor(pressFill);
}

/* Change the color back when the user is not clicking/hovering */
void Button::release() {
    setColor(originalFill);
}
