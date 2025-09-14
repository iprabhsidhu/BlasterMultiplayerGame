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
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* RocketMesh;

	UPROPERTY(EditAnywhere, Category = "Damage | Inner Radius")
	float InnerRadiusDamage = 200.f;
	UPROPERTY(EditAnywhere, Category = "Damage | Outer Radius")
	float OuterRadiusDamage = 500.f;
};
