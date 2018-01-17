#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>

static void on_display(void);

//kordinate lopte
double transX=0.8;
double transY=-0.8;
double transZ=0;


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
     
     	glutSwapBuffers();

}

