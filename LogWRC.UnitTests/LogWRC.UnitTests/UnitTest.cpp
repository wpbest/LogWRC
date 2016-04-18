#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace LogWRC;

namespace LogWRC_UnitTests
{
    TEST_CLASS(UnitTestsLogWRC)
    {
    public:
        TEST_METHOD(TestMethodCreate)
        {
            bool logCreated = LogWRC::Logger::Create("log.txt");
            Assert::AreEqual(true, logCreated, L"LogWRC::Logger::Create('log.txt')", LINE_INFO());
        }
        TEST_METHOD(TestMethodLog)
        {
            bool logWritten = LogWRC::Logger::Debug("Hello");
            Assert::AreEqual(true, logWritten, L"LogWRC::Logger::Debug('Hello')", LINE_INFO());
        }
    };
}