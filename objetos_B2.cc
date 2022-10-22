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
	float r, g, b;
	glPolygonMode(GL_FRONT,GL_FILL);
	
	glBegin(GL_TRIANGLES);
	for (i=0;i<caras.size();i++){
		if(colores.size() > i){
		    glColor3f(colores[i].r,colores[i].g,colores[i].b);
		}
		else{
		    if(i % 2 == 0){
		        r = 1;
		        g = 0;
		        b = 0;
		    }
		    else{
		        r = 1;
		        g = 1;
		        b = 0;
		    }
		    glColor3f(r,g,b);
		}
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
	case POINTS:draw_puntos(r, g, b, grosor);break;
	case EDGES:draw_aristas(r, g, b, grosor);break;
	case SOLID:draw_solido(r, g, b);		 break;
	case SOLID_COLORS:draw_solido_colores(); break;
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
  }
}

//*************************************************************************

void _triangulos3D::colors_chess(float r1, float g1, float b1, float r2, float g2, float b2)
{
int i, n_c;
n_c=caras.size();
colores.resize(n_c);
for (i=0;i<n_c;i++)  
  {if (i%2==0) 
     {colores[i].r=r1;
      colores[i].g=g1;
      colores[i].b=b1;
     }
   else 
     {colores[i].r=r2;
      colores[i].g=g2;
      colores[i].b=b2;
     } 
  }
}

//*************************************************************************

void _triangulos3D::asignar_color(float r, float g, float b)
{
int i, n_c;
n_c=caras.size();
colores.resize(n_c);
for (i=0;i<n_c;i++)  
  {colores[i].r=r;
   colores[i].g=g;
   colores[i].b=b;
  }
}

//*************************************************************************
// clase cubo
//*************************************************************************

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

//tapa superior
v1 = 1;
v2 = 3;
v3 = 2*num_aux-1;
if(tapa_su){
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
   
colors_random();
}


//************************************************************************
// práctica 3, objeto jerárquico articulado
//************************************************************************

//************************************************************************
// piezas
//************************************************************************

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
    largo1 = 4;       alto1 = 0.10;    ancho1 = 0.75;
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
    extrusion = new  _extrusion(poligono, 0, alto5, -ancho5, true, true);
    
    //cubo.asignar_color(0.5,0.5,0.5);
    cubo.colors_random();
    extrusion->colors_random();
    
    
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

//************************************************************************
// guardabarros delantero
//************************************************************************
_guardabarros::_guardabarros(){
    largo = 0.75;
    alto = 1; //alto = radio
    ancho = 2.25;
    lados_curva = LADOS_CIRCULO / 2;
    float angulo = (M_PI / lados_curva) * 2;

    //Creamos una extrusion por lado de la curva
    _vertex3f v_anterior;
    v_anterior.x = largo/2; v_anterior.y = 0; v_anterior.z = alto;
    for(int i = 1; i <= lados_curva / 4; i++){
        vector<_vertex3f> poligono;
        _vertex3f aux;
        _extrusion * arco;
        //Vertice a misma altura que vertice nuevo
        aux.x = largo / 2;  aux.y = alto*sin(angulo*i); aux.z = ancho/2;
        poligono.push_back(aux);
        //Vertice a misma altura que vertice antiguo
        aux.x = largo / 2;  aux.y = alto*sin(angulo*(i-1)); aux.z = ancho/2;
        poligono.push_back(aux);
        //Vertice de la curva anterior
        poligono.push_back(v_anterior);
        //Vertice nuevo de la curva
        aux.x = largo / 2;  aux.y = alto*sin(angulo*i); aux.z = alto*cos(angulo*i);
        poligono.push_back(aux);
        cout << "aux -> x= "<<aux.x<<"\ty= "<<aux.y<<"\tz= "<<aux.z<<endl;
        cout << "Angulo = " << angulo*i << endl;
        poligono.push_back(aux);
        //Crear extrusion
        arco = new  _extrusion(poligono, -largo, 0, 0, true, true);
        curva.push_back(arco);
        arco = NULL;
        //Actualizar v_anterior
        v_anterior = aux;
    }
}


void _guardabarros::draw(_modo modo, float r, float g, float b, float grosor){
    
    for(int i = 0; i < curva.size(); i++){
        
        glPushMatrix();
            curva[i]->draw(modo, r, g, b, grosor);
            glScalef(1, 1, -1);
            curva[i]->draw(modo, r, g, b, grosor);
        glPopMatrix();    
    }
}




//************************************************************************
// carroceria lateral
//************************************************************************
_carroceria_lateral::_carroceria_lateral(){
    largo1 = 0.5;           alto1 = 0.75;         ancho1 = 3;               altura1 = 1;
    largo2 = 0.5;           alto2 = altura1;      ancho2 = 0.25;
    largo3 = 0.75;          alto3 = altura1;      ancho3 = 2.25;
    largo_cil = 0.25;       alto_cil = 0.25;      ancho_cil = 0.25;
    largo4 = 0.25;          alto4 = altura1;      ancho4 = ancho3;
    largo5 = 0.5;           alto5 = altura1;      ancho5 = 0.5;
    largo6 = 0.25;          alto6 = 0.25;         ancho6 = 2.25;
    largo7 = 0.25;          alto7 = 1;            ancho7 = 1.25;
    largo8 = 0.75;          alto8 = altura1;      ancho8 = 2;
    largo9 = 0.25;          alto9 = altura1;      ancho9 = ancho8;
    largo10 = largo1;       alto10 = 1;           ancho10 = 1;
    largo11 = largo1;       alto11 = 0.9;        ancho11 = 0.75;   altura11 = 0.1;
    largo12 = largo1;       alto12 = 0.75;        ancho12 = 5;   altura12 = 1;
    //Extrusion pieza 10
    vector<_vertex3f> poligono;
    _vertex3f aux;
    aux.x = largo10/2;   aux.y = 0;      aux.z = 0;
    poligono.push_back(aux);
    aux.x = largo10/2;  aux.y = altura11;   aux.z = -ancho10;
    poligono.push_back(aux);
    aux.x = largo10/2;  aux.y = alto10;      aux.z = -ancho10;
    poligono.push_back(aux);
    aux.x = largo10/2;   aux.y = alto10;   aux.z = 0;
    poligono.push_back(aux);
    pieza10 = new _extrusion(poligono, -largo10, 0, 0, true, true);
    
    
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
            glTranslatef(largo1-largo8, 0, ancho8/2);
            glScalef(largo_cil, alto_cil, ancho_cil);
            glRotatef(90, 0, 0, 1);
            cilindro.draw(modo, r, g, b, grosor);
        glPopMatrix();
        
        //Pieza 9 - Parte trasera a la rueda trasera
        glPushMatrix();
            glTranslatef(largo9/2-largo8, 0, ancho8/2);
            glScalef(largo9, alto9, ancho9);
            cubo.draw(modo, r, g, b, grosor);
        glPopMatrix();
        

        //Pieza 8 - Guardabarros rueda trasera (arco)
        glPushMatrix();
            glTranslatef(largo1/2-largo8/2, 0, ancho8/2);
            glScalef(1, 1, ancho8/ancho3);
            gb.draw(modo, r, g, b, grosor);
        glPopMatrix();
        glTranslatef(0, 0, ancho8);

        //Pieza 7 - Carroceria lateral - Parte detras de puerta
        glPushMatrix();
            glTranslatef(largo7/2, 0, ancho7/2);
            glScalef(largo7, alto7, ancho7);
            cubo.draw(modo, r, g, b, grosor);
        glPopMatrix();
        glTranslatef(0, 0, ancho7);
        
        //Pieza 6 - Parte lateral por debajo de la puerta
        glPushMatrix();
            glTranslatef(largo6/2, 0, ancho6/2);
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
            glTranslatef(largo1-largo3, 0, ancho1-ancho2-ancho4/2);
            glScalef(largo_cil, alto_cil, ancho_cil);
            glRotatef(90, 0, 0, 1);
            cilindro.draw(modo, r, g, b, grosor);
        glPopMatrix();
        
        //Pieza 4 - Parte trasera a la rueda
        glPushMatrix();
            glTranslatef(largo4/2-largo3, 0, ancho1-ancho2-ancho4/2);
            glScalef(largo4, alto4, ancho4);
            cubo.draw(modo, r, g, b, grosor);
        glPopMatrix();
        
        //Pieza 3 - Guardabarros rueda delantera (arco)
        glPushMatrix();
            glTranslatef(largo1/2-largo3/2, 0, ancho1-ancho2-ancho3/2);
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

//************************************************************************
// retrovisor
//************************************************************************

_retrovisor::_retrovisor(){
    largo1 = 0.25, alto1 = 0.2, ancho1 = 0.05;
    largo2 = 0.2, alto2 = 0.02, ancho2 = 0.02;
    
}


void _retrovisor::draw(_modo modo, float r, float g, float b, float grosor){
    //Pieza 2 - Brazo pegado a puerta
    glPushMatrix();
        glRotatef(30, 0, 0, 1);
        glTranslatef(-largo2/2+0.02, 0, 0);
        glScalef(largo2, alto2, ancho2);
        glTranslatef(-0.5, 0, 0);   //Centramos el cilindro
        glRotatef(90, 0, 0, -1);
        cilindro.draw(modo, r, g, b, grosor);
    glPopMatrix();
    
    //Pieza 1 - Espejo retrovisor
    glTranslatef(largo1/2, 0, 0);
    glRotatef(10, 0, 1, 0);
    glScalef(largo1, alto1, ancho1);
    glTranslatef(0, 0, -0.5);   //Centramos el cilindro
    glRotatef(90, 1, 0, 0);
    cilindro.draw(modo, r, g, b, grosor);
}


//************************************************************************
// puerta
//************************************************************************

_puerta::_puerta(){
    largo1 = 0.25, alto1 = 1.5, ancho1 = 2.25;
    pos_largo_r = largo1/2 + 0.125, pos_alto_r = alto1+0.05, pos_ancho_r = -ancho1*2/11;
}


void _puerta::draw(_modo modo, float r, float g, float b, float grosor){
    //Pieza 2 - Retrovisor
    glPushMatrix();
        glTranslatef(pos_largo_r, pos_alto_r, pos_ancho_r);
        retrovisor.draw(modo, r, g, b, grosor);
    glPopMatrix();
    //Pieza 1 - Cuerpo de la puerta
    glPushMatrix();
        glTranslatef(0, 0, -ancho1/2);
        glScalef(largo1, alto1, ancho1);
        cubo.draw(modo, r, g, b, grosor);
    glPopMatrix();
}


_descapotable::_descapotable(){
    //Variables giros
    giro_dir_ruedas = 20;  //Giros = [-22, 22]
    giro_rot_ruedas = 0;   //Giros = [-inf, +inf]
    giro_puerta_izq = 25;  //Giros = [0, 70]
    giro_puerta_der = 70;  //Giros = [0, 70]
    
    //Valores
    largo = 4;              alto = 3.25;            ancho = 11;
    largo_chasis = 4;       alto_chasis = 0.1;      ancho_chasis = 11;
    largo_cl = 0.5;         alto_cl = 3.25;         ancho_cl = 11;
    largo_rueda = 0.3;      alto_rueda = 1.6;       ancho_rueda = 1.6;
    largo_puerta = 0.25;    alto_puerta = 1.5;      ancho_rueda = 2.25;
                            alto_pos_puerta = 0.25 + alto_chasis; ancho_pos_puerta = 7.5;
    largo_pos_rueda = 0.5;       
    ancho_pos_rueda_del = 9.25;
    ancho_pos_rueda_tra = 3;
}

void _descapotable::draw(_modo modo, float r, float g, float b, float grosor){
    glPushMatrix();
        //Puertas
        //Puerta derecha
        glPushMatrix();
            glTranslatef(largo_puerta/2 - largo_chasis/2, alto_pos_puerta, ancho_pos_puerta);
            glRotatef(giro_puerta_der, 0, 1, 0);
            glScalef(-1, 1, 1);
            puerta.draw(modo, r, g, b, grosor);
        glPopMatrix();
        //Puerta izquierda
        glPushMatrix();
            glTranslatef(largo_chasis/2 - largo_puerta/2, alto_pos_puerta, ancho_pos_puerta);
            glRotatef(giro_puerta_izq, 0, -1, 0);
            puerta.draw(modo, r, g, b, grosor);
        glPopMatrix();
        
        //Ruedas
        //Rueda delantera izquierda
        glPushMatrix();
            glTranslatef(largo_chasis/2-largo_pos_rueda, 0, ancho_pos_rueda_del);
            glRotatef(giro_dir_ruedas, 0, 1, 0);
            //glRotatef(giro_rot_ruedas, 1, 0, 0);
            rueda.draw(modo, r, g, b, grosor);
        glPopMatrix();
        //Rueda trasera izquierda
        glPushMatrix();
            glTranslatef(largo_chasis/2-largo_pos_rueda, 0, ancho_pos_rueda_tra);
            glRotatef(giro_rot_ruedas, 1, 0, 0);
            rueda.draw(modo, r, g, b, grosor);
        glPopMatrix();  
        //Rueda delantera derecha
        glPushMatrix();
            glTranslatef(-largo_chasis/2+largo_pos_rueda, 0, ancho_pos_rueda_del);
            glRotatef(giro_dir_ruedas, 0, 1, 0);
            glRotatef(giro_rot_ruedas, 1, 0, 0);
            glScalef(-1, 1, 1);
            rueda.draw(modo, r, g, b, grosor);
        glPopMatrix();
        //Rueda trasera derecha
        glPushMatrix();
            glTranslatef(-largo_chasis/2+largo_pos_rueda, 0, ancho_pos_rueda_tra);
            glRotatef(giro_rot_ruedas, 1, 0, 0);
            glScalef(-1, 1, 1);
            rueda.draw(modo, r, g, b, grosor);
        glPopMatrix();    
        
        glPushMatrix();
            glScalef(-1, 1, 1);
            glTranslatef(largo/2-largo_cl/2, alto_chasis, 0.25);
            carroceria_lateral.draw(modo, r, g, b, grosor);
        glPopMatrix();
        
        glPushMatrix();
            glTranslatef(largo/2-largo_cl/2, alto_chasis, 0.25);
            carroceria_lateral.draw(modo, r, g, b, grosor);
        glPopMatrix();
        
        chasis.draw(modo, r, g, b, grosor);
    glPopMatrix();
}














