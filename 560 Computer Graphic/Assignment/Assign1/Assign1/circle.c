#include <GLUT/GLUT.h>
#include <math.h>

typedef struct{
    GLint x;
    GLint y;
}Point;

Point _centerPoint;
Point _tempPoint;
int _tempRadius;
int _isStart = 0;

void myInit(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    
    glEnable(GL_COLOR_LOGIC_OP);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluOrtho2D(0.0, 500.0, 500.0, 0);

}

void plotCirclePixel(int cx, int cy, int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(cx + x, cy + y);
    glVertex2i(cx - x, cy + y);
    glVertex2i(cx + x, cy - y);
    glVertex2i(cx - x, cy - y);
    glVertex2i(cx + y, cy + x);
    glVertex2i(cx - y, cy + x);
    glVertex2i(cx + y, cy - x);
    glVertex2i(cx - y, cy - x);
    glEnd();
}

void bresenhamCircle(int cx, int cy, int r)
{
    int x = 0, y = r;
    int d = 1 - r;
    glColor3f(0.0, 1.0, 0.0);
    while (x <= y) {
        plotCirclePixel(cx, cy, x, y);
        if (d <= 0) {
            d += 2*x + 3;
        } else {
            d += 2*(x - y) + 5;
            y--;
        }
        x++;
    }
}
int getRadius(Point center, Point end){
    return round(sqrtf((center.x-end.x)*(center.x-end.x)+(center.y-end.y)*(center.y-end.y)));
}

void mouseClick(int button, int state, int x, int y){
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            _centerPoint.x = x;
            _centerPoint.y = y;
//            glBegin(GL_POINTS);
//            glVertex2i(x, y);
//            glEnd();
        }else if (state == GLUT_UP){
            Point end = {x,y};
            int radius = getRadius(_centerPoint, end);
            glLogicOp(GL_COPY);
            bresenhamCircle(_centerPoint.x, _centerPoint.y, radius);
            glFlush();
            _tempRadius = 0;
        }
    }
}

void mouseDrag(int x, int y){
    glLogicOp(GL_XOR);
    bresenhamCircle(_centerPoint.x, _centerPoint.y, _tempRadius);
    
    _tempPoint.x = x;
    _tempPoint.y = y;
    _tempRadius = getRadius(_centerPoint, _tempPoint);
    bresenhamCircle(_centerPoint.x, _centerPoint.y, _tempRadius);
    glFlush();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    //bresenhamCircle(250, 250, 150);
    glFlush();
}


#pragma menu

void menu(int value)
{
    
    switch(value) {
        case 1:
        break;
        case 2:
        break;
    }
    
}


void make_menu(void)
{
    /*MainMenu*/
    glutCreateMenu(menu);
    glutAddMenuEntry("circle", 1);
    //glutAddMenuEntry("curve", 2);
    
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}




int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Bresenham Circle");
    myInit();
    make_menu();

    glutDisplayFunc(display);
    glutMouseFunc(mouseClick);
    glutMotionFunc(mouseDrag);
    glutMainLoop();
    
    return 0;
}
//http://www.it610.com/article/1584435.htm
