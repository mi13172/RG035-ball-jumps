#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<math.h>

#define PI acos(-1)
//funkcia za skaliranje prozora , kako bi tela ostala istog oblika   
static void on_reshape(int width, int height);
//osnovne funkcije za pozivanje prozora i iscrtavanje na istom
static void on_display(void);
//funkcija za rad sa tastaturom
static void on_keybord(unsigned char key,int x, int y);
//funkcije za tajmere
static void on_timer(int value);
static void on_timer1(int value);
static void on_timer2(int value);
//iscrtavanja tela koja ce se kretati 
static void on_display1(void);
static void on_display2(void);
static void on_display3(void);
static void on_display4(void);
static void on_display5(void);
static void on_display6(void);
static void on_display7(void);
static void on_display8(void);
//bedzevi u tri razlicite boje koji ce imati istu ulogu 
static void zeton1(void);
static void zeton2(void);
static void zeton3(void);
//funkcija koja predstavlja pucaljku 
static void pucaljka(void);
//funkcije za izvlacenje random broja koji ce da popunjava niz uz pomoc kog ce se generisati random predmeti
int functionRound();
int functionRound1();
//funkcije za iscrtavanje objekata na pokretnoj traci
void iscrtavanje();
//funkcija koja opisuje sta se desava kada se sudati loptica sa datim predmetom na traci
void functionstop(double transX,double transY,double transX12,double transY12);
//funkcija koja ako loptica prede preko bedza povecava brojac pucaljki za 1 
void brojPucaljki(double X12,double Y12,double transX12,double transY12);
//ako ispalimo pucaljku , ova funkcija nam sluzi za ispitivanje da li je udarila u predmet
void funkcijZaPogadjanjeObjekta(double transX12,double transY12,double transX123,double transY123,int *niz,int k);
//funkcija za osvetljenje
static void osvetljenje(void);



int i=1;
int j;
//parametri koji sluze za kretanje lopte i ostalih objekata na traci 
float eps;
float gra=0.08;
float epss=0.06;
float eps1;
//promenjive koje cuvaju vreme kako bi smo ravnomerno generisali predmete 
long int vreme=0;
long int vreme1=0;
//promenjive za tajmere
static double p= -0.5;
double action_time=50;
double action_time1=50;
int action_time2=50;
// kordinate na kojima se nalazi metak za pcaljku
double X1=-2.7;
double Y1=-0.5;
double Z1=0;
//kordinate zetona 
double X=-2.3;
double Y=-0.8;
double Z=0;
//parametri koji predstavljaju akcije
int action1=1;
int action2=1;
int action3=1;
int action4=1;
int action5=1;
int action6=1;
int action7=1;
int action8=1;
int action9=1;
int action10=1;
int action11=1;
//vrednosti uz pomoc kojih zaustavljamo tajmere 
int value=0;
int value1=0;
int value2=0;
//kordinate loptice koja skace 
double transX=1.5;
double transY=-0.8;
double transZ=0;
double epsilon=0.03;
//kordinate prvog objekta
double transX10=-1.5;
double transY10=0.6;
double transZ10=0;
//kordinate drugog objekta
double transX2=-1.5;
double transY2=0.6;	
double transZ2=0;
//kordinate treceg objekta
double transX3=-1.5;
double transY3=0.6;
double transZ3=0;
//kordinate cetvrtog objekta
double transX4=-1.5;
double transY4=0.6;
double transZ4=0;
//kordinate petog objekta
double transX5=-1.5;
double transY5=0.6;
double transZ5=0;
//kordinate sesti objekat
double transX6=-1.5;
double transY6=0.6;
double transZ6=0;
//kordinate sedmog objekat
double transX7=-1.5;
double transY7=0.6;
double transZ7=0;
//kordinate sedmog objekat
double transX8=-1.5;
double transY8=0.6;
double transZ8=0;
//provera se odnosi na dati bedz koji ce se kretati
int provera=0;
int pokreni_pucaljku=0;
//kordinate nase lopte 
double korSphere=0.06;
int brOkz=20;
int brOkz1=20;
int pr=1;
int n=21;
int brojac_pucaljki=0;
//niz za pojavljivanje objekata na traci 
int niz[9]={0,0,0,0,0,0,0,0,0};
//niz bedzeva
int niz1[3]={0,0,0};
int main(int argc,char **argv){
	//inicijalizacija gluta 	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	
	//kreiranje prozora 
	glutInitWindowSize(800, 400);
    	glutInitWindowPosition(100, 100);
    	glutCreateWindow(argv[0]);
	glutKeyboardFunc(on_keybord);
	
	/*funkcija za poziv scene koja ce da se desava na pozornici on_display*/	
	glutDisplayFunc(on_display);
	//funkcia za skaliranje 
	glutReshapeFunc(on_reshape);	
	//funkcija za tajmer
	glutTimerFunc(action_time1, on_timer1, value1);
	//OPEN GL Inicijalizacija 	
	glClearColor(0, 0, 0, 0);
	
    	glEnable(GL_DEPTH_TEST);
    	glEnable(GL_CULL_FACE);
	

	
	//Program ulazi u glavnu petlju
	glutMainLoop();
return 0;
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


static void on_display(void){
	// brisanje postojece pozadine 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	osvetljenje();
	
	//podesavanje kamere 
	glMatrixMode(GL_MODELVIEW);
    	glLoadIdentity();
	gluLookAt(0,2,3.5, 0,-0.1,0, 0, 0.1, 0);	
	
     	//iscrtavanje lopte
	glDisable(GL_LIGHTING);
	glPushMatrix();
	 glColor3f(0.5,0.5,0);
	 glTranslatef(transX,transY,transZ);
	 glutSolidSphere(korSphere,brOkz,brOkz1);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	
	//iscrtavanje kocke koja ce da predstavlja cunak
	glDisable(GL_LIGHTING);
	glPushMatrix();
	 glColor3f(0,1,0);
	 glTranslatef(-1.5,0.6,0);
	 glutSolidCube(0.2);	
	glPopMatrix();
 
	//iscrtavanje trake 
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
	
	/*provere uz pomoc kojih ce se menjati vrednost niza
	  na 1 sto ce dozvoliti da se iscrta prvi predmet*/
	if(vreme>2200)
		vreme=30;
	if(vreme>0 && vreme<31){
	   while (niz[i] || i==0){
	    i=functionRound();
	  		         }
	   niz[i]=1;
                              }
     	if(vreme>749 && vreme <751){
	   while (niz[i] || i==0){
	    i=functionRound();
	  	                 }
	   niz[i]=1;		
		                   }
	if(vreme>1499 && vreme <1501){
	   while (niz[i] || i==0){
	     i=functionRound();
		                }
	   niz[i]=1;
  				      }
	/*provere za bedzeve radi isto kao navedene provere iznad samo se puni niz1*/
	if(vreme1>8999 && vreme1<9001){
	   j=functionRound1();		
	   niz1[j]=1;
	   glutTimerFunc(action_time2, on_timer2, value2);
	   value2=0;
				      }
	/*pozivanje funkcije za iscrtavanje datih predmeta*/
	glDisable(GL_LIGHTING);
		iscrtavanje();
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
			transX-=0.03;
				      }
	break;
	case 'd':
	case 'D':
	if(action3)
		if(transX<(2.3-0.09)){
			transX+=0.03;
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
	case 's':
	case 'S':
		if(brojac_pucaljki){
	 		brojac_pucaljki--;
			pokreni_pucaljku=1;
			X1=transX;
			Y1=transY;	
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
	  if(transY>-0.2)
		 action1=1;		
	       	    }
       else{    
	   transY-=epss;
	   if(transY<-0.8){
	   	transY=-0.8;
		value=1;
			 }
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
	eps1=0.04;	
	eps=0.05;
    /* Forsira se ponovno iscrtavanje prozora. */
    glutPostRedisplay();
   
    /* Po potrebi se ponovo postavlja tajmer. */
    vreme+=30;
    vreme1+=30;		
	if(action_time1>4)
		action_time1-=0.0001;
       
	glutTimerFunc(action_time1, on_timer1, 0);

}
static void on_timer2(int value){
	 /* Proverava se da li callback dolazi od odgovarajuceg tajmera. */
    if (value2 != 0)
        return;

    /* Azurira se vreme simulacije. */
	eps1=0.04;	
	
    /* Forsira se ponovno iscrtavanje prozora. */
   
   
    /* Po potrebi se ponovo postavlja tajmer. */
    vreme1+=30;		
	
       
	glutTimerFunc(action_time2, on_timer2, 0);

}


void functionstop(double transX,double transY,double transX12,double transY12){
	
  if((transX12+0.06>=transX-0.06 && transX+0.06>=transX12-0.06) && transY12+0.01>=transY ){
	value1=1;
	value=1;
	action3=0;		
	}
		
}
void brojPucaljki(double X12,double Y12,double transX12,double transY12){
	
  if((transX12+0.06>=X12-0.06 && X12+0.06>=transX12-0.06) && transY12+0.01>=Y12){
	X=-2.4;
        Y=-0.8;
	niz1[j]=0;
	provera=0;
	vreme1=0;
	value2=1;
	if(!brojac_pucaljki){
		brojac_pucaljki++;
		}	
	}
		
}
void funkcijZaPogadjanjeObjekta(double transX12,double transY12,double transX123,double transY123,int *niz,int k){
	
  if((transX123+0.02 >=transX12-0.02 && transX12+0.02>=transX123-0.02) && transY123+0.13>=transY12){
	niz[k]=0;
	X1=-2.7;
	Y1=-0.5;		
	}
		
}
static void on_display1(void){
	glPushMatrix();
	glColor3f(1,0,0);
	glTranslatef(transX10,transY10,transZ10);
	
    	glutSolidTeapot(0.06);

	
	glPopMatrix();

}
static void on_display2(void){
	glPushMatrix();
	 glColor3f(0.4,0.6,0.3);
	 glTranslatef(transX2,transY2,transZ2);
	 glRotatef(270,1,0,0);
    	 glutSolidCone(0.065, 0.2, 22,21);
	glPopMatrix();
}
static void on_display3(void){
	glPushMatrix();
	 glColor3f(0.5,0.5,0.5);
	 glTranslatef(transX3,transY3,transZ3);
    	 glutSolidSphere(0.06,20,20);
	glPopMatrix();
}
static void on_display4(void){
	glPushMatrix();
	 glColor3f(0.3,0.1,0.5);
	 glTranslatef(transX4,transY4,transZ4);
    	 glutSolidCube(0.12);
	glPopMatrix();
}
static void on_display5(void){
	glPushMatrix();
	 glColor3f(1,1,0);
	 glTranslatef(transX5,transY5,transZ5);
    	 glutWireTeapot(0.06);
	glPopMatrix();
}
static void on_display6(void){
	glPushMatrix();
	 glColor3f(0.7,0.1,0.3);
	 glTranslatef(transX6,transY6,transZ6);
	 glRotatef(270,1,0,0);
    	 glutSolidCone(0.065, 0.2, 22,21);	
	glPopMatrix();
}
static void on_display7(void){
	glPushMatrix();
	 glColor3f(0.4,0.4,0.9);
	 glTranslatef(transX7,transY7,transZ7);
    	 glutSolidCube(0.12);
	glPopMatrix();

}
static void on_display8(void){
	glPushMatrix();
	 glColor3f(0.7,0.7,0.2);
	 glTranslatef(transX8,transY8,transZ8);
    	 glutSolidSphere(0.06,20,20);
	glPopMatrix();

}
static void zeton1(void){
    glPushMatrix();
     glTranslatef(X,Y,Z);
     glColor3f(0.4,0.8,0.3);
     glutSolidSphere(0.04,20,20);
    glPopMatrix();
}
static void zeton2(void){
    glPushMatrix();
     glTranslatef(X,Y,Z);
     glColor3f(0.7,0.7,0.7);
     glutSolidSphere(0.04,20,20);
    glPopMatrix();
}
static void zeton3(void){
    glPushMatrix();
     glTranslatef(X,Y,Z);
     glColor3f(0.5,0.2,0.2);
     glutSolidSphere(0.04,20,20);
    glPopMatrix();
}
static void pucaljka(void){
    glPushMatrix();
     glColor3f(0.7,0,0.8);
     glTranslatef(X1,Y1,Z1);
     glutSolidCube(0.05);
    glPopMatrix();
}
int functionRound(){ 
	return rand() % 9;	
}
int functionRound1(){ 
	return rand() % 3;	
}
void iscrtavanje(){
	
	if(niz1[0]){
	        zeton1();
		provera=1;
		}
	if(niz1[1]){
		zeton2();
		provera=1;
		   }
	if(niz1[2]){
		zeton3();
			provera=1;
		}			
	
	if(provera){
	        if(!action11){
	           Y+=eps1;
                   X+=0.04;
	           if(Y>-0.3)
		      action11=1;
	                     }
                else {    
		   Y-=eps1;
                   X+=0.04;
	           if(Y<-0.8){
			Y=-0.8;
			action11=0;
                             }
                    if(X>2.4){ 
                        X=-2.0;
                 	Y=-0.8;
			niz1[j]=0;
			provera=0;
			vreme1=0;
			value2=1;
                	     }
		      }
	brojPucaljki(X,Y,transX,transY);
	}
	
	
    if(pokreni_pucaljku){
	     pucaljka();
	     X1-=eps;
	     if(X1<-2.5){
	           pokreni_pucaljku=0;
	           X1=-3.0;
                   Y1=0.6;
                   Z1=0;
		       }
	               }
		
	
    if(niz[8]){
	
       on_display1();
 
       if(action2){
	  transY10-=eps;
 	  if(transY10<-0.8){
	  transY10=-0.80;
	  action2=0;
			  }
	         }
       else{
          transX10+=eps;
	  if(transX10>2.0){
	     transX10=-1.5;
	     transY10=0.6;	
	     action2=1;
	     niz[8]=0;
			}
	  }
	 functionstop(transX,transY,transX10,transY10);
	if(pokreni_pucaljku){
		funkcijZaPogadjanjeObjekta(transX10,transY10,X1,Y1,niz,0);
		}
	if(!niz[8]){
	     transX10=-1.5;
	     transY10=0.6;	
	     action2=1;
	     niz[8]=0;
		}
              }
		
    if(niz[1]){
	on_display2();
	if(action4){
	   transY2-=eps;
	   if(transY2<-0.8){
	      transY2=-0.80;
	      action4=0;
			   }
		    }

       	else{
	   transX2+=eps;
	   if(transX2>2.0){
	      transX2=-1.5;
	      transY2=0.6;	
	      action4=1;
	      niz[1]=0;
			  }
            }
	functionstop(transX,transY,transX2,transY2);
	if(pokreni_pucaljku)	
		funkcijZaPogadjanjeObjekta(transX2,transY2,X1,Y1,niz,1);
	if(!niz[1]){
	     transX2=-1.5;
	     transY2=0.6;	
	     action4=1;
	     niz[1]=0;
		}		
		}
    if(niz[2]){
       on_display3();
       if(action5){
	  transY3-=eps;
	  if(transY3<-0.8){
	     transY3=-0.80;
	     action5=0;
	                  }
	           }
       else{
	   transX3+=eps;
	   if(transX3>2.0){
	      transX3=-1.5;
	      transY3=0.6;	
	      action5=1;
	      niz[2]=0;
			  }
	    }
		
      functionstop(transX,transY,transX3,transY3);
      if(pokreni_pucaljku)		      
	funkcijZaPogadjanjeObjekta(transX3,transY3,X1,Y1,niz,2);
      if(!niz[2]){
	     transX3=-1.5;
	     transY3=0.6;	
	     action5=1;
	     niz[2]=0;
		}		     
	 }
    if(niz[3]){
       on_display4();
       if(action6){
	  transY4-=eps;
	  if(transY4<-0.8){
	     transY4=-0.80;
	     action6=0;
		          }
	           }
       else{
	   transX4+=eps;
	   if(transX4>2.0){
	      transX4=-1.5;
	      transY4=0.6;	
	      action6=1;
	      niz[3]=0;
	                   }
	    }
		
	functionstop(transX,transY,transX4,transY4);
	if(pokreni_pucaljku)	
		funkcijZaPogadjanjeObjekta(transX4,transY4,X1,Y1,niz,3);                
	if(!niz[3]){
	     transX4=-1.5;
	     transY4=0.6;	
	     action6=1;
	     niz[3]=0;
		   }	
		}
    if(niz[4]){
       on_display5();
       if(action7){
	  transY5-=eps;
	  if(transY5<-0.8){
	     transY5=-0.80;
	     action7=0;
		          }
	          }
       else{
	  transX5+=eps;
	  if(transX5>2.0){
	     transX5=-1.5;
	     transY5=0.6;	
	     action7=1;
	     niz[4]=0;
			}
	   }
		
	functionstop(transX,transY,transX5,transY5);
	if(pokreni_pucaljku)		
		funkcijZaPogadjanjeObjekta(transX5,transY5,X1,Y1,niz,4);	
        if(!niz[4]){
	     transX5=-1.5;
	     transY5=0.6;	
	     action7=1;
	     niz[4]=0;
		}      
		 }
    if(niz[5]){
       on_display6();
       if(action8){
	  transY6-=eps;
	  if(transY6<-0.8){
	     transY6=-0.8;
	     action8=0;
		          }
	          }
       else{
	  transX6+=eps;
	  if(transX6>2.0){
	     transX6=-1.5;
	     transY6=0.6;	
	     action8=1;
	     niz[5]=0;
			}
	   }	
	functionstop(transX,transY,transX6,transY6);
	if(pokreni_pucaljku)
		funkcijZaPogadjanjeObjekta(transX6,transY6,X1,Y1,niz,5);
	if(!niz[5]){
	     transX6=-1.5;
	     transY6=0.6;	
	     action8=1;
	     niz[0]=0;
		}        
	      }
     if(niz[6]){
	on_display7();
	if(action9){
	   transY7-=eps;
	   if(transY7<-0.8){
	      transY7=-0.80;
	      action9=0;
		           }
	           }
        else{
	   transX7+=eps;
	   if(transX7>2.0){
	      transX7=-1.5;
	      transY7=0.6;	
	      action9=1;
	      niz[6]=0;
			  }
	   }
       functionstop(transX,transY,transX7,transY7);
       if(pokreni_pucaljku)       
       		funkcijZaPogadjanjeObjekta(transX7,transY7,X1,Y1,niz,6);
       if(!niz[6]){
	     transX7=-1.5;
	     transY7=0.6;	
	     action9=1;
	     niz[6]=0;
		}	
		}

	if(niz[7]){
       on_display8();
       if(action10){
	  transY8-=eps;
 	  if(transY8<-0.8){
	  transY8=-0.80;
	  action10=0;
			  }
	         }
       else{
          transX8+=eps;
	  if(transX8>2.0){
	     transX8=-1.5;
	     transY8=0.6;	
	     action10=1;
	     niz[7]=0;
			}
	  }
	 functionstop(transX,transY,transX8,transY8);
	 if(pokreni_pucaljku)	
		  funkcijZaPogadjanjeObjekta(transX8,transY8,X1,Y1,niz,7);
	 if(!niz[7]){
	     transX8=-1.5;
	     transY8=0.6;	
	     action10=1;
	     niz[7]=0;
		   }              
	          }
	}

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
