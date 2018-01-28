#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>

static void on_display(void);
static void on_keybord(unsigned char key,int x, int y);
static void on_timer(int value);
static void on_timer1(int value);
static void on_display1(void);
void functionstop(double transX,double transY,double transX1,double transY1);

//kordinate lopte
double transX=0.8;
double transY=-0.8;
double transZ=0;

//kordinate lopte koja  ce simulirati kretnju 

double transX1=-0.9;
double transY1=0.6;
double transZ1=0;

//vreme za koje se tajmeri pozivaju
int action_time=30;
int action_time1=50;

//vrednos za koje se lopta pomera napred ili nazad
double epsilon=0.05;

//predstavljanje akcije po koja ce da znaci da li se lopta spusta ili se krece po traci
int action1=1;
int action2=1;
int action3=1;
//vrednost za tajmer
int value=0;
int value1=0;
//pokretanje lopte
double eps=0.03;
double epss=0.08;

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
	 
	glutTimerFunc(action_time1,on_timer1, value1);
	
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
	
	 on_display1();
       if(action2){
	  transY1-=eps;
 	  if(transY1<-0.8){
	  transY1=-0.80;
	  action2=0;
			  }
	         }
       else{
          transX1+=eps;
	  if(transX1>1){
	     transX1=-0.9;
	     transY1=0.6;	
	     action2=1;
			}
	  }
	 functionstop(transX,transY,transX1,transY1);		
	
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
		if(action1 & action3){
		action1=0;
		value=0;
		glutTimerFunc(action_time,on_timer, value);
		   }
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
	 	
	  transY+=epss;
	  /*if(transX<(1+0.07) && transX>(-1+0.07))	
	  	transX-=epss;*/
	  if(transY>-0.2)
		 action1=1;		
	}
       else {    
		transY-=epss;
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
static void on_timer1(int value){
	 /* Proverava se da li callback dolazi od odgovarajuceg tajmera. */
    if (value1 != 0)
        return;

    /* Azurira se vreme simulacije. */
	eps=0.03;
    /* Forsira se ponovno iscrtavanje prozora. */
    glutPostRedisplay();
   
    /* Po potrebi se ponovo postavlja tajmer. */
    
	
	if(action_time1>4)
		action_time1-=0.0001;
       
	glutTimerFunc(action_time1, on_timer1, value);

}
void functionstop(double transX,double transY,double transX1,double transY1){
	
  if((transX1+0.06>=transX-0.06 && transX+0.06>=transX1-0.06) && transY1+0.01>=transY ){
	printf("usao je :\n");	
	value1=1;
	value=1;
	action3=0;		
	}
		
};
static void on_display1(void){
	glPushMatrix();
	glColor3f(1,0,0);
	glTranslatef(transX1,transY1,transZ1);
	
    	glutSolidTeapot(0.06);

	
	glPopMatrix();

}
