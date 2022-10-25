//**************************************************************************
// Práctica 2 
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>


const float AXIS_SIZE=5000;
const int LADOS_CIRCULO=50;
typedef enum{POINTS,EDGES,SOLID,SOLID_COLORS} _modo;

//*************************************************************************
// clase punto
//*************************************************************************
struct _color{
	float r;
	float g;
	float b;
	float a;
};

class _puntos3D
{
public:

  
	_puntos3D();
void 	draw_puntos(float r, float g, float b, int grosor);

vector<_vertex3f> vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:

	_triangulos3D();
void 	draw_aristas(float r, float g, float b, int grosor);
void    draw_solido(float r, float g, float b);
void 	draw_solido_colores();
void 	draw(_modo modo, float r, float g, float b, float grosor);

/* asignación de colores */
void 	colors_random();
void 	colors_chess(float r1, float g1, float b1, float a1, float r2, float g2, float b2, float a2);
void    asignar_color(float r, float g, float b, float a);

vector<_vertex3i> caras;
vector<_color> colores;
};


//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:

	_cubo(float tam=0.5);
};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

	_piramide(float tam=0.5, float al=1.0);
};

//*************************************************************************
// clase objeto ply
//*************************************************************************

class _objeto_ply: public _triangulos3D
{
public:
   _objeto_ply();

void  parametros(char *archivo);
};

//************************************************************************
// objeto por revolución
//************************************************************************

class _rotacion: public _triangulos3D
{
public:
       _rotacion();
       
void parametros(vector<_vertex3f> perfil, int num, bool tapa_in = true, bool tapa_su = true);
};

//************************************************************************
// objeto por revolucion a partir de perfil en archivo ply
//************************************************************************

class _rotacion_ply: public _rotacion
{
public:
       _rotacion_ply();
       void parametros(char *archivo, int num, bool tapa_in = true, bool tapa_su = true);
       
};


//************************************************************************
// clase cilindro
//************************************************************************

class _cilindro: public _rotacion
{
public:
       _cilindro(float radio = 0.5, float altura = 1);
};

//************************************************************************
// clase cono
//************************************************************************

class _cono: public _rotacion
{
public:
       _cono(float radio, float altura);
};

//************************************************************************
// clase esfera
//************************************************************************

class _esfera: public _rotacion
{
public:
       _esfera(float radio = 0.5);
};


//************************************************************************
// objeto por extrusión
//************************************************************************

class _extrusion: public _triangulos3D
{
public:
       _extrusion(vector<_vertex3f> poligono, float x, float y, float z, bool tapa_su, bool tapa_in);
};

//************************************************************************
// práctica 3, objeto jerárquico articulado descapotable
//************************************************************************
//************************************************************************
// semicilindro
//************************************************************************
class _semicilindro: public _triangulos3D
{
public:
      _semicilindro(float radio=0.5, float ancho=1.0, int num=LADOS_CIRCULO/2);
};

//************************************************************************
// semiesfera
//************************************************************************
class _semiesfera: public _rotacion
{
public:
    _semiesfera(float radio=1.0, int num1=12, int num2=12);
};


//************************************************************************
// piezas
//************************************************************************

class _chasis: public _triangulos3D
{
public:
       _chasis();
       void draw(_modo modo, float r, float g, float b, float grosor);
       
       //Valores
       float largo1, alto1, ancho1;
       float largo2, alto2, ancho2;
       float largo3, alto3, ancho3;
       float largo4, alto4, ancho4;
       float largo5, alto5, ancho5;
       float largo6, alto6, ancho6;
       
       protected:
       _cubo cubo;
       _extrusion *extrusion;
};

/*************************************************************************/
class _guardabarros: public _triangulos3D
{
public:
       _guardabarros();
       void draw(_modo modo, float r, float g, float b, float grosor);
       
       //Valores
       float largo, alto, ancho;
       float angulo;
       int lados_curva;
       
       protected:
       vector<_extrusion*> curva;
};

/*************************************************************************/
class _carroceria_lateral: public _triangulos3D
{
public:
       _carroceria_lateral();
       void draw(_modo modo, float r, float g, float b, float grosor);
       
       //Valores
       float largo1, alto1, ancho1, altura1;
       float largo2, alto2, ancho2;
       float largo3, alto3, ancho3;
       float largo4, alto4, ancho4;
       float largo5, alto5, ancho5;
       float largo6, alto6, ancho6;
       float largo7, alto7, ancho7;
       float largo8, alto8, ancho8;
       float largo9, alto9, ancho9;
       float largo10, alto10, ancho10;
       float largo11, alto11, ancho11, altura11;
       float largo12, alto12, ancho12, altura12;
       float largo_cil, alto_cil, ancho_cil;
       protected:
       _cubo cubo;
       _cilindro cilindro;
       _guardabarros gb;
       _extrusion *pieza10;
       _semicilindro semicilindro;
};

/*************************************************************************/
class _rueda: public _triangulos3D
{
public:
       _rueda();
       void draw(_modo modo, float r, float g, float b, float grosor);
       
       //Valores
       
       
       protected:
       _rotacion rotacion;
};

/*************************************************************************/
class _retrovisor: public _triangulos3D
{
public:
       _retrovisor();
       void draw(_modo modo, float r, float g, float b, float grosor);
       
       //Valores
       float largo1, alto1, ancho1;
       float largo2, alto2, ancho2;
       float largo3, alto3, ancho3;
       
       protected:
       _cilindro cilindro;
};

/*************************************************************************/
class _puerta: public _triangulos3D
{
public:
       _puerta();
       void draw(_modo modo, float r, float g, float b, float grosor);
       
       //Valores
       float largo1, alto1, ancho1;
       float pos_largo_r, pos_alto_r, pos_ancho_r;
       
       protected:
       _cubo cubo;
       _retrovisor retrovisor;
};

/*************************************************************************/
class _cuerpo_delantero: public _triangulos3D
{
public:
       _cuerpo_delantero();
       void draw(_modo modo, float r, float g, float b, float grosor);
       //Valores
       float largo1, alto1, ancho1;
       float escalaY;
       float alto2_escalado, ancho2_escalado;
       float largo2, alto2, ancho2;
       float largo3, alto3, ancho3;
       
       protected:
       _semicilindro semicilindro;
       _cubo parabrisas;
       _cubo cubo;
       
};

/*************************************************************************/
class _faro_delantero: public _triangulos3D
{
public:
       _faro_delantero();
       void draw(_modo modo, float r, float g, float b, float grosor);
       //Valores
       float largo1, alto1, ancho1;
       float radio_f1, ancho_f1, altura_f1;
       float radio_f2, ancho_f2, altura_f2;
       
       protected:
       _cilindro cilindro;
       _semicilindro semicilindro;
       _cubo cubo;
};

/*************************************************************************/
class _luz_antiniebla: public _triangulos3D
{
public:
       _luz_antiniebla();
       void draw(_modo modo, float r, float g, float b, float grosor);
       //Valores
       float largo1, alto1, ancho1;
       float largo2, alto2, ancho2;
       protected:
       _semicilindro semicilindro;
       _cubo cubo;
};

/*************************************************************************/
class _morro: public _triangulos3D
{
public:
       _morro();
       void draw(_modo modo, float r, float g, float b, float grosor);
       //Valores
       float largo1, alto1, ancho1;
       float largo2, radio2, separacion2;
       float largo5, alto5, ancho5;
       float radio_f2, ancho_f2, altura_f2;
       float largo_pos_antiniebla, alto_pos_antiniebla, ancho_pos_antiniebla;
       protected:
       _cilindro cilindro;
       _semicilindro semicilindro;
       _cubo cubo;
       _luz_antiniebla luz_antiniebla;
};

/*************************************************************************/
class _parachoques_delantero: public _triangulos3D
{
public:
    _parachoques_delantero();
    void draw(_modo modo, float r, float g, float b, float grosor);
    //Valores
    float largo1, alto1, ancho1;
    float largo2, alto2, ancho2;
    
    protected:
    _cilindro cilindro;
    _cubo cubo;
};

/*************************************************************************/
class _luz_trasera: public _triangulos3D
{
public:
    _luz_trasera();
    void draw(_modo modo, float r, float g, float b, float grosor);
    //Valores
    float radio1, ancho1;
    float radio2, ancho2;
    
    protected:
    _cilindro cilindro;
    _semiesfera semiesfera;
};

/*************************************************************************/
class _parachoques_trasero: public _triangulos3D
{
public:
    _parachoques_trasero();
    void draw(_modo modo, float r, float g, float b, float grosor);
    //Valores
    float largo1, alto1, ancho1;
    float largo2, alto2, ancho2;
    
    protected:
    _cilindro cilindro;
    _cubo cubo;
};

/*************************************************************************/
class _maletero: public  _triangulos3D
{
public:
    _maletero(float _angulo_puerta = 0);
    void draw(_modo modo, float r, float g, float b, float grosor);
    //Valores
    float largo1, alto1, ancho1;
    float largo2, alto2, ancho2;
    float largo3, alto3, ancho3;
    float largo4, alto4, ancho4;
    float largo5, alto5, ancho5;
    float largo6, alto6, ancho6;
    float angulo_puerta;
    
    protected:
    _cubo cubo;
};   

/*************************************************************************/
class _cuerpo_trasero: public  _triangulos3D
{
public:
    _cuerpo_trasero();
    void draw(_modo modo, float r, float g, float b, float grosor);
    //Valores
    float largo1, alto1, ancho1;
    float largo2, alto2, ancho2;
    float largo3, alto3, ancho3;
    protected:
    _cubo cubo;
    _extrusion* pieza2;
};

/*************************************************************************/
class _asiento: public  _triangulos3D
{
public:
    _asiento();
    void draw(_modo modo, float r, float g, float b, float grosor);
    //Valores
    float largo1, alto1, ancho1;
    float largo2, alto2, ancho2;
    float largo3, alto3, ancho3;
    float largo4, alto4, ancho4;
    protected:
    _cubo cubo;
    _semicilindro semicilindro;
};
/*************************************************************************/
class _volante: public  _triangulos3D
{
public:
    _volante();
    void draw(_modo modo, float r, float g, float b, float grosor);
    //Valores
    float radio;
    float largo1, alto1, ancho1;
    float largo2, alto2, ancho2;
    float largo3;
    protected:
    _cilindro cilindro;
};
/*************************************************************************/
class _palanca_cambios: public  _triangulos3D
{
public:
    _palanca_cambios();
    void draw(_modo modo, float r, float g, float b, float grosor);
    //Valores
    float radio;
    float largo1, alto1, ancho1;
    float largo2, alto2, ancho2;
    float radio3, alto3;
    float radio4;
    protected:
    _cubo cubo;
    _cilindro cilindro;
    _esfera esfera;
};

/*************************************************************************/
class _reposapies: public  _triangulos3D
{
public:
    _reposapies();
    ~_reposapies();
    void draw(_modo modo, float r, float g, float b, float grosor);
    //Valores
    float radio;
    float largo1, alto1, ancho1;
    float largo2, alto2, ancho2;
    float radio3, alto3;
    float radio4;
    protected:
    _cubo cubo;
    _extrusion* pieza2;
    
};

/*************************************************************************/
class _techo: public  _triangulos3D
{
public:
    _techo();
    void draw(_modo modo, float r, float g, float b, float grosor);
    //Valores
    float coef, alpha;
    float largo1, alto1, ancho1;
    float largo2, alto2, ancho2;
    float largo3, alto3, ancho3;
    float radio4;
    protected:
    _cubo cubo;
    _extrusion* pieza2;
    
};

/*************************************************************************/
class _descapotable: public _triangulos3D
{
public:
       _descapotable();
       ~_descapotable();
       void draw(_modo modo, float r, float g, float b, float grosor);
       //Variables giros
       float giro_dir_ruedas;
       float giro_rot_ruedas;
       float giro_puerta_izq, giro_puerta_der;
       float giro_puerta_maletero;
       float giro_volante;
       //Valores
       float largo, alto, ancho;
       float largo_cl, alto_cl, ancho_cl;
       float largo_chasis, alto_chasis, alto_chasis_trasero, ancho_chasis;
       float largo_rueda, alto_rueda, ancho_rueda;
       float largo_pos_rueda, ancho_pos_rueda_del, ancho_pos_rueda_tra;
       float largo_puerta, alto_puerta, ancho_puerta;
       float largo_faro_d, alto_faro_d, ancho_faro_d;
       float largo_luz_t, ancho_luz_t;
       float ancho_pos_puerta, alto_pos_puerta;
       float alto_pos_cuerpo_d, ancho_pos_cuerpo_d;
       float alto_pos_faro_d, alto_pos_luz_t;
       float ancho_pos_cuerpo_t;
       float ancho_pos_parachoques_t;
       float largo_asiento_t, ancho_pos_asiento_t;
       float largo_pos_asiento_d, ancho_pos_asiento_d;
       float inclinacion_volante, alto_pos_volante;
       float ancho_pos_reposapies;
       protected:
       _chasis chasis;
       _rueda rueda;
       _carroceria_lateral carroceria_lateral;
       _puerta puerta;
       //_rotacion rotacion;
       _cuerpo_delantero cuerpo_delantero;
       _faro_delantero faro_delantero;
       _morro morro;
       _parachoques_delantero parachoques_delantero;
       _luz_trasera luz_trasera;
       _parachoques_trasero parachoques_trasero;
       _maletero* maletero;
       _cuerpo_trasero cuerpo_trasero;
       _asiento asiento;
       _volante volante;
       _palanca_cambios palanca_cambios;
       _reposapies reposapies;
       _techo techo;
};


