#define _USE_MATH_DEFINES

#include "assets.hpp"

using namespace std;

Player user;
int _angle = 20.0;
double _slowback = -1.0;

int initRendering() {
  glClearColor(1.0, 1.0, 1.0, 1.0); //black and opaque
}

void handleResize(int w, int h) {

  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
  // glOrtho(2.0, 2.0, 2.0, 2.0, 1.0, 200)
}

void SpecialKeyHandler (int key, int x, int y) {
  switch (key) {
    case GLUT_KEY_UP:
      // camera move forward
      break;
    case GLUT_KEY_DOWN:
      // move camera backwards
      break;
  }
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Moving the camera back from the shape to show a greater area for shape movement
  glTranslatef(0.0, 0.0, -50.0);

  glPushMatrix();
    //Translation of the shape itself
    glTranslatef(-user.getXPos(), user.getYPos(), 0.0);
    // Z axis rotation
    glRotatef(user.getZRot(), 0.0, 0.0, 1.0);
    user.createPlayer();

    cout << user.getXPos() << " / " << user.getYPos() << endl;
  glPopMatrix();

  // replace user.createPlayer() with this to test a different shape with the translation.
  // I did this to make sure my unit circle generation wasnt the issue
  // glBegin(GL_TRIANGLES);
  //   glColor3f(1.0, 0.0, 0.0);
  //   glVertex2f(-0.5, 0.5);
  //   glVertex2f(-0.5, -0.5);
  //   glVertex2f(0.5, 0.5);
  //   glVertex2f(0.5, 0.5);
  //   glVertex2f(-0.5, -0.5);
  //   glVertex2f(0.5, -0.5);
  // glEnd();

  glutSwapBuffers();
  glutPostRedisplay();

}

void keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 27:
    exit(EXIT_SUCCESS);
    case 't':
    //change number of vertices
    user.addSides(1);
    break;
    case 'a':
    glutIgnoreKeyRepeat('a');
    user.holdLeft = true;
    break;
    case 'd':
    glutIgnoreKeyRepeat('d');
    user.holdRight = true;
    break;
    case 'w':
    glutIgnoreKeyRepeat('w');
    user.holdUp = true;
    break;
    case 's':
    glutIgnoreKeyRepeat('s');
    user.holdDown = true;
    break;
  }
}

void keyboardUp(unsigned char key, int x, int y) {
  switch(key) {
    case 'a':
    glutIgnoreKeyRepeat('a');
    user.holdLeft = false;
    break;
    case 'd':
    glutIgnoreKeyRepeat('d');
    user.holdRight = false;
    break;
    case 'w':
    glutIgnoreKeyRepeat('w');
    user.holdUp = false;
    break;
    case 's':
    glutIgnoreKeyRepeat('s');
    user.holdDown = false;
    break;
  }
}

void refresh(int value) {
  // _angle += 1.0;
  // if (_angle > 360) {
  //   _angle -= 360;
  // }

  // _slowback -= 0.01;

  // passing a generic time delta
  user.move(0.1);

  glutPostRedisplay(); //Tell GLUT the scene had changed

  //Tell glut to call the update again in 16 milliseconds
  glutTimerFunc(16, refresh, 0);
}

void idleFunc() {
  glutPostRedisplay();
}


int main(int argc, char** argv) {
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

  glutInitWindowSize(600, 400);
  glutCreateWindow("2D Movement Test");
  initRendering();

  // ###### HANDLER FUNCTIONS ######
  glutDisplayFunc(display);

  // Input handlers
  glutKeyboardFunc(keyboard);
  glutKeyboardUpFunc(keyboardUp);

  glutReshapeFunc(handleResize);
  glutTimerFunc(16, refresh, 0);
  glutIdleFunc(idleFunc);

  glutMainLoop();
  return (0);
}

//g++ movement_test.cpp -o test -lglut -lGLU -lGL
