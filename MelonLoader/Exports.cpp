#include "Exports.h"
#include "MelonLoader.h"
#include "Il2Cpp.h"
#include "Mono.h"
#include "HookManager.h"
#include "Logger.h"

void UNLOAD_MELONLOADER(bool alt) { MelonLoader::UNLOAD(alt); if (MelonLoader::IsGameIl2Cpp) Mono::Unload(); }
void Logger_Log(MonoString* txt) { Logger::Log(Mono::mono_string_to_utf8(txt)); }
void Logger_LogColor(MonoString* txt, ConsoleColor color) { Logger::Log(Mono::mono_string_to_utf8(txt), color); }
void Logger_LogWarning(MonoString* namesection, MonoString* txt) { Logger::LogWarning(Mono::mono_string_to_utf8(namesection), Mono::mono_string_to_utf8(txt)); }
void Logger_LogError(MonoString* namesection, MonoString* txt) { Logger::LogError(Mono::mono_string_to_utf8(namesection), Mono::mono_string_to_utf8(txt)); }
void Logger_LogModError(MonoString* namesection, MonoString* msg) { Logger::LogModError(Mono::mono_string_to_utf8(namesection), Mono::mono_string_to_utf8(msg)); }
void Logger_LogModStatus(int type) { Logger::LogModStatus(type); }
bool IsIl2CppGame() { return MelonLoader::IsGameIl2Cpp; }
bool IsDebugMode() { return MelonLoader::DebugMode; }
bool IsRainbowMode() { return MelonLoader::RainbowMode; }
bool IsRandomRainbowMode() { return MelonLoader::RandomRainbowMode; }
MonoString* GetGameDirectory() { return Mono::mono_string_new(Mono::Domain, MelonLoader::GamePath); }
MonoString* GetGameDataDirectory() { return Mono::mono_string_new(Mono::Domain, MelonLoader::DataPath); }
void Hook(Il2CppMethod* target, void* detour) { HookManager::Hook(target, detour); }
void Unhook(Il2CppMethod* target, void* detour) { HookManager::Unhook(target, detour); }
void Console_SetColor(ConsoleColor color) { Console::SetColor(color); }
bool IsOldMono() { return Mono::IsOldMono; }
MonoString* GetCompanyName() { return Mono::mono_string_new(Mono::Domain, ((MelonLoader::CompanyName == NULL) ? "UNKNOWN" : MelonLoader::CompanyName)); }
MonoString* GetProductName() { return Mono::mono_string_new(Mono::Domain, ((MelonLoader::ProductName == NULL) ? "UNKNOWN" : MelonLoader::ProductName)); }
MonoString* GetAssemblyDirectory() { return Mono::mono_string_new(Mono::Domain, Mono::AssemblyPath); }
MonoString* GetMonoConfigDirectory() { return Mono::mono_string_new(Mono::Domain, Mono::ConfigPath); }
MonoString* GetExePath() { return Mono::mono_string_new(Mono::Domain, MelonLoader::ExePath); }

void Exports::AddInternalCalls()
{
	Mono::mono_add_internal_call("MelonLoader.Imports::UNLOAD_MELONLOADER", UNLOAD_MELONLOADER);
	Mono::mono_add_internal_call("MelonLoader.Imports::Logger_Log", Logger_Log);
	Mono::mono_add_internal_call("MelonLoader.Imports::Logger_LogColor", Logger_LogColor);
	Mono::mono_add_internal_call("MelonLoader.Imports::Logger_LogWarning", Logger_LogWarning);
	Mono::mono_add_internal_call("MelonLoader.Imports::Logger_LogError", Logger_LogError);
	Mono::mono_add_internal_call("MelonLoader.Imports::Logger_LogModError", Logger_LogModError);
	Mono::mono_add_internal_call("MelonLoader.Imports::Logger_LogModStatus", Logger_LogModStatus);
	Mono::mono_add_internal_call("MelonLoader.Imports::IsIl2CppGame", IsIl2CppGame);
	Mono::mono_add_internal_call("MelonLoader.Imports::IsDebugMode", IsDebugMode);
	Mono::mono_add_internal_call("MelonLoader.Imports::IsRainbowMode", IsRainbowMode);
	Mono::mono_add_internal_call("MelonLoader.Imports::IsRandomRainbowMode", IsRandomRainbowMode);
	Mono::mono_add_internal_call("MelonLoader.Imports::GetGameDirectory", GetGameDirectory);
	Mono::mono_add_internal_call("MelonLoader.Imports::GetGameDataDirectory", GetGameDataDirectory);
	Mono::mono_add_internal_call("MelonLoader.Imports::GetAssemblyDirectory", GetAssemblyDirectory);
	Mono::mono_add_internal_call("MelonLoader.Imports::GetMonoConfigDirectory", GetMonoConfigDirectory);
	Mono::mono_add_internal_call("MelonLoader.Imports::Hook", Hook);
	Mono::mono_add_internal_call("MelonLoader.Imports::Unhook", Unhook);
	Mono::mono_add_internal_call("MelonLoader.Imports::AllocConsole", AllocConsole);
	Mono::mono_add_internal_call("MelonLoader.Imports::SetForegroundWindow", SetForegroundWindow);
	Mono::mono_add_internal_call("MelonLoader.Imports::GetConsoleWindow", GetConsoleWindow);
	Mono::mono_add_internal_call("MelonLoader.Imports::Console_SetColor", Console_SetColor);
	Mono::mono_add_internal_call("MelonLoader.Imports::IsOldMono", IsOldMono);
	Mono::mono_add_internal_call("MelonLoader.Imports::GetCompanyName", GetCompanyName);
	Mono::mono_add_internal_call("MelonLoader.Imports::GetProductName", GetProductName);
	Mono::mono_add_internal_call("MelonLoader.Imports::GetExePath", GetExePath);
}