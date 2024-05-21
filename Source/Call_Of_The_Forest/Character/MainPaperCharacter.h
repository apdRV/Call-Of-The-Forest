
#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "../World/StaticWorld.h"
#include "../Animals/Animal.h"
#include "../Animals/Predator.h"
#include "MainCharacterSpriteComponent.h"
#include "../World/AttackedDerivedDeclaration.h"
#include "Engine/EngineTypes.h"
#include "MainPaperCharacter.generated.h"
/**
 * 
 */

UCLASS()
class CALL_OF_THE_FOREST_API AMainPaperCharacter : public APaperCharacter
{
	GENERATED_BODY()

public:
	AMainPaperCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	float GetDamage();

	UFUNCTION()
	EMainCharacterState GetCharacterState();

protected:
    UPROPERTY()
	AStaticWorld* World;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State") 
	float Health;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimationCharacter | Config")
	bool bIsMoving;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	bool bIsDead;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	bool bIsAttacking;

	UPROPERTY()
	FTimerHandle AttackTimerHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	float Damage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimationCharacter | Config")
	EMainCharacterState CharacterState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimationCharacter | Config")
	EMainCharacterState LastMoveDirection;;

	UFUNCTION()
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "State")
	void Die(); // смерть персонажа

	UFUNCTION(BlueprintCallable, Category = "State")
	void PickUpItem(float Value); // поднять предмет

	UFUNCTION(BlueprintCallable, Category = "Movement")
    void MoveForwardBackward(float Value);

	UFUNCTION(BlueprintCallable, Category = "Movement")
    void MoveRightLeft(float Value);

	UFUNCTION(BlueprintCallable, Category = "Attacking")
	void Attack();

	UFUNCTION()
	void Attacked(float Value);

	UFUNCTION(BlueprintCallable, Category = "Animation")
	void UpdateCharacterSprite();

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    class USpringArmComponent* CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    class UCameraComponent* FollowCamera;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animation)
    class UMainCharacterSpriteComponent* MainCharacterSpriteComponent;

	UFUNCTION()
	void SetAttackAnimation();

	UFUNCTION()
	void EndAttackAnimation();

private:
	UPROPERTY(VisibleAnywhere)
    class USphereComponent* SphereCollider;

	UPROPERTY(VisibleAnywhere)
	float TriggerRadius;

	//Access to protected members for attacking system
	friend class AttackedActor;
	friend class AttackingActor;
};