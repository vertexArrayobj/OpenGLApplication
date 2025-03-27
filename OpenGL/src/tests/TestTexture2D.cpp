#include "TestTexture2D.h"


namespace test
{
	TestTexture2D::TestTexture2D() :
		m_translationA(0, 0, 0.0f), m_translationB(200, 0, 0.0f),
		m_proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
		m_view(glm::translate(glm::mat4(1.0f), glm::vec3(-200.0, -200.0, 0.0f))), m_io(ImGui::GetIO())
	{

		constexpr float positions[] = {
			200.0f, 200.0f, 0.0f, 0.0f,  // 0
			400.0f, 200.0f, 1.0f, 0.0f,  // 1
			400.0f,  400.0f, 1.0f, 1.0f, // 2
			200.0f,  400.0f, 0.0f, 1.0f  // 3
		};

		constexpr unsigned int indicies[] = {
			0, 1, 2,
			2, 3, 0
		};

		m_VAO = std::make_unique<VertexArray>();
		m_VB = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
		m_IB = std::make_unique<IndexBuffer>(indicies, 6);
		m_Layout = std::make_unique<VertexBufferLayout>();
		m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
		m_Texture = std::make_unique<Texture>("res/textures/logo.png");

		m_Layout->Push<float>(2);
		m_Layout->Push<float>(2);
		m_VAO->AddBuffer(*m_VB, *m_Layout);
		m_Shader->SetShaderUniform1i("u_Texture", 0);

		
	}
	TestTexture2D::~TestTexture2D()
	{

	}

	float r_increment = 0.01f;
	float r = 0.0f;
	void TestTexture2D::OnUpdate(float deltatime)
	{
		r += r_increment;
		if (r >= 1.0f)
			r_increment = -(r_increment);
		else if (r <= 0.0f)
			r_increment = -(r_increment);


	}
	void TestTexture2D::OnRender()
	{
		Renderer renderer;
		Renderer::SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		m_VAO->Bind();
		m_Texture->Bind();
		m_Shader->Bind();
		m_Shader->SetShaderUniform4f("u_Color", r, 0.0f, 0.0f, 1.0f);

		glm::mat4 model;
		glm::mat4 mvp;

		model = glm::translate(glm::mat4(1.0f), m_translationA);
		mvp = m_proj * m_view * model;
		m_Shader->SetShaderUniformMat4f("u_MVP", mvp);
		renderer.Draw(*m_VAO, *m_IB, *m_Shader);

		model = glm::translate(glm::mat4(1.0f), m_translationB);
		mvp = m_proj * m_view * model;
		m_Shader->SetShaderUniformMat4f("u_MVP", mvp);
		renderer.Draw(*m_VAO, *m_IB, *m_Shader);
	}

	void TestTexture2D::OnImGuiRender()
	{
		ImGui::SliderFloat("Red Channel", &r, 0.0f, 1.0f);
		ImGui::SliderFloat3("TranslationA", &m_translationA.x, -200.0f, 1000.0f);
		ImGui::SliderFloat3("TranslationB", &m_translationB.x, -200.0f, 1000.0f);
		ImGui::Text("Application Framerate: %f", m_io.Framerate);
	}

}