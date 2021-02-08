// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "UnrealCPPHUD.generated.h"

/**
 * 
 */
UCLASS()
class STUDY2_API AUnrealCPPHUD : public AHUD
{
	GENERATED_BODY()
public:
    AUnrealCPPHUD();
    /** Primary draw call for the HUD */
    virtual void DrawHUD() override;

    virtual void BeginPlay() override;

private:
    /** Crosshair asset pointer */
    class UTexture2D* CrosshairTex;

    UPROPERTY(EditAnywhere, Category = "Health")
    TSubclassOf<class UUserWidget> HUDWidgetClass;

    UPROPERTY(EditAnywhere, Category = "Health")
    class UUserWidget* CurrentWidget;
};
