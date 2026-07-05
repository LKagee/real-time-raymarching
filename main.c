#include <stdio.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

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
} GL;

typedef struct {
	GLFWwindow *window;
} glfw_c;

typedef void (*GL_GENBUFFERS)              (int, unsigned int*);
typedef void (*GL_VIEWPORTS)               (int, int, int, int);
typedef void (*GL_CLEARCOLOR)              (float, float, float, float);
typedef void (*GL_CLEAR)                   (unsigned int);
typedef void (*GL_BINDBUFFER)              (unsigned int, unsigned int);
typedef void (*GL_BUFFERDATA)              (unsigned int, int, void*, unsigned int);
typedef void (*GL_DRAWELEMENTS)            (unsigned int, int, unsigned int, int);
typedef void (*GL_BINDVERTEXARRAY)         (int);
typedef void (*GL_USEPROGRAM)	           (unsigned int);
typedef void (*GL_VERTEXATTRIBPOINTER)     (int, int, unsigned int, unsigned int, int, void*);
typedef void (*GL_ENABLEVERTEXATTRIBARRAY) (int);
typedef void (*GL_CREATESHADER)		   (unsigned int);
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
	context->window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
	if(context->window == NULL) {
		fprintf(stdout, "WINDOW CREATION FAILED\n");
		glfwTerminate();
		return NULL;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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
	return 0;
}

void size_callback(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}


int main( void )
{
	glfw_c *context;
	glfw_init(context);
	buffers_init();
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glfwSetFramebufferSizeCallback(context->window, size_callback);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	unsigned int VBO;
	unsigned int EBO;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangles), triangles, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);



	while(!glfwWindowShouldClose(context->window)) {
		glfwSwapBuffers(context->window);
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
	}

	glfw_destroyWindow(context);
	return 0;
}
