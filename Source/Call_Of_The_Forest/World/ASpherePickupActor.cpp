// Fill out your copyright notice in the Description page of Project Settings.


#include "ASpherePickupActor.h"
#include "Components/SphereComponent.h"
#include "../Character/MainPaperCharacter.h"

// Sets default values
AASpherePickupActor::AASpherePickupActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PickupSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PickupSphere"));
    PickupSphere->SetSphereRadius(5.f);
    PickupSphere->SetCollisionProfileName(TEXT("Trigger"));
    RootComponent = PickupSphere;

    // Привязка события перекрытия
    PickupSphere->OnComponentBeginOverlap.AddDynamic(this, &AASpherePickupActor::OnOverlapBegin);

}

// Called when the game starts or when spawned
void AASpherePickupActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AASpherePickupActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AASpherePickupActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    AMainPaperCharacter* Player = Cast<AMainPaperCharacter>(OtherActor);
    if (Player && LinkedResource)
    {
		LinkedResource->OnPickup(Player);
        Destroy();
		UE_LOG(LogTemp, Warning, TEXT("SpherePicked"));
    }
}

