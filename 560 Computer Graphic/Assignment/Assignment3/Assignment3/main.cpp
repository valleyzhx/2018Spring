//#include"main.h"
#include"menu.h"
#include"display.h"
#include"util.h"

//glutMainLoop never return;
int main(int argc, char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(700,700);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Assign-III Sample Code");
    
        setup();
        
            // initializing callbacks
     glutReshapeFunc(reshape);
     glutDisplayFunc(display);
     glutMouseFunc(mouseClick);
     glutMotionFunc(mouseDrag);
     
     glutSpecialFunc(specialKey); //register a special keyboard function.
    //Creates Menu on Right Click
     CreateMenu();

     glutMainLoop();
     return 0;

}
