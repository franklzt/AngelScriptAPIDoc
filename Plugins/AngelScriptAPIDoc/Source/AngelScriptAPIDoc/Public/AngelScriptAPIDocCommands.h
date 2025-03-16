// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Framework/Commands/Commands.h"
#include "AngelScriptAPIDocStyle.h"

class FAngelScriptAPIDocCommands : public TCommands<FAngelScriptAPIDocCommands>
{
public:

	FAngelScriptAPIDocCommands()
		: TCommands<FAngelScriptAPIDocCommands>(TEXT("AngelScriptAPIDoc"), NSLOCTEXT("Contexts", "AngelScriptAPIDoc", "AngelScriptAPIDoc Plugin"), NAME_None, FAngelScriptAPIDocStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
