#include <stdio.h>
#include <stdlib.h>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <math.h>


#define RADIAN(angle) (angle/180.0*M_PI)
typedef struct {
    int width;
    int height;
    unsigned char *data;
} BMP;
BMP _bmp;

GLuint _texture;

float _width;
float _height;
float _pointZ = 0.0f;
int _pointHits = 0;

int MOVENAME = 0;

GLint _viewport[4];

typedef struct {
    float x;
    float y;
    float z;
}Point;
Point _ctrlPoints[4][4];
Point _gridPoints[21][21];


GLdouble _modelViewMatrix[16], _projectionMatrix[16];



GLdouble eye[3] = {45.0, 45.0, 45.0};
GLdouble radius = sqrt(eye[0] * eye[0] + eye[1] * eye[1]+eye[2]*eye[2]);

GLdouble theta = acos(eye[1]/radius)*180/M_PI;
GLdouble alpha = -45.0;

float _shininess = 50.0;
float _diffuse = 0.7;
int _light_on = -1;

int _patchMode = -1;
int _textureMode = -1;



void setControlPoints(){
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            _ctrlPoints[i][j].x = j*20;
            _ctrlPoints[i][j].y = 0;
            _ctrlPoints[i][j].z = i*20;
        }
    }
}

void drawAxis(){
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(100, 0, 0);
    
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(0, 0.0, 0);
    glVertex3f(0, 100, 0);
    
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0, 0, 0.0);
    glVertex3f(0, 0, 100);
    glEnd();
}



void evalBezierCurve(Point *point ,const Point *P, const float t)
{
    float b0 = (1 - t) * (1 - t) * (1 - t);
    float b1 = 3 * t * (1 - t) * (1 - t);
    float b2 = 3 * t * t * (1 - t);
    float b3 = t * t * t;
    point->x = P[0].x * b0 + P[1].x * b1 + P[2].x * b2 + P[3].x * b3;
    point->y = P[0].y * b0 + P[1].y * b1 + P[2].y * b2 + P[3].y * b3;
    point->z = P[0].z * b0 + P[1].z * b1 + P[2].z * b2 + P[3].z * b3;
}

void evaluateBezierSurface()
{
    
    
    for (int u=0; u<=20; u++) {
        for (int v=0; v<=20; v++) {
            Point uPoints[4];
            for (int i=0; i<4; i++) {
                Point point = {0,0,0};
                evalBezierCurve(&point, _ctrlPoints[i],u/20.0);
                uPoints[i] = point;
            }
            Point final = {0,0,0};
            evalBezierCurve(&final, uPoints, v/20.0);
            _gridPoints[u][v] = final;
        }
    }
}


bool canbeVisible(Point p1, Point p2, Point p3){
    float Nx = (p2.y-p1.y)*(p3.z-p1.z)-(p3.y-p1.y)*(p2.z-p1.z);
    float Ny = (p2.z-p1.z)*(p3.x-p1.x)-(p3.z-p1.z)*(p2.x-p1.x);
    float Nz = (p2.x-p1.x)*(p3.y-p1.y)-(p3.x-p1.x)*(p2.y-p1.y);

    float result = eye[0]*Nx + eye[1]*Ny+eye[2]*Nz;
    
    return result<=0;
}



void drawGround(){
    glColor3f(0.0, 1.0, 0.0);
    if (_textureMode>0) {
        glColor3f(1.0, 1.0, 1.0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _texture);
        
        float points[4][4][3];
        for (int i=0; i<4; i++) {
            for (int j=0; j<4; j++) {
                points[i][j][0] = _ctrlPoints[i][j].x;
                points[i][j][1] = _ctrlPoints[i][j].y;
                points[i][j][2] = _ctrlPoints[i][j].z;
            }
        }
        
        glMap2f(GL_MAP2_VERTEX_3, 0.0, 1, 3, 4, 0, 1, 12, 4, &points[0][0][0]);
        glEvalMesh2(GL_FILL, 0, 20, 0, 20);
        glDisable(GL_TEXTURE_2D);
        
        
    }else{
        evaluateBezierSurface();
        for (int i=0; i<20; i++) {
            for (int j=0; j<20; j++) {
                if (_patchMode>0 || _textureMode>0) {
                    glBegin(GL_TRIANGLES);
                }else{
                    glBegin(GL_LINE_STRIP);
                }
                
                Point a = _gridPoints[i][j];
                Point b = _gridPoints[i+1][j];
                Point c = _gridPoints[i+1][j+1];
                Point d = _gridPoints[i][j+1];
                
                if (canbeVisible(a, b, c)) {
                    glVertex3f(a.x, a.y, a.z);
                    
                    glVertex3f(b.x, b.y, b.z);
                    glVertex3f(c.x, c.y, c.z);
                }
                if (canbeVisible(c,d,a)) {
                    glVertex3f(c.x, c.y, c.z);
                    glVertex3f(d.x, d.y, d.z);
                    glVertex3f(a.x, a.y, a.z);
                }
                
                glEnd();
            }
        }
    }
    
}

void drawPoints(GLenum mode)
{
    int i = 1;
    
    for (int a = 0; a < 4; a++) {
        for (int b = 0; b < 4; b++) {
            glPushMatrix();
            if (MOVENAME == 4 * a + b + 1) {
                glColor3f(0.0, 1.0, 1.0);
            } else {
                glColor3f(1.0, 1.0, 0.0);
            }
            glTranslatef(_ctrlPoints[a][b].x,
                         _ctrlPoints[a][b].y,
                         _ctrlPoints[a][b].z);
            if (mode == GL_SELECT) glLoadName(i);
            glutSolidSphere(1.5, 8, 8);
            glPopMatrix();
            ++i;
        }
    }
}

void projection(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, _width/_height, 10, 200);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void setLight(){
    GLfloat lightAmbient[] = {0.1, 0.1, 0.1, 1.0};
    GLfloat lightDiffuse[] = {0.7, 0.7, 0.7, 1.0};
    GLfloat lightSpecular[] = {0.4, 0.4, 0.4, 1.0};
    
    GLfloat light_position[] = {45.0, 25.0, 20.0, 1.0};
    GLfloat green_color[] = {0.0, _diffuse, 0.0, 1.0};
    GLfloat white_color[] = {1.0, 1.0, 1.0, 1.0};
    
    GLfloat mat_shininess[] = {_shininess};
    
   // glPushMatrix();

    glLightfv(GL_LIGHT0,GL_AMBIENT,lightAmbient);
    
    glLightfv(GL_LIGHT0,GL_DIFFUSE,lightDiffuse);
    glLightfv(GL_LIGHT0,GL_SPECULAR,lightSpecular);
    
    glLightfv(GL_LIGHT0,GL_POSITION,light_position);
    
    
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lightAmbient);

   

    glMaterialfv(GL_FRONT, GL_AMBIENT, green_color);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, green_color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white_color);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    
    
    //glPopMatrix();

}
void display(void)
{
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    projection();
    
    gluLookAt(eye[0], eye[1], eye[2], 0, 0, 0, 0, 1, 0);
    glScalef(0.6, 0.6, 0.6);
    
    GLfloat green_color[] = {0.0, _diffuse, 0.0, 1.0};
    GLfloat mat_shininess[] = {_shininess};

    //glPushMatrix();
    
    
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_AMBIENT, green_color);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, green_color);
    
    drawAxis();
    drawGround();
    drawPoints(GL_RENDER);
    
    setLight();

    //glPopMatrix();
    glutSwapBuffers();
    
    
}



void init(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    setControlPoints();
    
    glEnable(GL_MAP2_VERTEX_3);
    glEnable(GL_MAP2_TEXTURE_COORD_2);
    glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);


    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    setLight();

}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    _width = w;
    _height = h;
    projection();
    
    _viewport[0] = 0;
    _viewport[1] = 0;
    _viewport[2] = _width;
    _viewport[3] = _height;
    //setLight();

}

#pragma mark- mouse

void processHits(GLint hits, GLuint buffer[])
{
    int i, j;
    GLuint names, *ptr;
    float z1, z2;
    ptr =(GLuint *) buffer;
    names = *ptr;
    for (i = 0; i < hits; i++) {
        for (j = 0; j < names; j++) {
            z1 = (float) *(ptr+1)/0xffffffff;
            //printf("  z1 is %f;", z1 );
            z2 = (float) *(ptr+2)/0xffffffff;
            //printf(" z2 is %f\n", z2);
            _pointZ = (z1 + z2) / 2;
            MOVENAME = *(ptr + 3);
        }
    }
}



void processSelection(int x, int y){
    GLuint selectBuffer[1024];
    glSelectBuffer(1024, selectBuffer); // set buffer
    
    
    //change to select
    glRenderMode(GL_SELECT);
    glInitNames();
    glPushName(0);
    //pick matrix of mouse
    
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    
    gluPickMatrix(x, (_height - y), 2.0, 2.0, _viewport);
    gluPerspective(90, _width/_height, 10, 200);

    glMatrixMode(GL_MODELVIEW);
    drawPoints(GL_SELECT);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    
    GLint hits = glRenderMode(GL_RENDER);
    printf("hits:%d\n",hits);
    _pointHits = hits;
    processHits(hits, selectBuffer);
    
}

void mouseClick(int button, int state, int xPosition, int yPosition)
{
    // left mouse button down
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        processSelection(xPosition, yPosition);
    }
    
    // left mouse button up
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        MOVENAME = 0;
    }
    glutPostRedisplay();
}

void mouseMove(int xPosition, int yPosition)
{
    GLdouble pointX, pointY, pointZ;
    
    if (_pointHits > 0) {
        glGetIntegerv(GL_VIEWPORT, _viewport);
        glGetDoublev(GL_MODELVIEW_MATRIX, _modelViewMatrix);
        glGetDoublev(GL_PROJECTION_MATRIX, _projectionMatrix);
        
        gluUnProject((GLdouble) xPosition, (GLdouble) (_height - yPosition) , _pointZ,
                     _modelViewMatrix, _projectionMatrix, _viewport,
                     &pointX, &pointY, &pointZ);
        
        //printf("y:%f\n",pointY);
        
        _ctrlPoints[MOVENAME / 4][MOVENAME % 4 - 1].x = pointX;
        _ctrlPoints[MOVENAME / 4][MOVENAME % 4 - 1].y = pointY;
        _ctrlPoints[MOVENAME / 4][MOVENAME % 4 - 1].z = pointZ;
        glutPostRedisplay();
    }
}

// spectial key function for up arrow, down arrow, left arrow and right arrow
void specialKeys(int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_DOWN:
            theta -= 5;
            break;
        case GLUT_KEY_UP:
            theta += 5;
            break;
        case GLUT_KEY_RIGHT:
            alpha -= 5;
            break;
        case GLUT_KEY_LEFT:
            alpha += 5;
            break;
        case GLUT_KEY_PAGE_UP:        // turn and move camera up
            radius += 0.01;
            break;
        case GLUT_KEY_PAGE_DOWN:    // turn and move camera down
            radius -= 0.01;
            break;
    }
    eye[0] = round(radius * sin(RADIAN(theta))*cos(RADIAN(alpha)));
    eye[1] = round(radius * cos(RADIAN(theta)));
    eye[2] = -round(radius * sin(RADIAN(theta)) * sin(RADIAN(alpha)));
    
    glutPostRedisplay();
}

#pragma mark- texture
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
    if (bpp != 24) {
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

GLuint loadTexture(const char *filename)
{
    GLfloat texpts[2][2][2] = {{{0.0, 0.0}, {0.0, 1.0}},
        {{1.0, 0.0}, {1.0, 1.0}}};
     //GLfloat zPlane[] = {0.0f, 0.0f, 1.0f, 0.0f};
    loadImage(filename);
    
    GLuint texture;
    glGenTextures( 1, &texture );
    glBindTexture( GL_TEXTURE_2D, texture );
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, _bmp.width, _bmp.height, 0, GL_RGB, GL_UNSIGNED_BYTE, _bmp.data);
    
    glMap2f(GL_MAP2_TEXTURE_COORD_2, 0, 1, 2, 2,0, 1, 4, 2, &texpts[0][0][0]);
    return texture;
}



#pragma mark- menu


void lightMenu(int id){
    switch (id) {
        case 3:
            _shininess += 5.0;
            break;
        case 4:
            _shininess -= 5.0;
            break;
        case 5:
            _diffuse += 0.1;
            break;
        case 6:
            _diffuse -= 0.1;
            break;
            
        default:
            break;
    }
    if (_shininess<=0) {
        _shininess = 0;
    }
    if (_shininess>=128) {
        _shininess = 128;
    }
}

void menuFunction(int id){
    if (id == 1) {
        _patchMode = -_patchMode;
    }else if (id == 2){
        _light_on = - _light_on;
        if (_light_on>0) {
            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT0);
        }else{
            glDisable(GL_LIGHTING);
            glDisable(GL_LIGHT0);
        }
    }else if(id < 7){
        lightMenu(id);
    }else if (id == 7){
        _textureMode = - _textureMode;
        _light_on = -1;
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
    }
    glutPostRedisplay();
    //setLight();
}

void changeShadeModel(int id){
    if (id == 2) {
        glShadeModel(GL_FLAT);
    }else{
        glShadeModel(GL_SMOOTH);
    }
    glutPostRedisplay();
}

void creatMenus()
{
    int shadeMenu = glutCreateMenu(changeShadeModel);
    glutAddMenuEntry("smooth", 1);
    glutAddMenuEntry("flat", 2);
    
    glutCreateMenu(menuFunction);
    glutAddMenuEntry("patch mode", 1);
    glutAddMenuEntry("light On/off", 2);
    glutAddMenuEntry("shininess ++", 3);
    glutAddMenuEntry("shininess --", 4);
    glutAddMenuEntry("diffuse ++", 5);
    glutAddMenuEntry("diffuse --", 6);
    glutAddMenuEntry("texture", 7);
    glutAddSubMenu("shade mode", shadeMenu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (800, 800);
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    
    glutMouseFunc(mouseClick);
    glutMotionFunc(mouseMove);
    glutSpecialFunc(specialKeys);
    
    creatMenus();
    _texture = loadTexture("./flower.bmp");
    glutMainLoop();
    return 0;
}
