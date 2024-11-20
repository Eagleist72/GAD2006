// Fill out your copyright notice in the Description page of Project Settings.


#include "COAAvatar.h"
#include "GameFramework/CharacterMovementComponent.h"

ACOAAvatar::ACOAAvatar() :
	RunSpeed(900),
	Stamina(100.0f),
	MaxStamina(100.0f),
	StaminaDrainRate(20.0f),
	StaminaGainRate(10.0f),
	bIsStaminaDrained(false)

{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->TargetArmLength = 300.0f;
	SpringArm->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	CameraComponent->bUsePawnControlRotation = false;
	SpringArm->bUsePawnControlRotation = true;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

/*void ACOAAvatar::BeginPlay()
{
	CameraComponent->bUsePawnControlRotation = false;
	SpringArm->bUsePawnControlRotation = true;
	bUseControllerRotationYaw = false;
}*/

void ACOAAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &ACharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ACharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("MoveRight", this, &ACOAAvatar::MoveRight);
	PlayerInputComponent->BindAxis("MoveForward", this, &ACOAAvatar::MoveForward);

	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Pressed, this, &ACOAAvatar::RunPressed);
	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Released, this, &ACOAAvatar::RunReleased);
}

void ACOAAvatar::RunPressed()
{
	if (!bIsStaminaDrained)
	{
		GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	}
}

void ACOAAvatar::RunReleased()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void ACOAAvatar::MoveForward(float Amount)
{
	FRotator ControlRotation = GetController()->GetControlRotation();
	FRotator YawRotation(0.0f, ControlRotation.Yaw, 0.0f);
	FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, Amount);
}

void ACOAAvatar::MoveRight(float Amount)
{
	FRotator ControlRotation = GetController()->GetControlRotation();
	FRotator YawRotation(0.0f, ControlRotation.Yaw, 0.0f);
	FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDirection, Amount);
}
void ACOAAvatar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetCharacterMovement()->MaxWalkSpeed == RunSpeed && !bIsStaminaDrained)
	{
		DrainStamina(DeltaTime);
	}
	else
	{
		RecoverStamina(DeltaTime);
	}
}

void ACOAAvatar::DrainStamina(float DeltaTime)
{
	Stamina -= StaminaDrainRate * DeltaTime;

	if (Stamina <= 0.0f)
	{
		Stamina = 0.0f;
		bIsStaminaDrained = true;
		RunReleased();
	}
}

void ACOAAvatar::RecoverStamina(float DeltaTime)
{
	Stamina += StaminaGainRate * DeltaTime;

	if (Stamina >= MaxStamina)
	{
		Stamina = MaxStamina;
		bIsStaminaDrained = false;
	}
}
