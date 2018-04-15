void fun(){
    glColor3f(0, 0, 1);
    glBegin(GL_QUADS);
    glNormal3f( 0.0F, 0.0F, 1.0F);
    glVertex3f( 50.0f, 50.0f, 50.0f);
    glVertex3f(-50.0f, 50.0f, 50.0f);
    glVertex3f(-50.0f,-50.0f, 50.0f);
    glVertex3f( 50.0f,-50.0f, 50.0f);
    //1----------------------------
    glNormal3f( 0.0F, 0.0F,-1.0F);
    glVertex3f(-0.1f,-50.0f,-50.0f);
    glVertex3f(-50.0f, 50.0f,-50.0f);
    glVertex3f( 50.0f, 50.0f,-50.0f);
    glVertex3f( 50.0f,-50.0f,-50.0f);
    //2----------------------------
    glNormal3f( 0.0F, 1.0F, 0.0F);
    glVertex3f( 50.0f, 50.0f, 50.0f);
    glVertex3f( 50.0f, 50.0f,-50.0f);
    glVertex3f(-50.0f, 50.0f,-50.0f);
    glVertex3f(-50.0f, 50.0f, 50.0f);
    //3----------------------------
    glNormal3f( 0.0F,-1.0F, 0.0F);
    glVertex3f(-50.0f,-50.0f,-50.0f);
    glVertex3f( 50.0f,-50.0f,-50.0f);
    glVertex3f( 50.0f,-50.0f, 50.0f);
    glVertex3f(-50.0f,-50.0f, 50.0f);
    //4----------------------------
    glNormal3f( 1.0F, 0.0F, 0.0F);
    glVertex3f( 50.0f, 50.0f, 50.0f);
    glVertex3f( 50.0f,-50.0f, 50.0f);
    glVertex3f( 50.0f,-50.0f,-50.0f);
    glVertex3f( 50.0f, 50.0f,-50.0f);
    //5----------------------------
    glNormal3f(-1.0F, 0.0F, 0.0F);
    glVertex3f(-50.0f,-50.0f,-50.0f);
    glVertex3f(-50.0f,-50.0f, 50.0f);
    glVertex3f(-50.0f, 50.0f, 50.0f);
    glVertex3f(-50.0f, 50.0f,-50.0f);
    //6----------------------------*/
    glEnd();
}
