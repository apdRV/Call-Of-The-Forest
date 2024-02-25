// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceBase.h"
#include "PaperFlipbookComponent.h"
#include "PaperSpriteComponent.h"

// Sets default values
AResourceBase::AResourceBase()
{
 	SetActorRotation(FRotator(0.0f, 90.0f, -90.0f));
	SetActorRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));

	TriggerCapsule = CreateDefaultSubobject<class UCapsuleComponent>("Trigger capsule");
	TriggerCapsule->InitCapsuleSize(20.0f, 20.0f);
	TriggerCapsule->SetCollisionProfileName(TEXT("Trigger"));
	TriggerCapsule->SetupAttachment(RootComponent);
	TriggerCapsule->SetIsReplicated(true);

	Tooltip = CreateDefaultSubobject<class UTextRenderComponent>("Tooltip");
	Tooltip->SetupAttachment(RootComponent);
	Tooltip->SetAbsolute(false, true, true);
	Tooltip->SetRelativeLocation(FVector(0.0f, 200.0f, 10.0f));
	Tooltip->SetRelativeRotation(FRotator(90.0f, 180.0f, 0.0f));
	Tooltip->SetWorldScale3D(FVector(1.0f, 0.15f, 0.15f));
	Tooltip->SetHorizontalAlignment(EHTA_Center);
	Tooltip->SetVerticalAlignment(EVRTA_TextBottom);
	Tooltip->SetText(FText::FromString("Press E to take"));
	Tooltip->SetTextRenderColor(FColor(255, 122, 0, 255));
	Tooltip->SetHiddenInGame(true);
	Tooltip->SetIsReplicated(true);

	GetRenderComponent()->SetMobility(EComponentMobility::Movable);
	GetRenderComponent()->SetSimulatePhysics(true);
	GetRenderComponent()->SetEnableGravity(true);
	GetRenderComponent()->SetConstraintMode(EDOFMode::Type::Default);
	GetRenderComponent()->GetBodyInstance()->bLockXRotation = true;
	GetRenderComponent()->GetBodyInstance()->bLockYRotation = true;
	GetRenderComponent()->GetBodyInstance()->MassScale = 500.0f;
	GetRenderComponent()->CanCharacterStepUpOn = ECB_No;
	GetRenderComponent()->SetIsReplicated(true);

}

// Called when the game starts or when spawned
void AResourceBase::BeginPlay()
{
	Super::BeginPlay();
	
}


