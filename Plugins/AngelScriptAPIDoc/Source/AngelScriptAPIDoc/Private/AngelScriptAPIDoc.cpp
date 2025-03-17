// Copyright Epic Games, Inc. All Rights Reserved.

#include "AngelScriptAPIDoc.h"
#include "AngelScriptAPIDocStyle.h"
#include "AngelScriptAPIDocCommands.h"
#include "AngelscriptDocs.h"
#include "ToolMenus.h"

#include "AngelscriptManager.h"
#include "EditorDialogLibrary.h"
#include "Async/Async.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"
//#include "Containers/Ticker.h"
#include "Editor.h"
#include "Editor/EditorEngine.h"

#include "Engine/TimerHandle.h"

static const FName AngelScriptAPIDocTabName("AngelScriptAPIDoc");

#define LOCTEXT_NAMESPACE "FAngelScriptAPIDocModule"
bool bCanGenerateDoc = true;
#if WITH_EDITOR
TSharedPtr<SNotificationItem> GenerateDocShowNotification(bool Success, const FText& Title, const FText* SubText,
                                                          bool bInFireAndForget = true,
                                                          bool bUseInSuccessFailIcons = true)
{
	FNotificationInfo Info(Title);
	Info.ExpireDuration = 1.0f;
	Info.bUseSuccessFailIcons = true;
	Info.bFireAndForget = bInFireAndForget;
	Info.bUseThrobber = true;
	Info.bUseThrobber = true;
	if (SubText)
	{
		Info.SubText = *SubText;
	}
	if (TSharedPtr<SNotificationItem> CompileNotification = FSlateNotificationManager::Get().AddNotification(Info))
	{
		CompileNotification->SetCompletionState(
			SNotificationItem::CS_Pending /*Success ? SNotificationItem::CS_Success : SNotificationItem::CS_Fail*/);
		return CompileNotification;
	}
	return TSharedPtr<SNotificationItem>();
}
#endif


void FAngelScriptAPIDocModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	bCanGenerateDoc = true;
	FAngelScriptAPIDocStyle::Initialize();
	FAngelScriptAPIDocStyle::ReloadTextures();

	FAngelScriptAPIDocCommands::Register();

	PluginCommands = MakeShareable(new FUICommandList);

	auto canExecute = FCanExecuteAction::CreateLambda([] () { return bCanGenerateDoc; });
	PluginCommands->MapAction(
		FAngelScriptAPIDocCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FAngelScriptAPIDocModule::PluginButtonClicked),
		canExecute);

	UToolMenus::RegisterStartupCallback(
		FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FAngelScriptAPIDocModule::RegisterMenus));
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
	bCanGenerateDoc = false;
#if WITH_EDITOR
	auto FinishLamda = []
	{
		if (GEditor)
		{
			if (GEditor->IsRealTimeAudioMuted())
			{
				FTimerHandle DelegateHandle;
				FTimerDelegate Delegate;
				Delegate.BindLambda([DelegateHandle]()
				{
					FString GeneratedCodePath = TEXT("The Generated Code is Under ") + FPaths::ProjectDir() + TEXT(
						"Docs directory");
					UEditorDialogLibrary::ShowMessage(FText::FromString(TEXT("AngelScript API Doc")),
					                                  FText::FromString(GeneratedCodePath), EAppMsgType::Ok,
					                                  EAppReturnType::Ok, EAppMsgCategory::Success);
					bCanGenerateDoc = true;
				});
				GEditor->GetTimerManager().Get().SetTimer(DelegateHandle, Delegate, 2.0, false);
			}
		}
	};

	static const FText StartText = LOCTEXT("Start", "Generating AngelScript API Doc");
	static const FText ReinstancingText = LOCTEXT("Generating", "AngelScript API Doc");
	TSharedPtr<SNotificationItem> StartNotifyInfo = GenerateDocShowNotification(
		true, StartText, &ReinstancingText, false, false);

	auto tempFunction = [ StartNotifyInfo,FinishLamda]
	{
		FAngelscriptDocs::DumpDocumentation(FAngelscriptManager::Get().GetScriptEngine());
		auto tempFinished = [StartNotifyInfo,FinishLamda]
		{
			StartNotifyInfo.Get()->SetCompletionState(SNotificationItem::CS_Success);
			StartNotifyInfo.Get()->ExpireAndFadeout();
			AsyncTask(ENamedThreads::GameThread, FinishLamda);
		};
		AsyncTask(ENamedThreads::GameThread, tempFinished);
	};
	Async(EAsyncExecution::ThreadPool, tempFunction);
#endif
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
				FToolMenuEntry& Entry = Section.AddEntry(
					FToolMenuEntry::InitToolBarButton(FAngelScriptAPIDocCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}


#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FAngelScriptAPIDocModule, AngelScriptAPIDoc)
