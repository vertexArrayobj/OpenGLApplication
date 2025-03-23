#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "GLErrorManager.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "tests/TestClearColor.h"

int main(void)
{
	GLFWwindow* window;

	/* Initialize GLFW */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(960, 540, "OpenGL", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	// Vsync
	glfwSwapInterval(1);

	//// Setup Dear ImGui context
	ImGui::CreateContext();

	//
	//// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);   
	ImGui_ImplOpenGL3_Init();
	ImGuiIO& io = ImGui::GetIO();

	//// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	/* Initialize GLEW */
	if (glewInit() != GLEW_OK)
		std::cout << "ERROR" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;


	// Scope
	{
		float positions[] = {
			200.0f, 200.0f, 0.0f, 0.0f,  // 0
			400.0f, 200.0f, 1.0f, 0.0f,  // 1
			400.0f,  400.0f, 1.0f, 1.0f, // 2
			200.0f,  400.0f, 0.0f, 1.0f  // 3
		};

		unsigned int indicies[] = {
			0, 1, 2,
			2, 3, 0
		};

		// Blending
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		glEnable(GL_FRAMEBUFFER_SRGB);

		VertexArray va;
		VertexBuffer vb(positions, 4 * 4 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);

		IndexBuffer ib(indicies, 6);

		glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-200.0, -200.0, 0.0f));

		Shader shader("res/shaders/Basic.shader");

		Texture texture("res/textures/logo.png");
		texture.Bind();
		shader.SetShaderUniform1i("u_Texture", 0);
		
		Renderer renderer;

		float r = 0.8f;
		glm::vec3 translationA(0, 0, 0.0f);
		glm::vec3 translationB(200, 0, 0.0f);
		glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);

		// TODO: Tests


		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			renderer.Clear();

			// Start the Dear ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			model = glm::translate(glm::mat4(1.0f), translationA);
			glm::mat4 mvp = proj * view * model;

			shader.Bind();
			shader.SetShaderUniform4f("u_Color", r, r, 0.01f, 1.0f);
			shader.SetShaderUniformMat4f("u_MVP", mvp);

			renderer.Draw(va, ib, shader);

			model = glm::translate(glm::mat4(1.0f), translationB);
			mvp = proj * view * model;
			shader.SetShaderUniformMat4f("u_MVP", mvp);
			renderer.Draw(va, ib, shader);


			{
				ImGui::SliderFloat("float", &r, 0.0f, 1.0f);
				ImGui::SliderFloat3("TranslationA", &translationA.x, -200.0f, 1000.0f);
				ImGui::SliderFloat3("TranslationB", &translationB.x, -200.0f, 1000.0f);
				ImGui::Text("Application Framerate: %f" , io.Framerate);
			}

			// ImGui Render
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}

		shader.Unbind();
	}
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}