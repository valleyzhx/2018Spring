//
//  cubeTexture.c
//  Assignment4
//
//  Created by Xiang on 2018/4/10.
//  Copyright © 2018年 Xiang. All rights reserved.
//

#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int _width;
int _height;

typedef struct {
    int width;
    int height;
    unsigned char *data;
} BMP;

BMP _bmp;

float c=M_PI/180.0f; //弧度和角度转换参数
int xTheta=90;
int yTheta=1;
float r=120.0f; //r是视点绕y轴的半径

int _startX;
int _startY;
int _isMoving;


void reshape(int width, int height){
    glViewport( 0, 0, (GLsizei)width, (GLsizei)height); // set to size of window
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    _width = width;
    _height = height;
    glOrtho( 0, width, 0, height, -1, 1 );
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void projection(int width, int height, int perspectiveORortho){
    float ratio = (float)width/height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluPerspective(90, ratio, 1, 256);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void convert_xyz_to_cube_uv(float x, float y, float z, int *index, float *u, float *v)
{
    float absX = fabs(x);
    float absY = fabs(y);
    float absZ = fabs(z);
    
    int isXPositive = x > 0 ? 1 : 0;
    int isYPositive = y > 0 ? 1 : 0;
    int isZPositive = z > 0 ? 1 : 0;
    
    float maxAxis, uc, vc;
    
    // POSITIVE X
    if (isXPositive && absX >= absY && absX >= absZ) {
        // u (0 to 1) goes from +z to -z
        // v (0 to 1) goes from -y to +y
        maxAxis = absX;
        uc = -z;
        vc = y;
        *index = 0;
    }
    // NEGATIVE X
    if (!isXPositive && absX >= absY && absX >= absZ) {
        // u (0 to 1) goes from -z to +z
        // v (0 to 1) goes from -y to +y
        maxAxis = absX;
        uc = z;
        vc = y;
        *index = 1;
    }
    // POSITIVE Y
    if (isYPositive && absY >= absX && absY >= absZ) {
        // u (0 to 1) goes from -x to +x
        // v (0 to 1) goes from +z to -z
        maxAxis = absY;
        uc = x;
        vc = -z;
        *index = 2;
    }
    // NEGATIVE Y
    if (!isYPositive && absY >= absX && absY >= absZ) {
        // u (0 to 1) goes from -x to +x
        // v (0 to 1) goes from -z to +z
        maxAxis = absY;
        uc = x;
        vc = z;
        *index = 3;
    }
    // POSITIVE Z
    if (isZPositive && absZ >= absX && absZ >= absY) {
        // u (0 to 1) goes from -x to +x
        // v (0 to 1) goes from -y to +y
        maxAxis = absZ;
        uc = x;
        vc = y;
        *index = 4;
    }
    // NEGATIVE Z
    if (!isZPositive && absZ >= absX && absZ >= absY) {
        // u (0 to 1) goes from +x to -x
        // v (0 to 1) goes from -y to +y
        maxAxis = absZ;
        uc = -x;
        vc = y;
        *index = 5;
    }
    
    // Convert range from -1 to 1 to 0 to 1
    *u = 0.5f * (uc / maxAxis + 1.0f);
    *v = 0.5f * (vc / maxAxis + 1.0f);
}



void drawCube(){
    glBegin(GL_QUADS);
    glColor3f(0, 0, 1);
    glNormal3f( 0.0F, 0.0F, 1.0F);
    glVertex3f( 50.0f, 50.0f, 50.0f);
    glVertex3f(-50.0f, 50.0f, 50.0f);
    glVertex3f(-50.0f,-50.0f, 50.0f);
    glVertex3f( 50.0f,-50.0f, 50.0f);
    //1----------------------------
    glColor3f(0, 1, 0);
    glNormal3f( 0.0F, 0.0F,-1.0F);
    glVertex3f(-0.1f,-50.0f,-50.0f);
    glVertex3f(-50.0f, 50.0f,-50.0f);
    glVertex3f( 50.0f, 50.0f,-50.0f);
    glVertex3f( 50.0f,-50.0f,-50.0f);
    //2----------------------------
    glColor3f(1, 0, 0);
    glNormal3f( 0.0F, 1.0F, 0.0F);
    glVertex3f( 50.0f, 50.0f, 50.0f);
    glVertex3f( 50.0f, 50.0f,-50.0f);
    glVertex3f(-50.0f, 50.0f,-50.0f);
    glVertex3f(-50.0f, 50.0f, 50.0f);
    //3----------------------------
    glColor3f(1, 1, 0);
    glNormal3f( 0.0F,-1.0F, 0.0F);
    glVertex3f(-50.0f,-50.0f,-50.0f);
    glVertex3f( 50.0f,-50.0f,-50.0f);
    glVertex3f( 50.0f,-50.0f, 50.0f);
    glVertex3f(-50.0f,-50.0f, 50.0f);
    //4----------------------------
    glColor3f(1, 0, 1);
    glNormal3f( 1.0F, 0.0F, 0.0F);
    glVertex3f( 50.0f, 50.0f, 50.0f);
    glVertex3f( 50.0f,-50.0f, 50.0f);
    glVertex3f( 50.0f,-50.0f,-50.0f);
    glVertex3f( 50.0f, 50.0f,-50.0f);
    //5----------------------------
    glColor3f(0, 1, 1);
    glNormal3f(-1.0F, 0.0F, 0.0F);
    glVertex3f(-50.0f,-50.0f,-50.0f);
    glVertex3f(-50.0f,-50.0f, 50.0f);
    glVertex3f(-50.0f, 50.0f, 50.0f);
    glVertex3f(-50.0f, 50.0f,-50.0f);
    //6----------------------------*/
    glEnd();
}


void display(){
    glClearColor(0.91, 0.9, 0.82, 1.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    projection(_width, _height, 1);
    int x=0,y=1,z=0;
    
    if (yTheta >= 90) {
        x=0;
        y=0;
        z=-1;
    }
    if(yTheta >=180){
        x=0;y=-1;z=0;
    }
    if (yTheta>=270) {
        x=0;y=0;z=1;
    }
    
    if (xTheta<=45||xTheta>=315) {
        
    }
    
    
    
    printf("cos %d = %.2lf\n",xTheta,cos(c*xTheta));
    printf("sin %d = %.2lf\n",xTheta,sin(c*xTheta));

    
    gluLookAt(r*cos(c*yTheta)*cos(c*xTheta), r*sin(c*yTheta), r*cos(c*yTheta)*sin(c*xTheta), 0, 0, 0, x, y, z); //从视点看远点,y轴方向(0,1,0)是上方向

    glPushMatrix();
    
    drawCube();
    
    glPopMatrix();
    glutSwapBuffers(); //swap the buffers
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



void mouseClick(int button, int state, int x, int y){
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        _startX = x;
        _startY = y;
        _isMoving = 1;
    }else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        _isMoving = 0;
    }
}
void mouseMotion(int x, int y){
    if (_isMoving) {
        if (abs(x-_startX)>abs(y-_startY)) {
            xTheta+=x-_startX; //鼠标在窗口x轴方向上的增量加到视点绕y轴的角度上，这样就左右转了
        }else{
            yTheta+=y-_startY; //鼠标在窗口y轴方向上的改变加到视点的y坐标上，就上下转了
        }
        
        if (xTheta>=360) {
            xTheta = 0;
        }else if (xTheta<=0) {
            xTheta=360;
        }
        
        if (yTheta>=360) {
            yTheta = 0;
        }else if (yTheta<=0) {
            yTheta=360;
        }
        
        _startX = x;
        _startY = y;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv){
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Texture");
    glClearColor(0, 0, 0, 1.0); // *should* display black background
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouseClick);
    glutMotionFunc(mouseMotion);

    loadImage("./flower.bmp");
    // LoadTexture( "./flower.bmp" );
    //glEnable(GL_TEXTURE_2D);
    
    glutMainLoop();
    
    
    return 0;
}

