#pragma once
#if !defined(__DOUBLEBUFFER_HPP__)
#define __DOUblEBUFFER_HPP__

#include <Windows.h>
#include <iostream>

namespace Console
{
	int ScreenIdx = 0;
	int line = 0;
	DWORD width=0;
	HANDLE g_hScreen[2];

	void CreatBuffer()
	{
		CONSOLE_CURSOR_INFO cci;

		g_hScreen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		g_hScreen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	}

	void ClearBuffer()
	{
		COORD Coor = { 0,0 };
		DWORD dw;
		FillConsoleOutputCharacter(g_hScreen[ScreenIdx], ' ', width * line, Coor, &dw);
	}

	void WriteBuffer(const char* fmt, ...)
	{
		char text[2048] = { 0 };
		va_list va_alist;
		va_start(va_alist, fmt);
		vsprintf_s(text, fmt, va_alist);
		va_end(va_alist);

		COORD Coord = { 0, line++ };
		SetConsoleCursorPosition(g_hScreen[ScreenIdx], Coord);

		DWORD dw;
		DWORD len = strlen(text);
		WriteFile(g_hScreen[ScreenIdx], text, len, &dw, NULL);
		width = max(width, len);
	}

	void FlipBuffer()
	{
		SetConsoleActiveScreenBuffer(g_hScreen[ScreenIdx]);
		ScreenIdx ^= 1;
		ClearBuffer();
		line = 0;
		width = 0;
	}
}

#endif