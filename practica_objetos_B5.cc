//**************************************************************************
// Proyecto final: Alejandro 
//**************************************************************************

#include <GL/glut.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include "objetos_B5.h"


using namespace std;

// tipos
typedef enum{CUBO, PIRAMIDE, OBJETO_PLY, ROTACION, CILINDRO, CONO, ESFERA, ROT_PLY, EXTRUSION, EXCAVADORA, DINOSAURIO} _tipo_objeto;
_tipo_objeto t_objeto=CUBO;
_modo   modo=POINTS;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Size_x,Size_y,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int Window_x=50,Window_y=50,Window_width=650,Window_high=650;


// objetos
_cubo cubo;
_piramide piramide(0.85,1.3);
_objeto_ply  ply; 
_rotacion rotacion; 
_cilindro cilindro(1,2,20);
_cono cono(1,2,20);
_esfera esfera(1,20,20);
_rotacion_ply rot_ply;
_extrusion *extrusion;
_excavadora excavadora;
_dinosaurio dinosaurio;

// _objeto_ply *ply;

// variables para la animación automática
float giro1=0;
float giro2=0;
float giro3=0;
float giro4=0;
float giro5=0;
float giro6=0;
float giro7=0;
int flag1=0;
int flag2=0;
int flag3=0;
int flag4=0;
int flag5=0;
int flag6=0;
int flag7=0;

bool pulsado=true;


// variable para activar / desactivar la segunda luz

bool segunda_luz = true;

// variable para rotación de la luz puntual

float rotacion_luz=0.0;

// variables para el estado del ratón 
int estadoRaton, xc, yc, camara=0;
float factor=1.0;
float Ancho, Alto;




//**************************************************************************
//
//***************************************************************************

void clean_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,plano_delantero, plano_traser)
//  plano_delantero>0  plano_trasero>PlanoDelantero)
glFrustum(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);
// glFrustum(-Size_x*factor,Size_x*factor,-Size_y*factor,Size_y*factor,Front_plane,Back_plane);   //////CON ESTO SE HACE PRACTICA 5 (falta factor) /////
}

//**************************************************************************
// Funcion para definir la transformación*ply1 de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
	
glDisable(GL_LIGHTING);
glLineWidth(2);
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

void draw_objects()
{

switch (t_objeto){
	case CUBO: cubo.draw(modo,1.0,0.0,0.0,5);break;
	case PIRAMIDE: piramide.draw(modo,1.0,0.0,0.0,5);break;
        case OBJETO_PLY: ply.draw(modo,1.0,0.6,0.0,5);break;
        case ROTACION: rotacion.draw(modo,1.0,0.0,0.0,5);break;
		case CILINDRO: cilindro.draw(modo,1.0,0.0,0.0,5);break;
		case CONO: cono.draw(modo,1.0,0.0,0.0,5);break;
		case ESFERA: esfera.draw(modo,1.0,0.0,0.0,5);break;
		case ROT_PLY: rot_ply.draw(modo,1.0,0.0,0.0,5);break;
        case EXTRUSION: extrusion->draw(modo,1.0,0.0,0.0,5);break;
		case EXCAVADORA: excavadora.draw(modo,1.0,0.0,0.0,5);break;
        case DINOSAURIO: dinosaurio.draw(modo,1.0,0.0,0.0,5);break;
	}

}


//**************************************************************************
// luces
//***************************************************************************

void posicion_luz2 ()
{
    GLfloat luz_posicion_2 [] = {0.0, 0, 100.0, 1.0};       // definir posición (x,y,z, w (=1 puntual, =0 direccional))

    glPushMatrix();
    glRotatef(rotacion_luz,0,1,0);
    glLightfv (GL_LIGHT2, GL_POSITION, luz_posicion_2);
    glPopMatrix();
}


void luces() {


    // DIRECCIONAL BLANCA FIJA
    GLfloat luz_ambiente_1 [] = {0.5, 0.5, 0.5, 1.0},
            luz_difusa_1 [] = {0.5, 0.5, 0.5, 1.0},           // definir color de la luz
            luz_especular_1 [] = {0.5, 0.5, 0.5, 1.0},
            luz_posicion_1 [] = {0.0, 20.0, 20.0, 0.0};       // definir posición (x,y,z, w (=1 puntual, =0 direccional))

    // PUNTUAL 
    GLfloat luz_ambiente_2 [] = {0, 0.4, 0.2, 1.0},
            luz_difusa_2 [] = {0, 0.4, 0.2, 1.0},           // definir color de la luz
            luz_especular_2 [] = {0.35, 0.35, 0.35, 1.0};


    glLightfv (GL_LIGHT1, GL_AMBIENT, luz_ambiente_1);
    glLightfv (GL_LIGHT1, GL_DIFFUSE, luz_difusa_1);
    glLightfv (GL_LIGHT1, GL_SPECULAR, luz_especular_1);
    glLightfv (GL_LIGHT1, GL_POSITION, luz_posicion_1);

    glLightfv (GL_LIGHT2, GL_AMBIENT, luz_ambiente_2);
    glLightfv (GL_LIGHT2, GL_DIFFUSE, luz_difusa_2);
    glLightfv (GL_LIGHT2, GL_SPECULAR, luz_especular_2);
    //glLightfv (GL_LIGHT2, GL_POSITION, luz_posicion_2);
    posicion_luz2();


    glEnable (GL_LIGHT1);  

    if (segunda_luz)
        glEnable (GL_LIGHT2);
    else
        glDisable (GL_LIGHT2);


    glDisable (GL_LIGHT0);

}

/*
void posicion_luz1 ( )
{
GLfloat luz_posicion [ ] = {1.0, 1.0, 0.0 ,1.0};
glPushMatrix();
glTranslatef ( ... );
glRotatef ( angulo, ... );
glLightfv (GL_LIGHT0, GL_POSITION, luz_posicion);
glPopMatrix()
}
*/


void vista_ortogonal()
{
	// PLANTA
	glViewport(Ancho/2, Alto/2, Ancho/2, Alto/2);

	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
    // parámetros iniciales
	glOrtho(-5*factor,5*factor,-5*factor,5*factor,-100,100); 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	draw_axis();
	draw_objects();

	glViewport(0, Alto/2, Ancho/2, Alto/2);

	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	glOrtho(-5*factor,5*factor,-5*factor,5*factor,-100,100); 
	glRotatef(90,1,0,0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	draw_axis();
	draw_objects();


 	// PERFIL
	glViewport(0, 0, Ancho/2, Alto/2);

	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	glOrtho(-5*factor,5*factor,-5*factor,5*factor,-100,100); 
	glRotatef(90,0,1,0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	draw_axis();
	draw_objects();

	glViewport(Ancho/2, 0, Ancho/2, Alto/2);
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();

	glFrustum(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);

	change_projection();
	change_observer();

	draw_axis();
	draw_objects();

}


//**************************************************************************
//
//***************************************************************************

void draw(void)
{
    clean_window();
    luces();
    

    if (camara==0) {
        glViewport(0,0,Ancho,Alto);
        change_projection();
        change_observer();
        draw_axis();
        draw_objects();
    }
    else {
        vista_ortogonal();
    }

    glutSwapBuffers();

    if (t_objeto==EXCAVADORA)
    {glDrawBuffer(GL_BACK);
    clean_window();
    change_observer();
    excavadora.seleccion();
    }

    if (t_objeto==DINOSAURIO)
    {glDrawBuffer(GL_BACK);
    clean_window();
    change_observer();
    dinosaurio.seleccion();
    }

    glFlush();
}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
float Aspect_ratio;

Aspect_ratio=(float) Alto1/(float )Ancho1;
Size_y=Size_x*Aspect_ratio;
change_projection();
glViewport(0,0,Ancho1,Alto1);
Ancho = Ancho1;
Alto = Alto1;
glutPostRedisplay();
}


//***************************************************************************
// Funcion llamada cuando se aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_key(unsigned char Tecla1,int x,int y)
{
switch (toupper(Tecla1)){
	case 'Q':exit(0);
	case '1':modo=POINTS;break;
	case '2':modo=EDGES;break;
	case '3':modo=SOLID;break;
	case '4':modo=SOLID_COLORS;break;
    case '5':modo=SOLID_FLAT;break;
    case '6':modo=SOLID_SMOOTH;break;
    case 'S':   if (pulsado==true) {
                    giro1=0.4;giro2=0.4;giro3=0.5;giro4=0.25;giro5=0.25;giro6=0.4;giro7=0.5;
                    pulsado=false;
                    break;
                }   
                else {
                    giro1=0;giro2=0;giro3=0;giro4=0;giro5=0;giro6=0;giro7=0;
                    pulsado = true;
                    break;
                }
    case 'P':t_objeto=PIRAMIDE;break;
    case 'C':t_objeto=CUBO;break;
    case 'O':t_objeto=OBJETO_PLY;break;	
    case 'R':t_objeto=ROTACION;break;
    case 'L':t_objeto=CILINDRO;break;
    case 'K':t_objeto=CONO;break;
    case 'E':t_objeto=ESFERA;break;
    case 'M':t_objeto=ROT_PLY;break;
    case 'X':t_objeto=EXTRUSION;break;
    case 'Z':t_objeto=EXCAVADORA;break;
    case 'A':t_objeto=DINOSAURIO;break;
    case 'I':   if (segunda_luz)
                    segunda_luz=false;
                else
                    segunda_luz=true;
                break;
    case 'B':
                rotacion_luz+=5;
                if (rotacion_luz > 360)
                    rotacion_luz = 360;
                break;
    case 'N':
                rotacion_luz-=5;
                if (rotacion_luz < 0)
                    rotacion_luz = 0;
                break;
	
    case '7':camara=0;break;
    case '8':camara=1;break;
    case '+':factor*=0.9;break;
    case '-':factor*=1.1;break;
    }


glutPostRedisplay();
}

//***************************************************************************
// Funcion l-olamada cuando se aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_key(int Tecla1,int x,int y)
{

switch (Tecla1){
   case GLUT_KEY_LEFT:Observer_angle_y--;break;
   case GLUT_KEY_RIGHT:Observer_angle_y++;break;
   case GLUT_KEY_UP:Observer_angle_x--;break;
   case GLUT_KEY_DOWN:Observer_angle_x++;break;
   case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
   case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
	
   case GLUT_KEY_F1://excavadora.giro_cabina+=5;
        dinosaurio.giro_cola_vertical+=5;
        if (dinosaurio.giro_cola_vertical > dinosaurio.giro_cola_vertical_max)
            dinosaurio.giro_cola_vertical = dinosaurio.giro_cola_vertical_max;
        
   break;
   case GLUT_KEY_F2://excavadora.giro_cabina-=5;
        dinosaurio.giro_cola_vertical-=5;
        if (dinosaurio.giro_cola_vertical < dinosaurio.giro_cola_vertical_min)
            dinosaurio.giro_cola_vertical = dinosaurio.giro_cola_vertical_min;

   break;
   case GLUT_KEY_F3://excavadora.giro_primer_brazo+=1;
        dinosaurio.giro_cola_horizontal+=5;   
        if (dinosaurio.giro_cola_horizontal > dinosaurio.giro_cola_horizontal_max)
            dinosaurio.giro_cola_horizontal = dinosaurio.giro_cola_horizontal_max;         
        //if (excavadora.giro_primer_brazo > excavadora.giro_primer_brazo_max)
            //excavadora.giro_primer_brazo = excavadora.giro_primer_brazo_max;break;
    break;
   case GLUT_KEY_F4://excavadora.giro_primer_brazo-=1;
        dinosaurio.giro_cola_horizontal-=5;   
        if (dinosaurio.giro_cola_horizontal < dinosaurio.giro_cola_horizontal_min)
            dinosaurio.giro_cola_horizontal = dinosaurio.giro_cola_horizontal_min;  
        //if (excavadora.giro_primer_brazo < excavadora.giro_primer_brazo_min)
            //excavadora.giro_primer_brazo = excavadora.giro_primer_brazo_min;
    break;
   case GLUT_KEY_F5://excavadora.giro_pala+=1;
        dinosaurio.giro_cuello_horizontal+=5;
        if (dinosaurio.giro_cuello_horizontal > dinosaurio.giro_cuello_horizontal_max)
            dinosaurio.giro_cuello_horizontal = dinosaurio.giro_cuello_horizontal_max;

       // if (excavadora.giro_pala > excavadora.giro_pala_max)
           // excavadora.giro_pala = excavadora.giro_pala_max;

    break;
   case GLUT_KEY_F6://excavadora.giro_pala-=1;
        dinosaurio.giro_cuello_horizontal-=5;
        if (dinosaurio.giro_cuello_horizontal < dinosaurio.giro_cuello_horizontal_min)
            dinosaurio.giro_cuello_horizontal = dinosaurio.giro_cuello_horizontal_min;
       // if (excavadora.giro_pala < excavadora.giro_pala_min)
           // excavadora.giro_pala = excavadora.giro_pala_min;
    break;
   case GLUT_KEY_F7:
        dinosaurio.giro_pata1-=5;
        dinosaurio.giro_pata2-=5;
        if (dinosaurio.giro_pata1 < dinosaurio.giro_pata_min1)
            dinosaurio.giro_pata1 = dinosaurio.giro_pata_min1;
        if (dinosaurio.giro_pata2 < dinosaurio.giro_pata_min2)
            dinosaurio.giro_pata2 = dinosaurio.giro_pata_min2;
    break;
   case GLUT_KEY_F8:
        dinosaurio.giro_pata1+=5;
        dinosaurio.giro_pata2+=5;
        if (dinosaurio.giro_pata1 > dinosaurio.giro_pata_max1)
            dinosaurio.giro_pata1 = dinosaurio.giro_pata_max1;
        if (dinosaurio.giro_pata2 > dinosaurio.giro_pata_max2)
            dinosaurio.giro_pata2 = dinosaurio.giro_pata_max2;
    break;

   case GLUT_KEY_F9:
        dinosaurio.giro_cabeza-=5;
        if (dinosaurio.giro_cabeza < dinosaurio.giro_cabeza_min)
            dinosaurio.giro_cabeza = dinosaurio.giro_cabeza_min;
    break;
   case GLUT_KEY_F10:
        dinosaurio.giro_cabeza+=3;
        if (dinosaurio.giro_cabeza > dinosaurio.giro_cabeza_max)
            dinosaurio.giro_cabeza = dinosaurio.giro_cabeza_max;
    break;
	

   case GLUT_KEY_F11://excavadora.giro_segundo_brazo+=1;
        dinosaurio.giro_cuello_vertical+=5;
        if (dinosaurio.giro_cuello_vertical > dinosaurio.giro_cuello_vertical_max)
            dinosaurio.giro_cuello_vertical = dinosaurio.giro_cuello_vertical_max;
       // if (excavadora.giro_segundo_brazo > excavadora.giro_segundo_brazo_max)
            //excavadora.giro_segundo_brazo = excavadora.giro_segundo_brazo_max;
   break;
   case GLUT_KEY_F12://excavadora.giro_segundo_brazo-=1;
        dinosaurio.giro_cuello_vertical-=5;
        //if (excavadora.giro_segundo_brazo > excavadora.giro_segundo_brazo_max)
           // excavadora.giro_segundo_brazo = excavadora.giro_segundo_brazo_max;
        if (dinosaurio.giro_cuello_vertical < dinosaurio.giro_cuello_vertical_min)
            dinosaurio.giro_cuello_vertical = dinosaurio.giro_cuello_vertical_min;
   break;
    }
glutPostRedisplay();
}

//***************************************************************************
// Funcion de animación automática
//***************************************************************************

/*
void movimiento(){
    excavadora.giro_cabina+=giro;
    if (flag2==0)
        excavadora.giro_pala+=giro2;
    else
         excavadora.giro_pala-=giro2;

    if (excavadora.giro_pala > excavadora.giro_pala_max) {
        excavadora.giro_pala = excavadora.giro_pala_max;
        flag2=1;
    }

    if (excavadora.giro_pala < excavadora.giro_pala_min) {
        excavadora.giro_pala = excavadora.giro_pala_min;
        flag2=0;
    }


    glutPostRedisplay();
}
*/

void movimiento(){
    //dinosaurio.giro_cola_horizontal+=giro;

    // GIRO HORIZONTAL DE LA COLA

    if (flag1==0)
        dinosaurio.giro_cola_horizontal+=giro1;
    else
        dinosaurio.giro_cola_horizontal-=giro1;

    if (dinosaurio.giro_cola_horizontal > dinosaurio.giro_cola_horizontal_max) {
        dinosaurio.giro_cola_horizontal = dinosaurio.giro_cola_horizontal_max;
        flag1=1;
    }

    if (dinosaurio.giro_cola_horizontal < dinosaurio.giro_cola_horizontal_min) {
        dinosaurio.giro_cola_horizontal = dinosaurio.giro_cola_horizontal_min;
        flag1=0;
    }

    // GIRO VERTICAL DE LA COLA

    if (flag2==0)
        dinosaurio.giro_cola_vertical+=giro2;
    else
        dinosaurio.giro_cola_vertical-=giro2;

    if (dinosaurio.giro_cola_vertical > dinosaurio.giro_cola_vertical_max) {
        dinosaurio.giro_cola_vertical = dinosaurio.giro_cola_vertical_max;
        flag2=1;
    }

    if (dinosaurio.giro_cola_vertical < dinosaurio.giro_cola_vertical_min) {
        dinosaurio.giro_cola_vertical = dinosaurio.giro_cola_vertical_min;
        flag2=0;
    }

    // GIRO DE LAS PATAS 1a y 3a (intentamos simular que el dinosaurio camina)

    if (flag3==0)
        dinosaurio.giro_pata1+=giro3;
    else
        dinosaurio.giro_pata1-=giro3;

    if (dinosaurio.giro_pata1> dinosaurio.giro_pata_max1) {
        dinosaurio.giro_pata1= dinosaurio.giro_pata_max1;
        flag3=1;
    }

    if (dinosaurio.giro_pata1 < dinosaurio.giro_pata_min1) {
        dinosaurio.giro_pata1 = dinosaurio.giro_pata_min1;
        flag3=0;
    }

    // GIRO DE LAS PATAS 2a y 4a  (intentamos simular que el dinosaurio camina)

    if (flag7==0)
        dinosaurio.giro_pata2-=giro7;
    else
        dinosaurio.giro_pata2+=giro7;

    if (dinosaurio.giro_pata2> dinosaurio.giro_pata_max2) {
        dinosaurio.giro_pata2= dinosaurio.giro_pata_max2;
        flag7=0;
    }

    if (dinosaurio.giro_pata2 < dinosaurio.giro_pata_min2) {
        dinosaurio.giro_pata2 = dinosaurio.giro_pata_min2;
        flag7=1;
    }

    // GIRO VERTICAL DEL CUELLO

    if (flag4==0)
        dinosaurio.giro_cuello_vertical+=giro4;
    else
        dinosaurio.giro_cuello_vertical-=giro4;

    if (dinosaurio.giro_cuello_vertical > dinosaurio.giro_cuello_vertical_max) {
        dinosaurio.giro_cuello_vertical = dinosaurio.giro_cuello_vertical_max;
        flag4=1;
    }

    if (dinosaurio.giro_cuello_vertical < dinosaurio.giro_cuello_vertical_min) {
        dinosaurio.giro_cuello_vertical = dinosaurio.giro_cuello_vertical_min;
        flag4=0;
    }

    // GIRO HORIZONTAL DEL CUELLO

    if (flag5==0)
        dinosaurio.giro_cuello_horizontal+=giro5;
    else
        dinosaurio.giro_cuello_horizontal-=giro5;

    if (dinosaurio.giro_cuello_horizontal > dinosaurio.giro_cuello_horizontal_max) {
        dinosaurio.giro_cuello_horizontal = dinosaurio.giro_cuello_horizontal_max;
        flag5=1;
    }

    if (dinosaurio.giro_cuello_horizontal < dinosaurio.giro_cuello_horizontal_min) {
        dinosaurio.giro_cuello_horizontal = dinosaurio.giro_cuello_horizontal_min;
        flag5=0;
    }

    // GIRO DE LA CABEZA

    if (flag6==0)
        dinosaurio.giro_cabeza+=giro6;
    else
        dinosaurio.giro_cabeza-=giro6;

    if (dinosaurio.giro_cabeza > dinosaurio.giro_cabeza_max) {
        dinosaurio.giro_cabeza= dinosaurio.giro_cabeza_max;
        flag6=1;
    }

    if (dinosaurio.giro_cabeza < dinosaurio.giro_cabeza_min) {
        dinosaurio.giro_cabeza = dinosaurio.giro_cabeza_min;
        flag6=0;
    }



    glutPostRedisplay();
}



//***************************************************************************
// Funciones para la selección por color
//***************************************************************************
/*
void procesar_color(unsigned char color[3])
{
int i;

for (i=0;i<excavadora.piezas;i++)
   {if (color[0]==excavadora.color_select[i].r &&
        color[1]==excavadora.color_select[i].g &&
        color[2]==excavadora.color_select[i].r)
       {if (excavadora.activo[i]==0) 
                      {excavadora.activo[i]=1;
                      }
                  else 
                      {excavadora.activo[i]=0;
                      }
         glutPostRedisplay();
        }
    }                
}
*/
void procesar_color(unsigned char color[3])
{
int i;

for (i=0;i<dinosaurio.piezas;i++)
   {if (color[0]==dinosaurio.color_select[i].r &&
        color[1]==dinosaurio.color_select[i].g &&
        color[2]==dinosaurio.color_select[i].r)
       {if (dinosaurio.activo[i]==0) 
                      {dinosaurio.activo[i]=1;
                      }
                  else 
                      {dinosaurio.activo[i]=0;
                      }
         glutPostRedisplay();
        }
    }                
}

//***************************************************************************

void pick_color(int x, int y)
{
GLint viewport[4];
unsigned char pixel[3];

glGetIntegerv(GL_VIEWPORT, viewport);
glReadBuffer(GL_BACK);
glReadPixels(x,viewport[3]-y,1,1,GL_RGB,GL_UNSIGNED_BYTE,(GLubyte *) &pixel[0]);
printf(" valor x %d, valor y %d, color %d, %d, %d \n",x,y,pixel[0],pixel[1],pixel[2]);

procesar_color(pixel);
}

//***************************************************************************
// Funciones para manejo de eventos del ratón
//***************************************************************************

void clickRaton( int boton, int estado, int x, int y )
{
    if(boton==GLUT_RIGHT_BUTTON) {
            // se pulsa el botón derecho, entrado en el estado "moviendo cámara"
        if(estado==GLUT_DOWN) 
            {
            estadoRaton=1;
            xc=x;
            yc=y;
            } 
        else estadoRaton=0;
        // se levanta el botón derecho, saliendo del estado "moviendo cámara"
    }
    if(boton==GLUT_LEFT_BUTTON) 
    {
        if(estado==GLUT_DOWN) 
            {
                // se pulsa el botón izquierdo, entrado en el estado "pick"
            estadoRaton=2;
            xc=x;
            yc=y;
            pick_color(xc, yc);
            } 
    }

    // para el zoom del raton

        if(boton==3){
            if(estado == GLUT_UP){ 
                estadoRaton = 3;
                Observer_distance/=1.2;

            }
            else
                    estadoRaton = 3;
            }

            if(boton==4){             
                if(estado==GLUT_DOWN){ 
                    estadoRaton = 4;
                    Observer_distance*=1.2;
                }
                else
                        estadoRaton = 3;
                }

}
// estadoRaton=0 cuando se deja de pulsar el botón derecho
// estadoRaton=1 cuando se pulsa el botón derecho
// estadoRaton=2 cuando se pulsa el botón izquierdo
// xc, yc almacenan la posición del ratón

/*************************************************************************/

void RatonMovido( int x, int y )
{ 
if(estadoRaton==1) 
    {Observer_angle_y=Observer_angle_y-(x-xc);
     Observer_angle_x=Observer_angle_x+(y-yc);
     xc=x;
     yc=y;
     glutPostRedisplay();
    }
}





//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
// se inicalizan la ventana y los planos de corte
Size_x=0.5;
Size_y=0.5;
Front_plane=1;
Back_plane=1000;

// se incia la posicion del observador, en el eje z
Observer_distance=4*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
change_projection();
glViewport(0,0,Window_width,Window_high);
}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************


int main(int argc, char *argv[] )
{
 
// perfil 

vector<_vertex3f> perfil, poligono;
_vertex3f aux;

aux.x=1.0; aux.y=-1.0; aux.z=0.0;
perfil.push_back(aux);
aux.x=1.5; aux.y=0; aux.z=0;
perfil.push_back(aux);
aux.x=1.0; aux.y=1.0; aux.z=0.0; // perfil de clase
perfil.push_back(aux);

/*
aux.x=1.0; aux.y=-3.0; aux.z=0.0;
perfil.push_back(aux);
aux.x=2.0; aux.y=-2.0; aux.z=0;
perfil.push_back(aux);
aux.x=3.0; aux.y=-1.0; aux.z=0.0;    // pruebas mías 
perfil.push_back(aux);
aux.x=3.0; aux.y=1.0; aux.z=0;
perfil.push_back(aux);
aux.x=2.0; aux.y=2.0; aux.z=0.0;
perfil.push_back(aux);
aux.x=1.0; aux.y=3.0; aux.z=0.0;
perfil.push_back(aux);

*/
rotacion.parametros(perfil,6,0,1,1);



aux.x=1.0; aux.y=0.0; aux.z=1.0;
poligono.push_back(aux);
aux.x=1.0; aux.y=0.0; aux.z=-1.0;
poligono.push_back(aux);
aux.x=-1.2; aux.y=0.0; aux.z=-1.0;
poligono.push_back(aux);
aux.x=-0.8; aux.y=0.0; aux.z=0.0;
poligono.push_back(aux);
aux.x=-1.2; aux.y=0.0; aux.z=1.0;
poligono.push_back(aux);

extrusion= new _extrusion(poligono, 0.25, 1.0, 0.25);

// se llama a la inicialización de glut
glutInit(&argc, argv);

// se indica las caracteristicas que se desean para la visualización con OpenGL
// Las posibilidades son:
// GLUT_SIMPLE -> memoria de imagen simple
// GLUT_DOUBLE -> memoria de imagen doble
// GLUT_INDEX -> memoria de imagen con color indizado
// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
// GLUT_DEPTH -> memoria de profundidad o z-bufer
// GLUT_STENCIL -> memoria de estarcido_rotation Rotation;
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

// posicion de la esquina inferior izquierdad de la ventana
glutInitWindowPosition(Window_x,Window_y);

// tamaño de la ventana (ancho y alto)
glutInitWindowSize(Window_width,Window_high);

// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
// al bucle de eventos)
glutCreateWindow("PRACTICA - 5");

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw);
// asignación de la funcion llamada "change_window_size" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "normal_key" al evento correspondiente
glutKeyboardFunc(normal_key);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_key);

// para la animación
glutIdleFunc(movimiento);

// funcion de inicialización
initialize();

rot_ply.parametros_rotacion_ply(argv[2],20);   // objeto por rotación a través de fichero ply

// creación del objeto ply
ply.parametros(argv[1]);

// eventos ratón
glutMouseFunc(clickRaton);
glutMotionFunc(RatonMovido);

// inicio del bucle de eventos
glutMainLoop();
return 0;
}
