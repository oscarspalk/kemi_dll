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
			initlib("C:\\Program Files\\Maple 2022");
			Assert::AreEqual("Lithium", G(2));
		}

		TEST_METHOD(TestDifferentMasses) {
			initlib("C:\\Program Files\\Maple 2022");
			Assert::AreEqual(58.4397692820000003, M("NaCl"));
			Assert::AreEqual(1.00800000000000001, M("H"));
			Assert::AreEqual(315.0, M("Uue"));
		}
	};
}
