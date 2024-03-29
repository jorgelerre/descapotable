//**************************************************************************
// Práctica 2 
//**************************************************************************

#include <GL/glut.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include "objetos_B2.h"


using namespace std;

// tipos
typedef enum{/*CUBO, PIRAMIDE, OBJETO_PLY, ROTACION, EXTRUSION, CONO, ESFERA, CILINDRO, ROTACION_PLY,*/ DESCAPOTABLE} _tipo_objeto;
_tipo_objeto t_objeto=DESCAPOTABLE;
_modo   modo=POINTS;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Size_x,Size_y,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int Window_x=50,Window_y=50,Window_width=650,Window_high=650;

//variable que controla la activacion de la animacion
bool animacion_activa = false;


// objetos
/*
_cubo cubo;
_piramide piramide(0.85,1.3);
_objeto_ply  ply; 
_rotacion rotacion; 
_extrusion *extrusion;
_cilindro cilindro(0.75, 1);
_cono cono(0.75, 1);
_esfera esfera;
_rotacion_ply rotacion_ply;
*/

_descapotable descapotable;

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
        /*
	    case CUBO: cubo.draw(modo,1.0,0.0,0.0,5);break;
	    case PIRAMIDE: piramide.draw(modo,1.0,0.0,0.0,5);break;
        case OBJETO_PLY: ply.draw(modo,1.0,0.6,0.0,5);break;
        case ROTACION: rotacion.draw(modo,1.0,0.0,0.0,5);break;
        case EXTRUSION: extrusion->draw(modo,1.0,0.0,0.0,5);break;
        case CONO: cono.draw(modo,1.0,0.0,0.0,5);break;
        case ESFERA: esfera.draw(modo,1.0,0.0,0.0,1);break;
        case CILINDRO: cilindro.draw(modo,1.0,0.0,0.0,1);break;
        case ROTACION_PLY: rotacion_ply.draw(modo,1.0,0.6,0.0,5);break;
        */
        case DESCAPOTABLE: descapotable.draw(modo,1.0,0.6,0.0,5);break;
    }

}


//**************************************************************************
//
//***************************************************************************

void draw(void)
{
clean_window();
change_observer();
draw_axis();
draw_objects();
glutSwapBuffers();
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
	case '5':modo=SOLID_RANDOM;break;
	    /*
        case 'P':t_objeto=PIRAMIDE;break;
        case 'C':t_objeto=CUBO;break;
        case 'O':t_objeto=OBJETO_PLY;break;	
        case 'R':t_objeto=ROTACION;break;
        case 'X':t_objeto=EXTRUSION;break;
        case 'N':t_objeto=CONO;break;
        case 'E':t_objeto=ESFERA;break;
        case 'Y':t_objeto=CILINDRO;break;
        case 'Z':t_objeto=ROTACION_PLY;break;
        */
        case 'D':t_objeto=DESCAPOTABLE;break;
        case 'A':animacion_activa = !animacion_activa; break;
	}
glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se aprieta una tecla especial
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
	
	case GLUT_KEY_F1:
	    if(descapotable.giro_dir_ruedas < 22){
	        descapotable.giro_dir_ruedas+=0.5;  //Valores giro_dir_ruedas = [-22, 22]
	        descapotable.giro_volante-=5;       //Valores giro_volante= [-220, 220]
	    }
	break;
	case GLUT_KEY_F2:
	    if(descapotable.giro_dir_ruedas > -22){
	        descapotable.giro_dir_ruedas-=0.5;  //Valores giro_dir_ruedas = [-22, 22]
	        descapotable.giro_volante+=5;       //Valores giro_volante= [-220, 220]
	    }
	break;
	
	case GLUT_KEY_F3:
	    descapotable.giro_rot_ruedas+=2;
	break;
	case GLUT_KEY_F4:
	    descapotable.giro_rot_ruedas-=2;
	break;
	
	case GLUT_KEY_F5:
	    if(descapotable.giro_puerta_izq < 70)   //Giros = [0, 70]
	        descapotable.giro_puerta_izq+=2;
	break;
	case GLUT_KEY_F6:
	    if(descapotable.giro_puerta_izq > 0)    //Giros = [0, 70]
	        descapotable.giro_puerta_izq-=2;
	break;
	case GLUT_KEY_F7:
	    if(descapotable.giro_puerta_der < 70)   //Giros = [0, 70]
	        descapotable.giro_puerta_der+=2;
	break;
	case GLUT_KEY_F8:
	    if(descapotable.giro_puerta_der > 0)    //Giros = [0, 70]
	        descapotable.giro_puerta_der-=2;
	break;
	
	case GLUT_KEY_F9:
	    if(descapotable.giro_puerta_maletero < 80)  //Giros = [0, 80]
	        descapotable.giro_puerta_maletero+=2;
	break;
	case GLUT_KEY_F10:
	    if(descapotable.giro_puerta_maletero > 0)   //Giros = [0, 80]
	        descapotable.giro_puerta_maletero-=2;
	break;
	
	case GLUT_KEY_F11:
	    if(descapotable.coeficiente_techo < 1)  	//Coeficiente = [0 (cerrado), 1(abierto)]
	        descapotable.coeficiente_techo+=0.005;
	break;
	case GLUT_KEY_F12:
	    if(descapotable.coeficiente_techo > 0.01)  //Coeficiente = [0 (cerrado), 1(abierto)]
	        descapotable.coeficiente_techo-=0.005;
	break;
	}
glutPostRedisplay();
}



//***************************************************************************
// Funcion de inicializacion
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


void animacion(){
    static int estado = 0;
    static int avance = 0;
    if(animacion_activa){
        switch(estado){
	        case 0:  //Abre maletero  
                if(descapotable.giro_puerta_maletero < 80)  //Giros = [0, 80]
	                descapotable.giro_puerta_maletero+=1;
                else
                    estado = 1;
                break;    
            case 1:  //Portazo maletero
                if(descapotable.giro_puerta_maletero > 0)  //Giros = [0, 80]
	                descapotable.giro_puerta_maletero-=2;
                else
                    estado = 2;
                break;
            case 2:  //Abre puerta del conductor y del pasajero
                if(descapotable.giro_puerta_der < 70)  //Giros = [0, 70]
	                descapotable.giro_puerta_der+=2;
                if(descapotable.giro_puerta_izq < 70)  //Giros = [0, 70]
	                descapotable.giro_puerta_izq+=2;
                if(descapotable.giro_puerta_der >= 70 && descapotable.giro_puerta_izq >= 70)
                    estado = 3;
                break;
            case 3: //Cierra puerta del conductor y del pasajero
                if(descapotable.giro_puerta_der > 0)  //Giros = [0, 70]
	                descapotable.giro_puerta_der-=2;
                if(descapotable.giro_puerta_izq > 0)  //Giros = [0, 70]
	                descapotable.giro_puerta_izq-=2;
                if(descapotable.giro_puerta_der <= 0 && descapotable.giro_puerta_izq <= 0)
                    estado = 4;
                break;
            case 4: //Marcha atras y giro de ruedas a la izquierda
                if(descapotable.giro_dir_ruedas > -20){  //Giros = [0, -20]
	                descapotable.giro_dir_ruedas-=0.2;
	                descapotable.giro_volante+=2;   
	            }
                descapotable.giro_rot_ruedas-=2;
                if(descapotable.giro_dir_ruedas <= -20)
                    estado = 5;
                break;
            case 5: //Marcha adelante y giro de ruedas a la derecha
                if(descapotable.giro_dir_ruedas < 20){  //Giros = [-20, 20]
	                descapotable.giro_dir_ruedas+=0.2;
	                descapotable.giro_volante-=2;
	            }
                descapotable.giro_rot_ruedas+=2;
                if(descapotable.giro_dir_ruedas >= 20)
                    estado = 6;
                break;
            case 6: //Marcha adelante y giro de ruedas al centro
                if(descapotable.giro_dir_ruedas > 0){  //Giros = [-20, 20]
	                descapotable.giro_dir_ruedas-=0.2;
	                descapotable.giro_volante+=2;
	            }
                descapotable.giro_rot_ruedas+=3;
                if(descapotable.giro_dir_ruedas <= 0)
                    estado = 7;
                break;
            case 7: //Marcha adelante y apertura de techo
                descapotable.giro_rot_ruedas+=5;
                if(descapotable.coeficiente_techo < 1){
                    descapotable.coeficiente_techo+=0.005;
                }
                if(descapotable.coeficiente_techo >= 1)
                    estado = 8;
                break;
            case 8: //Marcha adelante
                descapotable.giro_rot_ruedas+=5 + 10*sin(M_PI*avance/400.0);
                avance++;
                if(avance >= 400){
                    estado = 9;
                    avance = 0;
                }
                break;
            case 9: //Marcha adelante y cierre de techo
                descapotable.giro_rot_ruedas+=5;
                if(descapotable.coeficiente_techo > 0){
                    descapotable.coeficiente_techo-=0.005;
                }
                if(descapotable.coeficiente_techo <= 0)
                    estado = 0;
                break;
        }
        glutPostRedisplay();
    }
}
//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************


int main(int argc, char *argv[] )
{
 
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
glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

// posicion de la esquina inferior izquierdad de la ventana
glutInitWindowPosition(Window_x,Window_y);

// tamaño de la ventana (ancho y alto)
glutInitWindowSize(Window_width,Window_high);

// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
// al bucle de eventos)
glutCreateWindow("PRACTICA - 2");
//Comandos para activar colores translucidos
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); glEnable( GL_BLEND );  glClearColor(0.0,0.0,0.0,0.0);
// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw);
// asignación de la funcion llamada "change_window_size" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "normal_key" al evento correspondiente
glutKeyboardFunc(normal_key);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_key);

glutIdleFunc(animacion);
// funcion de inicialización
initialize();

// inicio del bucle de eventos
glutMainLoop();
return 0;
}
