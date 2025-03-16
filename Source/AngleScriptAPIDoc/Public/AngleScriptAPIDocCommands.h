// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Framework/Commands/Commands.h"
#include "AngleScriptAPIDocStyle.h"

class FAngleScriptAPIDocCommands : public TCommands<FAngleScriptAPIDocCommands>
{
public:

	FAngleScriptAPIDocCommands()
		: TCommands<FAngleScriptAPIDocCommands>(TEXT("AngleScriptAPIDoc"), NSLOCTEXT("Contexts", "AngleScriptAPIDoc", "AngleScriptAPIDoc Plugin"), NAME_None, FAngleScriptAPIDocStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
