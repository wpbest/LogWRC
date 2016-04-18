#pragma once

using namespace Platform;
using namespace Windows::Storage;

namespace LogWRC
{
	public enum class LogLevel {debug=0, info=1, warn=2, error=3, fatal=4};

    public ref class Logger sealed
    {
    public:
        Logger();
        bool static Create(String^ fileName);
		void static SetLogLevel(LogLevel logLevel);
		bool static Debug(String^ message);
		bool static Info(String^ message);
		bool static Warn(String^ message);
		bool static Error(String^ message);
		bool static Fatal(String^ message);
    private:
		bool static Log(LogLevel logLeval, String^ message);
		static StorageFolder^ storageFolder;
        static String^ fileName;
		static LogLevel logLevel;
		static String^ GetLogLevelText(LogLevel logLevel);
        static String^ GetDateTime();
		bool static Write(String^ message);
	};
}
