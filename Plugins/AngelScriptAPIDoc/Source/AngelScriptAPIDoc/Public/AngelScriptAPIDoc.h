// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"
#include "UObject/ObjectMacros.h"

class FToolBarBuilder;
class FMenuBuilder;

class FAngelScriptAPIDocModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command. */
	void PluginButtonClicked();
	
private:

	void RegisterMenus();

	

private:
	TSharedPtr<class FUICommandList> PluginCommands;
};
