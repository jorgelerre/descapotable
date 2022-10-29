//**************************************************************************
// Práctica 2 
//**************************************************************************

#include "objetos_B2.h"
#include "file_ply_stl.hpp"

//*************************************************************************
// _puntos3D
//*************************************************************************

_puntos3D::_puntos3D()
{
}

//*************************************************************************
// dibujar puntos
//*************************************************************************

void _puntos3D::draw_puntos(float r, float g, float b, int grosor)
{
unsigned int i;
glPointSize(grosor);
glColor3f(r,g,b);
glBegin(GL_POINTS);
for (i=0;i<vertices.size();i++){
	glVertex3fv((GLfloat *) &vertices[i]);
	}
glEnd();
}


//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D()
{
}


//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
unsigned int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
}
glEnd();
}

//*************************************************************************
// dibujar en modo sólido con un único color
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b)
{
	unsigned int i;
	glPolygonMode(GL_FRONT,GL_FILL);
	glColor3f(r,g,b);
	glBegin(GL_TRIANGLES);
	for (i=0;i<caras.size();i++){
		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
	glEnd();
}

//*************************************************************************
// dibujar en modo sólido con colores diferentes para cada cara
//*************************************************************************

void _triangulos3D::draw_solido_colores( )
{
	unsigned int i;
	float r, g, b, a;
	glPolygonMode(GL_FRONT,GL_FILL);
	
	glBegin(GL_TRIANGLES);
	for (i=0;i<caras.size();i++){
		if(colores.size() > i){
		    glColor4f(colores[i].r,colores[i].g,colores[i].b,colores[i].a);
		}
		else{
		    if(i % 2 == 0){
		        r = 1;
		        g = 0;
		        b = 0;
		        a = 1;
		    }
		    else{
		        r = 1;
		        g = 1;
		        b = 0;
		        a = 1;
		    }
		    glColor4f(r,g,b,a);
		}
		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
	glEnd();
}

void _triangulos3D::draw_solido_colores_random(){
    unsigned int i;
	float r, g, b, a;
	glPolygonMode(GL_FRONT,GL_FILL);
	srand(1);
	glBegin(GL_TRIANGLES);
	for (i=0;i<caras.size();i++){
        r = (rand()%256) / 256.0;
        g = (rand()%256) / 256.0;
        b = (rand()%256) / 256.0;
        a = 1.0;

        glColor4f(r,g,b,a);
		
		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
	glEnd();
}


//*************************************************************************
// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(_modo modo, float r, float g, float b, float grosor)
{
switch (modo){
	case POINTS:draw_puntos(r, g, b, grosor);       break;
	case EDGES:draw_aristas(r, g, b, grosor);       break;
	case SOLID:draw_solido(r, g, b);		        break;
	case SOLID_COLORS:draw_solido_colores();        break;
	case SOLID_RANDOM:draw_solido_colores_random(); break;
	}
}

//*************************************************************************
// asignación colores
//*************************************************************************

void _triangulos3D::colors_random()
{
int i, n_c;
n_c=caras.size();
colores.resize(n_c);
srand (time(NULL));
for (i=0;i<n_c;i++)  
  {colores[i].r=rand()%1000/1000.0;
   colores[i].g=rand()%1000/1000.0;
   colores[i].b=rand()%1000/1000.0;
   colores[i].a=1.0;
  }
}

//*************************************************************************

void _triangulos3D::colors_chess(float r1, float g1, float b1, float a1, float r2, float g2, float b2, float a2)
{
int i, n_c;
n_c=caras.size();
colores.resize(n_c);
for (i=0;i<n_c;i++)  
  {if (i%2==0) 
     {colores[i].r=r1;
      colores[i].g=g1;
      colores[i].b=b1;
      colores[i].a=a1;
     }
   else 
     {colores[i].r=r2;
      colores[i].g=g2;
      colores[i].b=b2;
     } 
  }
}

//*************************************************************************

void _triangulos3D::asignar_color(float r, float g, float b, float a)
{
int i, n_c;
n_c=caras.size();
colores.resize(n_c);
for (i=0;i<n_c;i++)  
  {colores[i].r=r;
   colores[i].g=g;
   colores[i].b=b;
   colores[i].a=a;
  }
}

//*************************************************************************

void _triangulos3D::asignar_color(const _color & color)
{
int i, n_c;
n_c=caras.size();
colores.resize(n_c);
for (i=0;i<n_c;i++)  
  {colores[i].r=color.r;
   colores[i].g=color.g;
   colores[i].b=color.b;
   colores[i].a=color.a;
  }
}

//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam)
{
//vertices
vertices.resize(8); 
vertices[0].x=-tam;vertices[0].y=0;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=0;vertices[2].z=-tam;
vertices[3].x=-tam;vertices[3].y=0;vertices[3].z=-tam;
vertices[4].x=-tam;vertices[4].y=tam*2;vertices[4].z=tam;
vertices[5].x=tam;vertices[5].y=tam*2;vertices[5].z=tam;
vertices[6].x=tam;vertices[6].y=tam*2;vertices[6].z=-tam;
vertices[7].x=-tam;vertices[7].y=tam*2;vertices[7].z=-tam;
// triangulos
caras.resize(12);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=5;                    
caras[1]._0=0;caras[1]._1=5;caras[1]._2=4;
caras[2]._0=1;caras[2]._1=2;caras[2]._2=6;
caras[3]._0=1;caras[3]._1=6;caras[3]._2=5;   
caras[4]._0=2;caras[4]._1=3;caras[4]._2=7;   
caras[5]._0=2;caras[5]._1=7;caras[5]._2=6;
caras[6]._0=3;caras[6]._1=0;caras[6]._2=4; 
caras[7]._0=3;caras[7]._1=4;caras[7]._2=7;   
caras[8]._0=0;caras[8]._1=3;caras[8]._2=1;   
caras[9]._0=2;caras[9]._1=1;caras[9]._2=3;
caras[10]._0=4;caras[10]._1=5;caras[10]._2=7;   
caras[11]._0=6;caras[11]._1=7;caras[11]._2=5;     
//colores
colors_random();
}


//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al)
{

//vertices 
vertices.resize(5); 
vertices[0].x=-tam;vertices[0].y=0;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=0;vertices[2].z=-tam;
vertices[3].x=-tam;vertices[3].y=0;vertices[3].z=-tam;
vertices[4].x=0;vertices[4].y=al;vertices[4].z=0;

//caras
caras.resize(6);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=4;
caras[1]._0=1;caras[1]._1=2;caras[1]._2=4;
caras[2]._0=2;caras[2]._1=3;caras[2]._2=4;
caras[3]._0=3;caras[3]._1=0;caras[3]._2=4;
caras[4]._0=3;caras[4]._1=1;caras[4]._2=0;
caras[5]._0=3;caras[5]._1=2;caras[5]._2=1;

//colores
colors_random();
}


//*************************************************************************
// clase objeto ply
//*************************************************************************


_objeto_ply::_objeto_ply() 
{
   // leer lista de coordenadas de vértices y lista de indices de vértices
 	
}



void _objeto_ply::parametros(char *archivo)
{
int n_ver,n_car;

vector<float> ver_ply ;
vector<int>   car_ply ;
 
_file_ply::read(archivo, ver_ply, car_ply );

n_ver=ver_ply.size()/3;
n_car=car_ply.size()/3;

printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

vertices.resize(n_ver);



for(int i = 0; i < n_ver; i++){
	vertices[i].x = ver_ply[i*3];
	vertices[i].y = ver_ply[i*3+1];
	vertices[i].z = ver_ply[i*3+2];
}

caras.resize(n_car);
for(int i = 0; i < n_car; i++){
	caras[i]._0 = car_ply[i*3];
	caras[i]._1 = car_ply[i*3+1];
	caras[i]._2 = car_ply[i*3+2];
}

//colores
colors_random();
}


//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion()
{

}

//Funcion de rotación
//A tener en cuenta: esta version de la funcion hace que no se repitan vertices/caras en caso
//de que hayan vertices del perfil a girar en el eje de giro, ya que, al encontrarse dichos
//vertices, no se duplican los mismos, y se forman estructuras con forma de "cono" en vez de
//crearse 2 caras cada 4 vertices. De esta forma, las clases esfera, cono y cilindro pueden
//generarse facilmente empleando esta función, sin necesidad de implementar "casos especiales".
void _rotacion::parametros(vector<_vertex3f> perfil, int num, bool tapa_in, bool tapa_su)
{
int i,j;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int num_aux=perfil.size();

//Comprobaciones para evitar repeticiones de vertices y caras
vector<bool> vertice_en_eje;
int vertices_rotables = 0;
vertice_en_eje.resize(num_aux);
for(int i = 0; i < num_aux; i++){
    vertice_en_eje[i] = (perfil[i].x == 0 && perfil[i].z == 0);
    if(!vertice_en_eje[i])
        vertices_rotables++;
}

// tratamiento de los vértices
vertices.resize(vertices_rotables*num     //Vertices que van a rotarse num veces
              + num_aux-vertices_rotables //Vertices que no van a rotar (estan en el eje de giro)
              /* (Version 1)
              + (vertice_en_eje[0] ? 0 : 1) //Vertice auxiliar inferior (si es necesario)
              + (vertice_en_eje[num_aux-1] ? 0 : 1) //Vertice auxiliar inferior (si es necesario)
              */
              );

int k = 0;
for (i = 0; i<num_aux; i++){       
    if(!vertice_en_eje[i]){
        for (j=0;j<num;j++){
            vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
                        perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
            vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                        perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
            vertice_aux.y=perfil[i].y;
            vertices[k]=vertice_aux;
            k++;
        }
    }
    else{
            vertices[k]=perfil[i];
            k++;
    }
}


//Vertices auxiliares (version anterior de tapas)
/*
//Vertice inferior
int vertice_inf, vertice_sup;
if(!vertice_en_eje[0]){
    vertice_aux.x = 0;
    vertice_aux.y = perfil[0].y;
    vertice_aux.z = 0;
    vertices[k] = vertice_aux;
    vertice_inf = k;
    k++;
}

//Vertice superior
if(!vertice_en_eje[num_aux-1]){
    vertice_aux.x = 0;
    vertice_aux.y = perfil[num_aux-1].y;
    vertice_aux.z = 0;
    vertices[k] = vertice_aux;
    vertice_sup = k;
    k++;
}
*/

// tratamiento de las caras
//calculo del numero de caras
int caras_por_lado = 0;
for(int nivel = 0; nivel < num_aux-1; nivel++){
    if(!vertice_en_eje[nivel] && !vertice_en_eje[nivel+1]){
        caras_por_lado+=2;
    }
    else if(vertice_en_eje[nivel] != vertice_en_eje[nivel+1]){
        caras_por_lado++;
    }
}
/* (Version anterior de tapas)
caras.resize(caras_por_lado*num
            + (vertice_en_eje[0]&&tapa_in ? 0 : num)            
            + (vertice_en_eje[num_aux-1]&&tapa_su ? 0 : num)  
            );
caras.clear();
*/
caras.resize(caras_por_lado*num
            + (vertice_en_eje[0]&&tapa_in ? 0 : num-2)            
            + (vertice_en_eje[num_aux-1]&&tapa_su ? 0 : num-2)  
            );
caras.clear();


//Caras laterales
int v_inicial = 0;
for(i=0; i < num_aux-1; i++){
	
    if(!vertice_en_eje[i] && !vertice_en_eje[i+1]){ //Caso 1: ambas capas tienen vertices rotables
        for(j=0; j < num; j++){
            //Cara 1
            cara_aux._0 = v_inicial+j;
            cara_aux._1 = v_inicial+(j+1)%num;
            cara_aux._2 = v_inicial+num+(j+1)%num;
            caras.push_back(cara_aux);
            //Cara 2
            cara_aux._0 = v_inicial+j;
            cara_aux._1 = v_inicial+num+(j+1)%num;
            cara_aux._2 = v_inicial+j+num;
            caras.push_back(cara_aux);
        }
        v_inicial+=num;
    }
    else if(vertice_en_eje[i] != vertice_en_eje[i+1]){//Caso 2: una capa tiene vertices rotables
        if(vertice_en_eje[i]){  //La capa de abajo tiene vertice en eje y
                                //Creamos la capa con forma de "cono invertido"
            for(j=0; j < num; j++){
                cara_aux._0 = v_inicial;
                cara_aux._1 = v_inicial+1+(j+1)%num;
                cara_aux._2 = v_inicial+1+j;
                caras.push_back(cara_aux);
            }
            v_inicial++;
        }
        else{   //La capa de arriba tiene vertice en eje y
		        //Creamos la capa con forma de "cono"
            for(j=0; j < num; j++){
                cara_aux._0 = v_inicial+j;
                cara_aux._1 = v_inicial+(j+1)%num;
                cara_aux._2 = v_inicial+num;
                caras.push_back(cara_aux);
            }
            v_inicial+=num;
        }
        
    }
    else{
        v_inicial++;
    }

}
/* (version anterior de tapas)
//tapa inferior
int v_actual = 0;
if(!vertice_en_eje[0]){
    for(i = 0; i < num; i++){
        cara_aux._0 = v_actual + i;
        cara_aux._1 = vertice_inf;     //Vertice central inferior
        cara_aux._2 = v_actual + (i+1) % num;
        caras.push_back(cara_aux);
    }
}

//tapa superior
v_actual = vertices.size() - num - 1;
if(!vertice_en_eje[num_aux-1]){
    for(i = 0; i < num; i++){
        cara_aux._0 = v_actual + i;
        cara_aux._1 = v_actual + (i+1) % num ;
        cara_aux._2 = vertice_sup; //Vertice central superior
        caras.push_back(cara_aux);
    }
}
*/
//Generacion de tapas (sin necesidad de vertices auxiliares)
//tapa inferior
int v1 = 0, v2 = 1, v3 = num-1;

if(!vertice_en_eje[0] && tapa_in){
    for(int i = 0; i < num-2; i++){
        if(v3 != v1 && v3 != v2){   //Si k no coincide con i/j
            cara_aux._0 = v1;
            cara_aux._1 = v3;     
            cara_aux._2 = v2;
            caras.push_back(cara_aux);            
        }
        else{
            i--;
        }
        v1++;
        v2++;
        v3--;
    }
}

//tapa superior
v1 =  vertices.size() - num;
v2 = v1+1;
v3 = vertices.size()-1;
if(!vertice_en_eje[num_aux-1] && tapa_su){
    for(int i = 0; i < num-2; i++){
        if(v3 != v1 && v3 != v2){   //Si k no coincide con i/j
            cara_aux._0 = v1;
            cara_aux._1 = v2;     
            cara_aux._2 = v3;
            caras.push_back(cara_aux);  
        }
        else{
            i--;
        }
        v1++;
        v2++;
        v3--;
    }
}


//colores
colors_random();

}

//************************************************************************
// constructor de cilindros
//************************************************************************
_cilindro::_cilindro(float radio, float altura){
    vector<_vertex3f> perfil;
    perfil.resize(2);
    //Punto de la base
    perfil[0].x = radio;
    perfil[0].y = 0;
    perfil[0].z = 0;
    //Punto superior
    perfil[1].x = radio;
    perfil[1].y = altura;
    perfil[1].z = 0;
    parametros(perfil, LADOS_CIRCULO, true, true);
}

//************************************************************************
// constructor de conos
//************************************************************************
_cono::_cono(float radio, float altura){
    vector<_vertex3f> perfil;
    perfil.resize(2);
    //Punto de la base
    perfil[0].x = radio;
    perfil[0].y = 0;
    perfil[0].z = 0;
    //Vertice superior
    perfil[1].x = 0;
    perfil[1].y = altura;
    perfil[1].z = 0;
    parametros(perfil, LADOS_CIRCULO, true, true);
}

//************************************************************************
// constructor de esferas
//************************************************************************
_esfera::_esfera(float radio){
    vector<_vertex3f> perfil;
    perfil.resize(LADOS_CIRCULO);
    float x = 0;
    float angulo = M_PI / LADOS_CIRCULO;
    for(int i = 0; i < LADOS_CIRCULO; i++, x+=angulo){
        perfil[i].x = sin(x)*radio;
        perfil[i].y = -cos(x)*radio;
        perfil[i].z = 0;
    }
    parametros(perfil, LADOS_CIRCULO, true, true);
}

//************************************************************************
// rotacion de perfil PLY
//************************************************************************

_rotacion_ply::_rotacion_ply(){

}

void _rotacion_ply::parametros(char *archivo, int num, bool tapa_in, bool tapa_su)
{
int n_ver,n_car;

vector<float> ver_ply ;
vector<int>   car_ply ;
vector<_vertex3f> perfil;
_vertex3f aux;
_file_ply::read(archivo, ver_ply, car_ply );

n_ver=ver_ply.size()/3;
n_car=car_ply.size()/3;

printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

for(int i = 0; i < n_ver; i++){
	aux.x = ver_ply[i*3];
	aux.y = ver_ply[i*3+1];
	aux.z = ver_ply[i*3+2];
	perfil.push_back(aux);
}

_rotacion::parametros(perfil, num, tapa_in, tapa_su);
}

//************************************************************************
// objeto por extrusión
//************************************************************************

_extrusion::_extrusion(vector<_vertex3f> poligono, float x, float y, float z, bool tapa_su, bool tapa_in)
{
int i;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int num_aux;

// tratamiento de los vértices

num_aux=poligono.size();
vertices.resize(num_aux*2);
for (i=0;i<num_aux;i++)
    {
      vertices[2*i]=poligono[i];
      vertices[2*i+1].x=poligono[i].x+x;
      vertices[2*i+1].y=poligono[i].y+y;
      vertices[2*i+1].z=poligono[i].z+z;
    }
    
// tratamiento de las caras 
int num_caras = num_aux*2;
if(tapa_su)
    num_caras += num_aux-2;
if(tapa_in)
    num_caras += num_aux-2;
caras.resize(num_caras);

//Caras laterales
int c=0;
for (i=0;i<num_aux;i++){
   caras[c]._0=i*2;
   caras[c]._1=(i*2+2)%(num_aux*2);
   caras[c]._2=i*2+1;    
   c=c+1;
   caras[c]._0=(i*2+2)%(num_aux*2);
   caras[c]._1=(i*2+2)%(num_aux*2)+1;
   caras[c]._2=i*2+1;    
   c=c+1;    
}

//Generacion de tapas (solo para poligonos concavos)
//tapa inferior
int v1 = 0, v2 = 2, v3 = 2*num_aux - 2;

if(tapa_in){
    for(int i = 0; i < num_aux-2; i++){
        if(v3 != v1 && v3 != v2){   //Si k no coincide con i/j
            cara_aux._0 = v1;
            cara_aux._1 = v3;     
            cara_aux._2 = v2;
            caras.push_back(cara_aux);            
        }
        else{
            i--;
        }
        v1+=2;
        v2+=2;
        v3-=2;
    }
}

//tapa superior
v1 = 1;
v2 = 3;
v3 = 2*num_aux-1;
if(tapa_su){
    for(int i = 0; i < num_aux-2; i++){
        if(v3 != v1 && v3 != v2){   //Si k no coincide con i/j
            cara_aux._0 = v1;
            cara_aux._1 = v2;     
            cara_aux._2 = v3;
            caras.push_back(cara_aux);  
        }
        else{
            i--;
        }
        v1+=2;
        v2+=2;
        v3-=2;
    }
}
   
colors_random();
}


//************************************************************************
// práctica 3, objeto jerárquico articulado
//************************************************************************

//************************************************************************
// semiesfera 
//************************************************************************
_semiesfera::_semiesfera(float radio, int num1, int num2){
    vector<_vertex3f> perfil;
    _vertex3f aux;
    int i;

    for (i=0;i<=num1;i++)
      {aux.x=radio*cos(M_PI*i/(num1*2.0));
       aux.y=radio*sin(M_PI*i/(num1*2.0));
       aux.z=0.0;
       perfil.push_back(aux);
      }
    parametros(perfil,num2,true,true);
    
}

//************************************************************************
// pala -> Aqui la llamaremos semicilindro
//************************************************************************

_semicilindro::_semicilindro(float radio, float ancho, int num)
{
vector<_vertex3f> perfil;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int i, j;

vertice_aux.x=radio; vertice_aux.y=0; vertice_aux.z=-ancho/2.0;
perfil.push_back(vertice_aux);
vertice_aux.z=ancho/2.0;
perfil.push_back(vertice_aux);

// tratamiento de los vértices

for (j=0;j<=num;j++)
  {for (i=0;i<2;i++)	
     {
      vertice_aux.x=perfil[i].x*cos(M_PI*j/(1.0*num))-
                    perfil[i].y*sin(M_PI*j/(1.0*num));
      vertice_aux.y=perfil[i].x*sin(M_PI*j/(1.0*num))+
                    perfil[i].y*cos(M_PI*j/(1.0*num));
      vertice_aux.z=perfil[i].z;
      vertices.push_back(vertice_aux);
     }
  }
  
// tratamiento de las caras 

for (j=0;j<num;j++)
   {cara_aux._0=j*2;
    cara_aux._1=(j+1)*2;
    cara_aux._2=(j+1)*2+1;
    caras.push_back(cara_aux);
    
    cara_aux._0=j*2;
    cara_aux._1=(j+1)*2+1;
    cara_aux._2=j*2+1;
    caras.push_back(cara_aux);
   }
   
// tapa inferior
vertice_aux.x=0;
vertice_aux.y=0;
vertice_aux.z=-ancho/2.0;
vertices.push_back(vertice_aux); 

for (j=0;j<num;j++)
   {cara_aux._0=j*2;
    cara_aux._1=(j+1)*2;
    cara_aux._2=vertices.size()-1;
    caras.push_back(cara_aux);
   }
  
// tapa superior
vertice_aux.x=0;
vertice_aux.y=0;
vertice_aux.z=ancho/2.0;
vertices.push_back(vertice_aux); 

for (j=0;j<num;j++)
   {cara_aux._0=j*2+1;
    cara_aux._1=(j+1)*2+1;
    cara_aux._2=vertices.size()-1;
    caras.push_back(cara_aux);
   }
  
colors_random();
}

//************************************************************************
// chasis
//************************************************************************

_chasis::_chasis(){
    largo1 = 4;       alto1 = 0.10;    ancho1 = 0.5;
    largo2 = 2.5;     alto2 = 0.10;    ancho2 = 2.25;
    largo3 = 4;       alto3 = 0.10;    ancho3 = 4;
    largo4 = 2.5;     alto4 = 0.10;    ancho4 = 2;
    largo5 = 4;       alto5 = 0.10;    ancho5 = 1;
    largo6 = 4;       alto6 = 0.10;    ancho6 = 1;
    vector<_vertex3f> poligono;
    _vertex3f aux;
    aux.x = -largo5 / 2; aux.y = alto5; aux.z = 0;
    poligono.push_back(aux);
    aux.x = -largo5 / 2; aux.y = 0; aux.z = 0;
    poligono.push_back(aux);
    aux.x = largo5 / 2; aux.y = 0; aux.z = 0;
    poligono.push_back(aux);
    aux.x = largo5 / 2; aux.y = alto5; aux.z = 0;
    poligono.push_back(aux);
    extrusion = new  _extrusion(poligono, 0, alto5, ancho5, true, true);
    
}


void _chasis::draw(_modo modo, float r, float g, float b, float grosor){
    glPushMatrix();
        
        //Pieza 6
        glTranslatef(0, 0, ancho6/2);
        glPushMatrix();
            glTranslatef(0, alto6, 0);
            glScalef(largo6, alto6, ancho6);
            cubo.draw(modo, r, g, b, grosor);
        glPopMatrix();
        
        glTranslatef(0, 0, ancho6/2 + ancho5);
        
        //Pieza 5
        glPushMatrix();
            glRotatef(180, 0, 1, 0);
            extrusion->draw(modo, r, g, b, grosor);
        glPopMatrix();
        //Pieza 4
        glTranslatef(0, 0, ancho4/2);
        glPushMatrix();
            glScalef(largo4, alto4, ancho4);
            cubo.draw(modo, r, g, b, grosor);
        glPopMatrix();
        //Pieza 3
        glTranslatef(0, 0, ancho4/2 + ancho3/2);
        glPushMatrix();
            glScalef(largo3, alto3, ancho3);
            cubo.draw(modo, r, g, b, grosor);
        glPopMatrix();
        //Pieza 2
        glTranslatef(0, 0, ancho3/2 + ancho2/2);
        glPushMatrix();
            glScalef(largo2, alto2, ancho2);
            cubo.draw(modo, r, g, b, grosor);
        glPopMatrix();
        //Pieza 1
        glTranslatef(0, 0, ancho2/2 + ancho1/2);
        glPushMatrix();
            glScalef(largo1, alto1, ancho1);
            cubo.draw(modo, r, g, b, grosor);
        glPopMatrix();
    glPopMatrix();
}

void _chasis::asignar_color(_color color){
    cubo.asignar_color(color);
    extrusion->asignar_color(color);
}

//************************************************************************
// guardabarros 
//************************************************************************

_guardabarros::_guardabarros(){
    largo = 0.75;
    alto = 1; //alto = radio
    ancho = 2.25;
    lados_curva = LADOS_CIRCULO / 2;
    float angulo = (M_PI / lados_curva) * 2;
    //Creamos una extrusion por cada lado de la curva
    _vertex3f v_anterior;
    v_anterior.x = -largo/2; v_anterior.y = 0; v_anterior.z = alto;
    for(int i = 1; i <= lados_curva / 4; i++){
        vector<_vertex3f> poligono;
        _vertex3f aux;
        _extrusion * arco;
        //Vertice a misma altura que vertice nuevo
        aux.x = -largo / 2;  aux.y = alto*sin(angulo*i); aux.z = ancho/2;
        poligono.push_back(aux);
        //Vertice a misma altura que vertice antiguo
        aux.x = -largo / 2;  aux.y = alto*sin(angulo*(i-1)); aux.z = ancho/2;
        poligono.push_back(aux);
        //Vertice de la curva anterior
        poligono.push_back(v_anterior);
        //Vertice nuevo de la curva
        aux.x = -largo / 2;  aux.y = alto*sin(angulo*i); aux.z = alto*cos(angulo*i);
        poligono.push_back(aux);
        poligono.push_back(aux);
        //Crear extrusion
        arco = new  _extrusion(poligono, largo, 0, 0, true, true);
        curva.push_back(arco);
        arco = NULL;
        //Actualizar v_anterior
        v_anterior = aux;
    }
    
}


void _guardabarros::draw(_modo modo, float r, float g, float b, float grosor){
    //glTranslatef(-largo, 0, 0);
    for(int i = 0; i < curva.size(); i++){
        glPushMatrix();
            curva[i]->draw(modo, r, g, b, grosor);
            glRotatef(180, 0, 1, 0);
            curva[i]->draw(modo, r, g, b, grosor);
        glPopMatrix();    
    }
}

void _guardabarros::asignar_color(_color color){
    for(int i = 0; i < curva.size(); i++)
        curva[i]->asignar_color(color);
}


//************************************************************************
// carroceria lateral
//************************************************************************

_carroceria_lateral::_carroceria_lateral(bool lado_izquierdo){
    coef = lado_izquierdo ? 0 : 1;
    largo1 = 0.5;           alto1 = 0.75;         ancho1 = 3;       altura1 = 1;
    largo2 = 0.5;           alto2 = altura1;      ancho2 = 0.25;
    largo3 = 0.75;          alto3 = altura1;      ancho3 = 2.25;
    largo_cil = 0.25;       alto_cil = 0.25;      ancho_cil = 0.25;
    largo4 = 0.25;          alto4 = altura1;      ancho4 = ancho3;
    largo5 = 0.5;           alto5 = altura1;      ancho5 = 0.5;
    largo6 = 0.25;          alto6 = 0.25;         ancho6 = 2.25;
    largo7 = 0.5;           alto7 = 1;            ancho7 = 1.25;
    largo8 = 0.75;          alto8 = altura1;      ancho8 = 2;
    largo9 = 0.25;          alto9 = altura1;      ancho9 = ancho8;
    largo10 = largo1;       alto10 = 1;           ancho10 = 1;
    largo11 = largo1;       alto11 = 0.9;         ancho11 = 0.75;   altura11 = 0.1;
    largo12 = largo1;       alto12 = 0.75;        ancho12 = 5;      altura12 = 1;
    //Extrusion pieza 10
    vector<_vertex3f> poligono;
    _vertex3f aux;
    aux.x = -largo10/2;   aux.y = 0;            aux.z = 0;
    poligono.push_back(aux);
    aux.x = -largo10/2;   aux.y = altura11;     aux.z = -ancho10;
    poligono.push_back(aux);
    aux.x = -largo10/2;   aux.y = alto10;       aux.z = -ancho10;
    poligono.push_back(aux);
    aux.x = -largo10/2;   aux.y = alto10;       aux.z = 0;
    poligono.push_back(aux);
    pieza10 = new _extrusion(poligono, largo10, 0, 0, true, true);
    
    
}

void _carroceria_lateral::draw(_modo modo, float r, float g, float b, float grosor){
    glPushMatrix();
        
        //Pieza 12.5 - Cobertura parte baja pieza 12
        glPushMatrix();
            glTranslatef(0, altura12, ancho12/2);
            glScalef(largo12, alto12/2, ancho12);
            cubo.draw(modo, r, g, b, grosor);
        glPopMatrix();
        //Pieza 12 - Parte superior pieza trasera
        glPushMatrix();
            glTranslatef(0, altura12+alto12/2, ancho12/2);
            glScalef(largo12, alto12, ancho12);
            semicilindro.draw(modo, r, g, b, grosor);
        glPopMatrix();

        //Pieza 11 - Parte lateral pre-final
        glPushMatrix();
            glTranslatef(0, altura11, ancho11/2);
            glScalef(largo11, alto11, ancho11);
            cubo.draw(modo, r, g, b, grosor);
        glPopMatrix();
        glTranslatef(0, 0, ancho10 + ancho11);
        
        //Pieza 10 - Parte lateral detras de guardabarros trasero
        glPushMatrix();
            pieza10->draw(modo, r, g, b, grosor);
        glPopMatrix();
        
        //Eje de rueda
        glPushMatrix();
            glTranslatef((largo1-largo8)*(1-3*coef), 0, ancho8/2);
            glScalef(largo_cil, alto_cil, ancho_cil);
            glRotatef(90, 0, 0, 1);
            cilindro.draw(modo, r, g, b, grosor);
        glPopMatrix();
        
        //Pieza 9 - Parte trasera a la rueda trasera
        glPushMatrix();
            glTranslatef((largo9/2-largo8)*(1-2*coef), 0, ancho8/2);
            glScalef(largo9, alto9, ancho9);
            cubo.draw(modo, r, g, b, grosor);
        glPopMatrix();
        

        //Pieza 8 - Guardabarros rueda trasera (arco)
        glPushMatrix();
            glTranslatef((largo1/2-largo8/2)*(1-2*coef), 0, ancho8/2);
            glScalef(1, 1, ancho8/ancho3);
            gb.draw(modo, r, g, b, grosor);
        glPopMatrix();
        glTranslatef(0, 0, ancho8);
    
        //Pieza 7 - Carroceria lateral - Parte detras de puerta
        glPushMatrix();
            glTranslatef(0, 0, ancho7/2);
            glScalef(largo7, alto7, ancho7);
            cubo.draw(modo, r, g, b, grosor);
        glPopMatrix();
        glTranslatef(0, 0, ancho7);
        
        //Pieza 6 - Parte lateral por debajo de la puerta
        glPushMatrix();
            glTranslatef(largo6/2*(1-2*coef), 0, ancho6/2);
            glScalef(largo6, alto6, ancho6);
            cubo.draw(modo, r, g, b, grosor);
        glPopMatrix();
        
        glTranslatef(0, 0, ancho6);
        
        //Pieza 5 - Parte lateral detras de guardabarros
        glPushMatrix();
            glTranslatef(0, 0, ancho5/2);
            glScalef(largo5, alto5, ancho5);
            cubo.draw(modo, r, g, b, grosor);
        glPopMatrix();
        
        //Eje de rueda
        glPushMatrix();
            //1-3? -> El cilindro no está alineado al centro (tam_cilindro = largo1 - largo3)
            glTranslatef((largo1-largo3)*(1-3*coef), 0, ancho1-ancho2-ancho4/2);    
            glScalef(largo_cil, alto_cil, ancho_cil);
            glRotatef(90, 0, 0, 1);
            cilindro.draw(modo, r, g, b, grosor);
        glPopMatrix();
        
        //Pieza 4 - Parte trasera a la rueda
        glPushMatrix();
            glTranslatef((largo4/2-largo3)*(1-2*coef), 0, ancho1-ancho2-ancho4/2);
            glRotatef(coef*180, 0, 1, 0);
            glScalef(largo4, alto4, ancho4);
            cubo.draw(modo, r, g, b, grosor);
        glPopMatrix();
        
        //Pieza 3 - Guardabarros rueda delantera (arco)
        glPushMatrix();
            glTranslatef((largo1/2-largo3/2)*(1-2*coef), 0, ancho1-ancho2-ancho3/2);
            gb.draw(modo, r, g, b, grosor);
        glPopMatrix();
    
        //Pieza 2 - Parte lateral delantera
        glPushMatrix();
            glTranslatef(0, 0, ancho1 - ancho2/2);
            glScalef(largo2, alto2, ancho2);
            cubo.draw(modo, r, g, b, grosor);
        glPopMatrix();
        //Pieza 1.5 - Cobertura parte baja pieza 1
        glPushMatrix();
            glTranslatef(0, altura1, ancho1/2);
            glScalef(largo1, alto1/2, ancho1);
            cubo.draw(modo, r, g, b, grosor);
        glPopMatrix();
        //Pieza 1 - Parte lateral superior
        glPushMatrix();
            glTranslatef(0, altura1+alto1/2, ancho1/2);
            glScalef(largo1, alto1, ancho1);
            semicilindro.draw(modo, r, g, b, grosor);
        glPopMatrix();
    glPopMatrix();
}

void _carroceria_lateral::asignar_color(_color color){
    cubo.asignar_color(color);
    cilindro.asignar_color(color);
    gb.asignar_color(color);
    pieza10->asignar_color(color);
    semicilindro.asignar_color(color);
}

//************************************************************************
// rueda
//************************************************************************

_rueda::_rueda(){
    //CAMBIAR VALORES "MAGICOS" POR VARIABLES
    
    vector<_vertex3f> perfil;
    _vertex3f aux;
    aux.x = 0; aux.y = 0; aux.z = 0;
    perfil.push_back(aux);
    aux.x = 0.125; aux.y = 0; aux.z = 0;
    perfil.push_back(aux);
    aux.x = 0.65; aux.y = 0; aux.z = 0;
    perfil.push_back(aux);
    float angulo = M_PI / (LADOS_CIRCULO/8);
    for(int i = 1; i < LADOS_CIRCULO/8; i++){
        aux.x = 0.65 + 0.15*sin(i*angulo); aux.y = 0.15-0.15*cos(i*angulo); aux.z = 0;
        perfil.push_back(aux);
    }
    aux.x = 0.65; aux.y = 0.3; aux.z = 0;
    perfil.push_back(aux);
    aux.x = 0.5; aux.y = 0.31; aux.z = 0;
    perfil.push_back(aux);
    aux.x = 0.47; aux.y = 0.33; aux.z = 0;
    perfil.push_back(aux);
    aux.x = 0.15; aux.y = 0.33; aux.z = 0;
    perfil.push_back(aux);
    aux.x = 0.05; aux.y = 0.3; aux.z = 0;
    perfil.push_back(aux);
    aux.x = 0; aux.y = 0.33; aux.z = 0;
    perfil.push_back(aux);

    rotacion.parametros(perfil, LADOS_CIRCULO/4, true, true);
}


void _rueda::draw(_modo modo, float r, float g, float b, float grosor){
    glPushMatrix();
        //glTranslatef(0.15, 0, 0);
        glRotatef(270, 0, 0, 1);
        rotacion.draw(modo, r, g, b, grosor);
    glPopMatrix();
}

void _rueda::asignar_color(_color color_rueda, _color color_llanta){
    rotacion.asignar_color(color_llanta);
    for(int i = LADOS_CIRCULO/2 + LADOS_CIRCULO/4; i < LADOS_CIRCULO/2 + (LADOS_CIRCULO/8) * (LADOS_CIRCULO/2) + LADOS_CIRCULO/4; i++){
        rotacion.colores[i] = color_rueda;
    }
}
//************************************************************************
// retrovisor
//************************************************************************

_retrovisor::_retrovisor(bool lado_izquierdo){
    coef = lado_izquierdo ? 0 : 1;
    largo1 = 0.25, alto1 = 0.2, ancho1 = 0.05;
    largo2 = 0.2, alto2 = 0.02, ancho2 = 0.02;
    
}


void _retrovisor::draw(_modo modo, float r, float g, float b, float grosor){
    //Pieza 2 - Brazo 
    glPushMatrix();
        glRotatef(30*(1-2*coef), 0, 0, 1);
        glTranslatef((-largo2/2+0.02)*(1-2*coef), 0, 0);
        glScalef(largo2, alto2, ancho2);
        glTranslatef(-0.5, 0, 0);   //Centramos el cilindro
        glRotatef(90, 0, 0, -1);
        cilindro.draw(modo, r, g, b, grosor);
    glPopMatrix();
    
    //Pieza 1 - Espejo retrovisor
    glTranslatef((largo1/2)*(1-2*coef), 0, 0);
    glRotatef(10*(1-2*coef), 0, 1, 0);
    glPushMatrix();
    glScalef(largo1, alto1, ancho1);
        glTranslatef(0, 0, -0.5);   //Centramos el cilindro
        glRotatef(90, 1, 0, 0);
        cilindro.draw(modo, r, g, b, grosor);
    glPopMatrix();
    //Cristal
    glTranslatef(0, 0, -ancho1/2 - ancho1/6);
    glScalef(largo1*0.95, alto1*0.95, ancho1/3);
    glTranslatef(0, 0, -0.5);   //Centramos el cilindro
    glRotatef(90, 1, 0, 0);
    cristal.draw(modo, r, g, b, grosor);
}

void _retrovisor::asignar_color(_color color_cristal, _color color_trasero){
    cristal.asignar_color(color_cristal);
    cilindro.asignar_color(color_trasero);
}

//************************************************************************
// puerta
//************************************************************************

_puerta::_puerta(bool lado_izquierdo){
    coef = lado_izquierdo ? 0 : 1;
    retrovisor = new _retrovisor(lado_izquierdo);
    
    largo1 = 0.25, alto1 = 1.5, ancho1 = 2.25;
    pos_largo_r = largo1/2 + 0.125, pos_alto_r = alto1+0.05, pos_ancho_r = -ancho1*2/11;
}


void _puerta::draw(_modo modo, float r, float g, float b, float grosor){
    //Pieza 2 - Retrovisor
    glPushMatrix();
        glTranslatef(pos_largo_r*(1-2*coef), pos_alto_r, pos_ancho_r);
        retrovisor->draw(modo, r, g, b, grosor);
    glPopMatrix();
    //Pieza 1 - Cuerpo de la puerta
    glPushMatrix();
        glTranslatef(0, 0, -ancho1/2);
        glScalef(largo1, alto1, ancho1);
        cubo.draw(modo, r, g, b, grosor);
    glPopMatrix();
}
void _puerta::asignar_color(_color color_puerta, _color color_cristal, _color color_trasero){
    retrovisor->asignar_color(color_cristal, color_trasero);
    cubo.asignar_color(color_puerta);
}

//************************************************************************
// cuerpo delantero
//************************************************************************
_cuerpo_delantero::_cuerpo_delantero(){
    largo1 = 1, alto1 = 1, ancho1 = 0.05;
    largo2 = 3, alto2 = 0.5, ancho2 = 3;
    escalaY = 0.4641;
    ancho2_escalado = 0.4483*2;
    alto2_escalado = 0.28;
    largo3 = 3, alto3 = 0.5, ancho3 = 3.25;
}


void _cuerpo_delantero::draw(_modo modo, float r, float g, float b, float grosor){
    //Pieza 2 - Caja del motor
    glTranslatef(0, 0, ancho2/2);
    glPushMatrix();
        //glTranslatef(0, 0, -ancho2/2);
        glScalef(largo3, alto3, ancho3);
        cubo.draw(modo, r, g, b, grosor);
    glPopMatrix();
    
    //Pieza 1 - Capó + parabrisas
    glPushMatrix();
        glTranslatef(0, alto3, 0.25/2);
        glScalef(largo2, alto2/alto2_escalado, ancho2/ancho2_escalado);
        glRotatef(15, 1, 0, 0);
        glScalef(1, escalaY, 1);    //Queremos que la parte de delante este tumbada
        glRotatef(30, -1, 0, 0);
        semicilindro.draw(modo, r, g, b, grosor);
        glTranslatef(0, 0, -0.5);
        glScalef(largo1, alto1, ancho1);
        parabrisas.draw(modo, r, g, b, grosor);   //Parabrisas
    glPopMatrix();
}

void _cuerpo_delantero::asignar_color(_color color_capo, _color color_cristal){
    semicilindro.asignar_color(color_capo);
    cubo.asignar_color(color_capo);
    parabrisas.asignar_color(color_cristal);
}

//************************************************************************
// faro delantero
//************************************************************************
_faro_delantero::_faro_delantero(){
    largo1 = 0.5;       alto1 = 0.5;           ancho1 = 0.25;
    radio_f1 = 0.4;     ancho_f1 = 0.05;       altura_f1 = 0.7;
    radio_f2 = 0.3;     ancho_f2 = ancho_f1;   altura_f2 = 0.25;
}


void _faro_delantero::draw(_modo modo, float r, float g, float b, float grosor){
    glScalef(0.95, 0.95, 1);
    glTranslatef(0, 0, ancho1/2);
    
    glPushMatrix();
        //Pieza 3 - Parte inferior
        glPushMatrix();
            glTranslatef(0, alto1/2, 0);
            glScalef(largo1, alto1, ancho1);
            glRotatef(180, 1, 0, 0);
            semicilindro.draw(modo, r, g, b, grosor);
        glPopMatrix();
        
        //Pieza 2 - Parte media
        glTranslatef(0, alto1/2, 0);
        glPushMatrix();
            glScalef(largo1, alto1, ancho1);
            cubo.draw(modo, r, g, b, grosor);
        glPopMatrix();
        
        //Pieza 1 - Parte superior
        glPushMatrix();
            glTranslatef(0, alto1, 0);
            glScalef(largo1, alto1, ancho1);
            semicilindro.draw(modo, r, g, b, grosor);
        glPopMatrix();
    glPopMatrix();
    
    //Cambio de orden al pintar las piezas (transparencia)
    //Pieza 5 - Luces inferiores
    glPushMatrix();
        glTranslatef(0, altura_f2, ancho_f2/2 + ancho1/2);
        glScalef(radio_f2, radio_f2, ancho_f2);
        glTranslatef(0, 0, -0.5);
        glRotatef(90, 1, 0, 0);
        cilindro.draw(modo, r, g, b, grosor);
    glPopMatrix();
    
    //Pieza 4 - Luces superiores
    glPushMatrix();
        glTranslatef(0, altura_f1, ancho_f1/2 + ancho1/2);
        glScalef(radio_f1, radio_f1, ancho_f1);
        glTranslatef(0, 0, -0.5);
        glRotatef(90, 1, 0, 0);
        cilindro.draw(modo, r, g, b, grosor);
    glPopMatrix();
}

void _faro_delantero::asignar_color(_color color_cuerpo, _color color_cristal){
    cilindro.asignar_color(color_cristal);
    semicilindro.asignar_color(color_cuerpo);
    cubo.asignar_color(color_cuerpo);
}

//************************************************************************
// luz antiniebla
//************************************************************************
_luz_antiniebla::_luz_antiniebla(){
    largo1 = 0.25;      alto1 = 0.25;       ancho1 = 0.25;
    largo2 = 0.5;       alto2 = 0.25;       ancho2 = 0.25;
}


void _luz_antiniebla::draw(_modo modo, float r, float g, float b, float grosor){
    glTranslatef(largo2, 0, 0);  //Centramos el objeto
    
    //Parte 4 - Lateral derecha
    glPushMatrix();
        glTranslatef(0, alto1/2, 0);
        glScalef(largo1, alto1, ancho1);
        glRotatef(90, 0, 0, -1);
        semicilindro_d.draw(modo, r, g, b, grosor);
    glPopMatrix();
    
    //Parte 3 - Centro - derecha
    glTranslatef(-largo2/2, 0, 0);
    glPushMatrix();
        glScalef(largo2, alto2, ancho2);
        cubo_d.draw(modo, r, g, b, grosor);
    glPopMatrix();
    //Parte 2 - Centro - izquierda
    glTranslatef(-largo2, 0, 0);
    
    glPushMatrix();
        glScalef(largo2, alto2, ancho2);
        cubo_i.draw(modo, r, g, b, grosor);
    glPopMatrix();
    
    //Parte 1 - Lateral izquierdo
    glTranslatef(-largo2/2, alto1/2, 0);
    glPushMatrix();
        glScalef(largo1, alto1, ancho1);
        glRotatef(90, 0, 0, 1);
        semicilindro_i.draw(modo, r, g, b, grosor);
    glPopMatrix(); 
}

void _luz_antiniebla::asignar_color(_color color_izq, _color color_der){
    semicilindro_i.asignar_color(color_izq);
    semicilindro_d.asignar_color(color_der);
    cubo_i.asignar_color(color_izq);
    cubo_d.asignar_color(color_der);
}

//************************************************************************
// morro
//************************************************************************
_morro::_morro(){
    largo1 = 3;      alto1 = 1;       ancho1 = 0.05;
    largo2 = 3;      radio2 = 0.05;
    largo5 = 3;      alto5 = 0.25;    ancho5 = 0.15;
    largo_pos_antiniebla = 1.3;    alto_pos_antiniebla = 0.25; ancho_pos_antiniebla =0;
    separacion2 = 0.1;
}


void _morro::draw(_modo modo, float r, float g, float b, float grosor){
    
    glPushMatrix();
        //Pieza 5 - Bigotera
        glPushMatrix();
            glTranslatef(0, alto1, ancho1 + radio2 + ancho5/2);
            glScalef(largo5, alto5, ancho5);
            bigotera.draw(modo, r, g, b, grosor);
        glPopMatrix();
        
        //Pieza 4 - Luces antiniebla - derecha
        glPushMatrix();
            glTranslatef(-largo_pos_antiniebla, alto_pos_antiniebla, ancho1 + radio2);
            luz_antiniebla_d.draw(modo, r, g, b, grosor);
        glPopMatrix();
        //Pieza 3 - Luces antiniebla - izquierda
        glPushMatrix();
            glTranslatef(largo_pos_antiniebla, alto_pos_antiniebla, ancho1 + radio2);
            luz_antiniebla_i.draw(modo, r, g, b, grosor);
        glPopMatrix();
        //Pieza 2 - Barras parrilla
        glPushMatrix();
            glTranslatef(0, -radio2, 0);
            for(int i = 1; i < alto1/separacion2; i++){
                glTranslatef(0, separacion2, 0);
                glPushMatrix();
                glTranslatef(0, 0, ancho1/2);
                glScalef(largo2, radio2, radio2);
                glRotatef(45, 1, 0, 0);
                cubo.draw(modo, r, g, b, grosor);
                
                glPopMatrix();
                
            }
        glPopMatrix();
        //Pieza 1 - Parte trasera de la parrilla
        //glTranslatef
        glPushMatrix();
            glScalef(largo1, alto1, ancho1);
            parrilla.draw(modo, r, g, b, grosor);
        glPopMatrix();
    glPopMatrix();
}

void _morro::asignar_color(_color color_intermitente, _color color_faro_an, _color barras_parrilla, _color color_parrilla, _color color_bigotera){
    luz_antiniebla_d.asignar_color(color_intermitente, color_faro_an);
    luz_antiniebla_i.asignar_color(color_faro_an, color_intermitente);
    cubo.asignar_color(barras_parrilla);
    bigotera.asignar_color(color_bigotera);
    parrilla.asignar_color(color_parrilla);
}

//************************************************************************
// parachoques delantero
//************************************************************************
_parachoques_delantero::_parachoques_delantero(){
    largo1 = 0.25;      alto1 = 0.5;       ancho1 = 0.75;
    largo2 = 2.02;       alto2 = 0.5;       ancho2 = 0.25;
}

void _parachoques_delantero::draw(_modo modo, float r, float g, float b, float grosor){
    
    glTranslatef(-2, -0.25, 0);
    //Pieza 4 - Parte frontal derecha
    glPushMatrix();
        glRotatef(5, 0, -1, 0);
        glTranslatef(0, alto1/2, 0);
        glScalef(largo2, alto2, ancho2);
        glRotatef(90, 0, 0, -1);
        cilindro.draw(modo, r, g, b, grosor);
    glPopMatrix();
    //Pieza 3 - Parte lateral derecha
    
    glPushMatrix();
        glTranslatef(0, 0, ancho2/2-ancho1/2);
        glScalef(largo1, alto1, ancho1);
        cubo.draw(modo, r, g, b, grosor);
    glPopMatrix();
        
    //Pieza 2 - Parte frontal izquierda
    glTranslatef(4, 0, 0);
    glPushMatrix();
        glRotatef(5, 0, 1, 0);
        glTranslatef(0, alto1/2, 0);
        glScalef(largo2, alto2, ancho2);
        glRotatef(90, 0, 0, 1);
        cilindro.draw(modo, r, g, b, grosor);
    glPopMatrix();
    //Pieza 1 - Parte lateral izquierda
    glTranslatef(0, 0, ancho2/2-ancho1/2);
    glPushMatrix();
        glScalef(largo1, alto1, ancho1);
        cubo.draw(modo, r, g, b, grosor);
    glPopMatrix();
}

void _parachoques_delantero::asignar_color(_color color_parachoques){
    cubo.asignar_color(color_parachoques);
    cilindro.asignar_color(color_parachoques);
}
//************************************************************************
// luces traseras
//************************************************************************
_luz_trasera::_luz_trasera(){
    radio1 = 0.5;  ancho1 = 0.15;
    radio2 = 0.45; ancho2 = 0.15;
}

void _luz_trasera::draw(_modo modo, float r, float g, float b, float grosor){
    //Pieza 1 - Base
    glPushMatrix();
        glTranslatef(0, 0, -ancho1);
        glScalef(radio1, radio1, ancho1);
        glRotatef(90, 1, 0, 0);
        cilindro.draw(modo, r, g, b, grosor);
    glPopMatrix();
    
    //(cambio de orden por transparencia)
    //Pieza 2 - Faro
    glPushMatrix();
        glScalef(radio2/2, radio2/2, ancho2);
        glRotatef(90, 1, 0, 0);
        semiesfera.draw(modo, r, g, b, grosor);
    glPopMatrix();
    
    
}

void _luz_trasera::asignar_color(_color color_base, _color color_luz){
    cilindro.asignar_color(color_base);
    semiesfera.asignar_color(color_luz);
}
//************************************************************************
// parachoques trasero
//************************************************************************
_parachoques_trasero::_parachoques_trasero(){
    largo1 = 0.25;        alto1 = 0.25;       ancho1 = 1.15;
    largo2 = 2.14;        alto2 = 0.25;       ancho2 = 0.25;
}

void _parachoques_trasero::draw(_modo modo, float r, float g, float b, float grosor){
    glRotatef(180, 0, 1, 0);
    glTranslatef(-2.125, 0, -ancho2/2); //Centrar el objeto
    //Pieza 4 - Parte frontal derecha
    glPushMatrix();
        glRotatef(5, 0, -1, 0);
        glTranslatef(0, alto1/2, 0);
        glScalef(largo2, alto2, ancho2);
        glRotatef(90, 0, 0, -1);
        cilindro.draw(modo, r, g, b, grosor);
    glPopMatrix();
    //Pieza 3 - Parte lateral derecha
    glPushMatrix();
        glTranslatef(0, 0, ancho2/2-ancho1/2);
        glScalef(largo1, alto1, ancho1);
        cubo.draw(modo, r, g, b, grosor);
    glPopMatrix();
        
    //Pieza 2 - Parte frontal izquierda
    glTranslatef(4.25, 0, 0);
    glPushMatrix();
        glRotatef(5, 0, 1, 0);
        glTranslatef(0, alto1/2, 0);
        glScalef(largo2, alto2, ancho2);
        glRotatef(90, 0, 0, 1);
        cilindro.draw(modo, r, g, b, grosor);
    glPopMatrix();
    //Pieza 1 - Parte lateral izquierda
    glTranslatef(0, 0, ancho2/2-ancho1/2);
    glPushMatrix();
        glScalef(largo1, alto1, ancho1);
        cubo.draw(modo, r, g, b, grosor);
    glPopMatrix();
}

void _parachoques_trasero::asignar_color(_color color_parachoques){
    cubo.asignar_color(color_parachoques);
    cilindro.asignar_color(color_parachoques);
}

//************************************************************************
// maletero
//************************************************************************
_maletero::_maletero(float _angulo_puerta){
    angulo_puerta = _angulo_puerta;
    largo1 = 3;                         alto1 = 1.025;            ancho1 = 0.25;
    largo2 = 3;                         alto2 = 0.25;             ancho2 = 2.5;
    largo3 = 3;                         alto3 = 0.25;             ancho3 = ancho1 + ancho2;
    largo4 = 0.25;                      alto4 = alto1 - alto2;    ancho4 = 1.5;
    largo5 = largo1-2*largo4-0.0001;    alto5 = alto1 - alto2;    ancho5 = 0.25;
    largo6 = 0.25;                      alto6 = 0.25;             ancho6 = ancho3 - ancho4 - ancho1;
    largo_m = 1.25;                      alto_m = 0.25;            ancho_m = 0.05;
}

void _maletero::draw(_modo modo, float r, float g, float b, float grosor){
    
    glTranslatef(0, 0, ancho3/2);
    glRotatef(180, 0, 1, 0);
    //Pieza 6.2 - Parte lateral izquierda(sobre el guardabarros trasero)
    glPushMatrix();
        glTranslatef(-largo1/2 + largo4/2, alto4, ancho6/2-ancho3/2);
        glScalef(largo6, alto6, ancho6);
        cubo.draw(modo, r, g, b, grosor);
    glPopMatrix();
    //Pieza 6.1 - Parte lateral derecha(sobre el guardabarros trasero)
    glPushMatrix();
        glTranslatef(largo1/2 - largo4/2, alto4, ancho6/2-ancho3/2);
        glScalef(largo6, alto6, ancho6);
        cubo.draw(modo, r, g, b, grosor);
    glPopMatrix();
    
    //Pieza 5 - Parte trasera maletero
    glPushMatrix();
        glTranslatef(0, alto3, ancho5/2-ancho3/2);
        glScalef(largo5, alto5, ancho5);
        cubo.draw(modo, r, g, b, grosor);
    glPopMatrix();
    
    //Pieza 4.2 - Lateral izquierdo maletero
    glPushMatrix();
        glTranslatef(-largo1/2 + largo4/2, alto3, ancho3/2 - ancho4/2 - ancho1);
        glScalef(largo4, alto4, ancho4);
        cubo.draw(modo, r, g, b, grosor);
    glPopMatrix();
    //Pieza 4.1 - Lateral derecho maletero
    glPushMatrix();
        glTranslatef(largo1/2 - largo4/2, alto3, ancho3/2 - ancho4/2 - ancho1);
        glScalef(largo4, alto4, ancho4);
        cubo.draw(modo, r, g, b, grosor);
    glPopMatrix();
    //Pieza 3 - Base del maletero
    //glTranslatef(0, 0, ancho2/2);
    glPushMatrix();
        glScalef(largo3, alto3, ancho3);
        cubo.draw(modo, r, g, b, grosor);
    glPopMatrix();
    //Puerta maletero
    glTranslatef(0, alto1, -ancho3/2);
    //Aplicacion del giro de la puerta
    glRotatef(angulo_puerta, -1, 0, 0);
    //Pieza 2 - Puerta del maletero / Parte horizontal
    glTranslatef(0, 0, ancho2/2);
    glPushMatrix();
        glScalef(largo2, alto2, ancho2);
        cubo.draw(modo, r, g, b, grosor);
    glPopMatrix();
    
    glTranslatef(0, alto2 - alto1, ancho2/2);
    //Matricula trasera
    glPushMatrix();
        glTranslatef(0, alto1/2 - alto_m, ancho1);
        glScalef(largo_m, alto_m, ancho_m);
        matricula.draw(modo, r, g, b, grosor);
    glPopMatrix();

    //Pieza 1 - Puerta del maletero / Parte vertical
    
    glPushMatrix();
        glTranslatef(0, 0, ancho1/2);
        glScalef(largo1, alto1, ancho1);
        cubo.draw(modo, r, g, b, grosor);
    glPopMatrix();
}

void _maletero::asignar_color(_color color_maletero, _color color_matricula){
    cubo.asignar_color(color_maletero);
    matricula.asignar_color(color_matricula);
}

//************************************************************************
// Cuerpo trasero
//************************************************************************
_cuerpo_trasero::_cuerpo_trasero(){
    largo1 = 3;         alto1 = 0.5;         ancho1 = 1;
    largo2 = 3;         alto2 = 0.75;        ancho2 = 0.25;
    largo3 = 3;         alto3 = 1.75;        ancho3 = 0.25;
    vector<_vertex3f> poligono;
    _vertex3f aux;
    aux.x = -largo2 / 2; aux.y = 0; aux.z = ancho2;
    poligono.push_back(aux);
    aux.x = -largo2 / 2; aux.y = 0; aux.z = 0;
    poligono.push_back(aux);
    aux.x = -largo2 / 2; aux.y = alto1; aux.z = 0;
    poligono.push_back(aux);
    aux.x = -largo2 / 2; aux.y = alto2; aux.z = ancho2;
    poligono.push_back(aux);
    pieza2 = new _extrusion(poligono, largo2, 0, 0, true, true);
}


void _cuerpo_trasero::draw(_modo modo, float r, float g, float b, float grosor){
    //Pieza 3 - Pieza anterior a compartimento interior
    glPushMatrix();
        glTranslatef(0, 0, ancho3/2);
        glScalef(largo3, alto3, ancho3);
        cubo.draw(modo, r, g, b, grosor);
    glPopMatrix();
    
    //Pieza 2 - Subida diagonal
    glTranslatef(0, 1, -ancho2);
    pieza2->draw(modo, r, g, b, grosor);
    
    //Pieza 1 - Parte trasera
    glTranslatef(0, 0, -ancho1/2);
    glPushMatrix();
        glScalef(largo1, alto1, ancho1);
        cubo.draw(modo, r, g, b, grosor);
    glPopMatrix();
}

void _cuerpo_trasero::asignar_color(_color color_cuerpo_t){
    cubo.asignar_color(color_cuerpo_t);
    pieza2->asignar_color(color_cuerpo_t);
}


//************************************************************************
// Asiento trasero
//************************************************************************
_asiento::_asiento(){
    largo1 = 1;     alto1 = 0.5;                    ancho1 = 0.75;
    largo2 = 1;     alto2 = 0.25;                   ancho2 = 0.25;
    largo3 = 1;     alto3 = 0.25;                   ancho3 = 0.75;
    largo4 = 0.999; alto4 = sqrt(10)/2 - ancho4;    ancho4 = 0.25;
    
}

void _asiento::draw(_modo modo, float r, float g, float b, float grosor){
    glTranslatef(0, alto1, -ancho1/2);
    //Respaldo
    glPushMatrix();
        glTranslatef(0, 0, -0.1);
        glRotatef(30, -1, 0, 0);
        //Pieza 4.2 - Respaldo central
        glPushMatrix();
            glScalef(largo4, alto4, ancho4);
            cubo.draw(modo, r, g, b, grosor);
        glPopMatrix();
        //Pieza 4.1 - Respaldo alto
        glTranslatef(0, alto4, 0);
        glPushMatrix();
            glScalef(largo4, ancho4, ancho4);
            semicilindro.draw(modo, r, g, b, grosor);
        glPopMatrix();
    glPopMatrix();
    
    //Parte 3 - Parte central asiento
    glPushMatrix();
        //glTranslatef(0, -alto1 - alto2/2, -ancho1/2);
        glScalef(largo3, alto3, ancho3);
        cubo.draw(modo, r, g, b, grosor);
    glPopMatrix();
    glTranslatef(0, alto2/2, ancho3/2);
    //Parte 2 - Parte delantera asiento
    glPushMatrix();
        glScalef(largo2, alto2, ancho2);
        glRotatef(90, 1, 0, 0);
        glRotatef(90, 0, 1, 0);
        semicilindro.draw(modo, r, g, b, grosor);
    glPopMatrix();
    
    //Parte 1 - Soporte / Base
    glPushMatrix();
        glTranslatef(0, -alto1 - alto2/2, -ancho1/2);
        glScalef(largo1, alto1, ancho1);
        base.draw(modo, r, g, b, grosor);
    glPopMatrix();
    
}

void _asiento::asignar_color(_color color_base, _color color_asiento){
    base.asignar_color(color_base);
    cubo.asignar_color(color_asiento);
    semicilindro.asignar_color(color_asiento);
}
//************************************************************************
// volante
//************************************************************************
_volante::_volante(){
    radio = 0.375;
    largo1 = 0.05;      alto1 = 0.05;       ancho1 = 0.05;
    largo2 = 0.05;      alto2 = radio;      ancho2 = 0.05;
    largo3 = 0.5;
}

void _volante::draw(_modo modo, float r, float g, float b, float grosor){
    //Parte 3 - Eje
    glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(largo2, alto2, ancho2);
        cilindro.draw(modo, r, g, b, grosor);
    glPopMatrix();
    
    //Parte 2 - Parte interior
    for(int i = 0; i < 3; i++){
        glRotatef(360/3, 0, 0, 1);
        glPushMatrix();
            glScalef(largo2, alto2, ancho2);
            cilindro.draw(modo, r, g, b, grosor);
        glPopMatrix();
    }
    
    //Parte 1 - Parte exterior
    float angulo = (360.0/ LADOS_CIRCULO);
    for(int i = 0; i <= LADOS_CIRCULO; i++){
        glRotatef(angulo, 0, 0, 1);
        glPushMatrix();
            glTranslatef(0, radio, 0);
            glScalef(largo1, alto1, ancho1);
            glRotatef(90, 0, 0, 1);
            cilindro.draw(modo, r, g, b, grosor);
        glPopMatrix();
    }
    
    
}
void _volante::asignar_color(_color color_volante){
    cilindro.asignar_color(color_volante);
}

//************************************************************************
// palanca de cambios
//************************************************************************
_palanca_cambios::_palanca_cambios(){
    largo1 = 0.9;       alto1 = 1;          ancho1 = 1.5;
    largo2 = 0.5;       alto2 = 0.05;       ancho2 = 0.5;
    radio3 = 0.03;      alto3 = 0.3;
    radio4 = 0.1;
}

void _palanca_cambios::draw(_modo modo, float r, float g, float b, float grosor){
    glTranslatef(0, alto1 + alto2 + alto3 + radio4/3, 0);   //Ponemos el objeto apoyado 
                                                            //en el suelo
    
    //Pieza 4 - Parte superior palanca cambios
    glPushMatrix();
        glScalef(radio4*2, radio4*2, radio4*2);
        esfera.draw(modo, r, g, b, grosor);
    glPopMatrix();
    
    //Pieza 3 - Mango palanca cambios
    glTranslatef(0, -alto3 - radio4/3, 0);
    glPushMatrix();
        glScalef(radio3*2, alto3, radio3*2);
        cilindro.draw(modo, r, g, b, grosor);
    glPopMatrix();
    
    //Pieza 2 - Base palanca cambios
    glTranslatef(0, -alto2, 0);
    glPushMatrix();
        glScalef(largo2, alto2, ancho2);
        base.draw(modo, r, g, b, grosor);
    glPopMatrix();
    
    //Pieza 1 - Compartimento central
    glTranslatef(0, -alto1, 0);
    glPushMatrix();
        glScalef(largo1, alto1, ancho1);
        cubo.draw(modo, r, g, b, grosor);
    glPopMatrix();
}

void _palanca_cambios::asignar_color(_color color_comp, _color color_base, _color color_palanca)
{
    cilindro.asignar_color(color_palanca);
    esfera.asignar_color(color_palanca);
    base.asignar_color(color_base);
    cubo.asignar_color(color_comp);
}

//************************************************************************
// reposapies
//************************************************************************
_reposapies::_reposapies(){
    largo1 = 3;           alto1 = 1.25;          ancho1 = 0.25;
    largo2 = 3;           alto2 = 0.3;           ancho2 = 0.3;
    vector<_vertex3f> poligono;
    _vertex3f aux;
    aux.x = -largo2 / 2; aux.y = 0; aux.z = 0;
    poligono.push_back(aux);
    aux.x = -largo2 / 2; aux.y = 0; aux.z = ancho2;
    poligono.push_back(aux);
    aux.x = -largo2 / 2; aux.y = alto2; aux.z = 0;
    poligono.push_back(aux);
    pieza2 = new  _extrusion(poligono, largo2, 0, 0, true, true);
}

_reposapies::~_reposapies(){
    delete pieza2;
}

void _reposapies::draw(_modo modo, float r, float g, float b, float grosor){
    glRotatef(180, 0, 1, 0);
    //Pieza 2 - Reposapies
    glPushMatrix();
        pieza2->draw(modo, r, g, b, grosor);
    glPopMatrix();
    //Pieza 1 - Fondo
    glTranslatef(0, 0, -ancho1/2);
    glPushMatrix();
        glScalef(largo1, alto1, ancho1);
        cubo.draw(modo, r, g, b, grosor);
    glPopMatrix();
}

void _reposapies::asignar_color(_color color_reposapies)
{
    cubo.asignar_color(color_reposapies);
    pieza2->asignar_color(color_reposapies);
}

//************************************************************************
// techo
//************************************************************************
_techo::_techo(float _coeficiente){
    coef = _coeficiente;
    altura_pos = 0.9;
    anchura_pos = 0.7;
    alpha = (180/M_PI)*atan(anchura_pos/altura_pos);
    giro1 = coef*180;        //Min = 0    Max = 180
    giro2 = coef*(90 + alpha);         //Min = 0    Max = 90 + alpha
    giro3 = coef*(90 + alpha); //Min = 0    Max = 90 + alpha
    largo1 = 3.01;           alto1 = 0.125;          ancho1 = 1.25 - 0.5*coef;
    largo2 = 3.01;           alto2 = 0.125;          ancho2 = 1 - 0.25*coef;
    largo3 = 3;              alto3 = 0.125;          
    ancho3 = sqrt(anchura_pos*anchura_pos+altura_pos*altura_pos);
    ancho3 -= (sqrt(anchura_pos*anchura_pos+altura_pos*altura_pos)-0.75)*coef;
}

void _techo::draw(_modo modo, float r, float g, float b, float grosor){
    /*
    //Actualiza valores
    giro1 = coef*180;
    giro2 = coef*(90 + alpha);  
    giro3 = coef*(90 + alpha);
    ancho1 = 1.25 - 0.5*coef;
    ancho2 = 1 - 0.25*coef;
    ancho3 = sqrt(anchura_pos*anchura_pos+altura_pos*altura_pos);
    ancho3 -= (sqrt(anchura_pos*anchura_pos+altura_pos*altura_pos)-0.75)*coef;
    */
    //Pieza 3 - Parte trasera
    //glTranslatef(0, alto3, 0);
    glRotatef(giro3, -1, 0, 0);
    glTranslatef(0, ancho3*cos(alpha*M_PI/180), ancho3*sin(alpha*M_PI/180));
    glPushMatrix();
        glRotatef(90.0-alpha, -1, 0, 0);
        glTranslatef(0, 0, -ancho3/2);
        glScalef(largo3, alto3, ancho3);
        cubo.draw(modo, r, g, b, grosor);
    glPopMatrix();
    
    //Pieza 2 - Parte superior trasera
    glRotatef(giro2, 1, 0, 0);
    glTranslatef(0, alto2, ancho2);
    glPushMatrix();
        glTranslatef(0, -alto2, -ancho2/2);
        glScalef(largo2, alto2, ancho2);
        cubo.draw(modo, r, g, b, grosor);
    glPopMatrix();
    
    //Pieza 1 - Parte superior delantera
    //glTranslatef(0, 0, ancho1/2 + ancho2/2);
    glPushMatrix();
        glRotatef(giro1, -1, 0, 0);
        glTranslatef(0, -alto1, ancho1/2);
        glScalef(largo1, alto1, ancho1);
        cubo.draw(modo, r, g, b, grosor);
    glPopMatrix();
}

void _techo::asignar_color(_color color_techo)
{
    cubo.asignar_color(color_techo);
}

//************************************************************************
// descapotable (objeto final)
//************************************************************************
_descapotable::_descapotable(){
    
    //Variables giros
    giro_dir_ruedas = 0.0;       //Giros = [-22, 22]
    giro_volante    = 0.0;       //Giros = [-220, 220]
    giro_rot_ruedas = 0.0;       //Giros = [-inf, +inf]
    giro_puerta_izq = 0.0;       //Giros = [0, 70]
    giro_puerta_der = 0.0;       //Giros = [0, 70]
    giro_puerta_maletero = 0.0;  //Giros = [0, 80]
    coeficiente_techo = 0.0;     //Coeficiente = [0 (cerrado), 1(abierto)]
    
    gpm_anterior = giro_puerta_maletero;
    ct_anterior  = coeficiente_techo;
    
    //Inicializaciones
    maletero = NULL;
    techo = NULL;
    carroceria_lateral_der = new _carroceria_lateral(false);
    puerta_der = new _puerta(false);
    
    //Valores
    largo = 4;              alto = 3.25;            ancho = 11;
    largo_chasis = 4;       alto_chasis = 0.1;      ancho_chasis = 11;
                            alto_chasis_trasero = 0.2; 
    largo_cl = 0.5;         alto_cl = 3.25;         ancho_cl = 11;
    largo_rueda = 0.3;      alto_rueda = 1.6;       ancho_rueda = 1.6;
    largo_pos_rueda = 0.5;                          ancho_pos_rueda_del = 9.15;
                                                    ancho_pos_rueda_tra = 3;
    largo_puerta = 0.25;    alto_puerta = 1.5;      ancho_puerta = 2.25;
    
    largo_faro_d = 0.5;     alto_faro_d = 1;        ancho_faro_d = 0.5;
    largo_luz_t  = 0.5;                             ancho_luz_t  = 0.25;
    alto_pos_puerta = 0.25 + alto_chasis;           ancho_pos_puerta = 7.5;
    alto_pos_cuerpo_d = 1;                          ancho_pos_cuerpo_d = 7.5;
                                                    ancho_pos_cuerpo_t = 4;
    alto_pos_faro_d = 0.5;
    alto_pos_luz_t = 1.5;
    alto_pos_luz_t2 = 1;
    alto_pos_luz_t3 = 0.5;
    coef_luz_trasera_inf= 0.5;
    ancho_pos_parachoques_t = -0.15;
    largo_asiento_t = 3;
    ancho_pos_asiento_t = 5.5;
    largo_pos_asiento_d = 1;    ancho_pos_asiento_d = 7;
    inclinacion_volante = 15;   alto_pos_volante = 1.4;
    ancho_pos_reposapies = 7.74;
    alto_pos_techo = 1.5;
    ancho_pos_techo = 3.5;
    
    
    //Colores
    COLOR_CARROCERIA.r = 1.0;   COLOR_CARROCERIA.g = 0.0; 
    COLOR_CARROCERIA.b = 0.0;   COLOR_CARROCERIA.a = 1.0;
    COLOR_MATRICULA.r = 0.5;    COLOR_MATRICULA.g = 0.5; 
    COLOR_MATRICULA.b = 0.5;    COLOR_MATRICULA.a = 1.0;
    COLOR_TECHO.r = 0.5;        COLOR_TECHO.g = 0.5; 
    COLOR_TECHO.b = 0.5;        COLOR_TECHO.a = 1.0;
    
    
    const _color COLOR_CHASIS(0.5,0.5,0.5,1.0);
    const _color COLOR_RUEDA(0.0, 0.0, 0.0, 1.0);
    const _color COLOR_LLANTA(0.6, 0.6, 0.6, 1.0);
    const _color COLOR_RETROVISOR(1.0, 0.1, 0.1, 1.0);
    const _color COLOR_ESPEJO(0.7, 0.7, 1, 0.8);
    const _color COLOR_CRISTAL(0.5, 0.5, 1, 0.4);
    const _color COLOR_FARO(0.7, 0.7, 0.7, 1.0);
    const _color COLOR_CRISTAL_FARO(0.9, 0.9, 1, 0.7);
    const _color COLOR_INTERMITENTE(0.9, 0.9, 0.1, 1.0);
    const _color COLOR_PARRILLA(0.1, 0.1, 0.1, 1.0);
    const _color COLOR_BARRAS_PARRILLA(0.3, 0.3, 0.3, 1.0);
    const _color COLOR_BIGOTERA(0.4, 0.2, 0.2, 1.0);
    const _color COLOR_PARACHOQUES(0.9, 0.9, 0.9, 1.0);
    const _color COLOR_CRISTAL_FARO_T(1.0, 0.3, 0.3, 0.9);
    const _color COLOR_ASIENTO(1.0, 1.0, 0.7, 1.0);
    const _color COLOR_COMPARTIMENTO_CC(0.5, 0.0, 0.0, 1.0);
    const _color COLOR_BASE_CC(0.7, 0.0, 0.0, 1.0);
    const _color PALANCA_CC(0.5, 0.5, 0.5, 1.0);
    
    //Pintar objetos
    chasis.asignar_color(COLOR_CHASIS);
    carroceria_lateral_izq.asignar_color(COLOR_CARROCERIA);
    carroceria_lateral_der->asignar_color(COLOR_CARROCERIA);
    rueda.asignar_color(COLOR_RUEDA, COLOR_LLANTA);
    puerta_izq.asignar_color(COLOR_CARROCERIA, COLOR_ESPEJO, COLOR_RETROVISOR);
    puerta_der->asignar_color(COLOR_CARROCERIA, COLOR_ESPEJO, COLOR_RETROVISOR);
    cuerpo_delantero.asignar_color(COLOR_CARROCERIA, COLOR_CRISTAL);
    faro_delantero.asignar_color(COLOR_FARO, COLOR_CRISTAL_FARO);
    morro.asignar_color(COLOR_INTERMITENTE, COLOR_FARO, COLOR_BARRAS_PARRILLA, COLOR_PARRILLA, COLOR_BIGOTERA);
    parachoques_delantero.asignar_color(COLOR_PARACHOQUES);
    parachoques_trasero.asignar_color(COLOR_PARACHOQUES);
    luz_trasera.asignar_color(COLOR_FARO, COLOR_CRISTAL_FARO_T);
    luz_trasera_int.asignar_color(COLOR_FARO, COLOR_INTERMITENTE);
    luz_trasera_marcha_atras.asignar_color(COLOR_FARO, COLOR_CRISTAL_FARO);
    cuerpo_trasero.asignar_color(COLOR_CARROCERIA);
    asiento.asignar_color(COLOR_RUEDA, COLOR_ASIENTO);
    volante.asignar_color(COLOR_RUEDA);
    palanca_cambios.asignar_color(COLOR_COMPARTIMENTO_CC, COLOR_BASE_CC, PALANCA_CC);
    reposapies.asignar_color(COLOR_CHASIS);
}

_descapotable::~_descapotable(){
    delete maletero;
    delete techo;
    delete carroceria_lateral_der;
}


void _descapotable::draw(_modo modo, float r, float g, float b, float grosor){
    //Inicializaciones en JOT
    if(techo != NULL && ct_anterior != coeficiente_techo){
        delete techo;
        techo = NULL;
        //cout << "Borro techo" << endl;
    }
    if(maletero != NULL && gpm_anterior != giro_puerta_maletero){
        delete maletero;
        maletero = NULL;
        //cout << "Borro maletero" << endl;
    }
    
    if(maletero == NULL){
        maletero = new _maletero(giro_puerta_maletero);
        maletero->asignar_color(COLOR_CARROCERIA, COLOR_MATRICULA);
        //cout << "Creo maletero" << endl;
    }
    if(techo == NULL){
        techo = new _techo(coeficiente_techo);
        techo->asignar_color(COLOR_TECHO);
        //cout << "Creo techo" << endl;
    }

    /************Composición del objeto************/
    glPushMatrix();
        glScalef(0.5, 0.5, 0.5);
        glTranslatef(0,0,-ancho/2);
        
        //Techo
        glPushMatrix();
            glTranslatef(0, alto_chasis/2 + alto_pos_techo, ancho_pos_techo);
            techo->draw(modo, r, g, b, grosor);
        glPopMatrix();
        
        //Reposapies
        glPushMatrix();
            glTranslatef(0, alto_chasis/2, ancho_pos_reposapies);
            reposapies.draw(modo, r, g, b, grosor);
        glPopMatrix();
        
        //Palanca de cambios
        glPushMatrix();
            glTranslatef(0, alto_chasis/2, ancho_pos_asiento_d);
            palanca_cambios.draw(modo, r, g, b, grosor);
        glPopMatrix();
        
        //Volante
        glPushMatrix();
            glTranslatef(largo_pos_asiento_d, alto_chasis_trasero/2 + alto_pos_volante, ancho_pos_asiento_d);
            glRotatef(inclinacion_volante, 1, 0, 0);
            glRotatef(giro_volante, 0, 0, 1);
            volante.draw(modo, r, g, b, grosor);
        glPopMatrix();
        
        //Asiento delantero derecho
        glPushMatrix();
            glTranslatef(-largo_pos_asiento_d, alto_chasis_trasero/2, ancho_pos_asiento_d);
            asiento.draw(modo, r, g, b, grosor);
        glPopMatrix();
        
        //Asiento delantero izquierdo
        glPushMatrix();
            glTranslatef(largo_pos_asiento_d, alto_chasis_trasero/2, ancho_pos_asiento_d);
            asiento.draw(modo, r, g, b, grosor);
        glPopMatrix();
        
        //Asiento trasero (3 plazas)
        glPushMatrix();
            glTranslatef(0, alto_chasis_trasero/2, ancho_pos_asiento_t);
            glScalef(largo_asiento_t, 1, 1);
            asiento.draw(modo, r, g, b, grosor);
        glPopMatrix();
        
        //Parachoques trasero
        glPushMatrix();
            glTranslatef(0, alto_chasis_trasero/2, -0.15);
            parachoques_trasero.draw(modo, r, g, b, grosor);
        glPopMatrix();
        
        //Luces traseras
        //Luz trasera de marcha atras derecha
        glPushMatrix();
            glTranslatef(-largo/2 + largo_luz_t/2, alto_chasis + alto_pos_luz_t3, ancho_luz_t/2);
            glScalef(coef_luz_trasera_inf, coef_luz_trasera_inf, coef_luz_trasera_inf);
            glRotatef(180, 0, 1, 0);
            luz_trasera_marcha_atras.draw(modo, r, g, b, grosor);
        glPopMatrix();
        //Luz trasera de marcha atras izquierda
        glPushMatrix();
            glTranslatef(largo/2 - largo_luz_t/2, alto_chasis + alto_pos_luz_t3, ancho_luz_t/2);
            glScalef(coef_luz_trasera_inf, coef_luz_trasera_inf, coef_luz_trasera_inf);
            glRotatef(180, 0, 1, 0);
            luz_trasera_marcha_atras.draw(modo, r, g, b, grosor);
        glPopMatrix();
        //Luz trasera intermitente derecha
        glPushMatrix();
            glTranslatef(-largo/2 + largo_luz_t/2, alto_chasis + alto_pos_luz_t2, ancho_luz_t/2);
            glScalef(coef_luz_trasera_inf, coef_luz_trasera_inf, coef_luz_trasera_inf);
            glRotatef(180, 0, 1, 0);
            luz_trasera_int.draw(modo, r, g, b, grosor);
        glPopMatrix();
        //Luz trasera intermitente izquierda
        glPushMatrix();
            glTranslatef(largo/2 - largo_luz_t/2, alto_chasis + alto_pos_luz_t2, ancho_luz_t/2);
            glScalef(coef_luz_trasera_inf, coef_luz_trasera_inf, coef_luz_trasera_inf);
            glRotatef(180, 0, 1, 0);
            luz_trasera_int.draw(modo, r, g, b, grosor);
        glPopMatrix();
        //Luz trasera superior derecha
        glPushMatrix();
            glTranslatef(-largo/2 + largo_luz_t/2, alto_chasis + alto_pos_luz_t, ancho_luz_t/2);
            glRotatef(180, 0, 1, 0);
            luz_trasera.draw(modo, r, g, b, grosor);
        glPopMatrix();
        //Luz trasera superior izquierda
        glPushMatrix();
            glTranslatef(largo/2 - largo_luz_t/2, alto_chasis + alto_pos_luz_t, ancho_luz_t/2);
            glRotatef(180, 0, 1, 0);
            luz_trasera.draw(modo, r, g, b, grosor);
        glPopMatrix();
        
        //Cuerpo trasero
        glPushMatrix();
            glTranslatef(0, alto_chasis, ancho_pos_cuerpo_t);
            cuerpo_trasero.draw(modo, r, g, b, grosor);
        glPopMatrix();
        //Maletero
        glPushMatrix();
            glTranslatef(0, alto_chasis_trasero, 0);
            maletero->draw(modo, r, g, b, grosor);
        glPopMatrix();
        //Parachoques delantero
        glPushMatrix();
            glTranslatef(0, 0, ancho_chasis -0.25);
            parachoques_delantero.draw(modo, r, g, b, grosor);
        glPopMatrix();
        //Morro
        glPushMatrix();
            glTranslatef(0, alto_chasis, ancho_chasis -0.5);
            morro.draw(modo, r, g, b, grosor);
        glPopMatrix();
        //Faros delanteros
        glPushMatrix();
            glTranslatef(-largo/2 + largo_faro_d/2, alto_chasis + alto_pos_faro_d, ancho_chasis - ancho_faro_d);
            faro_delantero.draw(modo, r, g, b, grosor);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(largo/2 - largo_faro_d/2, alto_chasis + alto_pos_faro_d, ancho_chasis - ancho_faro_d);
            faro_delantero.draw(modo, r, g, b, grosor);
        glPopMatrix();
        
        //Puertas
        //Puerta derecha
        glPushMatrix();
            glTranslatef(largo_puerta/2 - largo_chasis/2, alto_pos_puerta, ancho_pos_puerta);
            glRotatef(giro_puerta_der, 0, 1, 0);
            puerta_der->draw(modo, r, g, b, grosor);
        glPopMatrix();
        //Puerta izquierda
        glPushMatrix();
            glTranslatef(largo_chasis/2 - largo_puerta/2, alto_pos_puerta, ancho_pos_puerta);
            glRotatef(giro_puerta_izq, 0, -1, 0);
            puerta_izq.draw(modo, r, g, b, grosor);
        glPopMatrix();
        
        //Ruedas
        //Rueda delantera izquierda
        glPushMatrix();
            glTranslatef(largo_chasis/2-largo_pos_rueda, alto_chasis, ancho_pos_rueda_del);
            glRotatef(giro_dir_ruedas, 0, 1, 0);
            glRotatef(giro_rot_ruedas, 1, 0, 0);
            rueda.draw(modo, r, g, b, grosor);
        glPopMatrix();
        //Rueda trasera izquierda
        glPushMatrix();
            glTranslatef(largo_chasis/2-largo_pos_rueda, alto_chasis, ancho_pos_rueda_tra);
            glRotatef(giro_rot_ruedas, 1, 0, 0);
            rueda.draw(modo, r, g, b, grosor);
        glPopMatrix();  
        //Rueda delantera derecha
        glPushMatrix();
            glTranslatef(-largo_chasis/2+largo_pos_rueda, alto_chasis, ancho_pos_rueda_del);
            glRotatef(giro_dir_ruedas, 0, 1, 0);
            glRotatef(giro_rot_ruedas, 1, 0, 0);
            glRotatef(180, 0, 1, 0);
            rueda.draw(modo, r, g, b, grosor);
        glPopMatrix();
        //Rueda trasera derecha
        glPushMatrix();
            glTranslatef(-largo_chasis/2+largo_pos_rueda, alto_chasis, ancho_pos_rueda_tra);
            glRotatef(giro_rot_ruedas, 1, 0, 0);
            glRotatef(180, 0, 1, 0);
            rueda.draw(modo, r, g, b, grosor);
        glPopMatrix();    
        
        //Carroceria lateral derecha
        glPushMatrix();
            glTranslatef(-largo/2+largo_cl/2, alto_chasis, 0.25);
            carroceria_lateral_der->draw(modo, r, g, b, grosor);
        glPopMatrix();
        //Carroceria lateral izquierda
        glPushMatrix();
            glTranslatef(largo/2-largo_cl/2, alto_chasis, 0.25);
            carroceria_lateral_izq.draw(modo, r, g, b, grosor);
        glPopMatrix();
        chasis.draw(modo, r, g, b, grosor);
        //Cuerpo delantero -- Esto tiene que ir lo primero por la transparencia
        glPushMatrix();
            glTranslatef(0, alto_chasis + alto_pos_cuerpo_d, ancho_pos_cuerpo_d);
            cuerpo_delantero.draw(modo, r, g, b, grosor);
        glPopMatrix();
    glPopMatrix();

    //Guardar valores actuales
    gpm_anterior= giro_puerta_maletero;
    ct_anterior = coeficiente_techo;
}



