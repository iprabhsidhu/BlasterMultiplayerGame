// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Blaster/BlasterTypes/TurningInPlace.h"
#include "Blaster/Interfaces/InteractWithCrosshairInterface.h"
#include "Components/TimelineComponent.h"
#include "Blaster/BlasterTypes/CombatState.h"
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
	virtual void Destroyed() override;

	virtual void OnRep_ReplicatedMovement() override;

	void PlayFireMontage(bool bAiming);
	void PlayHitReactMontage();
	void PlayReloadMontage();
	void PlayElimMontage();
	
	void Elim();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastElim();

	UPROPERTY(Replicated)
	bool bDisabledGameplay = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Character Motion
	void MoveForward(float Value);
	void MoveSide(float Value);
	void LookUp(float Value);
	void Turn(float Value);
	virtual void Jump() override;
	void SimProxiesTurn();

	// Actions
	void EquipButtonPressed();
	void CrouchButtonPressed();
	void AimButtonPressed();
	void AimButtonReleased();
	void ReloadButtonPressed();

	// Aim Offsets
	void AimOffset(float DeltaTime);

	void CalculateAO_Pitch();

	// Fire Actions
	void FireButtonPressed();
	void FireButtonReleased();

	/*
	*	Health Dmaage
	*/
	bool bElim = false;

	UFUNCTION()
	void RecieveDamage(AActor* DamageActor, float Damage, const UDamageType* DamageType, class AController* InstigatorController, AActor* DamageCauser);
	void UpdateHUDHealth();

	// Poll for any releveant classes & Initialize the HUD
	void PollInit();

	void RotateInPlace(float DeltaTime);
	
private:
	UPROPERTY(VisibleAnywhere, Category="Camera")
	class USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, Category="Camera")
	class UCameraComponent* FollowCamera;
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess="true"))
	//class UWidgetComponent* OverheadWidget;

	UPROPERTY(ReplicatedUsing = OnRep_OverlappingWeapon)
	class AWeapon* OverlappingWeapon;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat Component", meta = (AllowPrivateAccess = "true"))
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
	UPROPERTY(EditAnywhere, Category = "Combat")
	UAnimMontage* HitReactMontage;
	UPROPERTY(EditAnywhere, Category = "Combat")
	class UAnimMontage* ReloadWeaponMontage;
	UPROPERTY(EditAnywhere, Category = "Combat")
	UAnimMontage* ElimMontage;

	UPROPERTY(EditAnywhere)
	float CameraThreshold = 200.f;
	void HideCameraIfCharacterClose();

	bool bRotateRootBone;
	float TurnThreshold = 0.5f;
	FRotator ProxyRotationLastFrame;
	FRotator ProxyRotation;
	float ProxyYaw;

	float TimeSinceLastMovementReplication;

	float CalculateSpeed();

	/*
	*	Player Health
	*/
	UPROPERTY(EditAnywhere, Category = "Player Stats | Health")
	float MaxHealth = 100.f;
	UPROPERTY(ReplicatedUsing = OnRep_Health, VisibleAnywhere, Category = "Player Stats | Health")
	float Health = 100.f;

	FTimerHandle ElimTimer;

	UPROPERTY(EditDefaultsOnly, Category = "Player Stats | Health")
	float ElimDelay = 3.f;

	void ElimTimerFinish();

	UFUNCTION()
	void OnRep_Health();

	class ABlasterPlayerController* BlasterPlayerController;

	UPROPERTY(EditAnywhere, Category = "Player Stats | Elimination")
	UParticleSystem* ElimBotEffect;

	UPROPERTY(EditAnywhere, Category = "Player Stats | Elimination")
	UParticleSystemComponent*ElimBotComponent;

	UPROPERTY(EditAnywhere, Category = "Player Stats | Elimination")
	class USoundCue* ElimBotSound;

	/*
	*	Dynamic Eliminated Material
	*/

	UPROPERTY(VisibleAnywhere)
	UTimelineComponent* DissolvedTimeline;

	FOnTimelineFloat DissolvedTrack;

	UPROPERTY(EditAnywhere)
	UCurveFloat* DissolveCurve;

	UFUNCTION()
	void UpdateDissolvedMaterial(float DissolvedValue);

	void StartDissolved();

	UPROPERTY(VisibleAnywhere, Category = "Elim")
	UMaterialInstanceDynamic* DynamicDissolveMaterialInstance;

	UPROPERTY(EditAnywhere, Category = "Elim")
	UMaterialInstance* DissolvedMaterialInstance;

	class ABlasterPlayerState* BlasterPlayerState;
	
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
	FORCEINLINE bool ShouldRotateRootBone() const { return bRotateRootBone; }
	FORCEINLINE bool GetEIsElimated() const { return bElim; }
	FORCEINLINE float GetHealh() const { return Health; }
	FORCEINLINE float GetMaxHealh() const { return MaxHealth; }
	ECombatState GetCombatState() const;
	FORCEINLINE UCombatComponent* GetCombat() const { return Combat; }
	FORCEINLINE bool GetDisabledGameplay() const { return bDisabledGameplay; }
};
