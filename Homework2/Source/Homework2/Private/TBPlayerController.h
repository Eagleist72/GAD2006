// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameSlot.h"
#include "GameManager.h"
#include "InputCoreTypes.h"
#include "TBPlayerController.generated.h"

/**
 *
 */
UCLASS()
class ATBPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	void BeginPlay() override;

	void OnActorClicked(AActor* Actor, FKey Key);

	UPROPERTY(BlueprintReadWrite)
	AGameManager* GameManager;
};

