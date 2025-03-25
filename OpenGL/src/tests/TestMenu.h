#pragma once

#include "Test.h"
#include <vector>
#include <string>
#include <functional>
#include <iostream>


namespace test
{
	class TestMenu : public Test
	{
	public:
		TestMenu(Test*& currentTestP);

		void OnImGuiRender() override;

		template<typename T>
		void RegisterTest(const std::string& name)
		{

			std::cout << "Registering Test: " << name << std::endl;
			m_Tests.push_back(std::make_pair(name, []() { return new T(); }));
		}
		
	private:
		Test*& m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;
	};
}
