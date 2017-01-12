#ifndef CADVANCED_UTILITIES_H
#define CADVANCED_UTILITIES_H
#pragma once

#include <windows.h>
#include <tchar.h>

#ifdef __cpluscplus
extern "C"
#endif

short Am_I_Registered(PCWSTR);
TCHAR* Replicate_Self();
short Write_To_Registry();
char* hide_user_input();

#endif //CADVANCED_UTILITIES_H
