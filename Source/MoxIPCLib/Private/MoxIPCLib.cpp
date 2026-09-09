// Copyright Epic Games, Inc. All Rights Reserved.

#include "MoxIPCLib.h"
#include "Misc/MessageDialog.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/Paths.h"
#include "HAL/PlatformProcess.h"
#include "MoxIPCLibLibrary/ipcLib.h"

#include "IPCInterface.h"

#define LOCTEXT_NAMESPACE "FMoxIPCLibModule"

void FMoxIPCLibModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	// Get the base directory of this plugin
	FString BaseDir = IPluginManager::Get().FindPlugin("MoxIPCLib")->GetBaseDir();

	// Add on the relative location of the third party dll and load it
	FString LibraryPath;
// #if PLATFORM_WINDOWS
	LibraryPath = FPaths::Combine(*BaseDir, TEXT("Binaries/ThirdParty/MoxIPCLibLibrary/Win64/IPCLib.dll"));
// #endif
 // PLATFORM_WINDOWS

	IPCLibraryHandle = !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;
	
	IPCInterface::SetupInterface(IPCLibraryHandle);
}

void FMoxIPCLibModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	// Free the dll handle
	FPlatformProcess::FreeDllHandle(IPCLibraryHandle);
	IPCLibraryHandle = nullptr;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMoxIPCLibModule, MoxIPCLib)
