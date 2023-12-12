#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_9.3/Lab9.3.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest93
{
	TEST_CLASS(UnitTest93)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			string name1 = "Lviv";
			string name2 = "Sokal";
			Route* p = new Route[2];
			p[0].sname = "Lviv";
			p[0].ename = "Kyiv";
			p[0].rnum = 12;

			p[1].sname = "Sokal";
			p[1].ename = "Kyiv";
			p[1].rnum = 18;

			Sort(p, 2);
			Assert::AreEqual(p[0].sname, name1);

		}
	};
}
