
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <stdio.h>
#include <tchar.h>

#include "ThreadParameter.h"
#include "com_oneapm_jni_ThreadJni.h"

using namespace std ;

DWORD WINAPI LaunchEXE(LPVOID lpParameter) ;  //创建进程
DWORD g_processID ;

/*
* Class:     com_oneapm_jni_ThreadJni
* Method:    CreateThread
* Signature: (Ljava/lang/String;Ljava/lang/String;)J
*/
JNIEXPORT jlong JNICALL Java_com_oneapm_jni_ThreadJni_CreateThread
	(JNIEnv *env, jobject object, jstring applicationName, jstring cmdLine)
{
	ThreadParameter *pParameter = new ThreadParameter(env->GetStringUTFChars(applicationName,0),env->GetStringUTFChars(cmdLine,0)) ;
	HANDLE hThread1 = CreateThread(NULL,0,LaunchEXE,(LPVOID)pParameter,0,NULL) ;

	Sleep(1) ;
	CloseHandle(hThread1) ;
	return g_processID ;
}

DWORD WINAPI LaunchEXE(LPVOID lpParameter)
{
	STARTUPINFO si = { sizeof(si) };   
	PROCESS_INFORMATION pi;   

	si.dwFlags = STARTF_USESHOWWINDOW;   
	si.wShowWindow = TRUE; //TRUE表示显示创建的进程的窗口  

	ThreadParameter* parameter = (ThreadParameter*)lpParameter ;
	if(parameter == NULL)
	{
		return -1 ;
	}

	/*deal string */
	WCHAR   applicationName[MAX_PATH]={0}; 
	WCHAR  cmdLine[MAX_PATH]={0} ;
	MultiByteToWideChar(CP_ACP,   0,  parameter->GetApplicationName(),  -1,   applicationName,   sizeof(applicationName));
	MultiByteToWideChar(CP_ACP,   0,  parameter->GetCmdLine(),  -1,   cmdLine,   sizeof(cmdLine));

	BOOL bRet = ::CreateProcess (   
		applicationName,
		cmdLine, //在Unicode版本中此参数不能为常量字符串，因为此参数会被修改    
		NULL,   
		NULL,   
		FALSE,   
		CREATE_NEW_CONSOLE,   
		NULL,   
		NULL,   
		&si,   
		&pi);   

	int error = GetLastError();  
	if(bRet)   
	{   
		::CloseHandle (pi.hThread);   
		::CloseHandle (pi.hProcess);   
	}     
	g_processID = pi.dwProcessId ;
	return pi.dwProcessId ;
}

