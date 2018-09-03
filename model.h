#ifndef MODEL_H
#define MODEL_H
#define PATH_LENGTH -100
#define CAMERA_HEIGHT 5
#define CAMERA_Z_OFFSET -3
#define CAMERA_SENSITIVITY .1
#define JUMP_INTENSITY .05
#define GRAVITY .0005
#define FRICTION .0001
#define X_INTENSITY .01
#define BALL_RADIUS .5
//f-ja parametra brojSekundi kad je TIME_DIVIDER manji ka 0 f-ja raste
//ne manje od 0 i sto je manji parametar to je teza igra
#define DIFICULTY_TIME_DIVIDER 10
#define DIFICULTY_ITEM_NUMBER 10
#define DIFICULTY_FREQUENCY 1000


#define MAX_PREDMETA 100000

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
extern double DIFICULTY_SPEED_INITIAL;
extern double DIFICULTY_SPEED;

extern BallPosition ballPosition;
extern double movSpeed;
extern double movVector[3];
extern short sgnMovVecX;

extern double backLine;
extern double frontLine;
extern double dropLine;
extern double cameraPosition[3];

extern int brojSekundi;

extern double predmeti[MAX_PREDMETA][3];
extern int brojPredmeta;

extern int poceteniIndex;
extern int krajnjiIndex;
extern int jePopunjeno;

void initModel();

#endif
