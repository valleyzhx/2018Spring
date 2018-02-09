#include <GLUT/GLUT.h>
#include <OpenGL/gl.h>
#include <math.h>
#include <stdlib.h>

typedef struct{
    GLint x;
    GLint y;
}Point;

typedef enum {
    CurveBottom = 1,
    CurveLeft = 1 << 1,
    CurveRight = 1 << 2,
    CurveTop = 1 << 3,
}Curve;

Point _centerPoint;
Point _tempPoint;
int _tempRadius;

int _tempA;
int _tempB;

int _isStart = 0;
int _type = 1;
Curve _curve;
float _scale = 0.5;


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

#pragma mark- eclipse

void setEclipsePixel(int x, int y){
    if (_type == 2) {
        glVertex2i ( x,  y);
        glVertex2i ( x, -y);
        glVertex2i (-x,  y);
        glVertex2i (-x, -y);
        return;
    }
    
    if (_curve & CurveTop) {
        glVertex2i (-x, -y);
        glVertex2i ( x, -y);
    }
    if (_curve & CurveBottom) {
        glVertex2i ( x,  y);
        glVertex2i (-x,  y);
    }
    if (_curve & CurveLeft){
        glVertex2i (-x,  y);
        glVertex2i (-x, -y);
    }
    if (_curve & CurveRight) {
        glVertex2i ( x,  y);
        glVertex2i ( x, -y);
    }
}

void bresenhamEclipse (int a, int b, int xLoc, int yLoc)
{
    //long radius a , short radius b
    glPushMatrix (); // glTranslatef using
    glColor3f(0.0, 1.0, 0.0);

    int x, y;
    float d1, d2, aa, bb;
    aa = a * a;
    bb = b * b;
    d1 = bb + aa * (-b + 0.25);
    glTranslatef ((GLfloat) xLoc, (GLfloat) yLoc, 0.0f);
    x = 0;
    y = b;
    glBegin (GL_POINTS);
    while (bb * (x + 1) < aa * (y - 0.5))
    {
        if (d1 <= -0.000001)
        {
            d1 += bb * (x * 2 + 3);
        }
        else
        {
            d1 += bb * (x * 2 + 3) + aa * (2 - y * 2);
            -- y;
        }
        ++ x;
        setEclipsePixel(x,y);
    }
    d2 = bb * (0.25 * x) + aa * (1 - y * 2);
    while (y > 0)
    {
        if (d2 <= -0.000001)
        {
            ++ x;
            d2 += bb * ((x + 1) * 2) + aa * (3 - (y * 2));
        }
        else
        {
            d2 += aa * (3 - (y * 2));
        }
        -- y;
        setEclipsePixel(x,y);
    }
    glEnd ();
    glPopMatrix ();
}


void setTempAAndTempB(int x, int y){
    _tempA = abs(x-_centerPoint.x);
    _tempB = abs(y-_centerPoint.y);
    
    if (_tempA > _tempB) {
        _tempB = _scale*_tempA;
    }else{
        _tempA = _tempB/_scale;
    }
}

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



void mouseClick(int button, int state, int x, int y){
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            _centerPoint.x = x;
            _centerPoint.y = y;
        }else if (state == GLUT_UP){
            glLogicOp(GL_COPY);
            if(_type == 1){
                Point end = {x,y};
                int radius = getRadius(_centerPoint, end);
                bresenhamCircle(_centerPoint.x, _centerPoint.y, radius);
                _tempRadius = 0;
            }else if (_type == 2 || _type == 3){
                setTempAAndTempB(x,y);
                bresenhamEclipse(_tempA, _tempB, _centerPoint.x, _centerPoint.y);
                _tempA = 0;
                _tempB = 0;
            }
            glFlush();
        }
    }
}

void mouseDrag(int x, int y){
    glLogicOp(GL_XOR);
    if (_type == 1) {
        bresenhamCircle(_centerPoint.x, _centerPoint.y, _tempRadius);
        _tempPoint.x = x;
        _tempPoint.y = y;
        _tempRadius = getRadius(_centerPoint, _tempPoint);
        bresenhamCircle(_centerPoint.x, _centerPoint.y, _tempRadius);
    }else if (_type == 2 || _type == 3){
        bresenhamEclipse(_tempA, _tempB, _centerPoint.x, _centerPoint.y);
        setTempAAndTempB(x,y);
        bresenhamEclipse(_tempA, _tempB, _centerPoint.x, _centerPoint.y);
    }

    glFlush();
}

void drawSmile(void){
    bresenhamCircle(120, 120, 100);
    bresenhamCircle(90, 80, 10);
    bresenhamCircle(150, 80, 10);
    _curve = CurveBottom;
    bresenhamEclipse(50, 20, 120, 160);
}
void drawUP(void){
    //U
    Point p1 = {300,50};
    Point p2 = {300,105};
    midpointBresenham(p1,p2);
    Point p3 = {340,50};
    Point p4 = {340,105};
    midpointBresenham(p3,p4);
    bresenhamEclipse(20, 15, 320, 105);
    //P
    Point p5 = {370,50};
    Point p6 = {370,120};
    midpointBresenham(p5,p6);
    Point p7 = {370,50};
    Point p8 = {400,50};
    midpointBresenham(p7,p8);
    Point p9 = {370,80};
    Point p10 = {400,80};
    midpointBresenham(p9,p10);
    _curve = CurveRight;
    bresenhamEclipse(10, 15, 400, 65);

}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    //bresenhamCircle(250, 250, 150);
    drawSmile();
    drawUP();
    glFlush();
}


#pragma menu
void subMenu(int value){
    switch(value) {
        case 1:
        _curve = CurveLeft;
        break;
        case 2:
        _curve = CurveRight;
        break;
        case 3:
        _curve = CurveTop;
        break;
        case 4:
        _curve = CurveBottom;
        break;
    }
    _type = 3;
}

void scaleMenu(int value){
    switch (value) {
        case 1://2:1
        _scale = 0.5;
        break;
        case 2://3:1
        _scale = 0.333;
        break;
        case 3://1:3
        _scale = 3.0;
        break;
        case 4://2:1
        _scale = 2.0;
        break;
        
        default:
        break;
    }
}


void menu(int value)
{
    switch(value) {
        case 1:
        _type = 1;
        break;
        case 2:
        _type = 2;
        _curve = CurveLeft | CurveRight | CurveTop | CurveBottom;
        break;
        case 3:
        _type = 3;
        break;
    }
    
}


void make_menu(void)
{
    /*SubMenu*/
    int sub = glutCreateMenu(subMenu);
    glutAddMenuEntry("CurveLeft", 1);
    glutAddMenuEntry("CurveRight", 2);
    glutAddMenuEntry("CurveTop", 3);
    glutAddMenuEntry("CurveBottom", 4);
    
    
    int scale = glutCreateMenu(scaleMenu);
    glutAddMenuEntry("2:1", 1);
    glutAddMenuEntry("3:1", 2);
    glutAddMenuEntry("1:3", 3);
    glutAddMenuEntry("1:2", 4);
    
    /*MainMenu*/
    glutCreateMenu(menu);
    glutAddMenuEntry("circle", 1);
    glutAddMenuEntry("eclipse", 2);
    glutAddSubMenu("curve", sub);
    glutAddSubMenu("A:B of axis", scale);

    
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
