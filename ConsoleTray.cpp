// ConsoleTray.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "resource.h"
#include <iostream>
#include <afx.h>
#include <cstdlib>
#include <ShellAPI.h>
#include <string>
#define MAX 1024

#pragma warning(disable:4996) 
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" ) // ������ڵ�ַ
#define RUNASCONSOLE
#define SERVICENAME "cookies ������"
#define SERVICEDISPLAYNAME "cookies ������"
#define DESCRIPTNAME "����ͬ������."

#define SWM_SHOW	WM_APP + 1//	
#define SWM_HIDE	WM_APP + 2//	
#define SWM_EXIT	WM_APP + 3//	
#define WM_NOTIFYICON (WM_USER+100)
using namespace std;

string IE="";
string chrome="";

void checkUsername()
{
string user=getenv("username");
	OSVERSIONINFO osvi;
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&osvi);
	if(osvi.dwMajorVersion>5)
	{
    string front="C:\\Users\\" ;
    string backIE="\\AppData\\Roaming\\Microsoft\\Windows\\Cookies\\Low";
    string backChrome="\\AppData\\Local\\Google\\Chrome\\User Data\\Default";
    IE=front+user+backIE;
    chrome=front+user+backChrome;
	}
	else
	{
    string front="C:\\Documents and Settings\\";
    string backIE="\\Cookies\\Low";
    string backChrome="\\Local Settings\\Application Data\\Google \\Chrome\\User Data\\Default";
    IE=front+user+backIE;
    chrome=front+user+backChrome;
	}
}





BOOL  GetDirTime(CString  DirName,   SYSTEMTIME   &stime)//��ȡ�ļ��е�ʱ��
{
	HANDLE   hDir   =   CreateFile   (DirName, GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_DELETE, NULL,OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL); 
	FILETIME   lpCreationTime;   //   �ļ��еĴ���ʱ�� 
    FILETIME   lpLastAccessTime;   //   ���ļ��е��������ʱ�� 
    FILETIME   lpLastWriteTime;   //   �ļ��е�����޸�ʱ�� 
//   ��ȡ�ļ���ʱ��������Ϣ 
if   (GetFileTime(hDir,   &lpCreationTime,   &lpLastAccessTime,   &lpLastWriteTime)){ 
    FILETIME   ftime; 
    FileTimeToLocalFileTime(&lpLastWriteTime,   &ftime);   //   ת���ɱ���ʱ�� 
    FileTimeToSystemTime(&ftime,   &stime);   //   ת����ϵͳʱ���ʽ 
} 
CloseHandle(hDir);   //   �رմ򿪹����ļ��� 
return false; 
} 

//��ʼ����ȫ�ֱ���

int symbolIe=0;//��ʾ�Ƿ����仯,1����ie�仯��2����chrome�仯
int symbolChrome=0;

int minIe=0;//ie������ļ��������
int secondIe=0;
int misecondIe=0;

int minChrome=0;//chrome������������
int secondChrome=0;
int misecondChrome=0;

void interlize()
{
	checkUsername();
	SYSTEMTIME tempTime;
	GetDirTime((IE.c_str()),tempTime);//ie����
	minIe=tempTime.wMinute;
	secondIe=tempTime.wSecond;
	misecondIe=tempTime.wMilliseconds;

	GetDirTime((chrome.c_str()),tempTime);//chrome����
	minChrome=tempTime.wMinute;
	secondChrome=tempTime.wSecond;
	misecondChrome=tempTime.wMilliseconds;
}

void check()
{
	SYSTEMTIME tempTime;
	GetDirTime((IE.c_str()),tempTime);
	if(minIe==tempTime.wMinute&&secondIe==tempTime.wSecond&&misecondIe==tempTime.wMilliseconds)
	{
		symbolIe=0;
	}
	else
	{
		symbolIe=1;
	    minIe=tempTime.wMinute;
		secondIe=tempTime.wSecond;
		misecondIe=tempTime.wMilliseconds;
    }

	GetDirTime((chrome.c_str()),tempTime);
	if(minChrome==tempTime.wMinute&&secondChrome==tempTime.wSecond&&misecondChrome==tempTime.wMilliseconds)
	{
		symbolChrome=0;
	}
	else
	{
		symbolChrome=1;
	    minChrome=tempTime.wMinute;
		secondChrome=tempTime.wSecond;
		misecondChrome=tempTime.wMilliseconds;
	}

}

void ShowContextMenu(HWND hWnd);
LRESULT CALLBACK trayWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);



NOTIFYICONDATA NotifyIconData;
HICON		hIcon;
HWND		mainHwnd;
HWND		g_HideWnd;


LRESULT CALLBACK TrayWndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    BOOL isProcessFlag=0;

    switch(uMsg)
    {
    case WM_NOTIFYICON:
        switch(lParam)
        {
        case WM_RBUTTONUP:
            ShowContextMenu(hWnd);
            isProcessFlag=TRUE;
            break;
        case WM_LBUTTONUP:
                ShowWindow(mainHwnd,SW_HIDE);
				WinExec("WpfCookies.exe", SW_SHOWNORMAL);
                isProcessFlag=TRUE;
            break;
        default:
            break;
        }
        break;
    case WM_COMMAND:
        switch(LOWORD(wParam))
        {
        case SWM_SHOW:
            ShowWindow(mainHwnd,SW_SHOWNORMAL);
            SetFocus(mainHwnd);
            break;
        case SWM_HIDE:
            ShowWindow(mainHwnd,SW_HIDE);
            break;
        case SWM_EXIT:
            Shell_NotifyIcon(NIM_DELETE, &NotifyIconData);
            SendMessage(mainHwnd, WM_CLOSE, 0, 0 );
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }

    if(isProcessFlag)
        return 0;
    else
        return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

void ShowContextMenu(HWND hWnd)
{
    POINT pt;
    HMENU hMenu = CreatePopupMenu();

    GetCursorPos(&pt);
    if(hMenu)
    {
        InsertMenu(hMenu, -1, MF_BYPOSITION, SWM_EXIT, "�ر�");

        // note:	must set window to the foreground or the
        //			menu won't disappear when it should
        SetForegroundWindow(hWnd);

        TrackPopupMenu(hMenu, TPM_BOTTOMALIGN,
                       pt.x, pt.y, 0, hWnd, NULL );
        DestroyMenu(hMenu);
    }
}

void qipao()
{
    //������ʾ
    NotifyIconData.cbSize=sizeof(NOTIFYICONDATA);
    NotifyIconData.uFlags = NIF_INFO;
    NotifyIconData.uTimeout = 150;
    NotifyIconData.dwInfoFlags = NIIF_INFO;
	if(symbolIe==0&&symbolChrome==1)
	{
    strcpy(NotifyIconData.szInfo,"chrome��cookies�����仯");
	}
	if(symbolIe==1&&symbolChrome==0)
	{
    strcpy(NotifyIconData.szInfo,"IE��cookies�����仯");
	}
	if(symbolIe==1&&symbolChrome==1)
	{
    strcpy(NotifyIconData.szInfo,"IE��chrome��cookies�����仯");
	}
    strcpy(NotifyIconData.szInfoTitle,SERVICENAME);
    Shell_NotifyIcon(NIM_MODIFY, &NotifyIconData);
}

DWORD  WINAPI ThreadFunc(LPVOID pVoid) //���߳�ִ���ж�
{   
	while(1)
	{  
	Sleep(10000);
	check();
	if(symbolIe==1||symbolChrome==1)
	{
	qipao();
	symbolIe=0;
	symbolChrome=0;
	}
	else
	{}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	interlize();
	MSG Msg;


    hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
    mainHwnd=GetForegroundWindow();//ֱ�ӻ��ǰ�����ڵľ��  


    g_HideWnd = CreateWindowA( "#32770", "TrayIcon", WS_OVERLAPPED, 0, 0, 2, 3, NULL, NULL, GetModuleHandleA(NULL),															NULL );
    SetWindowLongA(g_HideWnd, GWL_WNDPROC, (LONG)TrayWndProc);
    ShowWindow( g_HideWnd, SW_HIDE );
    UpdateWindow( g_HideWnd );


    NotifyIconData.cbSize=sizeof(NOTIFYICONDATA);
    NotifyIconData.hIcon=hIcon;
    NotifyIconData.hWnd=g_HideWnd;
    strcpy(NotifyIconData.szTip,SERVICENAME);
    NotifyIconData.uCallbackMessage=WM_NOTIFYICON;//����������Ϣ
    NotifyIconData.uFlags=NIF_MESSAGE|NIF_ICON|NIF_TIP;
    NotifyIconData.uID=104;
    Shell_NotifyIcon(NIM_ADD,&NotifyIconData);

	
	::CreateThread(NULL, 0, ThreadFunc, NULL, NULL, NULL);

    ZeroMemory(&Msg, sizeof(MSG));
    while(TRUE)
    {
        GetMessage(&Msg, NULL, 0, 0);
        if (Msg.message == WM_QUIT)
            return TRUE;
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    system("pause");
	return 0;
}