#include "TestClearColor.h"
#include "../GLErrorManager.h"
#include "imgui/imgui.h"
#include <iostream>

namespace test
{
	test::TestClearColor::TestClearColor()
		:m_ClearColor {0.2, 0.3f, 0.8f, 1.0f}
	{
	}

	test::TestClearColor::~TestClearColor()
	{
		std::cout << "Destroyed Clear Color Scene" << std::endl;
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
	}

	void test::TestClearColor::OnUpdate(float deltatime)
	{
	}

	void test::TestClearColor::OnRender()
	{
		GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
	}

	void test::TestClearColor::OnImGuiRender()
	{
		ImGui::ColorEdit4("Clear Color", m_ClearColor);
	}

}

