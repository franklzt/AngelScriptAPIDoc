// Copyright Epic Games, Inc. All Rights Reserved.

#include "AngelScriptAPIDoc.h"
#include "AngelScriptAPIDocStyle.h"
#include "AngelScriptAPIDocCommands.h"
#include "AngelscriptDocs.h"
#include "ToolMenus.h"

#include "AngelscriptManager.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"

static const FName AngelScriptAPIDocTabName("AngelScriptAPIDoc");

#define LOCTEXT_NAMESPACE "FAngelScriptAPIDocModule"


#if WITH_EDITOR
void GenerateDocShowNotification(bool Success, const FText& Title, const FText* SubText)
{
	FNotificationInfo Info(Title);
	Info.ExpireDuration = 5.0f;
	Info.bUseSuccessFailIcons = true;
	if (SubText)
	{
		Info.SubText = *SubText;
	}
	if (TSharedPtr<SNotificationItem> CompileNotification = FSlateNotificationManager::Get().AddNotification(Info))
	{
		CompileNotification->SetCompletionState(Success ? SNotificationItem::CS_Success : SNotificationItem::CS_Fail);
	}
}
#endif


void FAngelScriptAPIDocModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FAngelScriptAPIDocStyle::Initialize();
	FAngelScriptAPIDocStyle::ReloadTextures();

	FAngelScriptAPIDocCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FAngelScriptAPIDocCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FAngelScriptAPIDocModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FAngelScriptAPIDocModule::RegisterMenus));
}

void FAngelScriptAPIDocModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FAngelScriptAPIDocStyle::Shutdown();

	FAngelScriptAPIDocCommands::Unregister();
}

void FAngelScriptAPIDocModule::PluginButtonClicked()
{
	static const FText SuccessText = LOCTEXT("Success", "Generate API Doc succeeded");
	static const FText ReinstancingText = LOCTEXT("Generating", "AngelScript API Doc");
	FAngelscriptDocs::DumpDocumentation(FAngelscriptManager::Get().GetScriptEngine());
	GenerateDocShowNotification(true, SuccessText, &ReinstancingText);
}

void FAngelScriptAPIDocModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FAngelScriptAPIDocCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FAngelScriptAPIDocCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAngelScriptAPIDocModule, AngelScriptAPIDoc)