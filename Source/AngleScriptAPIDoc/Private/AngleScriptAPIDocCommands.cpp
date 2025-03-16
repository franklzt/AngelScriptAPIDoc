// Copyright Epic Games, Inc. All Rights Reserved.

#include "AngleScriptAPIDocCommands.h"

#define LOCTEXT_NAMESPACE "FAngleScriptAPIDocModule"

void FAngleScriptAPIDocCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "AngleScriptAPIDoc", "Generate AngleScript API Doc Source File", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
