#pragma once
#ifdef REVERSICORE_LIB
#define REVERSI_EXPORT __declspec(dllexport)
#else 
#define REVERSI_EXPORT __declspec(dllimport)
#endif