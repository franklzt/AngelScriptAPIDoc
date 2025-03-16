// Copyright Epic Games, Inc. All Rights Reserved.

#include "AngleScriptAPIDoc.h"
#include "AngleScriptAPIDocStyle.h"
#include "AngleScriptAPIDocCommands.h"
#include "ToolMenus.h"
#include "AngelscriptDocs.h"
#include "AngelscriptManager.h"

static const FName AngleScriptAPIDocTabName("AngleScriptAPIDoc");

#define LOCTEXT_NAMESPACE "FAngleScriptAPIDocModule"

void FAngleScriptAPIDocModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FAngleScriptAPIDocStyle::Initialize();
	FAngleScriptAPIDocStyle::ReloadTextures();

	FAngleScriptAPIDocCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FAngleScriptAPIDocCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FAngleScriptAPIDocModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FAngleScriptAPIDocModule::RegisterMenus));
}

void FAngleScriptAPIDocModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FAngleScriptAPIDocStyle::Shutdown();

	FAngleScriptAPIDocCommands::Unregister();
}

void FAngleScriptAPIDocModule::PluginButtonClicked()
{
	FAngelscriptDocs::DumpDocumentation(FAngelscriptManager::Get().GetScriptEngine());;
}

void FAngleScriptAPIDocModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FAngleScriptAPIDocCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FAngleScriptAPIDocCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAngleScriptAPIDocModule, AngleScriptAPIDoc)