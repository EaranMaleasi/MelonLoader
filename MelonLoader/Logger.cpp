#include <chrono>
#include <sstream>
#include <direct.h>
#include <ctime>
#include <list>
#include <string>
#include "Logger.h"
#include "MelonLoader.h"

LogStream Logger::LogFile;
int Logger::MaxLogs = 10;
const char* Logger::FilePrefix = "MelonLoader_";
const char* Logger::FileExtention = "log";

void Logger::Initialize(std::string filepathstr)
{
	auto now = std::chrono::system_clock::now();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
	auto timer = std::chrono::system_clock::to_time_t(now);
	std::tm bt;
	localtime_s(&bt, &timer);
	std::string logFolderPath = filepathstr + "\\Logs";
	if (!MelonLoader::DirectoryExists(logFolderPath.c_str()))
		int returnval = _mkdir(logFolderPath.c_str());
	else
		CleanOldLogs(logFolderPath);
	std::stringstream filepath;
	filepath << logFolderPath << "\\" << FilePrefix << std::put_time(&bt, "%y-%m-%d_%OH-%OM-%OS") << "." << std::setfill('0') << std::setw(3) << ms.count() << "." << FileExtention;
	LogFile.coss = std::ofstream(filepath.str());
}

void Logger::CleanOldLogs(std::string logFolderPath)
{
	if (MaxLogs > 0)
	{
		std::list<std::filesystem::directory_entry>entry_list;
		for (std::filesystem::directory_entry entry : std::filesystem::directory_iterator(logFolderPath))
		{
			if (entry.is_regular_file())
			{
				std::string entry_file = entry.path().filename().generic_string();
				if ((entry_file.rfind(FilePrefix, NULL) == NULL) && (entry_file.rfind(FileExtention) == (entry_file.size() - std::string(FileExtention).size())))
					entry_list.push_back(entry);
			}
		}
		if (entry_list.size() >= MaxLogs)
		{
			entry_list.sort(Logger::CompareWritetime);
			for (std::list<std::filesystem::directory_entry>::iterator it = std::next(entry_list.begin(), (MaxLogs - 1)); it != entry_list.end(); ++it)
				remove((*it).path().u8string().c_str());
		}
	}
}

void Logger::LogTimestamp(ConsoleColor color)
{
	auto now = std::chrono::system_clock::now();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
	auto timer = std::chrono::system_clock::to_time_t(now);
	std::tm bt;
	localtime_s(&bt, &timer);

	std::stringstream output;
	output << std::put_time(&bt, "%H:%M:%S") << "." << std::setfill('0') << std::setw(3) << ms.count();
	LogFile << "[" << output.str() << "] ";

	if (MelonLoader::DebugMode)
	{
		Console::Write("[", ((color != ConsoleColor_Black) ? color : ConsoleColor_Gray));
		Console::Write(output.str(), ((color != ConsoleColor_Black) ? color : ConsoleColor_Green));
		Console::Write("] ", ((color != ConsoleColor_Black) ? color : ConsoleColor_Gray));
	}
}

void Logger::Log(const char* txt)
{
	LogTimestamp();
	LogFile << txt << std::endl;
	if (MelonLoader::DebugMode)
	{
		Console::Write("[");
		Console::Write("MelonLoader", ConsoleColor_Magenta);
		Console::Write("] ");
		Console::WriteLine(txt);
	}
}

void Logger::Log(const char* txt, ConsoleColor color)
{
	LogTimestamp(color);
	LogFile << txt << std::endl;
	if (MelonLoader::DebugMode)
	{
		Console::Write("[");
		Console::Write("MelonLoader", ConsoleColor_Magenta);
		Console::Write("] ");
		Console::WriteLine(txt, color);
	}
}

void Logger::LogWarning(const char* txt)
{
	LogTimestamp(ConsoleColor_Yellow);
	LogFile << "[Warning] " << txt << std::endl;
	if (MelonLoader::DebugMode)
	{
		Console::Write("[MelonLoader] ", ConsoleColor_Yellow);
		Console::WriteLine(("[Warning] " + std::string(txt)), ConsoleColor_Yellow);
	}
}

void Logger::LogWarning(const char* namesection, const char* txt)
{
	LogTimestamp(ConsoleColor_Yellow);
	LogFile << namesection << "[Warning] " << txt << std::endl;
	if (MelonLoader::DebugMode)
	{
		Console::Write("[MelonLoader] ", ConsoleColor_Yellow);
		Console::WriteLine((std::string(namesection) + "[Warning] " + std::string(txt)), ConsoleColor_Yellow);
	}
}

void Logger::LogError(const char* txt)
{
	LogTimestamp(ConsoleColor_Red);
	LogFile << "[Error] " << txt << std::endl;
	if (MelonLoader::DebugMode)
	{
		Console::Write("[MelonLoader] ", ConsoleColor_Red);
		Console::WriteLine(("[Error] " + std::string(txt)), ConsoleColor_Red);
	}
}

void Logger::LogError(const char* namesection, const char* txt)
{
	LogTimestamp(ConsoleColor_Red);
	LogFile << namesection << "[Error] " << txt << std::endl;
	if (MelonLoader::DebugMode)
	{
		Console::Write("[MelonLoader] ", ConsoleColor_Red);
		Console::WriteLine((std::string(namesection) + "[Error] " + std::string(txt)), ConsoleColor_Red);
	}
}

void Logger::LogModError(const char* namesection, const char* msg)
{
	LogTimestamp(ConsoleColor_Yellow);
	LogFile << namesection << "[Error] " << msg << std::endl;
	if (MelonLoader::DebugMode)
	{
		Console::Write("[MelonLoader] ", ConsoleColor_Yellow);
		Console::WriteLine((std::string(namesection) + "[Error] " + std::string(msg)), ConsoleColor_Yellow);
	}
}

void Logger::LogModStatus(int type)
{
	LogTimestamp();
	LogFile << "Status: " << ((type == 0) ? "Universal" : ((type == 1) ? "Compatible" : ((type == 2) ? "No MelonModGameAttribute!" : "INCOMPATIBLE!"))) << std::endl;
	if (MelonLoader::DebugMode)
	{
		Console::Write("[");
		Console::Write("MelonLoader", ConsoleColor_Magenta);
		Console::Write("] ");
		Console::Write("Status: ", ConsoleColor_Blue);
		if (type == 0)
			Console::WriteLine("Universal", ConsoleColor_Cyan);
		else if (type == 1)
			Console::WriteLine("Compatible", ConsoleColor_Green);
		else if (type == 2)
			Console::WriteLine("No MelonModGameAttribute!", ConsoleColor_Yellow);
		else
			Console::WriteLine("INCOMPATIBLE!", ConsoleColor_Red);
	}
}