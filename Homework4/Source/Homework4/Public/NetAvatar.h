// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NetBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "NetAvatar.generated.h"

/**
 * 
 */
UCLASS()
class HOMEWORK4_API ANetAvatar : public ANetBaseCharacter
{
	GENERATED_BODY()

public:

	ANetAvatar();

	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;
	
	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm;

	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_bIsRunning();

	UFUNCTION()
	void UpdateMovementSpeed();

	UFUNCTION(Server, Reliable)
	void ServerSetIsRunning(bool _isRunning);

	UPROPERTY(EditAnywhere, BLueprintReadWrite)
	float RunSpeed;

	UPROPERTY(ReplicatedUsing = OnRep_bIsRunning)
	bool bIsRunning;

private:
	void MoveForward(float Scale);
	void MoveRight(float Scale);
	void RunStart();
	void RunStop();

};
