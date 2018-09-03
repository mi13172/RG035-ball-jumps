#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <time.h>
#include <math.h>

#include "draw.h"
#include "model.h"
#include "misc.h"
#include "commands.h"



void initGL();
void render();
void onKeyboard(unsigned char c , int x , int y);
void onSpecial(int key, int x, int y);
void onTimer(int id);
void onBacanje(int id);




int main(int argc, char** argv)
{
  glutInit(&argc, argv);

  glutInitWindowSize(1600, 900);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("ball-jump");

  initModel();
  initGL();
  //incijalizacija random generator
  srand(time(NULL));

  glutSpecialFunc(onSpecial);
  glutDisplayFunc(render);
  glutKeyboardFunc(onKeyboard);
  glutTimerFunc(1000, onTimer, 1);

  //postavljamo timer za bacanje predmeta
  glutTimerFunc(1000, onBacanje, 2);
  
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

//glavna petlja igre
void render()
{  
  //postavimo pogle kamere za svako crtanje
  glLoadIdentity();
  gluLookAt(cameraPosition[0], cameraPosition[1], cameraPosition[2],
	    1.5, 0, ballPosition.z - 5,
	    0, 1, 0);

  //radimo UPDATE modela

  //pomeramo predmete
  for(int i = poceteniIndex; i < krajnjiIndex; i++, i %= MAX_PREDMETA) {
    predmeti[i][2] += DIFICULTY_SPEED;
  }

  //dodavanje vektora pokreta lopti
  if(movVector[0]) {
    ballPosition.x += movVector[0];
  }
  if(movVector[1]) {
    ballPosition.y += movVector[1];
  }
  if(movVector[2]) {
    ballPosition.z += movVector[2];
  }

  //fixirati kameru za loput po z koord
  cameraPosition[2] = ballPosition.z - CAMERA_Z_OFFSET;

  //dodavanje gravitacije
  if(ballPosition.y){
    movVector[1] -= GRAVITY;
    if(ballPosition.y < BALL_RADIUS
       && //samo ako je lopta na stazi
       (ballPosition.x <= 3 && ballPosition.x >= 0)
       ) ballPosition.y = BALL_RADIUS;
  }
  //dodavanje trenja
  int tmp = sgnMovVecX;
  if(movVector[0]) {
    printf("%lf \n", movVector[0]);
    
    if(sgnMovVecX > 0) {
      movVector[0] -= FRICTION;
      if(movVector[0] < 0) sgnMovVecX = -1;
    }
    else {
      movVector[0] += FRICTION;
      if(movVector[0] > 0) sgnMovVecX = 1;
    }

    //korekcija
    if(tmp != sgnMovVecX) movVector[0] = 0;
  }

  //gledamo da li ima kolizije
  
  
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
  case 'a': //lijevo
    commandLeft();
    break;
  case 'd': //desno
    commandRight();
    break;

  case 's': //nazad
    commandBack();
    break;

  case 'w': //napred
    commandForward();
    break;
  case ' ':
    commandJump();
    break;
    
  }
}

void initModel()
{
  //na pocetku u sredini
  ballPosition.x = 1.5;
  ballPosition.y = BALL_RADIUS;
  ballPosition.z = backLine;

  movVector[0] = 0;
  movVector[1] = 0;
  movVector[2] = 0;
  
  cameraPosition[0] = 1.5;
  cameraPosition[1] = CAMERA_HEIGHT;
  cameraPosition[2] = ballPosition.z - CAMERA_Z_OFFSET;
}


void onTimer(int id)
{
  brojSekundi++;
  glutTimerFunc(1000, onTimer, 1);
}
void onBacanje(int id)
{
  if(id != 2) return;
  //azuriramo brzinu trako
  //DIFICULTY_SPEED = getSpeed(brojSekundi);

  //koliko kutija se baca
  int broj = getKardinalnost(brojSekundi);

  //pravimo podskup od broj clanova od 0 do 9
  int pozicije[broj];
  int brojNapravljenihKoordinata = 0;

  for(int i = 0; i < broj; i++) {
    int kandidat = rand() % 9;
    while(nizSadrzi(kandidat, pozicije, brojNapravljenihKoordinata))
      kandidat = rand() % 9;

    pozicije[i] = kandidat;
    brojNapravljenihKoordinata++;
  }

  //kopiramo podskup u niz predmeta
  for(int i = 0; i < broj; i++) {
    //da li ima mesta
    if(krajnjiIndex == poceteniIndex && jePopunjeno){ 
      fprintf(stderr, "Nema mesta za ubacivanje predmeta\n");
      exit(1);
    }
    
    int index = krajnjiIndex;
    //racunamo kordinate u xy ravni
    predmeti[index][0] = pozicije[i] % 3;
    predmeti[index][1] = pozicije[i] / 3;
    predmeti[index][2] = PATH_LENGTH;

    //kruzna korekcija indexa u nizu fixne velicine
    krajnjiIndex++;
    if(krajnjiIndex == MAX_PREDMETA) krajnjiIndex %= MAX_PREDMETA;
    if(krajnjiIndex == poceteniIndex) jePopunjeno = 1;
  }

  glutTimerFunc(getFrekvencija(brojSekundi), onBacanje, id);
}

