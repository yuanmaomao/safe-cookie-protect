#include <cstring>
#include <string>
#include <Windows.h>
#include <tchar.h>
#include "dll_ChangeUser.h"

using namespace std;

TCHAR initKeyValue[110];
TCHAR secInitKeyValue[110];
bool tag = false;

bool UserLogin(){
	/*判断登录状态*/
	if(tag) return false;

	/*打开注册表项*/
	HKEY myKey;
	LPCTSTR keyPath = _T("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\User Shell Folders");
	if(RegOpenKeyEx(HKEY_CURRENT_USER, keyPath, 0, KEY_ALL_ACCESS, &myKey) != ERROR_SUCCESS) return false;

	/*获取注册表项键值*/
	LPCTSTR keyName = _T("Cookies");
	DWORD keyType = REG_EXPAND_SZ;
	TCHAR keyValue[110];
	DWORD keySize;
	if(RegQueryValueEx(myKey, keyName, 0, &keyType, (LPBYTE)keyValue, &keySize) != ERROR_SUCCESS) return false;
	wcscpy(initKeyValue, keyValue);

	/*修改注册表项键值*/
	wcscat(keyValue, _T("\\Guest"));

	/*写入注册表项*/
	keySize = wcslen(keyValue)*sizeof(TCHAR);
	if(RegSetValueEx(myKey, keyName, 0, keyType, (LPBYTE)keyValue, keySize) != ERROR_SUCCESS) return false;

	/*关闭注册表项*/
	if(RegCloseKey(myKey) != ERROR_SUCCESS) return false;

	/*获取windows版本信息*/
	OSVERSIONINFO osvi;
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&osvi);

	/*对win7系统注册表进行修改*/
	if(osvi.dwMajorVersion == 6&&osvi.dwMinorVersion == 1)
	{
		/*打开注册表项*/
		HKEY myKey;
		LPCTSTR keyPath = _T("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders");
		if(RegOpenKeyEx(HKEY_CURRENT_USER, keyPath, 0, KEY_ALL_ACCESS, &myKey) != ERROR_SUCCESS) return false;

		/*获取注册表项键值*/
		LPCTSTR keyName = _T("Cookies");
		DWORD keyType = REG_EXPAND_SZ;
		TCHAR keyValue[110];
		DWORD keySize;
		if(RegQueryValueEx(myKey, keyName, 0, &keyType, (LPBYTE)keyValue, &keySize) != ERROR_SUCCESS) return false;
		wcscpy(secInitKeyValue, keyValue);

		/*修改注册表项键值*/
		wcscat(keyValue, _T("\\Guest"));

		/*写入注册表项*/
		keySize = wcslen(keyValue)*sizeof(TCHAR);
		if(RegSetValueEx(myKey, keyName, 0, keyType, (LPBYTE)keyValue, keySize) != ERROR_SUCCESS) return false;

		/*关闭注册表项*/
		if(RegCloseKey(myKey) != ERROR_SUCCESS) return false;
	}

	/*更改登录状态*/
	tag = true;

	return true;
}

bool UserLogout(){
	/*判断登录状态*/
	if(!tag) return false;

	/*打开注册表项*/
	HKEY myKey;
	LPCTSTR keyPath = _T("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\User Shell Folders");
	if(RegOpenKeyEx(HKEY_CURRENT_USER, keyPath, 0, KEY_ALL_ACCESS, &myKey) != ERROR_SUCCESS) return false;

	/*写入注册表项*/
	LPCTSTR keyName = _T("Cookies");
	DWORD keyType = REG_EXPAND_SZ;
	DWORD keySize = wcslen(initKeyValue)*sizeof(TCHAR);
	if(RegSetValueEx(myKey, keyName, 0, keyType, (LPBYTE)initKeyValue, keySize) != ERROR_SUCCESS) return false;

	/*关闭注册表项*/
	if(RegCloseKey(myKey) != ERROR_SUCCESS) return false;

	/*获取windows版本信息*/
	OSVERSIONINFO osvi;
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&osvi);

	/*对win7系统注册表进行修改*/
	if(osvi.dwMajorVersion == 6&&osvi.dwMinorVersion == 1)
	{
		/*打开注册表项*/
		HKEY myKey;
		LPCTSTR keyPath = _T("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders");
		if(RegOpenKeyEx(HKEY_CURRENT_USER, keyPath, 0, KEY_ALL_ACCESS, &myKey) != ERROR_SUCCESS) return false;

		/*写入注册表项*/
		LPCTSTR keyName = _T("Cookies");
		DWORD keyType = REG_EXPAND_SZ;
		DWORD keySize = wcslen(secInitKeyValue)*sizeof(TCHAR);
		if(RegSetValueEx(myKey, keyName, 0, keyType, (LPBYTE)initKeyValue, keySize) != ERROR_SUCCESS) return false;

		/*关闭注册表项*/
		if(RegCloseKey(myKey) != ERROR_SUCCESS) return false;
	}

	/*更改登录状态*/
	tag = false;

	return true;
}