// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Blaster/BlasterTypes/TurningInPlace.h"
#include "Blaster/Interfaces/InteractWithCrosshairInterface.h"
#include "BlasterCharacter.generated.h"

UCLASS()
class BLASTER_API ABlasterCharacter : public ACharacter, public IInteractWithCrosshairInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABlasterCharacter();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PostInitializeComponents() override;

	void PlayFireMontage(bool bAiming);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Character Motion
	void MoveForward(float Value);
	void MoveSide(float Value);
	void LookUp(float Value);
	void Turn(float Value);
	virtual void Jump() override;

	// Actions
	void EquipButtonPressed();
	void CrouchButtonPressed();
	void AimButtonPressed();
	void AimButtonReleased();

	// Aim Offsets
	void AimOffset(float DeltaTime);

	// Fire Actions
	void FireButtonPressed();
	void FireButtonReleased();

private:
	UPROPERTY(VisibleAnywhere, Category="Camera")
	class USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, Category="Camera")
	class UCameraComponent* FollowCamera;
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess="true"))
	//class UWidgetComponent* OverheadWidget;

	UPROPERTY(ReplicatedUsing = OnRep_OverlappingWeapon)
	class AWeapon* OverlappingWeapon;
	UPROPERTY(VisibleAnywhere)
	class UCombatComponent* Combat;

	FRotator StartingAimRotation;
	float AO_Yaw;
	float AO_Pitch;
	float InterpAOYaw;

	UFUNCTION()
	void OnRep_OverlappingWeapon(AWeapon* LastWeapon);

	UFUNCTION(Server, Reliable)
	void ServerEquipButtonPressed();

	ETurningInPlace TurningInPlace;
	void TurnInPlace(float DeltaTime);

	UPROPERTY(EditAnywhere, Category = "Combat")
	class UAnimMontage* FireWeaponMontage;

	UPROPERTY(EditAnywhere)
	float CameraThreshold = 200.f;
	void HideCameraIfCharacterClose();

public:
	void SetOverlappingWeapon(AWeapon* Weapon);
	bool IsWeaponEquipped();
	bool IsAiming();
	FORCEINLINE float GetAO_Yaw() const { return AO_Yaw; }
	FORCEINLINE float GetAO_Pitch() const { return AO_Pitch; }
	AWeapon* GetEquippedWeapon();
	FORCEINLINE ETurningInPlace GetTurningInPlace() const { return TurningInPlace; }
	FVector GetHitTarget() const;
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
