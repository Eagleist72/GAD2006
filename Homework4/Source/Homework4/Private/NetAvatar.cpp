// Fill out your copyright notice in the Description page of Project Settings.


#include "NetAvatar.h"
#include "NetBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"



ANetAvatar::ANetAvatar() : 
RunSpeed(800.0f)
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

void ANetAvatar::BeginPlay()
{
	Super::BeginPlay();

	Camera->bUsePawnControlRotation = false;
	SpringArm->bUsePawnControlRotation = true;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void ANetAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("turn", this, &ACharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("lookup", this, &ACharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("MoveForward", this, &ANetAvatar::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ANetAvatar::MoveRight);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ANetAvatar::RunStart);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ANetAvatar::RunStop);
}

void ANetAvatar::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ANetAvatar, bIsRunning);
}

void ANetAvatar::OnRep_bIsRunning()
{
	UpdateMovementSpeed();
}

void ANetAvatar::UpdateMovementSpeed()
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = bIsRunning ? RunSpeed : 600.0f;
	}
}

void ANetAvatar::ServerSetIsRunning_Implementation(bool _isRunning)
{
	bIsRunning = _isRunning;
}

void ANetAvatar::MoveForward(float Scale)
{
	FRotator Rotation = GetController()->GetControlRotation();
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
	FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, Scale);
}

void ANetAvatar::MoveRight(float Scale)
{
	FRotator Rotation = GetController()->GetControlRotation();
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
	FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(ForwardDirection, Scale);
}

void ANetAvatar::RunStart()
{
	if (HasAuthority())
	{
		bIsRunning = true;
		UpdateMovementSpeed();
	}
	else
	{
		ServerSetIsRunning(true);
		UpdateMovementSpeed();
	}

}

void ANetAvatar::RunStop()
{
	if (HasAuthority())
	{
		bIsRunning = false;
		UpdateMovementSpeed();
	}
	else
	{
		ServerSetIsRunning(false);
		UpdateMovementSpeed();
	}
}
