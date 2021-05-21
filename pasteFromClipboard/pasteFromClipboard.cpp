
#include "pch.h"

#include "stdlib.h"

#pragma comment (lib, "winmm.lib")


#define MACR_STRNCPY(x) strncpy_s(output,outputSize,x,_TRUNCATE)
const std::string version = "paste v1";

extern "C"
{
	__declspec (dllexport) void __stdcall RVExtensionVersion(char* output, int outputSize);
	__declspec (dllexport) void __stdcall RVExtension(char* output, int outputSize, const char* function);
}



std::string get_last_paste()
{
	if (!OpenClipboard( nullptr ))
		throw "can not open clipboard: " + GetLastError(); // error

	HANDLE hData = GetClipboardData( CF_TEXT );
	if (hData == nullptr)
		throw "Handle null: " + GetLastError(); // error


	char* pszText = static_cast<char*>(GlobalLock( hData ));
	if (pszText == nullptr)
		throw "PszText null: " + GetLastError(); // error


	std::string text( pszText );

	GlobalUnlock( hData );

	CloseClipboard();

	return text;
}



void __stdcall
RVExtension( char* output, int outputSize, const char* function )
{
	std::string result;
	std::string input( function );

	if (input == "paste")
	{
		MACR_STRNCPY( get_last_paste().c_str() );
	}
	if (input == "version")
	{
		MACR_STRNCPY( "Use command \"paste\" to get paste clipboard" );
	}
}



void __stdcall
RVExtensionVersion(char* output, int outputSize)
{
	MACR_STRNCPY(version.c_str());
}