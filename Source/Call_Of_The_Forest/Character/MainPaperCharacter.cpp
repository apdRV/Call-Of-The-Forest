// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPaperCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

AMainPaperCharacter::AMainPaperCharacter(){
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->SetRelativeRotation(FRotator(0.f, -30.0f, -90.0f));
    SpringArmComponent->TargetArmLength = 100.f; // расстояние от камеры до игрока
    SpringArmComponent->bInheritPitch = false;
    SpringArmComponent->bInheritYaw = false;
    SpringArmComponent->bInheritRoll = false;
    SpringArmComponent->bEnableCameraLag = true;
    SpringArmComponent->bEnableCameraRotationLag = true;
	SpringArmComponent->CameraLagSpeed = 4.f;
	SpringArmComponent->CameraRotationLagSpeed = 4.f;
	SpringArmComponent->CameraLagMaxDistance = 600.f;


    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    CameraComponent->SetupAttachment(SpringArmComponent);
    
	// OnCharacterMovementUpdated.AddDynamic(this, &AMainPaperCharacter::Animate);

	bIsMoving = false;
}

// Called every frame
void AMainPaperCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMainPaperCharacter::BeginPlay()
{
    Super::BeginPlay();
}

// void AMainPaperCharacter::SetCurrentAnimationDirection(FVector const& Velocity)
// {
// 	const float x = Velocity.GetSafeNormal().X;
// 	const float y = Velocity.GetSafeNormal().Y;

// 	bIsMoving = x != 0.0f || y != 0.0f;

// 	if(bIsMoving)
// 	{
// 		if(y > 0.0f && (abs(x) < 0.5f || x == 0.0))
// 		{
// 			//Доделать

// 		}

// 	}

// }

// void AMainPaperCharacter::Animate(float DeltaTime, FVector OldLocation, FVector const OldVelocity){

// }

// void AMainPaperCharacter::AddMovementInput(FVector WorldDirection, float Scalevalue, bool bForce)
// {
// 	auto MovementComponent = GetMovementComponent();

// 	if(MovementComponent)
// 	{
// 		MovementComponent->AddInputVector(WorldDirection * ScaleValue, bForce);
// 	}
// 	else
// 	{
// 		Internal_AddMovementInput(WorldDirection * ScaleValue, bForce);

// 	}


// }