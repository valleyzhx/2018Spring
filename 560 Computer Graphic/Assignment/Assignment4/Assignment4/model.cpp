//
//  main.cpp
//  Assignment4
//
//  Created by Xiang on 2018/3/22.
//  Copyright © 2018年 Xiang. All rights reserved.
//

#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;


typedef struct {
    float x;
    float y;
    float z;
} Point;

typedef struct {
    float u;
    float v;
} UV;

int _width;
int _height;

int _startX;
int _startY;
int _moving = 0;

double m_xtheta=0;
double m_ytheta=0;
double m_ztheta=0;

int _chageXZ= 0;
int _Z = 3;


vector<Point>vSets;//
vector<Point>fSets;//
vector<UV>vtSets;//
vector<Point>vnSets;//

void loadObj(string fname)
{
    string line;
    fstream f;
    f.open(fname, ios::in);
    if (!f.is_open()){
        cout << "Opening Objfiles Error" << endl;
    }
    while (!f.eof()){
        getline(f, line);
        vector<string>parameters;
        string tailMark = " ";
        string ans = "";
        
        line = line.append(tailMark);
        for (int i = 0; i < line.length(); i++) {
            char ch = line[i];
            if (ch != ' ') {
                ans+=ch;
            }
            else {
                if (ans != "") {
                    parameters.push_back(ans); //取出字符串中的元素，以空格切分
                    ans = "";
                }
            }
        }
        //cout << parameters.size() << endl;
        if (parameters.size() != 4) {
            //cout << "the size is not correct" << endl;
            continue;
        }else{
            if (parameters[0] == "v") {   //如果是顶点的话
                Point point;
                point.x = atof(parameters[1].c_str());
                point.y = atof(parameters[2].c_str());
                point.z = atof(parameters[3].c_str());
                vSets.push_back(point);
            }else if (parameters[0] == "vt"){
                UV uv;
                uv.u = atof(parameters[1].c_str());
                uv.v = atof(parameters[2].c_str());
                vtSets.push_back(uv);
                
            }else if (parameters[0] == "vn"){
                Point point;
                point.x = atof(parameters[1].c_str());
                point.y = atof(parameters[2].c_str());
                point.z = atof(parameters[3].c_str());
                vnSets.push_back(point);
            }
            else if (parameters[0] == "f") {   //如果是面的话，存放三个顶点的索引
                Point vIndexSets;
                for (int i = 1; i < 4; i++){
                    string x = parameters[i];
                    string ans = "";
                    for (int j = 0; j < x.length(); j++) {   //跳过‘/’
                        char ch = x[j];
                        if (ch != '/') {
                            ans += ch;
                        }
                        else {
                            break;
                        }
                    }
                    if (i==1) {
                        vIndexSets.x = atof(ans.c_str())-1;
                    }else if (i == 2){
                        vIndexSets.y = atof(ans.c_str())-1;
                    }else{
                        vIndexSets.z = atof(ans.c_str())-1;
                    }
                }
                fSets.push_back(vIndexSets);
            }
        }
    }
    f.close();
}
void projection(int width, int height, int perspectiveORortho){
    float ratio = (float)width/height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
  
    gluPerspective(90, ratio, 1, 256);
   
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void drawObject()
{
    projection(_width, _height, 1);
    gluLookAt(0, 0, 150, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glColor3f(0.733,0.733,0.733);

    
    glPushMatrix();
    glRotatef(m_xtheta, 1,0,0);
    glRotatef(m_ytheta, 0,1,0);
    glRotatef(m_ztheta, 0,0,1);
    glBegin(GL_TRIANGLES);

    for (int i = 0; i < fSets.size(); i++) {
        GLfloat VN[3];
        Point SV1;
        Point SV2;
        Point SV3;
         {
            GLint firstVertexIndex = (fSets[i]).x;//取出顶点索引
            GLint secondVertexIndex = (fSets[i]).y;
            GLint thirdVertexIndex = (fSets[i]).z;

            SV1 = vSets[firstVertexIndex];//first vertex
            SV2 = vSets[secondVertexIndex]; //second vertex
            SV3 = vSets[thirdVertexIndex]; //third vertex
             
            GLfloat vec1[3], vec2[3], vec3[3];//vector
            //(x2-x1,y2-y1,z2-z1)
            vec1[0] = SV1.x - SV2.x;
            vec1[1] = SV1.y - SV2.y;
            vec1[2] = SV1.z - SV2.z;

            //(x3-x2,y3-y2,z3-z2)
            vec2[0] = SV1.x - SV3.x;
            vec2[1] = SV1.y - SV3.y;
            vec2[2] = SV1.z - SV3.z;

            //(x3-x1,y3-y1,z3-z1)
            vec3[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
            vec3[1] = vec2[0] * vec1[2] - vec2[2] * vec1[0];
            vec3[2] = vec2[1] * vec1[0] - vec2[0] * vec1[1];

            GLfloat D = sqrt(pow(vec3[0], 2) + pow(vec3[1], 2) + pow(vec3[2], 2));

            VN[0] = vec3[0] / D;
            VN[1] = vec3[1] / D;
            VN[2] = vec3[2] / D;
            glNormal3f(VN[0], VN[1], VN[2]);//绘制法向量

            glVertex3f(SV1.x, SV1.y, SV1.z);//绘制三角面片
            glVertex3f(SV2.x, SV2.y, SV2.z);
            glVertex3f(SV3.x, SV3.y, SV3.z);
        }
    }
    
    glPopMatrix();
    
    glEnd();
}
void display(void)
{
    glClearColor(0.91, 0.9, 0.82, 1.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawObject();
    
    glutSwapBuffers(); //swap the buffers
}
void reshape(int w,int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    _width = w;
    _height = h;
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 0.1, 1000.0);
    //glOrtho(-25,25,-2,2,0.1,100);
    glOrtho( 0, w, h, 0, -1, 1 );

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}
void RollUp(float n){
    m_ztheta+=n;
    if(m_ztheta > 360) m_ztheta=0;
    if(m_ztheta < -360) m_ztheta=0;
}
void PitchUp(float n){
        m_ytheta+=n;
        if(m_ytheta > 360) m_ytheta=0;
        if(m_ytheta < -360) m_ytheta=0;
    
}
void YawUp(float n){
    m_xtheta+=n;
    //printf("yaw up:%.2f\n",m_xtheta);
    if (_Z == 3 &&((abs(m_xtheta)>45 && abs(m_xtheta)<135)||(abs(m_xtheta)>225 && abs(m_xtheta)<315))) {
        _chageXZ = 1;
    }else{
        _chageXZ = 0;
    }
    
    if(m_xtheta > 360) m_xtheta=0;
    if(m_xtheta < -360) m_xtheta=0;

}
void mouseClick(int button, int state, int x, int y){
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        _startX = x;
        _startY = y;
        _moving = 1;
    }
}
void mouseMotion(int x, int y){
    if (_moving) {
        if (abs(x-_startX)>abs(y-_startY)) {
            if (_chageXZ) {
                RollUp(x-_startX);
            }else{
                PitchUp(x-_startX);
            }
        }else{
            
            YawUp(y-_startY);
        }
        
        _startX = x;
        _startY = y;
    }
    glutPostRedisplay();
}


int main(int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(600,700);
    glutInitWindowPosition(20,20);
    glutCreateWindow("ObjLoader");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouseClick);
    glutMotionFunc(mouseMotion);
    
    loadObj("./minicooper.obj");
    
    glutMainLoop();
    return 0;
}
