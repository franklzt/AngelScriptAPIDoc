// Copyright Epic Games, Inc. All Rights Reserved.

#include "AngleScriptAPIDocStyle.h"
#include "AngleScriptAPIDoc.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FAngleScriptAPIDocStyle::StyleInstance = nullptr;

void FAngleScriptAPIDocStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FAngleScriptAPIDocStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FAngleScriptAPIDocStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("AngleScriptAPIDocStyle"));
	return StyleSetName;
}


const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FAngleScriptAPIDocStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("AngleScriptAPIDocStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("AngleScriptAPIDoc")->GetBaseDir() / TEXT("Resources"));

	Style->Set("AngleScriptAPIDoc.PluginAction", new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), Icon20x20));
	return Style;
}

void FAngleScriptAPIDocStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FAngleScriptAPIDocStyle::Get()
{
	return *StyleInstance;
}
