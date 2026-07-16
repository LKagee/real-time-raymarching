#include <stdio.h>
#include <string.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "shaders.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define WINDOW_TITLE "ShaderPlay"



typedef enum {
	GL_COLOR_BUFFER_BIT	 = 0x00004000,
	GL_ARRAY_BUFFER    	 = 0x8892,
	GL_ELEMENT_ARRAY_BUFFER  = 0x8893,
	GL_STATIC_DRAW	    	 = 0x88E4,
	GL_UNSIGNED_INT		 = 0x1405,
	GL_TRIANGLES		 = 0x0004,
	GL_VERTEX_SHADER	 = 0x8B31,
	GL_FRAGMENT_SHADER	 = 0x8B30,
	GL_FLOAT		 = 0x1406,
	GL_FALSE		 = 0x0000,
	GL_TRUE			 = 0x0001,
	GL_LINE			 = 0x1B01,
	GL_FRONT_AND_BACK	 = 0x0408,
} GL;

typedef struct {
	GLFWwindow *window;
} glfw_c;

typedef void (*GL_GENBUFFERS)              		(int, unsigned int*);
typedef void (*GL_VIEWPORTS)              		(int, int, int, int);
typedef void (*GL_CLEARCOLOR)            		(float, float, float, float);
typedef void (*GL_CLEAR)                   		(unsigned int);
typedef void (*GL_BINDBUFFER)              		(unsigned int, unsigned int);
typedef void (*GL_BUFFERDATA)              		(unsigned int, int, void*, unsigned int);
typedef void (*GL_DRAWELEMENTS)            		(unsigned int, int, unsigned int, int);
typedef void (*GL_BINDVERTEXARRAY)         		(int);
typedef void (*GL_USEPROGRAM)	           		(unsigned int);
typedef void (*GL_VERTEXATTRIBPOINTER)     		(int, int, unsigned int, unsigned int, int, void*);
typedef void (*GL_ENABLEVERTEXATTRIBARRAY) 		(int);
typedef unsigned int (*GL_CREATESHADER)		   	(unsigned int);
typedef void (*GL_SHADERSOURCE)		   		(unsigned int, int, char**, int*);
typedef void (*GL_COMPILESHADER)	   		(unsigned int);
typedef void (*GL_GETSHADERIV)		   		(unsigned int, unsigned int, int*);
typedef unsigned int (*GL_CREATEPROGRAM)		(void);
typedef void (*GL_ATTACHSHADER)				(unsigned int, unsigned int);
typedef void (*GL_LINKPROGRAM)				(unsigned int);
typedef void (*GL_DELETESHADER)				(unsigned int);
typedef void (*GL_GENVERTEXARRAYS)			(int, unsigned int*);
typedef void (*GL_DRAWARRAYS)				(unsigned int, int, int);
typedef void (*GL_POLYGONMODE)				(unsigned int, unsigned int);
GL_GENBUFFERS glGenBuffers;
GL_VIEWPORTS glViewport;
GL_CLEARCOLOR glClearColor;
GL_CLEAR glClear;
GL_BINDBUFFER glBindBuffer;
GL_BUFFERDATA glBufferData;
GL_DRAWELEMENTS glDrawElements;
GL_BINDVERTEXARRAY glBindVertexArray;
GL_USEPROGRAM glUseProgram;
GL_VERTEXATTRIBPOINTER glVertexAttribPointer;
GL_ENABLEVERTEXATTRIBARRAY glEnableVertexAttribArray;
GL_CREATESHADER glCreateShader;
GL_SHADERSOURCE glShaderSource;
GL_COMPILESHADER glCompileShader;
GL_GETSHADERIV glGetShaderiv;
GL_CREATEPROGRAM glCreateProgram;
GL_ATTACHSHADER glAttachShader;
GL_LINKPROGRAM glLinkProgram;
GL_DELETESHADER glDeleteShader;
GL_GENVERTEXARRAYS glGenVertexArrays;
GL_DRAWARRAYS glDrawArrays;
GL_POLYGONMODE glPolygonMode;

float triangles[] = {
	-1.0f, 1.0f, 0.0f,
	-1.0f, -1.0f, 0.0f,
	 1.0f,  1.0f, 0.0f, 
	 1.0f, -1.0f, 0.0f
};

unsigned int index[] = {
	0, 1, 2,
	1, 3, 2
};




void* glfw_init(glfw_c *context) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	context->window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
	if(context->window == NULL) {
		fprintf(stdout, "WINDOW CREATION FAILED\n");
		glfwTerminate();
		return NULL;
	}

	glfwMakeContextCurrent(context->window);
	return context->window;
}

void glfw_destroyWindow(glfw_c *context) {
	glfwDestroyWindow(context->window);
	glfwTerminate();
}

int buffers_init() {
	glGenBuffers = (GL_GENBUFFERS)glfwGetProcAddress("glGenBuffers");
	glViewport = (GL_VIEWPORTS)glfwGetProcAddress("glViewport");
	if(glViewport == NULL) fprintf(stdout, "FAILED LOADING GLVIEWPORT\n");
	glClearColor = (GL_CLEARCOLOR)glfwGetProcAddress("glClearColor");
	glClear = (GL_CLEAR)glfwGetProcAddress("glClear");
	glBindBuffer = (GL_BINDBUFFER)glfwGetProcAddress("glBindBuffer");
	glBufferData = (GL_BUFFERDATA)glfwGetProcAddress("glBufferData");
	glDrawElements = (GL_DRAWELEMENTS)glfwGetProcAddress("glDrawElements");
	glBindVertexArray = (GL_BINDVERTEXARRAY)glfwGetProcAddress("glBindVertexArray");
	glUseProgram = (GL_USEPROGRAM)glfwGetProcAddress("glUseProgram");
	glVertexAttribPointer = (GL_VERTEXATTRIBPOINTER)glfwGetProcAddress("glVertexAttribPointer");
	glEnableVertexAttribArray = (GL_ENABLEVERTEXATTRIBARRAY)glfwGetProcAddress("glEnableVertexAttribArray");
	glCreateShader = (GL_CREATESHADER)glfwGetProcAddress("glCreateShader");
	glShaderSource = (GL_SHADERSOURCE)glfwGetProcAddress("glShaderSource");
	glCompileShader = (GL_COMPILESHADER)glfwGetProcAddress("glCompileShader");
	glGetShaderiv = (GL_GETSHADERIV)glfwGetProcAddress("glGetShaderiv");
	glCreateProgram = (GL_CREATEPROGRAM)glfwGetProcAddress("glCreateProgram");
	glAttachShader = (GL_ATTACHSHADER)glfwGetProcAddress("glAttachShader");
	glLinkProgram = (GL_LINKPROGRAM)glfwGetProcAddress("glLinkProgram");
	glDeleteShader = (GL_DELETESHADER)glfwGetProcAddress("glDeleteShader");
	glGenVertexArrays = (GL_GENVERTEXARRAYS)glfwGetProcAddress("glGenVertexArrays");
	glDrawArrays = (GL_DRAWARRAYS)glfwGetProcAddress("glDrawArrays");
	glPolygonMode = (GL_POLYGONMODE)glfwGetProcAddress("glPolygonMode");
	return 0;
}

void size_callback(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}


int main( void )
{
	glfw_c context;
	glfw_init(&context);
	buffers_init();
     	char* fragShader = getFragShader();
	char* vertShader = getVertexShader();
	if(fragShader == NULL) printf("Fragment shader failed\n");
	if(vertShader == NULL) printf("Vertex shader failed\n");
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glfwSetFramebufferSizeCallback(context.window, size_callback);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	unsigned int VBO;
	unsigned int EBO;
	unsigned int VAO;
	unsigned int fragShaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
	unsigned int vertShaderHandle = glCreateShader(GL_VERTEX_SHADER);
	unsigned int shaderProgram = glCreateProgram();

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangles), triangles, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

	glShaderSource(vertShaderHandle, 1, &vertShader, NULL);
	glCompileShader(vertShaderHandle);

	glShaderSource(fragShaderHandle, 1, &fragShader, NULL);
	glCompileShader(fragShaderHandle);

	glAttachShader(shaderProgram, vertShaderHandle);
	glAttachShader(shaderProgram, fragShaderHandle);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	glDeleteShader(vertShaderHandle);
	glDeleteShader(fragShaderHandle);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

#ifdef WIREFRAME
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#endif
	

	while(!glfwWindowShouldClose(context.window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);	
		glfwSwapBuffers(context.window);
		glfwPollEvents();
	}

	glfw_destroyWindow(&context);
	return 0;
}
