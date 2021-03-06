#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#in

#define PATH_LENGTH -100
#define CAMERA_HEIGHT 5
#define CAMERA_Z_OFFSET -3
#define CAMERA_SENSITIVITY .1
#define JUMP_INTENSITY .05
#define GRAVITY .005

typedef enum {
  TRACK_LEFT,
  TRACK_RIGHT,
  TRACK_MIDDLE
} Track;

typedef struct ballPosition_ {
  double x;
  double y;
  double z;
  Track t;
  
} BallPosition;

//MODEL
BallPosition ballPosition;
double movVector[3];
double backLine = 0;
double frontLine = 10;
double dropLine = 20;
double cameraPosition[3];


void initModel();

void initGL();
void drawTriangle();
void render();
void onKeyboard(unsigned char c , int x , int y);
void onSpecial(int key, int x, int y);

void commandLeft();
void commandRight();
void commandBack();
void commandForward();
void commandJump();

void commandCameraUp();
void commandCameraDown();
void commandCameraLeft();
void commandCameraRight();

void drawPath();
void drawBall();
void drawObstacles();

int main(int argc, char** argv)
{
  glutInit(&argc, argv);

  glutInitWindowSize(1600, 900);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("ball-jump");

  initModel();
  initGL();

  glutSpecialFunc(onSpecial);
  glutDisplayFunc(render);
  glutKeyboardFunc(onKeyboard);
  
  glutMainLoop();

  return EXIT_SUCCESS;
}


void initGL()
{
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

  glEnable(GL_DEPTH_TEST);

  glClearColor(0, 0, 0, 0);

  //perspective
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, 16 / (float) 9, 1, 1000);
  glMatrixMode(GL_MODELVIEW);
  //path je 3m pa stavljamo po sredini
  //stavljamo neki offset na
  //staza je na 0  
  
}

void render()
{
  //postavimo pogle kamere za svako crtanje
  glLoadIdentity();
  gluLookAt(cameraPosition[0], cameraPosition[1], cameraPosition[2],
	    1.5, 0, ballPosition.z - 5,
	    0, 1, 0);

  //radimo updejt modela
  if(movVector[0]) {
    ballPosition.x += movVector[0];
  }
  if(movVector[1]) {
    ballPosition.y += movVector[1];
  }
  if(movVector[2]) {
    ballPosition.z += movVector[2];
  }
  
  if(ballPosition.y){
    movVector[1] -= GRAVITY;
    if(ballPosition.y < 0) ballPosition.y = 0;
  }
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glColor3f(1, 0, 0);
  drawPath();
  drawBall();
  drawObstacles();
  
  glutSwapBuffers();
  glutPostRedisplay();
}


void onSpecial(int key, int x, int y)
{
  switch(key) {
  case GLUT_KEY_LEFT: //lijevo
    commandCameraLeft();
    break;
  case GLUT_KEY_RIGHT: //desno
    commandCameraRight();
    break;

  case GLUT_KEY_DOWN: //nazad
    commandCameraDown();
    break;

  case GLUT_KEY_UP: //napred
    commandCameraUp();
    break;
  } 
}

void onKeyboard(unsigned char c, int x, int y)
{
  switch(c) {
  case 'o': //lijevo
    commandLeft();
    break;
  case 'u': //desno
    commandRight();
    break;

  case 'e': //nazad
    commandBack();
    break;

  case '.': //napred
    commandForward();
    break;
  case ' ':
    commandJump();
    break;
    
  }
}

void commandLeft()
{
  
}
void commandRight()
{

}
void commandBack()
{

}
void commandForward()
{

}
void commandJump()
{
  movVector[1] = JUMP_INTENSITY;
}
void initModel()
{
  //na pocetku u sredini
  ballPosition.x = 1.5;
  ballPosition.y = .5;
  ballPosition.z = backLine;

  movVector[0] = 0;
  movVector[1] = 0;
  movVector[2] = 0;
  
  cameraPosition[0] = 1.5;
  cameraPosition[1] = CAMERA_HEIGHT;
  cameraPosition[2] = ballPosition.z - CAMERA_Z_OFFSET;
}

void commandCameraUp()
{
  cameraPosition[2] += CAMERA_SENSITIVITY;
}
void commandCameraDown()
{
  cameraPosition[2] -= CAMERA_SENSITIVITY;
}
void commandCameraLeft()
{
  cameraPosition[0] -= CAMERA_SENSITIVITY;
}
void commandCameraRight()
{
  cameraPosition[0] += CAMERA_SENSITIVITY;
}

void drawPath()
{ //ovi su uvijek u ravni pa ne mora triangles. Nema transformacija nad stazom

  //lijeva staza
  glColor3f(1, 0, 0);
  glBegin(GL_QUADS);
  glVertex3i(0, 0, 0);
  glVertex3i(1, 0, 0);
  glVertex3i(1, 0, PATH_LENGTH);
  glVertex3i(0, 0, PATH_LENGTH);
  glEnd();

  //srednja staza
  glColor3f(0, 1, 0);
  glBegin(GL_QUADS);
  glVertex3i(1, 0, 0);
  glVertex3i(2, 0, 0);
  glVertex3i(2, 0, PATH_LENGTH);
  glVertex3i(1, 0, PATH_LENGTH);
  glEnd();

  //desna staza
  glColor3f(0, 0, 1);
  glBegin(GL_QUADS);
  glVertex3i(2, 0, 0);
  glVertex3i(3, 0, 0);
  glVertex3i(3, 0, PATH_LENGTH);
  glVertex3i(2, 0, PATH_LENGTH);
  glEnd();

}
void drawBall()
{
  glColor3f(1, .5, 1);
  glPushMatrix();

  glTranslatef(ballPosition.x, ballPosition.y, ballPosition.z);
  glutSolidSphere(.5, 10, 10);

  glPopMatrix();
}
void drawObstacles()
{

}
