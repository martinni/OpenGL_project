//**************************************************************************
// Práctica 1
//
// Domingo Martin Perandres 2013
//
// GPL
//**************************************************************************

#define GL_GLEXT_PROTOTYPES

#include <GL/gl.h>
#include <cstdlib>
#include <math.h>
#include <string.h>
#include "vertex.h"
#include "file_ply_stl.h"

using namespace std;


typedef GLfloat Real ; 	

typedef GLuint Natural ;

const unsigned int X=0, Y=1, Z=2 ;	//indices enteros de los ejes

struct Tupla3r		//tupla con 3 valores reales que representan coordenas
{
	Real coo[3];
} ;

struct Tupla3n		//tupla de 3 entero no negativos (naturales)
{
	Natural ind[3];	
} ;

struct CVerTri		//Coordenadas de los 3 vertices de un triangulo
{
	Tupla3r ver[3];
} ;

struct MallaTVT		//Malla con tabla de vertices y triangulos
{
	Natural num_ver ;	//numero de vertices
	Natural num_tri	;	//numero de triangulos
	Tupla3r * ver ;		//tabla de vertices (num_ver entradas)
	Tupla3n * tri ;		//tabla de triangulos (num_tri entradas)
				//Atributos
	Tupla3r * nor_tri ;	//normales de triangulos (num_tri entradas)
	Tupla3r * nor_ver ;	//normales de vertices (num_ver entradas)
	Tupla3r * col_tri ; 	//colores de triangulos(num_tri entradas)
	Tupla3r * col_ver ;	//colores de vertices (num_ver entradas)

	GLuint id_vbo_ver ; 	//identificador del VBO con la tabla de vertices
	GLuint id_vbo_tri ; 	//identificador del VBO con la tabla de triangulos

	GLuint id_vbo_col_ver;
	GLuint id_vbo_nor_ver;

	unsigned int tam_ver ; 	//tamano en bytes de la table de vertices
	unsigned int tam_tri ;	//tamano en bytes de la tabla de triangulos
} ;
	
struct NodoGE ;		//nodo del grafo e escena 

struct ParTransformacion	//parametros de una transformacion
{
	unsigned char tipo ;		//0=rotaction, 1=escalado, 2=traslacion
	Real par[3] ; 	// si tipo==0 -> eje de rotacion
			//	    1 -> vector de desplazamiento
			// 	    2 -> factores de escala
	Real angulo ;	// si tipo==0 -> angulo de rotacion
} ;

struct EntradaNGE	//entrada del nodo del grafo de escena
{
	unsigned char tipo ;	//0=malla, 1-sub-escena, 2=transformacion

	union
	{
		MallaTVT * malla; 	//ptr. a una malla tvt
		NodoGE * subesc ;	//ptr. a un sub-arbol
		ParTransformacion * transf ;	//ptr. a transformacion
	} ;
} ;

struct NodoGE 	//nodo del grafo de escena
{	
	std::vector<EntradaNGE> entrada ; 	//vector de entradas
} ;


void generar_malla(MallaTVT* malla, const char* nombre_fichero, bool revolucion, int N);

void draw_malla(MallaTVT* malla, int modo);

void leer_ply(const char* nombre_fichero, bool revolucion, vector<float> &vertices, vector<int> &caras, int N);

void MTVT_Visualizar_VA(MallaTVT * pm);

GLuint VBO_Crear(GLuint tipo, GLuint tamanio, GLvoid * puntero);

void MTVT_Crear_VBOs(MallaTVT * pm);

void MTVT_Visualizar_VBOs(MallaTVT *pm);

void MTVT_Visualizar_VBOs_AV(MallaTVT *pm);

void generate_vertices( vector<float> vertices, vector<float> &vertices_final, int N, char eje);

void generate_faces(vector<int> &caras, int N, int M);

void calculate_normales_tri(MallaTVT* malla);

void calculate_normales_ver(MallaTVT * malla);



// funciones de la practica3

void NGE_Visualizar(NodoGE *nodo, int modo);

void ComponerTrans(ParTransformacion *pt);

void escena(Real h, Real alpha, Real d);




