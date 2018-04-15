#include"display.h"
#include"util.h"

//#define NDEBUG  // used to disabled all assert.
GLsizei width, height;


double m_xtheta=0;
double m_ytheta=0;
double m_ztheta=0;
double m_slide=40;

double lr_ythetha = 0;
double lr_zthetha = 0;

int _moving;
int _startX;
int _startY;
int _isAnimated;
int _stopAnimation;

void setup()
{
    glClearColor(0, 0, 0, 1.0); // *should* display black background
}


void reshape( int w, int h ){
    glViewport( 0, 0, (GLsizei)w, (GLsizei)h ); // set to size of window
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    //gluOrtho2D( 0.0, (float)w, 0.0, (float)h );

    glOrtho( 0, w, h, 0, -1, 1 );
    width = w;  // records width globally
    height = h; // records height globally

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}



void display(){
   // glClear(GL_COLOR_BUFFER_BIT); // clear window
   glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT );

   glColor3f(0,1,0);
   glLineWidth(1);

   glViewport(width/2.0, 0, width/2.0, height/2.0); //V1
   {
     
      projection(width/2.0, height/2.0, 1);
       /*
        u' = cos(alpha)*u - sin(alpha)*v
        v' = sin(alpha)*u + cos(alpha)*v
        n' = n
        */
       
      gluLookAt(0, 0, m_slide, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
     // glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
      glPushMatrix();
       glRotatef(m_xtheta, 1,0,0);
       glRotatef(m_ytheta, 0,1,0);
       glRotatef(m_ztheta, 0,0,1);
      RenderGLScene(5, 5, 30);
      glPopMatrix();
   }
    glViewport(0, 0, width/2.0, height/2.0); //V2
    {
        
        projection(width/2.0, height/2.0, 1);
       // GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ, GLdouble centerX, GLdouble centerY, GLdouble centerZ, GLdouble upX, GLdouble upY, GLdouble upZ
      
        gluLookAt(0, m_slide, 0, 0.0, 0.0, 0, 0.0, 0.0, -1);
        
        // glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT );
        glPushMatrix();
        glRotatef(m_xtheta, 1,0,0);
        glRotatef(m_ytheta, 0,1,0);
        glRotatef(m_ztheta, 0,0,1);
        RenderHierarchicalGLScene(5, 5, 30);
        glPopMatrix();
    }
    glViewport(0, height/2.0, width/2.0, height/2.0); //V3
    {
        
        projection(width/2.0, height/2.0, 1);
        
        gluLookAt(m_slide, 0, 0, 0.0, 0.0, 0, 0.0, 1.0, 0.0);
        
        // glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT );
        glPushMatrix();
        glRotatef(m_xtheta, 1,0,0);
        glRotatef(m_ytheta, 0,1,0);
        glRotatef(m_ztheta, 0,0,1);
        RenderHierarchicalGLScene(5, 5, 30);
        glPopMatrix();
    }
    glViewport(width/2.0, height/2.0, width/2.0, height/2.0); //V4
    {

        projection(width/2.0, height/2.0, 1);

        gluLookAt(0, 0, m_slide, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

        // glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT );
        glPushMatrix();
        glRotatef(m_xtheta, 1,0,0);
        glRotatef(m_ytheta, 0,1,0);
        glRotatef(m_ztheta, 0,0,1);
        RenderHierarchicalGLScene(5, 5, 30);
        glPopMatrix();
    }
    

   glutSwapBuffers(); // display newly drawn image in window
}


void projection(int width, int height, int perspectiveORortho){
  float ratio = (float)width/height;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (perspectiveORortho)
      gluPerspective(90, ratio, 1, 256);
  else 
      glOrtho(-ratio, ratio, -ratio, ratio, 1, 1000);
  glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
}


void RenderGLScene(int base_radius, int top_radius, int height){
  // draw a cylinder or a sphere, 
  // you will draw more objects in this function
  GLUquadricObj* quadObj = gluNewQuadric();
  gluQuadricDrawStyle (quadObj, GLU_LINE);
 
  gluCylinder(quadObj, base_radius, top_radius, height, 20, 10);       //draw a cone shape cylinder
  DrawGround();                 //draw ground lines for reference 
  gluDeleteQuadric(quadObj);
  glFlush();
}

void drawSphere(float radius){
    //glColor3f(1,1,0);
    glutSolidSphere(radius,20,20);

}

void RenderHierarchicalGLScene(int base_radius, int top_radius, int height){
    DrawGround();
    glColor3f(1,1,0);
    GLUquadricObj* quadObj = gluNewQuadric();
    gluQuadricDrawStyle (quadObj, GLU_LINE);
    
    //s1
    glRotatef( -90, 1, 0, 0 );
    gluCylinder(quadObj, 1, 1, 20, 8, 3);       //draw a cone shape cylinder
    //DrawGround();                 //draw ground lines for reference
    
    glRotatef( 90, 1, 0, 0 );
    glRotated(lr_ythetha, 0, 1, 0);// Animate s1 s2
    //s2
    glTranslatef(0.0,20.0,0.0);//
    gluCylinder(quadObj, 1, 1, 10, 5, 3);       //draw a cone shape cylinder
    //s3
    glRotatef( 180, 0, 1, 0 );
    gluCylinder(quadObj, 1, 1, 10, 5, 3);       //draw a cone shape cylinder
    //b2
    drawSphere(1.5);

    //b1
    glTranslatef(0.0,0,-10.0);//
    drawSphere(1.5);
    //Animate s4 s5
    glRotated(lr_zthetha, 0, 0, 1);// Animate s1 s2

    //s4
    glRotatef( 90, 1, 0, 0 );
    //glTranslatef(0.0,0,10.0+1);//
    gluCylinder(quadObj, 0.1, 1, 10, 5, 3);       //draw a cone shape cylinder
    //b4
    glTranslatef(0.0,0,10.0);//
    drawSphere(3);

    //b5
    glTranslatef(0.0,2*10.0,0);//
    drawSphere(3);
    //s4
    glRotatef( 180, 0, 1, 0 );
    gluCylinder(quadObj, 1, 0.1, 10, 5, 3);
    //b3
    glTranslatef(0.0,0,10.0);//
    glutSolidSphere(1.5,20,20);

    gluDeleteQuadric(quadObj);
    glColor3f(0,1,0);

    glFlush();
}



void DrawGround(){
  glBegin(GL_LINES);
  
  for(float i =-1; i<=1; )
   {
       glVertex3f(i*100.f, -10.f, -100.f);
       glVertex3f(i*100.f, -10.f, 100.f);
       i+=0.1;
   }
  for(float j =-1; j<=1; )
    {
       glVertex3f(-100.f, -10.f, j*100.f);
       glVertex3f(100.f, -10.f, j*100.f);
       j+=0.1;
    }
  glEnd();
}

void mouseClick(int button, int state, int x, int y){
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            _moving = 1;
            _startX = x;
            _startY = y;
        }
        if (state == GLUT_UP) {
            _moving = 0;
        }
    }
    if (button == GLUT_MIDDLE_BUTTON) {
        if (state == GLUT_DOWN) {
            
        }
        if (state == GLUT_UP) {
            
        }
    }
}

void mouseDrag(int x, int y){
    if (_moving) {
        PitchUp(x-_startX);
        YawUp(y-_startY);
        
        _startX = x;
        _startY = y;
        glutPostRedisplay();
    }
}

void RollUp(float n){
  m_ztheta+=n;
  if(m_ztheta > 360) m_ztheta=-360;
}
void RollDown(float n){
  m_ztheta-=n;
  if(m_ztheta < -360) m_ztheta=360;
}
void PitchUp(float n){
  m_ytheta+=n;
  if(m_ytheta > 360) m_ytheta=-360;
}
void PitchDown(float n){
  m_ytheta-=n;
  if(m_ytheta < -360) m_ytheta=360;
}
void YawUp(float n){
  m_xtheta+=n;
  if(m_xtheta > 360) m_xtheta=-360;
}
void YawDown(float n){
  m_xtheta-=n;
  if(m_xtheta < -360) m_xtheta=360;
}
void SlideUp(float n){
  m_slide+=n;
}
void SlideDown(float n ){
  m_slide-=n;
}

void leversRotation(){
    lr_ythetha += 10;
    lr_zthetha += 10;
    if(lr_ythetha > 360) lr_ythetha=-360;
    if(lr_zthetha > 360) lr_zthetha=-360;
    glutPostRedisplay();

}
void timerProc(int id)
{
    if (_stopAnimation) {
        _isAnimated = 0;
        _stopAnimation = 0;
    }else{
        leversRotation();
        glutTimerFunc(150,timerProc,1);
    }
}
void roateAnimation(){
    if (_isAnimated) {
        _stopAnimation = 1;
        return;
    }
    _isAnimated = 1;
    glutTimerFunc(0,timerProc,1);

}





