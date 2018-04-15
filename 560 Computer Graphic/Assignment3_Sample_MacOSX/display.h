#define PI 3.1415926


void setup();
void reshape( int w, int h );
void display();
void projection(int width, int height, int perspectiveORortho);
void RenderGLScene(int base_radius, int top_radius, int height);
void RenderHierarchicalGLScene(int base_radius, int top_radius, int height);

void DrawGround();

// setting the rotation.
void RollUp(float n);
void RollDown(float n);
void PitchUp(float n);
void PitchDown(float n);
void YawUp(float n);
void YawDown(float n);
void SlideUp(float n);
void SlideDown(float n );
//
void leversRotation();
void roateAnimation();


void mouseClick(int button, int state, int x, int y);// call when left/right/middle click.
void mouseDrag( int x, int y );// call when mouse motion
