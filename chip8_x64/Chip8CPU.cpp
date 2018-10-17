#include "Chip8CPU.h"


Chip8CPU::Chip8CPU(PWSTR romPath)
{
	this->romPath = romPath;
}

Chip8CPU::~Chip8CPU()
{
}

void Chip8CPU::CPUReset()
{
	m_AddressI = 0 ;
	m_ProgramCounter = 0x200 ;
	memset(m_Registers,0,sizeof(m_Registers)) ; // set registers to 0

	// load in the game
	FILE* rom;
	if (_wfopen_s(&rom, romPath, L"rb") != 0)
	{
		MessageBox(NULL, "Chip8CPU::CPUReset()/_wfopen_s(): could not open the ROM file", NULL, MB_OK);
		MessageBoxW(NULL, romPath, L"romPath:", MB_OK);
		throw;
	}

	fread_s(&m_GameMemory[0x200], 0xFFF, 1, 0xDFF, rom);
	if (ferror(rom) != 0)
	{
		fclose(rom);
		MessageBox(NULL, "Chip8CPU::CPUReset()/fread_s: error reading the ROM file", NULL, MB_OK);
		throw;
	}
	fclose(rom);
}
