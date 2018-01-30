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
void midpointBresenham(Point p1,Point p2)    //中点Bresenham算法画线
{
    glColor3f(0.0, 1.0, 0.0);
    
    int x0 = p1.x;
    int y0 = p1.y;
    int x1 = p2.x;
    int y1 = p2.y;
    
    int dx,dy,d,UpIncre,DownIncre,x,y;
    if(x0>x1){
        x=x1;x1=x0;x0=x;
        y=y1;y1=y0;y0=y;
    }
    x = x0;y = y0;
    dx = x1-x0;
    dy = y1-y0;
    if(dy>0&&dy<=dx){    //0<k<=1
        d = dx-2*dy;
        UpIncre = 2*dx-2*dy;
        DownIncre = -2*dy;
        while(x<=x1){
            glBegin(GL_POINTS);
            glVertex2i(x,y);
            glEnd();
            x++;
            if(d<0){
                y++;
                d+=UpIncre;
            }
            else
                d+=DownIncre;
        }
    }
    else if((dy>=(-dx))&&dy<=0) //-1<=k<=0
    {
        d=dx-2*dy;
        UpIncre=-2*dy;
        DownIncre=-2*dx-2*dy;
        while(x<=x1)
        {
            glBegin(GL_POINTS);
            glVertex2i(x,y);
            glEnd();
            x++;
            if(d>0)
            {
                y--;
                d+=DownIncre;
            }
            else d+=UpIncre;
        }
    }
    else if(dy<(-dx)) //k<-1
    {
        d=-dy-2*dx;
        UpIncre=2*dx+2*dy;
        DownIncre=2*dx;
        while(y>=y1)
        {
            glBegin(GL_POINTS);
            glVertex2i(x,y);
            glEnd();
            y--;
            if(d<0)
            {
                x++;
                d-=UpIncre;
            }
            else d-=DownIncre;
        }
    }
    
    else //k>1和k不存在
    {
        d=dy-2*dx;
        UpIncre=2*dy-2*dx;
        DownIncre=-2*dx;
        while(y<=y1)
        {
            glBegin(GL_POINTS);
            glVertex2i(x,y);
            glEnd();
            y++;
            if(d<0)
            {
                x++;
                d+=UpIncre;
            }
            else d+=DownIncre;
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
    
    glFlush();
}


void init(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    
    glEnable(GL_COLOR_LOGIC_OP);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glOrtho(0.0, 600.0, 600.0, 0.0, -1.0, 1.0);
    
    
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


