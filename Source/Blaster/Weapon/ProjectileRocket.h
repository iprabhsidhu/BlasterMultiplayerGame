// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "ProjectileRocket.generated.h"

/**
 * 
 */
UCLASS()
class BLASTER_API AProjectileRocket : public AProjectile
{
	GENERATED_BODY()
public:
	AProjectileRocket();

protected:
	virtual void BeginPlay() override;
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	virtual void Destroyed() override;
	void DestroyTimerFinished();

	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* TrailSystem;
	class UNiagaraComponent* TrailSystemComponent;

	UPROPERTY(EditAnywhere)
	class USoundCue* ProjectileLoop;
	UPROPERTY()
	UAudioComponent* ProjectileLoopComponent;
	UPROPERTY(EditAnywhere)
	USoundAttenuation* LoopingSoundAttenuation;

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* RocketMesh;

	UPROPERTY(EditAnywhere, Category = "Damage | Inner Radius")
	float InnerRadiusDamage = 200.f;
	UPROPERTY(EditAnywhere, Category = "Damage | Outer Radius")
	float OuterRadiusDamage = 500.f;

	FTimerHandle DestroyTimer;
	UPROPERTY(EditAnywhere)
	float DestroyTime = 3.f;
};
