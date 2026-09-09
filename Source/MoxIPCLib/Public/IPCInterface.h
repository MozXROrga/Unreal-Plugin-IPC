// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <Windows.h>

/**
 * 
 */
class MOXIPCLIB_API IPCInterface
{
public:
	static void SetupInterface(void* libHandle);




	// Return: 0 if successful, else result of GetLastError()
	static int InitServerPipe(const char* pipeName, HANDLE& pipeHandle, bool blocking);

	// Return: 0 if successful, else result of GetLastError()
	static int CreateOverlappedStruct(LPOVERLAPPED overlapped);

	// Blocking unless overlapped
	// Return: 0 if successful, else result of GetLastError()
	static int AcceptConnection(HANDLE& pipeHandle, LPOVERLAPPED overlapped);

	// Non-Blocking unless overlapped
	// Return: 0 if successful, else result of GetLastError()
	static int PeekPipe(HANDLE& pipeHandle, char* buffer, const int bufferSize, DWORD& bytesRead);

	// Blocking unless overlapped
	// Return: 0 if successful, else result of GetLastError()
	static int ReadPipe(HANDLE& pipeHandle, char* buffer, const int bufferSize, DWORD& bytesRead, LPOVERLAPPED overlapped);

	// Return: 0 if successful, else result of GetLastError()
	static int DisconnectPipe(HANDLE& pipeHandle);

	// Return: 0 if successful, else result of GetLastError()
	static void CloseServerPipe(HANDLE& pipeHandle);

	// Return: 0 if successful, else result of GetLastError()
	static int CheckOperationFinished(HANDLE& pipeHandle, LPOVERLAPPED overlapped, int waitTimeInMS);




	// Return: 0 if successful, else result of GetLastError()
	static int InitClientPipe(const char* pipeName, HANDLE& pipeHandle);

	// Return: 0 if successful, else result of GetLastError()
	static int WritePipe(HANDLE& pipeHandle, const char* buffer, const int bufferSize, DWORD& bytesWritten);

	// Return: 0 if successful, else result of GetLastError()
	static void CloseClientPipe(HANDLE& pipeHandle);


	// pipeName without the preceding "\\\\.\\pipe\\"
	// Return: 0 if pipe was found, -1 if it wasn't (or function handle is null), else result of GetLastError()
	static int PipeExistsByName(const char* pipeName);
};
