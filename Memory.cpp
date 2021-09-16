#include "Memory.h"

uintptr_t Memory::getProcessID() {
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);
	uintptr_t processID = NULL;
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (snapshot == NULL)
	{
		std::cout << "Failed to get list of processes." << std::endl;
		return 0;
	}
	if (Process32First(snapshot, &entry))
	{
		do
		{
			if (_wcsicmp(entry.szExeFile, L"GTA5.exe") == 0)
			{
				processID = entry.th32ProcessID;
				std::cout << "Comparsion Successfull! Process ID: " << processID << std::endl;
				break;
			}
		} while (Process32Next(snapshot, &entry));
	}
	else {
		std::cout << "Failed to get first element in process list." << std::endl;
	}
	CloseHandle(snapshot);
	return processID;
}

uintptr_t Memory::getModuleBaseAddress(DWORD pID)
{
	uintptr_t modBaseAddr = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pID);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(hSnap, &modEntry))
		{
			do
			{
				if (!_wcsicmp(modEntry.szModule, L"GTA5.exe"))
				{

					modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
					std::cout << "Comparsion Successfull! Found Base Address @: " << modBaseAddr << std::endl;
					CloseHandle(hSnap);
					return modBaseAddr;
				}
			} while (Module32Next(hSnap, &modEntry));
		}
	}
	CloseHandle(hSnap);
	return modBaseAddr;
}

uintptr_t Memory::getPointerAddressVector(uintptr_t pointer, std::vector<uintptr_t> offsets) {
	uintptr_t buffer = pointer;
	int numOffsets = offsets.size();
	for (int x = 0; x < numOffsets; x++) {
		uintptr_t offset = offsets[x];
		ReadProcessMemory(hProcess, (LPCVOID)(buffer), &buffer, sizeof(uintptr_t), nullptr);
		buffer += offset;
	}
	return buffer;
}

int Memory::SetupMemory() {
	pID = getProcessID();
	baseAddress = getModuleBaseAddress(pID);

	hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, pID);
	if (hProcess == INVALID_HANDLE_VALUE || hProcess == NULL) { // error handling
		std::cout << "Failed to open process" << std::endl;
		return 0;
	}
	return 1;
}

void Memory::WriteByte(std::vector<uintptr_t> offsets, uintptr_t sig, byte data) {
	int sizeOfArray = sizeof(offsets) / sizeof(uintptr_t);
	uintptr_t adr = getPointerAddressVector((baseAddress + sig), offsets);
	WriteProcessMemory(hProcess, (LPVOID)(adr), &data, sizeof(byte), nullptr);
}

void Memory::WriteInt(std::vector<uintptr_t> offsets, uintptr_t sig, int data) {
	int sizeOfArray = sizeof(offsets) / sizeof(uintptr_t);
	uintptr_t adr = getPointerAddressVector((baseAddress + sig), offsets);
	WriteProcessMemory(hProcess, (LPVOID)(adr), &data, sizeof(int), nullptr);
}

void Memory::WriteFloat(std::vector<uintptr_t> offsets, uintptr_t sig, float data) {
	int sizeOfArray = sizeof(offsets) / sizeof(uintptr_t);
	uintptr_t adr = getPointerAddressVector((baseAddress + sig), offsets);
	WriteProcessMemory(hProcess, (LPVOID)(adr), &data, sizeof(float), nullptr);
}

void Memory::WriteDWORD(std::vector<uintptr_t> offsets, uintptr_t sig, DWORD data) {
	int sizeOfArray = sizeof(offsets) / sizeof(uintptr_t);
	uintptr_t adr = getPointerAddressVector((baseAddress + sig), offsets);
	WriteProcessMemory(hProcess, (LPVOID)(adr), &data, sizeof(DWORD), nullptr);
}

byte Memory::ReadByte(std::vector<uintptr_t> offsets, uintptr_t sig) {
	uintptr_t adr = getPointerAddressVector((baseAddress + sig), offsets);
	byte data = 0;
	ReadProcessMemory(hProcess, (LPVOID)(adr), &data, sizeof(byte), nullptr);
	return data;
}

int Memory::ReadInt(std::vector<uintptr_t> offsets, uintptr_t sig) {
	uintptr_t adr = getPointerAddressVector((baseAddress + sig), offsets);
	int data = 0;
	ReadProcessMemory(hProcess, (LPVOID)(adr), &data, sizeof(int), nullptr);
	return data;
}


float Memory::ReadFloat(std::vector<uintptr_t> offsets, uintptr_t sig) {
	uintptr_t adr = getPointerAddressVector((baseAddress + sig), offsets);
	float data = 0;
	ReadProcessMemory(hProcess, (LPVOID)(adr), &data, sizeof(float), nullptr);
	return data;
}

DWORD Memory::ReadDWORD(std::vector<uintptr_t> offsets, uintptr_t sig) {
	uintptr_t adr = getPointerAddressVector((baseAddress + sig), offsets);
	DWORD data = 0;
	ReadProcessMemory(hProcess, (LPVOID)(adr), &data, sizeof(DWORD), nullptr);
	return data;
}
