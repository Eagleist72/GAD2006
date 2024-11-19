// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "COABaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "COAAvatar.generated.h"

/**
 * 
 */
UCLASS()
class LABWORK_1_API ACOAAvatar : public ACOABaseCharacter
{
	GENERATED_BODY()

public:
	ACOAAvatar();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "COA")
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "COA")
	UCameraComponent* CameraComponent;

	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "COA")
	float RunSpeed;

private:
	void RunPressed();
	void RunReleased();
	void MoveForward(float Amount);
	void MoveRight(float Amount);
};
