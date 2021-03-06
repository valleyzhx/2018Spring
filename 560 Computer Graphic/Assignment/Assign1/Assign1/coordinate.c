#include <OpenGL/gl.h>
#include <GLUT/GLUT.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
    GLint x;
    GLint y;
}Point;

Point _startPoint;
Point _endPoint;

Point _tempStart;
Point _tempEnd;

int _isStart = 0;

#pragma mark- mid-point draw line
void swap(int *a,int *b){
    int t = *b;
    *b = *a;
    *a = t;
}
void setPixel(int x, int y, float distance){
    float alpha = (16-round(fabs(distance)))/16.0;
    glColor4f(0.0, 1.0, 0.0,alpha);
    glVertex2i(x,y);
    
}
void midpointBresenham(Point p1,Point p2)    //中点Bresenham算法画线
{
    int x1 = p1.x;
    int y1 = p1.y;
    int x2 = p2.x;
    int y2 = p2.y;
    
    int dx,dy,d,x,y;
    
    int flip = 0;
    //if slope is greater than one
    if( abs(y2-y1) > abs(x2-x1) ) {
        swap(&x1,&y1);
        swap(&x2,&y2);
        flip = 1;
    }
    //if from left to right
    if(x2-x1<0) {
        swap(&x1,&x2);
        swap(&y1,&y2);
    }
    dx = x2-x1;
    dy = y2-y1;
    int ystep = 1;
    if(dy < 0) {
        dy = -dy;
        ystep = -1;
    }
    
    d = 2*dy-dx;
    int incE = 2*dy;
    int incNE = 2*(dy-dx);
    // antialiasing
    int two_vdx = 0;
    double L = 2*sqrt(dx*dx+dy*dy);
    
    x = x1;
    y = y1;
    
    while(x<=x2){
        glBegin(GL_POINTS);
        //
        int pixX = x;
        int pixY = y;
        if (flip) {
            pixX = y;
            pixY = x;
        }
        setPixel(pixX, pixY, two_vdx/L);
        
        glEnd();
        x++;
        if(d<=0){// E
            d+=incE;
            two_vdx = d+dx;
            setPixel(pixX, pixY+1, (2*dx-two_vdx)/L);
            setPixel(pixX, pixY-1, (2*dx+two_vdx)/L);
        }else{ // NE
            d+=incNE;
            y+=ystep;
            two_vdx = d-dx;
            setPixel(pixX, pixY+2, (2*dx-two_vdx)/L);
            setPixel(pixX, pixY, (2*dx+two_vdx)/L);
        }
    }
}

#pragma mark- mouse

void mouseClick(int button, int state, int x, int y){
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (_isStart == 0) {
            _startPoint.x = x;
            _startPoint.y = y;
            _tempStart.x = x;
            _tempStart.y = y;
            _tempEnd.x = x;
            _tempEnd.y = y;
            _isStart = 1;
        }else{
            _endPoint.x = x;
            _endPoint.y = y;
            _tempStart.x = x;
            _tempStart.y = y;
            glLogicOp(GL_COPY);
            midpointBresenham(_startPoint, _endPoint);
            _startPoint.x = _endPoint.x;
            _startPoint.y = _endPoint.y;
        }
    }else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
        if (_isStart) {
            _endPoint.x = x;
            _endPoint.y = y;
            glLogicOp(GL_COPY);
            midpointBresenham(_startPoint,_endPoint);
            _isStart = 0;
        }
    }
}

void mouseMotion(int x, int y){
    if (_isStart) {
        glLogicOp(GL_XOR);
        midpointBresenham(_tempStart,_tempEnd);
        //glFlush();
        
        _tempEnd.x = x;
        _tempEnd.y = y;
        midpointBresenham(_tempStart,_tempEnd);
        glFlush();
    }
}


void display(void)
{
    glClear(GL_CURRENT_BIT);
    
    Point p1 = {200,200};
    Point p2 = {200,80};
    midpointBresenham(p1, p2);
    p2.x = 320;
    p2.y = 200;
    midpointBresenham(p1, p2);
    p2.x = 100;
    p2.y = 235;
    midpointBresenham(p1, p2);
    // S
    p1.x = 180;
    p1.y = 130;
    p2.x = 150;
    p2.y = 140;
    midpointBresenham(p1, p2);
    p1.x = 150;
    p1.y = 165;
    midpointBresenham(p2, p1);
    p2.x = 180;
    p2.y = 155;
    midpointBresenham(p1, p2);
    p1.x = 180;
    p1.y = 180;
    midpointBresenham(p2, p1);
    p2.x = 150;
    p2.y = 190;
    midpointBresenham(p1, p2);
    //C
    p1.x = 135;
    p1.y = 145;
    p2.x = 105;
    p2.y = 155;
    midpointBresenham(p1, p2);
    p1.x = 105;
    p1.y = 205;
    midpointBresenham(p1, p2);
    p2.x = 135;
    p2.y = 195;
    midpointBresenham(p1, p2);

    glFlush();
}


void init(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    
    glEnable(GL_COLOR_LOGIC_OP);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluOrtho2D(0.0, 600.0, 600.0, 0.0);

    
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Draw");
    
    init();
    
    glutDisplayFunc(display);
    glutMouseFunc(mouseClick);
    glutPassiveMotionFunc(mouseMotion);
    glutMainLoop();
    return 0;
}


