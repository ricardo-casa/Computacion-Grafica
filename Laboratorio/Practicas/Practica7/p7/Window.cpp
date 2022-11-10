#include "Window.h"

Window::Window()
{
	width = 800;
	height = 600;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
Window::Window(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
	muevex = 2.0f;

	move_helicopter_x = 50.0f;
	move_helicopter_y = 50.0f;
	move_helicopter_z = 50.0f;

	move_carro_x = 0.0f;
	move_carro_z = 0.0f;

	move_cofre_y = 0.0f;






	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
int Window::Initialise()
{
	//Inicialización de GLFW
	if (!glfwInit())
	{
		printf("Falló inicializar GLFW");
		glfwTerminate();
		return 1;
	}
	//Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	mainWindow = glfwCreateWindow(width, height, "Primer ventana", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tamaño de Buffer
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//MANEJAR TECLADO y MOUSE
	createCallbacks();


	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST); //HABILITAR BUFFER DE PROFUNDIDAD
	// Asignar valores de la ventana y coordenadas

	//Asignar Viewport
	glViewport(0, 0, bufferWidth, bufferHeight);
	//Callback para detectar que se está usando la ventana
	glfwSetWindowUserPointer(mainWindow, this);
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, ManejaTeclado);
	glfwSetCursorPosCallback(mainWindow, ManejaMouse);
}
GLfloat Window::getXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat Window::getYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}




void Window::ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key == GLFW_KEY_Y)
	{
		theWindow->muevex += 1.0;
	}
	if (key == GLFW_KEY_U)
	{
		theWindow->muevex -= 1.0;
	}

	// TECLA Z
	if (key == GLFW_KEY_Z) theWindow->is_z_down = action == GLFW_PRESS;

	// TECLA Y
	if (key == GLFW_KEY_Y) theWindow->is_y_down = action == GLFW_PRESS;

	// TECLA X
	if (key == GLFW_KEY_X) theWindow->is_x_down = action == GLFW_PRESS;

	// TECLA C
	if (key == GLFW_KEY_C) theWindow->is_c_down = action == GLFW_PRESS;

	// TECLA 1
	if (key == GLFW_KEY_1) theWindow->is_1_down = action == GLFW_PRESS;
	// TECLA 2
	if (key == GLFW_KEY_2) theWindow->is_2_down = action == GLFW_PRESS;


	// LEFT
	if (key == GLFW_KEY_LEFT) theWindow->is_LEFT_down = action == GLFW_PRESS;
	// RIGHT
	if (key == GLFW_KEY_RIGHT) theWindow->is_RIGHT_down = action == GLFW_PRESS;

	// UP
	if (key == GLFW_KEY_UP) theWindow->is_UP_down = action == GLFW_PRESS;
	// DOWN
	if (key == GLFW_KEY_DOWN) theWindow->is_DOWN_down = action == GLFW_PRESS;


	//MOVIMIENTO Helicoptero 
	// z + 1 + UP
	if (theWindow->is_z_down && theWindow->is_1_down && theWindow->is_UP_down) theWindow->move_helicopter_z += 10.0;
	// z + 1 + DOWN 	  
	if (theWindow->is_z_down && theWindow->is_1_down && theWindow->is_DOWN_down) theWindow->move_helicopter_z -= 10.0;

	// y + 1 + UP
	if (theWindow->is_y_down && theWindow->is_1_down && theWindow->is_UP_down) theWindow->move_helicopter_y += 10.0;
	// y + 1 + DOWN 	  
	if (theWindow->is_y_down && theWindow->is_1_down && theWindow->is_DOWN_down) theWindow->move_helicopter_y -= 10.0;


	// x + 1 + UP
	if (theWindow->is_x_down && theWindow->is_1_down && theWindow->is_UP_down) theWindow->move_helicopter_x += 10.0;
	// x + 1 + DOWN 	  
	if (theWindow->is_x_down && theWindow->is_1_down && theWindow->is_DOWN_down) theWindow->move_helicopter_x -= 10.0;


	//MOVIMIENTO CARRO 
	// cofre
	// c + 2 + LEFT
	if (theWindow->is_z_down && theWindow->is_2_down && theWindow->is_LEFT_down) theWindow->move_cofre_y += 10.0;
	// c + 2 + RIGHT 	  
	if (theWindow->is_z_down && theWindow->is_2_down && theWindow->is_RIGHT_down) theWindow->move_cofre_y -= 10.0;
	
	//carro xyz
	// z + 2 + UP
	if (theWindow->is_z_down && theWindow->is_2_down && theWindow->is_UP_down) theWindow->move_carro_z += 10.0;
	// z + 2 + DOWN 	  					  
	if (theWindow->is_z_down && theWindow->is_2_down && theWindow->is_DOWN_down) theWindow->move_carro_z -= 10.0;
											  
										  
	// x + 2 + UP							  
	if (theWindow->is_x_down && theWindow->is_2_down && theWindow->is_UP_down) theWindow->move_carro_x += 10.0;
	// x + 2 + DOWN 	  					  
	if (theWindow->is_x_down && theWindow->is_2_down && theWindow->is_DOWN_down) theWindow->move_carro_x -= 10.0;
	printf("-----------------------------------------------\n");
	printf("%d %d %d\n", theWindow->is_z_down, theWindow->is_1_down, theWindow->is_UP_down);
	printf("%d", theWindow->is_c_down && theWindow->is_1_down && theWindow->is_UP_down);
	printf("-----------------------------------------------\n");

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
			printf("se presiono la tecla %d'\n", key);
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
			printf("se solto la tecla %d'\n", key);
		}
	}
}

void Window::ManejaMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;
}


Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();

}