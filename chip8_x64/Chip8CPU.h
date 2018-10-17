#pragma once

#include <vector>
#include <Windows.h>

typedef unsigned char BYTE;
typedef unsigned short int WORD;

class Chip8CPU
{
public:
	Chip8CPU(PWSTR romPath);
	~Chip8CPU();
	void CPUReset();

	PWSTR romPath; // Path to the ROM file
	BYTE m_GameMemory[0xFFF]; // 0xFFF bytes of memory
	BYTE m_Registers[16]; // 16 registers, 1 byte each
	WORD m_AddressI; // the 16-bit address register I
	WORD m_ProgramCounter; // the 16-bit program counter
	std::vector<WORD> m_Stack; // the 16-bit stack
};

