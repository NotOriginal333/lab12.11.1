#include "pch.h"
#include "CppUnitTest.h"
#include "../lab12.11.1/FileName.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestAddSubscriber)
		{
			TelephoneDirectory directory;
			std::string phoneNumber = "1234567890";
			int callDuration = 10;

			directory.addSubscriber(phoneNumber, callDuration);

			Node* temp = directory.getHead();
			Assert::AreEqual(phoneNumber, temp->data.phoneNumber);
			Assert::AreEqual(callDuration, temp->data.callDuration);
			Assert::IsNull(temp->next);
		}
	};
}
