// Copyright Epic Games, Inc. All Rights Reserved.

#include "AngelScriptAPIDocCommands.h"

#define LOCTEXT_NAMESPACE "FAngelScriptAPIDocModule"

void FAngelScriptAPIDocCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "AngelScriptAPIDoc", "Generate AngelScript API Doc Source File", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
