#include <GL/glut.h>
#include "model.h"


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
  glutSolidSphere(BALL_RADIUS, 20, 20);

  glPopMatrix();
}
void drawObstacles()
{
  for(int i = poceteniIndex; i < krajnjiIndex; i++, i %= MAX_PREDMETA) {
    glPushMatrix();
    glTranslatef(predmeti[i][0] + .5,
		predmeti[i][1] + .5,
		predmeti[i][2]);
    glutSolidCube(1);
    glPopMatrix();
  }
}
