#include "pch.h"
#include "CppUnitTest.h"
#include "kemi.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(Tests)
	{
	public:
		
		TEST_METHOD(TestInit)
		{
			initlib();
			Assert::AreEqual("", G(2));
		}

		TEST_METHOD(TestM) {
			Assert::AreEqual("Oscar", M("Oscar"));
		}
	};
}
