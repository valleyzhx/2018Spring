//
//  main.c
//  Assign2
//
//  Created by Xiang on 2018/2/20.
//  Copyright © 2018年 Xiang. All rights reserved.
//

#include <OpenGL/gl.h>
#include <GLUT/GLUT.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#define MIN(x1,x2) (x1<x2?x1:x2)
#define MAX(x1,x2) (x1>x2?x1:x2)


typedef struct{
    GLint x;
    GLint y;
}Point;

typedef struct{
    Point points[100];
    int pointNumber;
    int lineMode;
} Polygon;

typedef enum {
    LinePositionLeft = 0,
    LinePositionUp ,
    LinePositionRight ,
    LinePositionBottom ,
}LinePosition;




Point _clicpPoints[4] = {{200, 200+200}, // left bottom
                         {200, 200},    // left up
                         {200+200, 200}, // right up
                         {200+200, 200+200}}; // right bottom
Point _viewPoints[4] = {{500, 300+100}, // left bottom
                        {500, 300},    // left up
                        {500+100, 300}, // right up
                        {500+100, 300+100}}; // right bottom

int _menu_type = 0;

Polygon _polygon;
Polygon _vpPolygon;

Point _movingStart;

int _isStart = 0;
int _isTemp = 0;// draw the temp line

bool _isChangeViewSize = 0;
bool _isChangeWindowSize = 0;
bool _isMovingWindow = 0;


Point _points[40000];
int _pointsNumber = 0;



float _matrix[3][3];



void suthHodgClipping(Point points[],Point clicpPoints[],int *number);


#pragma mark- matrix
void matrix_multiplication(float a[3][3], float b[3][3], float c[3][3])
{
    int i, j, k;
    float temp[3] = {0};
    for(i = 0; i < 3; i++){
        for(k = 0; k < 3; k ++)
            temp[k] = 0;
        for(j = 0; j < 3; j++){//当前行的每个元素
            for(k = 0; k < 3; k++){
                temp[k] += a[i][j] * b[j][k];
            }
        }
        for(k = 0; k < 3; k++){
            c[i][k] = temp[k];
        }
    }
}
void makeMatrix(){
    
    Point wLeftBottom = _clicpPoints[0];// left bottom
    Point wLeftUp = _clicpPoints[1];// left up
    Point wRightUp = _clicpPoints[2];// right up
    
    float transMatrix1[3][3] = {1,0,-wLeftUp.x,
        0,1,-wLeftUp.y,
        0,0,1};
    
    float height = wLeftBottom.y-wLeftUp.y;
    float width = wRightUp.x - wLeftUp.x;
    
    Point leftBottom = _viewPoints[0];// left bottom
    Point leftUp = _viewPoints[1];// left up
    Point rightUp = _viewPoints[2];// right up
    
    
    float transMatrix2[3][3] = {1,0,leftUp.x,
        0,1,leftUp.y,
        0,0,1};
    float newHeight = leftBottom.y-leftUp.y;
    float newWidth = rightUp.x - leftUp.x;
    
    float shearingMatrix[3][3]= {newWidth/width,0,0,
        0,newHeight/height,0,
        0, 0,1};
    
    matrix_multiplication(transMatrix2, shearingMatrix, _matrix);
    matrix_multiplication(_matrix, transMatrix1, _matrix);
    
}

#pragma mark- polygon
void addPoint(Polygon *polygon,Point point){
    int index = polygon->pointNumber;
    polygon->points[index] = point;
    polygon->pointNumber = index+1;
}


#pragma mark- draw viewport
void drawViewport(void){
    glLineStipple(5, 0xAAAA);
    glEnable(GL_LINE_STIPPLE);
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 0.0, 1.0);
    for (int i=0; i<4; i++) {
        Point p = _viewPoints[i];
        glVertex3i(p.x, p.y, 0.0);
    }
    glEnd();
}


#pragma mark- draw dashed window

void drawDashedWindow(void){
    
    glLineStipple(5, 0xAAAA);
    glEnable(GL_LINE_STIPPLE);
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 1.0, 0.0);
    for (int i=0; i<4; i++) {
        Point p = _clicpPoints[i];
        glVertex3i(p.x, p.y, 0.0);
    }
    glEnd();
}

bool isInsiseWindow(Point p){
    Point wLeftBottom = _clicpPoints[0];// left bottom
    Point wLeftUp = _clicpPoints[1];// left up
    Point wRightUp = _clicpPoints[2];// right up
    
   return p.x>wLeftUp.x && p.x <wRightUp.x && p.y > wLeftUp.y && p.y < wLeftBottom.y;
}


#pragma mark- draw points
void drawPoints(){
    
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POINTS);
    for (int i=0; i<_pointsNumber; i++) {
        Point p = _points[i];
        glVertex3i(p.x, p.y, 0.0);
    }
    glEnd();
}

#pragma mark- opengl draw line
void drawpolygon(){
    Point tempArr[20];
    int tempNumber = _polygon.pointNumber;
    glDisable(GL_LINE_STIPPLE);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(_polygon.lineMode);
    
    for (int i=0; i<_polygon.pointNumber; i++) {
        Point p = _polygon.points[i];
        glVertex3i(p.x, p.y, 0.0);
        float value[3][3] = {p.x,0,0,
                             p.y,0,0,
                             1,0,0};
        float result[3][3];
        matrix_multiplication(_matrix, value, result);
        
        float x = result[0][0];
        float y = result[1][0];
        tempArr[i] = (Point){x,y};
    }
    glEnd();
    
    if (_isStart == 0) {
        suthHodgClipping(tempArr,_viewPoints,&tempNumber);
    }
    
    glBegin(_polygon.lineMode);
    for (int i=0; i<tempNumber; i++) {
        Point p = tempArr[i];
        glVertex3i(p.x, p.y, 0.0);
    }
    
    
    glEnd();
    if (_menu_type == 2) {
        drawPoints();
    }
}

#pragma mark- mouse

void mouseClick(int button, int state, int x, int y){
   
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        Point rightUp = _viewPoints[2];
        if (abs(rightUp.x - x) <20 && abs(rightUp.y-y) <20) {
            _isChangeViewSize = true;
        }else{
            rightUp = _clicpPoints[2];
            if (abs(rightUp.x - x) <20 && abs(rightUp.y-y) <20) {
                _isChangeWindowSize = true;
            }else if(isInsiseWindow((Point){x,y})){
                _movingStart.x = x;
                _movingStart.y = y;
                _isMovingWindow = true;
            }
        }
        
        
        if (!_isChangeViewSize && !_isChangeWindowSize && !_isMovingWindow) {
            if (_isStart == 0) {
                _polygon.pointNumber = 0;
                _polygon.lineMode = GL_LINE_STRIP;
                _pointsNumber = 0;
                _menu_type = 0;
                Point start = {x,y};
                addPoint(&_polygon, start);
                _isStart = 1;
                glutDetachMenu(GLUT_RIGHT_BUTTON);
            }else{
                addPoint(&_polygon, (Point){x,y});
                _isTemp = 0;
                glutPostRedisplay();
            }
        }
        
    }else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP){
        _isChangeViewSize = false;
        _isChangeWindowSize = false;
        _isMovingWindow = false;
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
        if (_isStart) {
            addPoint(&_polygon, (Point){x,y});
            _polygon.lineMode = GL_LINE_LOOP;
            _isStart = 0;
            glutPostRedisplay();
            _isTemp = 0;
            glutAttachMenu(GLUT_RIGHT_BUTTON);

        }
    }

}

void mousePassiveMotion(int x, int y){
    if (_isStart) {
        if (_isTemp == 0) {
            _isTemp = 1;
        }else{
            _polygon.pointNumber--;
        }
        addPoint(&_polygon, (Point){x,y});
        glutPostRedisplay();
    }
}

void mouseMotion(int x, int y){
    if (_isChangeViewSize) {
    
        _viewPoints[1].y = y;
        _viewPoints[2].x = x;
        _viewPoints[2].y = y;
        _viewPoints[3].x = x;
        
        makeMatrix();
        glutPostRedisplay();
    }else if (_isChangeWindowSize){ // zoom in zoom out

        _clicpPoints[1].y = y;
        _clicpPoints[2].x = x;
        _clicpPoints[2].y = y;
        _clicpPoints[3].x = x;
        
        makeMatrix();
        glutPostRedisplay();
    }else if (_isMovingWindow){
        float width =  _movingStart.x - x;
        float height = _movingStart.y - y;
        
        for (int i=0; i<4; i++) {
            _clicpPoints[i].x -= width;
            _clicpPoints[i].y -= height;
            _movingStart.x = x;
            _movingStart.y = y;

        }
        
        makeMatrix();
        glutPostRedisplay();
    }
    
    
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawDashedWindow();

    drawpolygon();
    
    drawViewport();

    glutSwapBuffers();
}

#pragma mark- clip

Point intersectPoint(Point p1,Point p2, Point clicpPoints[], LinePosition linePosition){
    Point p3 = clicpPoints[0];
    Point p4 = clicpPoints[1]; // left
    if (linePosition == LinePositionUp) {
        p3 = clicpPoints[1];
        p4 = clicpPoints[2];
    }else if (linePosition == LinePositionRight){
        p3 = clicpPoints[2];
        p4 = clicpPoints[3];
    }else if (linePosition == LinePositionBottom){
        p3 = clicpPoints[3];
        p4 = clicpPoints[0];
    }
    
    int num = (p1.x*p2.y - p1.y*p2.x) * (p3.x-p4.x) -(p1.x-p2.x) * (p3.x*p4.y - p3.y*p4.x);
    int den = (p1.x-p2.x) * (p3.y-p4.y) - (p1.y-p2.y) * (p3.x-p4.x);
    
    int px = num/den;
    
    num = (p1.x*p2.y - p1.y*p2.x) * (p3.y-p4.y) - (p1.y-p2.y) * (p3.x*p4.y - p3.y*p4.x);
    den = (p1.x-p2.x) * (p3.y-p4.y) - (p1.y-p2.y) * (p3.x-p4.x);
    
    int py = num/den;
    
    return (Point){px,py};
}

bool isOutside(Point vertex,Point clicpPoints[],LinePosition linePosition){
    
    Point p1 = clicpPoints[0];
    if (linePosition == LinePositionLeft) {
        if (vertex.x <= p1.x) {
            return true;
        }
    }else if (linePosition == LinePositionUp) {
        p1 = clicpPoints[1];
        if (vertex.y <= p1.y) {
            return true;
        }
    }else if (linePosition == LinePositionRight){
        p1 = clicpPoints[2];
        if (vertex.x >= p1.x) {
            return true;
        }
    }else if (linePosition == LinePositionBottom){
        p1 = clicpPoints[3];
        if (vertex.y >= p1.y) {
            return true;
        }
    }
    return false;
}

void clipping(Point points[],Point clicpPoints[],LinePosition linePosition,int *number){
    
    Point newPoints[100];
    int newNumber = 0;
    for (int i=0; i<*number; i++) {
        Point vertex1 = points[i];
        int nextIndx = i+1<*number?i+1:0;
        Point vertex2 = points[nextIndx];
        
        if (!isOutside(vertex1,clicpPoints, linePosition)&&!isOutside(vertex2,clicpPoints, linePosition)) {
            //Only second point is added
            newPoints[newNumber++] = vertex2;
        }else if(isOutside(vertex1,clicpPoints, linePosition)&&!isOutside(vertex2,clicpPoints, linePosition)){
            // Point of intersection with edge
            newPoints[newNumber++] = intersectPoint(vertex1, vertex2,clicpPoints, linePosition);
            // and the second point is added
            newPoints[newNumber++] = vertex2;
        }else if (!isOutside(vertex1,clicpPoints, linePosition)&&isOutside(vertex2,clicpPoints, linePosition)){
            //Only point of intersection with edge is added
            newPoints[newNumber++] = intersectPoint(vertex1, vertex2,clicpPoints, linePosition);
        }else{
            //both outside
        }
    }
    *number = newNumber;
    for (int i=0; i<*number; i++) {
        points[i] = newPoints[i];
    }
    
    
}

void suthHodgClipping(Point points[],Point clicpPoints[],int *number){
    
    for (int i=0; i<4; i++) {
        clipping(points,clicpPoints,(LinePosition)i,number);
    }

    glutPostRedisplay();
}

#pragma mark- filling

bool insidePolygon(Point point){
    
    int nCross = 0;
    int nCount = _polygon.pointNumber;
    Point p = point;
    for (int i = 0; i < nCount; i++)
    {
        Point p1 = _polygon.points[i];
        Point p2 = _polygon.points[(i + 1) % nCount];
        // 求解 y=p.y 与 p1p2 的交点
        if (p1.y == p2.y)
        {// p1p2 与 y=p0.y平行
            continue;
        }
        if (p.y < MIN(p1.y, p2.y))
        {// 交点在p1p2延长线上
            continue;
        }
        if (p.y >= MAX(p1.y, p2.y))
        {// 交点在p1p2延长线上
            continue;
        }
        // 求交点的 X 坐标 --------------------------------------------------------------
        double x = (double)(p.y - p1.y) * (double)(p2.x - p1.x) / (double)(p2.y - p1.y) + p1.x;
        if (x > p.x){
            nCross++; // 只统计单边交点
        }
    }

    return (nCross % 2 == 1);
}


void fillPolygon(Point polygon[]){
    
}


void scanFilling(){
    //Point point = pointInsidePolygon();
    
    
    
    
    for (int i=200; i<400; i++) {
        for (int j=200; j<400; j++) {
            if (insidePolygon((Point){j,i})) {
                _points[_pointsNumber++] = (Point){j,i};
            }
        }
    }
    glutPostRedisplay();
}



#pragma mark- menu
void menuMethod(int value){
    switch(value) {
        case 1:
            _menu_type = 1;
            suthHodgClipping(_polygon.points,_clicpPoints,&(_polygon.pointNumber));
            _polygon.lineMode = GL_LINE_LOOP;
            break;
        case 2:
            _menu_type = 2;
            scanFilling();
          
            break;
        case 3:
            
            break;
        default:
            break;
    }
}

void make_menu(void)
{
    /*MainMenu*/
    glutCreateMenu(menuMethod);
    glutAddMenuEntry("polygon clipping", 1);
    glutAddMenuEntry("region filling", 2);
    glutAddMenuEntry("Window-to-Viewport Mapping", 3);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void init(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    
    glMatrixMode(GL_PROJECTION);
    glOrtho(0.0, 680.0, 680.0, 0.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}




int main(int argc, char** argv)
{
    _polygon.lineMode = GL_LINE_STRIP;
    
    makeMatrix();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(680, 680);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("WAKE");
    
    init();
    make_menu();
    glutDisplayFunc(display);
    glutMouseFunc(mouseClick);
    glutMotionFunc(mouseMotion);
    glutPassiveMotionFunc(mousePassiveMotion);
    glutMainLoop();
    return 0;
}



