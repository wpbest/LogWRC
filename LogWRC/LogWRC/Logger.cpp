#include "pch.h"
#include "Logger.h"

using namespace LogWRC;
using namespace concurrency;
using namespace Windows::Globalization;
using namespace Windows::Foundation;

StorageFolder^ LogWRC::Logger::storageFolder = ApplicationData::Current->LocalFolder;
String^ LogWRC::Logger::fileName = "log.txt";
LogLevel  LogWRC::Logger::logLevel = LogWRC::LogLevel::debug;

LogWRC::Logger::Logger()
{
}

bool LogWRC::Logger::Create(String ^ fileName)
{
	bool returnValue = true;
	
	auto createFileTask = create_task(LogWRC::Logger::storageFolder->CreateFileAsync(fileName, Windows::Storage::CreationCollisionOption::ReplaceExisting));

	createFileTask.then([&](StorageFile^ newFile) {
		returnValue = true;
	}).wait();

	if (returnValue) LogWRC::Logger::fileName = fileName;

	return returnValue;
}

bool LogWRC::Logger::Write(String ^ message)
{
	bool returnValue = true;

	auto writeFileTask = create_task(LogWRC::Logger::storageFolder->CreateFileAsync(LogWRC::Logger::fileName, Windows::Storage::CreationCollisionOption::OpenIfExists));

	writeFileTask.then([&](StorageFile^ openedFile) {
		FileIO::WriteTextAsync(openedFile, message);
		returnValue = true;
	}).wait();

	return returnValue;
}

void LogWRC::Logger::SetLogLevel(LogLevel logLevel)
{
	LogWRC::Logger::logLevel = logLevel;
}

bool LogWRC::Logger::Debug(String ^ message)
{
	bool returnValue = false;
	returnValue = Log(LogLevel::debug, message);
	return returnValue;
}

bool LogWRC::Logger::Info(String ^ message)
{
	bool returnValue = false;
	returnValue = Log(LogLevel::info, message);
	return returnValue;
}

bool LogWRC::Logger::Warn(String ^ message)
{
	bool returnValue = false;
	returnValue = Log(LogLevel::warn, message);
	return returnValue;
}

bool LogWRC::Logger::Error(String ^ message)
{
	bool returnValue = false;
	returnValue = Log(LogLevel::error, message);
	return returnValue;
}

bool LogWRC::Logger::Fatal(String ^ message)
{
	bool returnValue = false;
	returnValue = Log(LogLevel::fatal, message);
	return returnValue;
}

bool LogWRC::Logger::Log(LogLevel logLeval, String^ message)
{
	bool returnValue = true;

	if (LogWRC::Logger::logLevel <= logLeval)
	{
		auto logMessage = GetLogLevelText(logLeval) + L" " + GetDateTime() + L" " + message;
		returnValue = Write(logMessage);
	}

	return returnValue;
}

String ^ LogWRC::Logger::GetLogLevelText(LogLevel logLevel)
{
	String^ logLevelText;

	switch (logLevel)
	{
	case LogLevel::debug:
		logLevelText = L"[Debug]";
		break;
	case LogLevel::info:
		logLevelText = L"[Info] ";
		break;
	case LogLevel::warn:
		logLevelText = L"[Warn] ";
		break;
	case LogLevel::error:
		logLevelText = L"[Error]";
		break;
	case LogLevel::fatal:
		logLevelText = L"[Fatal]";
		break;
	default:
		logLevelText = L"[?????]";
	}

	return logLevelText;
}

String ^ LogWRC::Logger::GetDateTime()
{
	auto dateFormatter = ref new Windows::Globalization::DateTimeFormatting::DateTimeFormatter("shortdate");
	auto timeFormatter = ref new Windows::Globalization::DateTimeFormatting::DateTimeFormatter("longtime");
	auto calendar = ref new Windows::Globalization::Calendar();
	auto now = calendar->GetDateTime();
	auto date = dateFormatter->Format(now);
	auto time = timeFormatter->Format(now);
	auto dateTime = date + L" " + time;
	return dateTime;
}
