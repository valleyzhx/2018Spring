#include"menu.h"
#include"util.h"
#include"display.h"

#define ANGLE 10

bool YawBool=false;
bool PitchBool=false;
bool RollBool=false;
bool SlideBool=false;


//creat menu
void CreateMenu(void){ 
 
  glutCreateMenu(MenuItemClicked);
  glutAddMenuEntry("Roll+",  1);
  glutAddMenuEntry("Roll-",  2);
  glutAddMenuEntry("Pitch+", 3);
  glutAddMenuEntry("Pitch-", 4);
  glutAddMenuEntry("Yaw+",   5);
  glutAddMenuEntry("Yaw-",   6);
  glutAddMenuEntry("Slide+", 7);
  glutAddMenuEntry("Slide-", 8);
  //Attach Menu to RightClick
  glutAddMenuEntry("Levers rotation", 9);
  glutAddMenuEntry("Rotation Animation", 10);


  glutAttachMenu(GLUT_RIGHT_BUTTON);
}




void MenuItemClicked(int Value){
	switch(Value) 
	{
		case 1:
      YawBool=false;
      PitchBool=false;
      RollBool=true;
      SlideBool=false;
      RollUp(ANGLE);
		  break;
		case 2:
      YawBool=false; 
      PitchBool=false;
      RollBool=true;
      SlideBool=false;
      RollDown(ANGLE);
			break;
		case 3:
      YawBool=false; 
      PitchBool=true;
      RollBool=false;
      SlideBool=false;
      PitchUp(ANGLE);
			break;
		case 4:
      YawBool=false; 
      PitchBool=true;
      RollBool=false;
      SlideBool=false;
      PitchDown(ANGLE);
			break;
		case 5:
      YawBool=true;
      PitchBool=false;
      RollBool=false;
      SlideBool=false;
      YawUp(ANGLE);
			break;
		case 6:
      YawBool=true;
      PitchBool=false;
      RollBool=false;
      SlideBool=false;

      YawDown(ANGLE);
			break;
		case 7:
      YawBool=false;
      PitchBool=false;
      RollBool=false;
      SlideBool=true;
     
      SlideUp(ANGLE);
			break;
		case 8:
      YawBool=false;
      PitchBool=false;
      RollBool=false;
      SlideBool=true;
      SlideDown(ANGLE);
			break;
            case 9:
            leversRotation();
            break;
        case 10:
            roateAnimation();
            break;
   	}
 	glutPostRedisplay();
}




void SubMenuItemClicked(int Value){
 	//glutPostRedisplay();
}


void specialKey(int key, int x, int y){
  switch(key){
    case 119:
          SlideDown(ANGLE/2);
          break;
    case GLUT_KEY_UP:
      if(YawBool)   YawUp(ANGLE);
      if(PitchBool) PitchUp(ANGLE);
      if(RollBool)  RollUp(ANGLE);
      if(SlideBool) SlideUp(ANGLE);
      
      break;
    case 115:
          SlideUp(ANGLE/2);
          break;
    case GLUT_KEY_DOWN:
      if(YawBool)   YawDown(ANGLE);
      if(PitchBool) PitchDown(ANGLE);
      if(RollBool)  RollDown(ANGLE);
      if(SlideBool) SlideDown(ANGLE);
      break;
  }
    glutPostRedisplay();
}
