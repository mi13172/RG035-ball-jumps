#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<math.h>


static void on_reshape(int width, int height);
static void on_display(void);
static void on_keybord(unsigned char key,int x, int y);
static void on_timer(int value);
static void on_timer1(int value);
static void on_display1(void);
void functionstop(double transX,double transY,double transX1,double transY1);
static void osvetljenje(void);
//kordinate lopte
double transX=1.5;
double transY=-0.8;
double transZ=0;



//kordinate prvog objekta
double transX1=-1.5;
double transY1=0.6;
double transZ1=0;

//vreme za koje se tajmeri pozivaju
double action_time=50;
double action_time1=50;

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
float eps=0.02;
float gra=0.08;
float epss=0.06;

//promenjive koje opisuju loptu 
double korSphere=0.06;
int brOkz=20;
int brOkz1=20;

int main(int argc,char **argv){
	//inicijalizacija gluta 	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA| GLUT_DOUBLE | GLUT_DEPTH);
	
	//kreiranje prozora 
	glutInitWindowSize(800, 400);
    	glutInitWindowPosition(100, 100);
    	glutCreateWindow(argv[0]);
	
	
	/*funkcija za poziv scene koja ce da se desava na pozornici on_display*/	
	glutDisplayFunc(on_display);	
	//funkcija za tastere
	glutKeyboardFunc(on_keybord);
	 //funkcija za skaliranje prozora i podesavanje proekcije
	glutReshapeFunc(on_reshape);
	glutTimerFunc(action_time1,on_timer1, value1);
	
	//OPEN GL Inicijalizacija 
	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);
    	glEnable(GL_CULL_FACE);
	//Program ulazi u glavnu petlju
	glutMainLoop();
return 0;
}

static void on_display(void){
	// brisanje postojece pozadine 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//pozicioniranje kamere 
	glMatrixMode(GL_MODELVIEW);
    	glLoadIdentity();
	gluLookAt(0,2,3.5, 0,-0.1,0, 0, 0.1, 0);	
	
     	//boja lopte
	osvetljenje();
	
	glDisable(GL_LIGHTING);
	//pusujemo jedinicnu maticu na stek 
	glPushMatrix();
	glColor3f(0.5,0.5,0);
	// dati kordinatni sistem transliramo za dati vektor
	glTranslatef(transX,transY,transZ);
	//iscrtavamo sveru u translirani kordinatni sistem
    	glutSolidSphere(korSphere,brOkz,brOkz1);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	
	//iscrtava se kocka koja predstavlja cunak
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glColor3f(0,1,0);
	glTranslatef(-1.5,0.6,0);
	glutSolidCube(0.2);	
	glPopMatrix();
	glEnable(GL_LIGHTING);	
        
	//Iscrtavanje staze koja ce predstavljati pokretnu traku 
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glColor3f(0,0.1,0);
	glTranslatef(0,-0.87,0);
	glBegin(GL_TRIANGLE_STRIP);
         glVertex3f(2.5,0,0.1);
	 glVertex3f(2.5,0,-0.1);
	 glVertex3f(-2.5,0,-0.1);
	 glVertex3f(-2.5,0,0.1);
         glVertex3f(2.5,0,0.1);
	glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);	
	
glDisable(GL_LIGHTING);
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
	  if(transX1>2.5){
	     transX1=-1.5;
	     transY1=0.6;	
	     action2=1;
	    
			}
	  }
	functionstop(transX,transY,transX1,transY1);	
	glEnable(GL_LIGHTING);
     	glutSwapBuffers();

}
static void on_keybord(unsigned char key,int x, int y){

	switch(key){
	case 27:
	exit(0);
	break;
	case 'a':
	case 'A':
	 if(action3)
	if(transX>(-2.3+0.07)){
		transX-=epsilon;
	
	}
	 
	break;
	case 'd':
	case 'D':
	if(action3)
	if(transX<(2.3-0.09)){
		transX+=epsilon;
	}
	 
	break;
	case 'w':
	case 'W':
		if(action1 && action3){
		action1=0;
		value=0;
		glutTimerFunc(action_time,on_timer, value);
		   }
	break;
	
		
}

}
static void on_reshape(int width, int height)
{
    /* Podesava se viewport. */
    glViewport(0, 0, width, height);

    /* Podesava se projekcija. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30, (float) width / height,1, 100.0);
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
    if(action_time>3)
	action_time-=0.005;

    /* Po potrebi se ponovo postavlja tajmer. */
    
        glutTimerFunc(action_time, on_timer, value);
}
static void on_timer1(int value){
	 /* Proverava se da li callback dolazi od odgovarajuceg tajmera. */
    if (value1 != 0)
        return;

    /* Azurira se vreme simulacije. */
	eps=0.05;
    /* Forsira se ponovno iscrtavanje prozora. */
    glutPostRedisplay();
   
    /* Po potrebi se ponovo postavlja tajmer. */
   
	
	if(action_time1>4)
		action_time1-=0.0001;
       
	glutTimerFunc(action_time1, on_timer1, 0);

}
void functionstop(double transX,double transY,double transX1,double transY1){
	
  if((transX1+0.06>=transX-0.06 && transX+0.06>=transX1-0.06) && transY1+0.01>=transY ){
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

//funkcija za osvetljenje koja je kopirana iz knjige red book
static void osvetljenje(void){
   GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
   GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat light_specular[] = { 0.5, 0.5, 0.4, 0.7 };
   GLfloat light_position[] = { 0.5, 0.4, 0.3, 0.2 };

  
   GLfloat mat_ambient[] = { 0.2, 0.6, 0.7, 0.5 };
   GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat mat_emission[] = {0.3, 0.2, 0.2, 0.0};

   glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
   glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  
   glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_ambient);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_specular);
   glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
}

