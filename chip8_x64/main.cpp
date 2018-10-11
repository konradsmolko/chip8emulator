#include <Windows.h>
#include <ShObjIdl.h>
#include <fstream>
//#include <exception>

#include "SDL.h"
#include "Chip8CPU.h"

Chip8CPU* cpu;

PWSTR OpenROM()
{
	PWSTR pszFilePath = NULL;
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

	if (SUCCEEDED(hr))
	{
		IFileOpenDialog *pFileOpen;

		// Create the FileOpenDialog object.
		hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
			IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

		if (SUCCEEDED(hr))
		{
			// Show the Open dialog box.
			hr = pFileOpen->Show(NULL);

			if (SUCCEEDED(hr))
			{
				IShellItem *pItem;
				hr = pFileOpen->GetResult(&pItem);
				if (SUCCEEDED(hr))
				{
					hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath); // Format - F:\myfolder\kappa.txt
					CoTaskMemFree(pszFilePath);
					pItem->Release();
				}
			}
			pFileOpen->Release();
		}
		CoUninitialize();
	}

	if (pszFilePath == NULL)
	{
		throw "OpenRom()/GetRomPath(): pszFilePath is NULL";
	}

	return pszFilePath;
}

int main(int argc, char* argv[])
{
	cpu = new Chip8CPU(OpenROM());
	cpu->CPUReset();

	return 0;
}