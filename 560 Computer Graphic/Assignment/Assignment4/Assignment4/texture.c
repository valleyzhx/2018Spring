//
//  texture.c
//  Assignment4
//
//  Created by Xiang on 2018/4/6.
//  Copyright © 2018年 Xiang. All rights reserved.
//

#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int width;
    int height;
    unsigned char *data;
} BMP;
typedef struct{
    GLint x;
    GLint y;
}Point;

BMP _bmp;

Point _viewPoints[4] = {
    {250-400, 100-200}, // left bottom
    {550-400, 100-200},    // right bottom
    {550-400, 300-200}, // right bottom
    {250-400, 300-200}}; // left up

Point _start;
Point _end;
int _moved = 0;
int _isAnimated = -1;
float _angle = 0.0;

int _width;
int _height;

void bilinearInterpolation(Point imagePoints[2], Point rectPoints[4]){
    Point leftBottom = imagePoints[0];
    Point rightUp = imagePoints[1];
    
    int width = rightUp.x - leftBottom.x;
    int height = rightUp.y - leftBottom.y;
    int startX = leftBottom.x;
    int startY = leftBottom.y;

    int a1 = rectPoints[0].x;
    int a2 = rectPoints[0].y;
    int b1 = rectPoints[1].x;
    int b2 = rectPoints[1].y;
    int c1 = rectPoints[2].x;
    int c2 = rectPoints[2].y;
    int d1 = rectPoints[3].x;
    int d2 = rectPoints[3].y;
    
    int a = c1-b1+a1-d1;
    int b = b1-a1;
    int c = d1-a1;
    int d = a1;
    int e = c2-b2+a2-d2;
    int f = b2-a2;
    int g = d2-a2;
    int h = a2;
    //bilinear
    /*
     x = auv + bu + cv + d;
     y = euv + fu + gv + h;
     */
    glBegin(GL_POINTS);
    for (int he=0; he<height; he++) {
        for (int we=0; we<width; we++) {
            float u = we*1.0/width;
            float v = he*1.0/height;
            
            int x = (int)round(a*u*v + b*u + c*v +d);
            int y = (int)round(e*u*v + f*u + g*v +h);
            int R = _bmp.data[(he+startY)*_bmp.width*3 + (we+startX)*3];
            int G = _bmp.data[(he+startY)*_bmp.width*3 + (we+startX)*3 + 1];
            int B = _bmp.data[(he+startY)*_bmp.width*3 + (we+startX)*3 + 2];
            glColor3f(R/255.0, G/255.0, B/255.0);
            glVertex3f(x,y,0);
        }
    }
    
    glEnd();
    
}
void projection(int width, int height, int perspectiveORortho){
    float ratio = (float)width/height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
   
    gluPerspective(90, ratio, 0.1, 1000);
   
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void drawScene(void)
{
    
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    
    glColor4f(1.0, 1.0, 1.0, 0.0);
    //glEnable(GL_TEXTURE_2D);
    
    //rectangle + texture   //// You may rewrite this part for your own implementation
   // glBegin(GL_POLYGON);
    Point leftBottom = _viewPoints[0];
    Point rightBottom = _viewPoints[1];
    Point rightUp = _viewPoints[2];
    Point leftUp = _viewPoints[3];

//    glVertex3f(leftBottom.x,leftBottom.y,0.0);
//
//    glVertex3f(rightBottom.x,rightBottom.y,0.0);
//
//    glVertex3f(rightUp.x,rightUp.y,0.0);
//
//    glVertex3f(leftUp.x,leftUp.y,0.0);

    glPushMatrix();
    if (_isAnimated>0) {
        glRotatef(_angle,0,0,1);
    }

    float rectWid = rightBottom.x - leftBottom.x;
    float rectHei = rightUp.y - rightBottom.y;
    if (_moved) {
        Point first[4] = {
            {0,0},
            {1.0*(_start.x-leftBottom.x)/rectWid*_bmp.width,1.0*(_start.y-leftBottom.y)/rectHei*_bmp.height}};
        Point firstView[4] = {
            leftBottom,
            {_end.x,leftBottom.y},
            {_end.x,_end.y},
            {leftBottom.x,_end.y}
        };
        bilinearInterpolation(first, firstView);
        Point second[4] = {
            {1.0*(_start.x-leftBottom.x)/rectWid*_bmp.width,0},
            {_bmp.width,1.0*(_start.y-leftBottom.y)/rectHei*_bmp.height},
        };
        Point secondView[4] = {
            {_end.x,leftBottom.y},
            rightBottom,
            {rightBottom.x,_end.y},
            {_end.x,_end.y}
        };
        bilinearInterpolation(second, secondView);
        Point third[4] = {
            {1.0*(_start.x-leftBottom.x)/rectWid*_bmp.width,1.0*(_start.y-leftBottom.y)/rectHei*_bmp.height},
            {_bmp.width,_bmp.height},
        };
        Point thirdView[4] = {
            {_end.x,_end.y},
            {rightBottom.x,_end.y},
            rightUp,
            {_end.x,rightUp.y}
        };
        bilinearInterpolation(third, thirdView);
        Point forth[4] = {
            {0,1.0*(_start.y-leftBottom.y)/rectHei*_bmp.height},
            {1.0*(_start.x-leftBottom.x)/rectWid*_bmp.width,_bmp.height},
        };
        Point forthView[4] = {
            {leftUp.x,_end.y},
            {_end.x,_end.y},
            {_end.x,rightUp.y},
            leftUp
        };
        bilinearInterpolation(forth, forthView);
        
    }else{
        Point imageArr[4] = {{0,0},{_bmp.width,_bmp.height}};
        bilinearInterpolation(imageArr, _viewPoints);
    }
    glPopMatrix();

    //glDisable(GL_TEXTURE_2D);
    
    glutSwapBuffers();
}

void loadImage(const char *filename){
    
    int width;
    int height;
    unsigned long size;
    unsigned long i;
    unsigned short int planes;
    unsigned short int bpp;            // pixels
    unsigned char * data;
    
    
    FILE * file;
    
    file = fopen( filename, "rb" );
    
    if ( file == NULL ) return;
    
    /***************************
     HEADER = >bfType 2, bfSize 4, bfReserved1 2, bfReserved2 2, bfOffBits 4;
     INFO = > biSize 4, go on ->
     ***************************/
    fseek(file, 18, SEEK_CUR);
    //width
    if ((i = fread(&width, 4, 1, file)) != 1) {
        return;
    }
    //height
    if ((i = fread(&height, 4, 1, file)) != 1) {
        return;
    }
    size = width * height *3;
    _bmp.width = width;
    _bmp.height = height;
    
    if ((fread(&planes, 2, 1, file)) != 1) {
        return ;
    }
    if (planes != 1) {
        printf("not bmp image!\n");
        return ;
    }
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        return ;
    }
    if (bpp != 24) {//如果不是24bpp的话失败
        printf("not a 24bit image!\n");
        return ;
    }
    fseek(file, 24, SEEK_CUR);    //load data
    
    data = (unsigned char *)malloc(size);
    fread( data, size, 1, file );
    fclose( file );
    for(int i = 0; i < width * height ; ++i)
    {
        int index = i*3;
        unsigned char B,R;
        B = data[index];
        R = data[index+2];
        
        data[index] = R;
        data[index+2] = B;
    }
    _bmp.data = data;
    
    
}
GLuint LoadTexture( const char * filename )
{
    GLuint texture;
    loadImage(filename);
    
    glDrawBuffer(GL_BACK);
    glGenTextures( 1, &texture );
    glBindTexture( GL_TEXTURE_2D, texture );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, _bmp.width, _bmp.height,GL_RGB, GL_UNSIGNED_BYTE, _bmp.data);
    
    return texture;
}



// reshaped window
void reshape(int width, int height) {
    
    glViewport( 0, 0, (GLsizei)width, (GLsizei)height); // set to size of window
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    _width = width;
    _height = height;
   // gluOrtho2D( 0.0, (float)width, 0.0, (float)height );
    glOrtho( -width/2, width/2, -height/2, height/2, -1, 1 );

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void mouseClick(int button, int state, int x, int y){
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        _start.x = x-_width/2;
        _start.y = _height/2-y;
        _moved = 1;
    }
}
void mouseMotion(int x, int y){
    if (_moved) {
        _end.x = x-_width/2;
        _end.y = _height/2-y;
    }
    glutPostRedisplay();
}

void timerProc(int id)
{
    if (_isAnimated) {
        _angle += 30;
        if (_angle>=360) {
            _angle = 0.0;
        }
        glutPostRedisplay();
        glutTimerFunc(1000,timerProc,1);
    }
}
void roateAnimation(){
    _isAnimated = -_isAnimated;
    glutTimerFunc(0,timerProc,1);
}


#pragma mark- menu
void menu(int value){
    roateAnimation();
}

void make_menu(void)
{
    glutCreateMenu(menu);
    glutAddMenuEntry("rotate animation", 1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}



int main(int argc, char **argv){
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Texture");
    glClearColor(0, 0, 0, 1.0); // *should* display black background

    glutDisplayFunc(drawScene);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouseClick);
    glutMotionFunc(mouseMotion);
    make_menu();
    loadImage("./flower.bmp");
   // LoadTexture( "./flower.bmp" );
    //glEnable(GL_TEXTURE_2D);

    glutMainLoop();

    
    return 0;
}
