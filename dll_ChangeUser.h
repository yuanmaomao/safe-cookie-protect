#ifndef _DLL_CHANGEUSER_
#define _DLL_CHANGEUSER_

#include <string>

using namespace std;

extern "C" __declspec(dllexport) bool UserLogin();
extern "C" __declspec(dllexport) bool UserLogout();

#endif