
//#include <windows.h>  // for MS Windows
#include <GL/glut.h>  //Unix, GLUT, include glu.h and gl.h
//#include <GLUT/glut.h> //Max OSX

void display() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer (background)
 
// Define shapes enclosed within a pair of glBegin and glEnd
   glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
      glColor3f(1.0f, 0.0f, 0.0f); // Red
      glVertex2f(-0.8f, 0.1f);     // Define vertices in counter-clockwise (CCW) order
      glVertex2f(-0.2f, 0.1f);     //  so that the normal (front-face) is facing you
      glVertex2f(-0.2f, 0.7f);
      glVertex2f(-0.8f, 0.7f);
 
      // glColor3f(0.0f, 1.0f, 0.0f); // Green
      // glVertex2f(-0.7f, -0.6f);
      // glVertex2f(-0.1f, -0.6f);
      // glVertex2f(-0.1f,  0.0f);
      // glVertex2f(-0.7f,  0.0f);
 
      // glColor3f(0.2f, 0.2f, 0.2f); // Dark Gray
      // glVertex2f(-0.9f, -0.7f);
      // glColor3f(1.0f, 1.0f, 1.0f); // White
      // glVertex2f(-0.5f, -0.7f);
      // glColor3f(0.2f, 0.2f, 0.2f); // Dark Gray
      // glVertex2f(-0.5f, -0.3f);
      // glColor3f(1.0f, 1.0f, 1.0f); // White
      // glVertex2f(-0.9f, -0.3f);
   glEnd();
 
   glBegin(GL_TRIANGLES);          // Each set of 3 vertices form a triangle
      glColor3f(0.0f, 0.0f, 1.0f); // Blue
      glVertex2f(0.1f, -0.6f);
      glVertex2f(0.7f, -0.6f);
      glVertex2f(0.4f, -0.1f);
 
      // glColor3f(1.0f, 0.0f, 0.0f); // Red
      // glVertex2f(0.3f, -0.4f);
      // glColor3f(0.0f, 1.0f, 0.0f); // Green
      // glVertex2f(0.9f, -0.4f);
      // glColor3f(0.0f, 0.0f, 1.0f); // Blue
      // glVertex2f(0.6f, -0.9f);
   glEnd();
 
   glBegin(GL_POLYGON);            // These vertices form a closed polygon
      glColor3f(1.0f, 1.0f, 0.0f); // Yellow
      glVertex2f(0.4f, 0.2f);
      glVertex2f(0.6f, 0.2f);
      glVertex2f(0.7f, 0.4f);
      glVertex2f(0.6f, 0.6f);
      glVertex2f(0.4f, 0.6f);
      glVertex2f(0.3f, 0.4f);
   glEnd();

   glFlush();  // Render now
}
 
int main(int argc, char** argv) {
   glutInit(&argc, argv);                 // Initialize GLUT
   glutCreateWindow("Hello CS460/560"); // Create a window with the given title
   glutInitWindowSize(500, 500);   // Set the window's initial width & height
   glutInitWindowPosition(200, 200); // Position the window's initial top-left corner
   glutDisplayFunc(display); // Register display callback handler for window re-paint
   glutMainLoop();           // Enter the event-processing loop
   return 0;
}

