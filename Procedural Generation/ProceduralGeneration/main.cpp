#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

#include "Sky.h"


int Width;
int Height;
using namespace std;

void SetBackgroundColor(float time)
{
	float dayDuration = 10.0f;
	glm::vec4 backgroundcolor = glm::vec4(Sky::GetColorForTimeOfDay(time, dayDuration), 1.0f);
	glClearColor(backgroundcolor.r, backgroundcolor.g, backgroundcolor.b, 1.0f);
}


void display(GLFWwindow* window)
{
	float currentTime = glfwGetTime();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SetBackgroundColor(currentTime);


}

void LoadShaders()
{

}


void LoadCameras()
{

}

void LoadObjects()
{

}

void initLight()
{

}

void init()
{
	glEnable(GL_DEPTH_TEST);
	glm::vec4 backgroundcolor = glm::vec4(Sky::GetColorForTimeOfDay(75, 600), 1.0f);;
	glClearColor(backgroundcolor.r, backgroundcolor.g, backgroundcolor.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	initLight();
	LoadShaders();
	LoadCameras();
	LoadObjects();
}



// function to allow keyboard control
// it's called a callback function and must be registerd in main() using glutKeyboardFunc();
// the functions must be of a specific format - see freeglut documentation
// similar functions exist for mouse control etc
void keyPress(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	Height = height;
	Width = width;
	glViewport(0, 0, width, height);
}

// Function where we set our debuggables
void ImguiData()
{
	//ImGui new frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::SetNextWindowSize(ImVec2(400, 200));
	ImGui::Begin("ImGUI window");

}

void ImguiDraw()
{
	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

int main()
{
	Width = 1200;
	Height = 900;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// --------------------
	GLFWwindow* window = glfwCreateWindow(Width, Height, "Scene", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, keyPress);
	// For potential future use
	//glfwSetCursorPosCallback(window, mouse_callback);
	//glfwSetScrollCallback(window, scroll_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


	//IMGUI code
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	init();


	while (!glfwWindowShouldClose(window))
	{

		ImguiData();
		display(window);
		ImguiDraw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}