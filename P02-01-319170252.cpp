//Pr�ctica 2: �ndices, mesh, proyecciones, transformaciones geom�tricas
#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>
//glm
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
//clases para dar orden y limpieza al c�digo
#include"Mesh.h"
#include"Shader.h"
#include"Window.h"
//Dimensiones de la ventana
const float toRadians = 3.14159265f / 180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList; //lista de mallas
std::vector<MeshColor*> meshColorList; //lista de mallas con color
std::vector<Shader>shaderList; //lista de shaders
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";
static const char* vContorno = "shaders/contorno.vert";
static const char* fContorno = "shaders/contorno.frag";
//shaders nuevos se crear�an ac�

float angulo = 0.0f;

//color caf� en RGB : 0.478, 0.255, 0.067

//Pir�mide triangular regular
void CreaPiramide()
{
	unsigned int indices[] = {
		0,1,2,
		1,3,2,
		3,0,2,
		1,0,3

	};
	GLfloat vertices[] = {
		-0.5f, -0.5f,0.0f,	//0
		0.5f,-0.5f,0.0f,	//1
		0.0f,0.5f, -0.25f,	//2
		0.0f,-0.5f,-0.5f,	//3

	};
	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);
}
//V�rtices de un cubo
void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	GLfloat cubo_vertices[] = {
		// front
		-0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		// back
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f
	};
	Mesh* cubo = new Mesh();
	cubo->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
	meshList.push_back(cubo);
}

void CrearLetrasyFiguras()
{
	GLfloat vertices_letras[] = {
	//LETRA M 
		-0.95f, -0.5f, 0.0f,1.0f, 0.713f, 0.757f,
		-0.85f, -0.5f, 0.0f,1.0f, 0.713f, 0.757f,
		-0.95f,  0.5f, 0.0f,1.0f, 0.713f, 0.757f,
		
		-0.95f, 0.5f, 0.0f,1.0f, 0.713f, 0.757f,
		-0.85f, 0.5f, 0.0f,1.0f, 0.713f, 0.757f,
		-0.85f,  -0.5f, 0.0f,1.0f, 0.713f, 0.757f,

		 -0.85f, 0.25f, 0.0f,1.0f, 0.713f, 0.757f,
		 -0.65f, 0.25f, 0.0f,1.0f, 0.713f, 0.757f,
		 -0.85f, 0.5f, 0.0f,1.0f, 0.713f, 0.757f,

		 -0.65, 0.25f, 0.0f,1.0f, 0.713f, 0.757f,
		 -0.45, 0.25f, 0.0f,1.0f, 0.713f, 0.757f,
		 -0.45f, 0.5f, 0.0f,1.0f, 0.713f, 0.757f,

		 -0.85f, 0.25f, 0.0f,1.0f, 0.713f, 0.757f,
		 -0.45f, 0.25f, 0.0f,1.0f, 0.713f, 0.757f,
		 -0.65f, 0.0f, 0.0f,1.0f, 0.713f, 0.757f,

		-0.45f, -0.5f, 0.0f,1.0f, 0.713f, 0.757f,
		-0.35f, -0.5f, 0.0f,1.0f, 0.713f, 0.757f,
		-0.35f,  0.5f, 0.0f,1.0f, 0.713f, 0.757f,

		-0.45f, 0.5f, 0.0f,1.0f, 0.713f, 0.757f,
		-0.35f, 0.5f, 0.0f,1.0f, 0.713f, 0.757f,
		-0.45f,  -0.5f, 0.0f,1.0f, 0.713f, 0.757f

	};
	MeshColor* letras = new MeshColor();
	letras->CreateMeshColor(vertices_letras,126);
	meshColorList.push_back(letras);

	GLfloat vertices_letrasA[] = {
		//LETRA A 

		-0.3f, -0.5f, 0.0f,0.73f, 0.57f, 0.87f,
		-0.2f, -0.5f, 0.0f,0.73f, 0.57f, 0.87f,
		-0.2f, -0.2f, 0.0f,0.73f, 0.57f, 0.87f,
		-0.2f, -0.2f, 0.0f,0.73f, 0.57f, 0.87f,
		-0.1f, -0.2f, 0.0f,0.73f, 0.57f, 0.87f,
		-0.2f, -0.5f, 0.0f,0.73f, 0.57f, 0.87f,

		-0.2f, -0.2f, 0.0f,0.73f, 0.57f, 0.87f,
		-0.1, -0.2f, 0.0f,0.73f, 0.57f, 0.87f,
		-0.1f,0.1f, 0.0f,0.73f, 0.57f, 0.87f,

		-0.1, 0.1f, 0.0f,0.73f, 0.57f, 0.87f,
		0.0, 0.1f, 0.0f,0.73f, 0.57f, 0.87f,
		-0.1f, -0.2f, 0.0f,0.73f, 0.57f, 0.87f,
		//pico
		-0.1f, 0.1f, 0.0f,0.73f, 0.57f, 0.87f,
		0.0f, 0.1f, 0.0f,0.73f, 0.57f, 0.87f,
		0.0f, 0.5f, 0.0f,0.73f, 0.57f, 0.87f,
		//pico
		0.0f, 0.1f, 0.0f,0.73f, 0.57f, 0.87f,
		0.1f, 0.1f, 0.0f,0.73f, 0.57f, 0.87f,
		0.0f,  0.5f, 0.0f,0.73f, 0.57f, 0.87f,

		0.1f, 0.1f, 0.0f,0.73f, 0.57f, 0.87f,
		0.0f, 0.1f, 0.0f,0.73f, 0.57f, 0.87f,
		0.1f,  -0.2f, 0.0f,0.73f, 0.57f, 0.87f,

		0.2f, -0.2f, 0.0f,0.73f, 0.57f, 0.87f,
		0.1, -0.2f, 0.0f, 0.73f, 0.57f, 0.87f,
		0.1f,0.1f, 0.0f,0.73f, 0.57f, 0.87f,

		0.2f, -0.2f, 0.0f,0.73f, 0.57f, 0.87f,
		0.1f, -0.2f, 0.0f,0.73f, 0.57f, 0.87f,
		0.2f, -0.5f, 0.0f,0.73f, 0.57f, 0.87f,

		0.3f, -0.5f, 0.0f,0.73f, 0.57f, 0.87f,
		0.2f, -0.5f, 0.0f,0.73f, 0.57f, 0.87f,
		0.2f, -0.2f, 0.0f,0.73f, 0.57f, 0.87f,

		0.0f, -0.3f, 0.0f,0.73f, 0.57f, 0.87f,
		0.15f, -0.3f, 0.0f,0.73f, 0.57f, 0.87f,
		0.0f, -0.2f, 0.0f,0.73f, 0.57f, 0.87f,

		0.0f, -0.2f, 0.0f,0.73f, 0.57f, 0.87f,
		0.15f, -0.2f, 0.0f,0.73f, 0.57f, 0.87f,
		0.15f, -0.3f, 0.0f,0.73f, 0.57f, 0.87f,

		0.0f, -0.3f, 0.0f,0.73f, 0.57f, 0.87f,
		-0.15f, -0.3f, 0.0f,0.73f, 0.57f, 0.87f,
		0.0f, -0.2f, 0.0f,0.73f, 0.57f, 0.87f,

		0.0f, -0.2f, 0.0f,0.73f, 0.57f, 0.87f,
		-0.15f, -0.2f, 0.0f,0.73f, 0.57f, 0.87f,
		-0.15f, -0.3f, 0.0f,0.73f, 0.57f, 0.87f,
	};
	MeshColor* letrasA = new MeshColor();
	letrasA->CreateMeshColor(vertices_letrasA, 252);
	meshColorList.push_back(letrasA);


	GLfloat vertices_letrasS[] = {

		0.35f, -0.3f, 0.0f,0.68f, 0.85f, 0.90f,
		0.55f, -0.3f, 0.0f,0.68f, 0.85f, 0.90f,
		0.35f,  -0.1f, 0.0f,0.68f, 0.85f, 0.90f,

		0.35f, -0.3f, 0.0f,0.68f, 0.85f, 0.90f,
		0.55f, -0.3f, 0.0f,0.68f, 0.85f, 0.90f,
		0.55f,  -0.5f, 0.0f,0.68f, 0.85f, 0.90f,

		0.55f, -0.3f, 0.0f, 0.68f, 0.85f, 0.90f,
		0.75f, -0.3f, 0.0f, 0.68f, 0.85f, 0.90f,
		0.55f,  -0.5f, 0.0f, 0.68f, 0.85f, 0.90f,

		0.55f, -0.5f, 0.0f, 0.68f, 0.85f, 0.90f,
		0.75f, -0.5f, 0.0f, 0.68f, 0.85f, 0.90f,
		0.75f, -0.3f, 0.0f, 0.68f, 0.85f, 0.90f,

		0.75f, -0.3f, 0.0f, 0.68f, 0.85f, 0.90f,
		0.95f, -0.3f, 0.0f, 0.68f, 0.85f, 0.90f,
		0.75f, -0.5f, 0.0f, 0.68f, 0.85f, 0.90f,

		0.75f, -0.3f, 0.0f, 0.68f, 0.85f, 0.90f,
		0.95f, -0.3f, 0.0f, 0.68f, 0.85f, 0.90f,
		0.95f, -0.1f, 0.0f, 0.68f, 0.85f, 0.90f,

		0.75f, -0.3f, 0.0f, 0.68f, 0.85f, 0.90f,
		0.95f, -0.1f, 0.0f, 0.68f, 0.85f, 0.90f,
		0.75f, 0.1f, 0.0f, 0.68f, 0.85f, 0.90f,

		0.55f, -0.1f, 0.0f, 0.68f, 0.85f, 0.90f,
		0.75f, -0.3f, 0.0f, 0.68f, 0.85f, 0.90f,
		0.75f, 0.1f, 0.0f, 0.68f, 0.85f, 0.90f,

		0.55f, -0.1f, 0.0f, 0.68f, 0.85f, 0.90f,
		0.75f, 0.1f, 0.0f, 0.68f, 0.85f, 0.90f,
		0.55f, 0.3f, 0.0f, 0.68f, 0.85f, 0.90f,

		0.35f, 0.1f, 0.0f, 0.68f, 0.85f, 0.90f,
		0.55f, -0.1f, 0.0f, 0.68f, 0.85f, 0.90f,
		0.55f, 0.3f, 0.0f, 0.68f, 0.85f, 0.90f,

		0.35f, 0.3f, 0.0f, 0.68f, 0.85f, 0.90f,
		0.55f, 0.3f, 0.0f,0.68f, 0.85f, 0.90f,
		0.35f, 0.1f, 0.0f,0.68f, 0.85f, 0.90f,

		0.35f, 0.3f, 0.0f, 0.68f, 0.85f, 0.90f,
		0.55f, 0.3f, 0.0f, 0.68f, 0.85f, 0.90f,
		0.55f, 0.5f, 0.0f, 0.68f, 0.85f, 0.90f,

		0.55f, 0.3f, 0.0f, 0.68f, 0.85f, 0.90f,
		0.75f, 0.3f, 0.0f,  0.68f, 0.85f, 0.90f,
		0.55f, 0.5f, 0.0f,  0.68f, 0.85f, 0.90f,

		0.55f, 0.5f, 0.0f,  0.68f, 0.85f, 0.90f,
		0.75f, 0.5f, 0.0f, 0.68f, 0.85f, 0.90f,
		0.75f, 0.3f, 0.0f, 0.68f, 0.85f, 0.90f,

		0.75f, 0.3f, 0.0f, 0.68f, 0.85f, 0.90f,
		0.95f, 0.3f, 0.0f,  0.68f, 0.85f, 0.90f,
		0.75f, 0.5f, 0.0f,  0.68f, 0.85f, 0.90f,

		0.75f, 0.3f, 0.0f,  0.68f, 0.85f, 0.90f,
		0.95f, 0.3f, 0.0f,  0.68f, 0.85f, 0.90f,
		0.95f, 0.1f, 0.0f, 0.68f, 0.85f, 0.90f,

	};
	MeshColor* letrasS = new MeshColor();
	letrasS->CreateMeshColor(vertices_letrasS,288);
	meshColorList.push_back(letrasS);

	GLfloat vertices_triangulorojo[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.0f,	1.0f,		0.5f,			1.0f,	0.0f,	0.0f,

	};

	MeshColor* triangulorojo = new MeshColor();
	triangulorojo->CreateMeshColor(vertices_triangulorojo, 18);
	meshColorList.push_back(triangulorojo);

	GLfloat vertices_cuadradoverde[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,

	};

	MeshColor* cuadradoverde = new MeshColor();
	cuadradoverde->CreateMeshColor(vertices_cuadradoverde, 36);
	meshColorList.push_back(cuadradoverde);

	GLfloat vertices_trianguloverde[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			0.0f,	1.0f,	0.0f,
		1.0f,	-1.0f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.0f,	1.0f,		0.5f,			0.0f,	1.0f,	0.0f,

	};

	MeshColor* trianguloverde = new MeshColor();
	trianguloverde->CreateMeshColor(vertices_trianguloverde, 18);
	meshColorList.push_back(trianguloverde);


	GLfloat vertices_cuadradorojo[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.5f,	-0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		-0.5f,	-0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		-0.5f,	0.5f,		0.5f,			1.0f,	0.0f,	0.0f,

	};

	MeshColor* cuadradorojo = new MeshColor();
	cuadradorojo->CreateMeshColor(vertices_cuadradorojo, 36);
	meshColorList.push_back(cuadradorojo);

	GLfloat vertices_trianguloazul[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
		1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
		0.0f,	1.0f,		0.5f,			0.0f,	0.0f,	1.0f,

	};

	MeshColor* trianguloazul = new MeshColor();
	trianguloazul->CreateMeshColor(vertices_trianguloazul, 18);
	meshColorList.push_back(trianguloazul);

	GLfloat vertices_trianguloarbol[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			0.0f,	0.5f,	0.0f,
		1.0f,	-1.0f,		0.5f,			0.0f,	0.5f,	0.0f,
		0.0f,	1.0f,		0.5f,			0.0f,	0.5f,	0.0f,

	};

	MeshColor* trianguloarbol = new MeshColor();
	trianguloarbol->CreateMeshColor(vertices_trianguloarbol, 18);
	meshColorList.push_back(trianguloarbol);

	GLfloat vertices_cuadradoarbol[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			0.478f,	0.255f,	0.067f,
		0.5f,	-0.5f,		0.5f,			0.478f,	0.255f,	0.067f,
		0.5f,	0.5f,		0.5f,			0.478f,	0.255f,	0.067f,
		-0.5f,	-0.5f,		0.5f,			0.478f,	0.255f,	0.067f,
		0.5f,	0.5f,		0.5f,			0.478f,	0.255f,	0.067f,
		-0.5f,	0.5f,		0.5f,			0.478f,	0.255f,	0.067f,

	};

	MeshColor* cuadradoarbol = new MeshColor();
	cuadradoarbol->CreateMeshColor(vertices_cuadradoarbol, 36);
	meshColorList.push_back(cuadradoarbol);


}

void CreateShaders()
{

	Shader* shader1 = new Shader(); //shader para usar �ndices: objetos: cubo y  pir�mide
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

	Shader* shader2 = new Shader();//shader para usar color como parte del VAO: letras 
	shader2->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader2);

	Shader* shader3 = new Shader();//shader para usar color como parte del VAO: letras 
	shader3->CreateFromFiles(vContorno, fContorno);
	shaderList.push_back(*shader3);
}


int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();
	//CreaPiramide(); //�ndice 0 en MeshList
	//CrearCubo();//�ndice 1 en MeshList
	CrearLetrasyFiguras(); //usa MeshColor, �ndices en MeshColorList
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	//Projection: Matriz de Dimensi�n 4x4 para indicar si vemos en 2D( orthogonal) o en 3D) perspectiva
	glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
	//glm::mat4 projection = glm::perspective(glm::radians(60.0f)	,mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

	//Model
	// : Matriz de Dimensi�n 4x4 en la cual se almacena la multiplicaci�n de las transformaciones geom�tricas.
	glm::mat4 model(1.0); //fuera del while se usa para inicializar la matriz con una identidad

	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad


		//Para las letras hay que usar el segundo set de shaders con �ndice 1 en ShaderList 
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();



		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.0f, -0.1f, -5.0f));
		//model = glm::scale(model, glm::vec3(1.0f, 1.6f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[0]->RenderMeshColor();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.0f, -0.1f, -5.0f));
		//model = glm::scale(model, glm::vec3(1.0f, 1.6f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[1]->RenderMeshColor();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.0f, -0.1f, -5.0f));
		//model = glm::scale(model, glm::vec3(1.0f, 1.6f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[2]->RenderMeshColor();

		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas
		/*model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.25f, -0.1f, -4.0f));
		model = glm::scale(model, glm::vec3(0.35f, 0.4f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[2]->RenderMeshColor();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.25f, -0.1f, -4.0f));
		model = glm::scale(model, glm::vec3(0.35f, 0.4f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[2]->RenderMeshColor();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.8f, -4.0f));
		model = glm::scale(model, glm::vec3(0.35f, 0.4f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[2]->RenderMeshColor();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.6f, -4.0f));
		model = glm::scale(model, glm::vec3(0.6f, 0.4f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[5]->RenderMeshColor();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.75f, -0.4f, -4.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.35f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[6]->RenderMeshColor();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.75f, -0.4f, -4.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.35f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[6]->RenderMeshColor();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.75f, -0.8f, -4.0f));
		model = glm::scale(model, glm::vec3(0.15f, 0.4f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[7]->RenderMeshColor();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.75f, -0.8f, -4.0f));
		model = glm::scale(model, glm::vec3(0.15f, 0.4f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[7]->RenderMeshColor();

		shaderList[2].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.75f, -0.8f, -4.0f));
		model = glm::scale(model, glm::vec3(0.15f, 0.4f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[7]->RenderMeshColorOutline();

		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.0f, -0.5f, -5.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.6f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[4]->RenderMeshColorOutline();

		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.25f, -0.1f, -4.0f));
		model = glm::scale(model, glm::vec3(0.35f, 0.4f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[2]->RenderMeshColorOutline();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.25f, -0.1f, -4.0f));
		model = glm::scale(model, glm::vec3(0.35f, 0.4f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[2]->RenderMeshColorOutline();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.8f, -4.0f));
		model = glm::scale(model, glm::vec3(0.35f, 0.4f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[2]->RenderMeshColorOutline();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.6f, -4.0f));
		model = glm::scale(model, glm::vec3(0.6f, 0.4f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[5]->RenderMeshColorOutline();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.75f, -0.4f, -4.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.35f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[6]->RenderMeshColorOutline();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.75f, -0.4f, -4.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.35f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[6]->RenderMeshColorOutline();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.75f, -0.8f, -4.0f));
		model = glm::scale(model, glm::vec3(0.15f, 0.4f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[7]->RenderMeshColorOutline();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.75f, -0.8f, -4.0f));
		model = glm::scale(model, glm::vec3(0.15f, 0.4f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[7]->RenderMeshColorOutline();
		//Para el cubo y la pir�mide se usa el primer set de shaders con �ndice 0 en ShaderList*/

		//shaderList[0].useShader(); 
		//uniformModel = shaderList[0].getModelLocation();
		//uniformProjection = shaderList[0].getProjectLocation();
		//angulo += 0.1;
		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas

		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));// EL ROTATE VA DESPUES DEL TRANSLATE 

		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshList[1]->RenderMesh();


		//PIRAMUDE 
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(2.0f, 0.0f, -3.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		//meshList[0]->RenderMesh();


		glUseProgram(0);
		mainWindow.swapBuffers();

	}
	return 0;
}
// inicializar matriz: glm::mat4 model(1.0);
// reestablecer matriz: model = glm::mat4(1.0);
//Traslaci�n
//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
//////////////// ROTACI�N //////////////////
//model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
////////////////  ESCALA ////////////////
//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
///////////////////// T+R////////////////
/*model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
*/
/////////////R+T//////////
/*model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
*/