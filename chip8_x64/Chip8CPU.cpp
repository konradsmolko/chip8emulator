#include "Chip8CPU.h"


Chip8CPU::Chip8CPU(PWSTR rom)
{
	romPath = rom;
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
	if (_wfopen_s(&rom, romPath, L"rb") == 0)
	{
		system("pause");
		throw "Chip8CPU::CPUReset()/_wfopen_s(): could not open the ROM file";
	}

	fread_s(&m_GameMemory[0x200], 0xFFF, 1, 0xFFF, rom);
	if (ferror(rom) != 0)
	{
		//system("pause");
		fclose(rom);
		throw "Chip8CPU::CPUReset()/fread_s: error reading the ROM file";
	}
	fclose(rom);
}
