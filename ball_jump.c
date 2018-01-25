#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>

static void on_display(void);
static void on_keybord(unsigned char key,int x, int y);
static void on_timer(int value);


//kordinate lopte
double transX=0.8;
double transY=-0.8;
double transZ=0;

int action_time=25;

//vrednos za koje se lopta pomera napred ili nazad
double epsilon=0.05;
int action1=1;
int value=0;
float eps=0.03;


int main(int argc,char **argv){
	//inicijalizacija gluta 	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE | GLUT_DEPTH);
	
	//kreiranje prozora 
	glutInitWindowSize(800, 400);
    	glutInitWindowPosition(100, 100);
    	glutCreateWindow(argv[0]);
	
	/*funkcija za poziv scene koja ce da se desava na pozornici on_display*/	
	glutDisplayFunc(on_display);	
	//funkcija za tastere
	glutKeyboardFunc(on_keybord);
	//OPEN GL Inicijalizacija 	
	glClearColor(0.75, 0.75, 0.75, 0);

	//Program ulazi u glavnu petlju
	glutMainLoop();
return 0;
}

static void on_display(void){
	// brisanje postojece pozadine 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//pusujemo jedinicnu maticu na stek 
	glPushMatrix();
	glColor3f(0.33,0.5,0.25);
	// dati kordinatni sistem transliramo za dati vektor
	glTranslatef(transX,transY,transZ);
	//iscrtavamo sveru u translirani kordinatni sistem
    	glutSolidSphere(0.06,20,20);
	glPopMatrix();
        
	//iscrtavanje trake koja ce da simuluira pokretnu traku 		
	glPushMatrix();
	 glColor3f(0,1,0);
	 glTranslatef(0,-0.87,0);
	 glScalef(2,1,0);
	 glBegin(GL_LINE_STRIP);
          glVertex3f(0.5,0,0.3);
	  glVertex3f(0.5,0,-0.3);
	  glVertex3f(-0.5,0,-0.3);
	  glVertex3f(-0.5,0,0.3);	
	 glEnd();
	glPopMatrix();
        
        //iscrtava se kocka na mesto gde treba doci cunak 
	glPushMatrix();
	glColor3f(1,1,0.5);
	glTranslatef(-0.9,0.6,1);
	glutSolidCube(0.2);	
	glPopMatrix();
	
     	glutSwapBuffers();

}
static void on_keybord(unsigned char key,int x, int y){

	switch(key){
	case 27:
	exit(0);
	break;
	case 'a':
	case 'A':
	if(transX>(-1+0.07)){
		transX-=epsilon;}
	 glutPostRedisplay();
	break;
	case 'd':
	case 'D':
	if(transX<(1-0.09)){
		transX+=epsilon;}
	 glutPostRedisplay();
	break;
	case 'w':
	case 'W':
		if(action1){
		action1=0;
		value=0;
		glutTimerFunc(action_time,on_timer, value);
		   }
	break;
	
	case 's':
	case 'S':
	printf("ssss");
		break;	
}

}
static void on_timer(int value)
{
    /* Proverava se da li callback dolazi od odgovarajuceg tajmera. */
    if (value != 0)
        return;

    /* Azurira se vreme simulacije. */
	if(!action1){
	 	
	  transY+=eps;
	  /*if(transX<(1+0.07) && transX>(-1+0.07))	
	  	transX-=epss;*/
	  if(transY>-0.2)
		 action1=1;		
	}
       else {    
		transY-=eps;
	/*if(transX<(1+0.07) && transX>(-1+0.07))
		transX-=epss;*/
	     if(transY<-0.8){
		transY=-0.8;
		value=1;}
			}
	
    /* Forsira se ponovno iscrtavanje prozora. */
    glutPostRedisplay();

    /* Po potrebi se ponovo postavlja tajmer. */
    
        glutTimerFunc(action_time, on_timer, value);
}

