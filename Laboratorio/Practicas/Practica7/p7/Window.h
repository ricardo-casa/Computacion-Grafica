#pragma once
#include<stdio.h>
#include<glew.h>
#include<glfw3.h>

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);
	int Initialise();
	GLfloat getBufferWidth() { return bufferWidth; }
	GLfloat getBufferHeight() { return bufferHeight; }
	GLfloat getXChange();
	GLfloat getYChange();
	GLfloat getmuevex() { return muevex; }

	GLfloat getHelicopter_x() { return move_helicopter_x; }
	GLfloat getHelicopter_y() { return move_helicopter_y; }
	GLfloat getHelicopter_z() { return move_helicopter_z; }

	GLfloat getCarro_x() { return move_carro_x; }
	GLfloat getCarro_z() { return move_carro_z; }
	GLfloat getCofre2() { return move_cofre_y; }

	int getCarMovement() { return car_movement; }


	bool getShouldClose() {
		return  glfwWindowShouldClose(mainWindow);
	}
	bool* getsKeys() { return keys; }
	void swapBuffers() { return glfwSwapBuffers(mainWindow); }

	~Window();
private:
	GLFWwindow* mainWindow;
	GLint width, height;
	bool keys[1024];
	GLint bufferWidth, bufferHeight;
	void createCallbacks();
	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	GLfloat muevex;

	GLfloat move_helicopter_x;
	GLfloat move_helicopter_y;
	GLfloat move_helicopter_z;

	
	GLfloat move_carro_x;
	GLfloat move_carro_z;

	GLfloat move_cofre_y;




	//teclas

	bool is_UP_down = false;
	bool is_DOWN_down = false;
	bool is_RIGHT_down = false;
	bool is_LEFT_down = false;

	bool is_1_down = false;
	bool is_2_down = false;

	bool is_z_down = false;
	bool is_y_down = false;
	bool is_x_down = false;
	
	bool is_c_down = false;


	//carro adelante atras
	//1 adelante
	//-1 atras
	int car_movement;


	bool mouseFirstMoved;
	static void ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode);
	static void ManejaMouse(GLFWwindow* window, double xPos, double yPos);

};
