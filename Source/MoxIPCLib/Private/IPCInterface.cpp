// Fill out your copyright notice in the Description page of Project Settings.


#include "IPCInterface.h"

#define LOCTEXT_NAMESPACE "FMoxIPCLibModule"

typedef int(*_initServerPipe)(const char* pipeName, HANDLE& pipeHandle, bool blocking);
typedef int(*_createOverlappedStruct)(LPOVERLAPPED overlapped);
typedef int(*_acceptConnection)(HANDLE& pipeHandle, LPOVERLAPPED overlapped);
typedef int(*_peekPipe)(HANDLE& pipeHandle, char* buffer, const int bufferSize, DWORD& bytesRead);
typedef int(*_readPipe)(HANDLE& pipeHandle, char* buffer, const int bufferSize, DWORD& bytesRead, LPOVERLAPPED overlapped);
typedef int(*_disconnectPipe)(HANDLE& pipeHandle);
typedef void(*_closeServerPipe)(HANDLE& pipeHandle);
typedef int(*_checkOperationFinished)(HANDLE& pipeHandle, LPOVERLAPPED overlapped, int waitTimeInMS);

typedef int(*_initClientPipe)(const char* pipeName, HANDLE& pipeHandle);
typedef int(*_writePipe)(HANDLE& pipeHandle, const char* buffer, const int bufferSize, DWORD& bytesWritten);
typedef void(*_closeClientPipe)(HANDLE& pipeHandle);
typedef int(*_pipeExistsByName)(const char* pipeName);


_initServerPipe m_initServerPipe = nullptr;
_createOverlappedStruct m_createOverlappedStruct = nullptr;
_acceptConnection m_acceptConnection = nullptr;
_peekPipe m_peekPipe = nullptr;
_readPipe m_readPipe = nullptr;
_disconnectPipe m_disconnectPipe = nullptr;
_closeServerPipe m_closeServerPipe = nullptr;
_checkOperationFinished m_checkOperationFinished = nullptr;

_initClientPipe m_initClientPipe = nullptr;
_writePipe m_writePipe = nullptr;
_closeClientPipe m_closeClientPipe = nullptr;

_pipeExistsByName m_pipeExistsByName = nullptr;

void IPCInterface::SetupInterface(void* libHandle)
{
	if (libHandle)
	{
		m_initServerPipe = (_initServerPipe)FPlatformProcess::GetDllExport(libHandle, L"InitServerPipe");
		m_createOverlappedStruct = (_createOverlappedStruct)FPlatformProcess::GetDllExport(libHandle, L"CreateOverlappedStruct");
		m_acceptConnection = (_acceptConnection)FPlatformProcess::GetDllExport(libHandle, L"AcceptConnection");
		m_peekPipe = (_peekPipe)FPlatformProcess::GetDllExport(libHandle, L"PeekPipe");
		m_readPipe = (_readPipe)FPlatformProcess::GetDllExport(libHandle, L"ReadPipe");
		m_disconnectPipe = (_disconnectPipe)FPlatformProcess::GetDllExport(libHandle, L"DisconnectPipe");
		m_closeServerPipe = (_closeServerPipe)FPlatformProcess::GetDllExport(libHandle, L"CloseServerPipe");
		m_checkOperationFinished = (_checkOperationFinished)FPlatformProcess::GetDllExport(libHandle, L"CheckOperationFinished");

		m_initClientPipe = (_initClientPipe)FPlatformProcess::GetDllExport(libHandle, L"InitClientPipe");
		m_writePipe = (_writePipe)FPlatformProcess::GetDllExport(libHandle, L"WritePipe");
		m_closeClientPipe = (_closeClientPipe)FPlatformProcess::GetDllExport(libHandle, L"CloseClientPipe");

		m_pipeExistsByName = (_pipeExistsByName)FPlatformProcess::GetDllExport(libHandle, L"PipeExistsByName");
	}
	else
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("ThirdPartyLibraryError", "Failed to load example third party library"));
	}
}

int IPCInterface::InitServerPipe(const char* pipeName, HANDLE& pipeHandle, bool blocking)
{
	if (m_initServerPipe != nullptr)
	{
		return m_initServerPipe(pipeName, pipeHandle, blocking);
	}

	return -1;
}

int IPCInterface::CreateOverlappedStruct(LPOVERLAPPED overlapped)
{
	if (m_createOverlappedStruct != nullptr)
	{
		return m_createOverlappedStruct(overlapped);
	}

	return -1;
}

int IPCInterface::AcceptConnection(HANDLE& pipeHandle, LPOVERLAPPED overlapped)
{
	if (m_acceptConnection != nullptr)
	{
		return m_acceptConnection(pipeHandle, overlapped);
	}

	return -1;
}

int IPCInterface::PeekPipe(HANDLE& pipeHandle, char* buffer, const int bufferSize, DWORD& bytesRead)
{
	if (m_peekPipe != nullptr)
	{
		return m_peekPipe(pipeHandle, buffer, bufferSize, bytesRead);
	}

	return -1;
}

int IPCInterface::ReadPipe(HANDLE& pipeHandle, char* buffer, const int bufferSize, DWORD& bytesRead, LPOVERLAPPED overlapped)
{
	if (m_readPipe != nullptr)
	{
		return m_readPipe(pipeHandle, buffer, bufferSize, bytesRead, overlapped);
	}

	return -1;
}

int IPCInterface::DisconnectPipe(HANDLE& pipeHandle)
{
	if (m_disconnectPipe != nullptr)
	{
		return m_disconnectPipe(pipeHandle);
	}

	return -1;
}

void IPCInterface::CloseServerPipe(HANDLE& pipeHandle)
{
	if (m_closeServerPipe != nullptr)
	{
		m_closeServerPipe(pipeHandle);
	}
}

int IPCInterface::CheckOperationFinished(HANDLE& pipeHandle, LPOVERLAPPED overlapped, int waitTimeInMS)
{
	if (m_checkOperationFinished != nullptr)
	{
		return m_checkOperationFinished(pipeHandle, overlapped, waitTimeInMS);
	}

	return -1;
}

int IPCInterface::InitClientPipe(const char* pipeName, HANDLE& pipeHandle)
{
	if (m_initClientPipe != nullptr)
	{
		return m_initClientPipe(pipeName, pipeHandle);
	}

	return -1;
}

int IPCInterface::WritePipe(HANDLE& pipeHandle, const char* buffer, const int bufferSize, DWORD& bytesWritten)
{
	if (m_writePipe != nullptr)
	{
		return m_writePipe(pipeHandle, buffer, bufferSize, bytesWritten);
	}

	return -1;
}

void IPCInterface::CloseClientPipe(HANDLE& pipeHandle)
{
	if (m_closeClientPipe != nullptr)
	{
		m_closeClientPipe(pipeHandle);
	}
}

int IPCInterface::PipeExistsByName(const char* pipeName)
{
	if (m_pipeExistsByName != nullptr)
	{
		return m_pipeExistsByName(pipeName);
	}

	return -1;
}
