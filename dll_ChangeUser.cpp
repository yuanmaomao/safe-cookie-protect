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
	/*�жϵ�¼״̬*/
	if(tag) return false;

	/*��ע�����*/
	HKEY myKey;
	LPCTSTR keyPath = _T("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\User Shell Folders");
	if(RegOpenKeyEx(HKEY_CURRENT_USER, keyPath, 0, KEY_ALL_ACCESS, &myKey) != ERROR_SUCCESS) return false;

	/*��ȡע������ֵ*/
	LPCTSTR keyName = _T("Cookies");
	DWORD keyType = REG_EXPAND_SZ;
	TCHAR keyValue[110];
	DWORD keySize;
	if(RegQueryValueEx(myKey, keyName, 0, &keyType, (LPBYTE)keyValue, &keySize) != ERROR_SUCCESS) return false;
	wcscpy(initKeyValue, keyValue);

	/*�޸�ע������ֵ*/
	wcscat(keyValue, _T("\\Guest"));

	/*д��ע�����*/
	keySize = wcslen(keyValue)*sizeof(TCHAR);
	if(RegSetValueEx(myKey, keyName, 0, keyType, (LPBYTE)keyValue, keySize) != ERROR_SUCCESS) return false;

	/*�ر�ע�����*/
	if(RegCloseKey(myKey) != ERROR_SUCCESS) return false;

	/*��ȡwindows�汾��Ϣ*/
	OSVERSIONINFO osvi;
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&osvi);

	/*��win7ϵͳע�������޸�*/
	if(osvi.dwMajorVersion == 6&&osvi.dwMinorVersion == 1)
	{
		/*��ע�����*/
		HKEY myKey;
		LPCTSTR keyPath = _T("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders");
		if(RegOpenKeyEx(HKEY_CURRENT_USER, keyPath, 0, KEY_ALL_ACCESS, &myKey) != ERROR_SUCCESS) return false;

		/*��ȡע������ֵ*/
		LPCTSTR keyName = _T("Cookies");
		DWORD keyType = REG_EXPAND_SZ;
		TCHAR keyValue[110];
		DWORD keySize;
		if(RegQueryValueEx(myKey, keyName, 0, &keyType, (LPBYTE)keyValue, &keySize) != ERROR_SUCCESS) return false;
		wcscpy(secInitKeyValue, keyValue);

		/*�޸�ע������ֵ*/
		wcscat(keyValue, _T("\\Guest"));

		/*д��ע�����*/
		keySize = wcslen(keyValue)*sizeof(TCHAR);
		if(RegSetValueEx(myKey, keyName, 0, keyType, (LPBYTE)keyValue, keySize) != ERROR_SUCCESS) return false;

		/*�ر�ע�����*/
		if(RegCloseKey(myKey) != ERROR_SUCCESS) return false;
	}

	/*���ĵ�¼״̬*/
	tag = true;

	return true;
}

bool UserLogout(){
	/*�жϵ�¼״̬*/
	if(!tag) return false;

	/*��ע�����*/
	HKEY myKey;
	LPCTSTR keyPath = _T("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\User Shell Folders");
	if(RegOpenKeyEx(HKEY_CURRENT_USER, keyPath, 0, KEY_ALL_ACCESS, &myKey) != ERROR_SUCCESS) return false;

	/*д��ע�����*/
	LPCTSTR keyName = _T("Cookies");
	DWORD keyType = REG_EXPAND_SZ;
	DWORD keySize = wcslen(initKeyValue)*sizeof(TCHAR);
	if(RegSetValueEx(myKey, keyName, 0, keyType, (LPBYTE)initKeyValue, keySize) != ERROR_SUCCESS) return false;

	/*�ر�ע�����*/
	if(RegCloseKey(myKey) != ERROR_SUCCESS) return false;

	/*��ȡwindows�汾��Ϣ*/
	OSVERSIONINFO osvi;
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&osvi);

	/*��win7ϵͳע�������޸�*/
	if(osvi.dwMajorVersion == 6&&osvi.dwMinorVersion == 1)
	{
		/*��ע�����*/
		HKEY myKey;
		LPCTSTR keyPath = _T("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders");
		if(RegOpenKeyEx(HKEY_CURRENT_USER, keyPath, 0, KEY_ALL_ACCESS, &myKey) != ERROR_SUCCESS) return false;

		/*д��ע�����*/
		LPCTSTR keyName = _T("Cookies");
		DWORD keyType = REG_EXPAND_SZ;
		DWORD keySize = wcslen(secInitKeyValue)*sizeof(TCHAR);
		if(RegSetValueEx(myKey, keyName, 0, keyType, (LPBYTE)initKeyValue, keySize) != ERROR_SUCCESS) return false;

		/*�ر�ע�����*/
		if(RegCloseKey(myKey) != ERROR_SUCCESS) return false;
	}

	/*���ĵ�¼״̬*/
	tag = false;

	return true;
}