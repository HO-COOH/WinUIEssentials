#pragma once

#if BuildWinUIEssential
#define WinUIEssentialDllApi __declspec(dllexport)
#else
#define WinUIEssentialDllApi __declspec(dllimport)
#endif