// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UnrealStudy2HUD.generated.h"

UCLASS()
class AUnrealStudy2HUD : public AHUD
{
	GENERATED_BODY()

public:
	AUnrealStudy2HUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;
	virtual void BeginPlay() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

public:

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> HUDWidgetClass;
	UPROPERTY(EditAnywhere)
	class UUserWidget* CurrentWidget;

};

