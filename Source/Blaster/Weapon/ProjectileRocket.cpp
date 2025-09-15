// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileRocket.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Sound/SoundCue.h"
#include "NiagaraComponent.h"
#include "NiagaraSystemInstance.h"
#include "Sound/SoundAttenuation.h"
#include "Components/AudioComponent.h"

AProjectileRocket::AProjectileRocket()
{
	RocketMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RocketMesh"));
	RocketMesh->SetupAttachment(RootComponent);
	RocketMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AProjectileRocket::BeginPlay()
{
	Super::BeginPlay();

	if (!HasAuthority())
	{
		CollisionBox->OnComponentHit.AddDynamic(this, &ThisClass::OnHit);
	}
	if (TrailSystem)
	{
		TrailSystemComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(TrailSystem, GetRootComponent(), FName(), GetActorLocation(), GetActorRotation(), EAttachLocation::KeepWorldPosition, false);
	}
	if (ProjectileLoop && LoopingSoundAttenuation)
	{
		ProjectileLoopComponent = UGameplayStatics::SpawnSoundAttached(ProjectileLoop, GetRootComponent(), FName(), GetActorLocation(), EAttachLocation::KeepWorldPosition, false, 1.f, 1.f, 0.f, LoopingSoundAttenuation, (USoundConcurrency*)nullptr, false);
	}
	if (ProjectileLoopComponent && ProjectileLoopComponent->IsPlaying())
	{
		ProjectileLoopComponent->Stop();
	}
}

void AProjectileRocket::Destroyed()
{
}

void AProjectileRocket::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	 APawn* FiringPawn = GetInstigator();
	 if (FiringPawn && HasAuthority())
	 {
		 AController* FiringController = FiringPawn->GetController();
		 if (FiringController)
		 {
			 UGameplayStatics::ApplyRadialDamageWithFalloff(this, Damage, 10.f, GetActorLocation(), InnerRadiusDamage, OuterRadiusDamage, 1.f, UDamageType::StaticClass(), TArray<AActor*>(), this, FiringController);
		 }
	 }
	 
	 GetWorldTimerManager().SetTimer(DestroyTimer, this, &AProjectileRocket::DestroyTimerFinished, DestroyTime);

	 if (ImpactParticles)
	 {
		 UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticles, GetActorTransform());
	 }
	 if (ImpactSound)
	 {
		 UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
	 }
	 if (RocketMesh)
	 {
		 RocketMesh->SetVisibility(false);
	 }
	 if (CollisionBox)
	 {
		 CollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	 }
	 if (TrailSystemComponent && TrailSystemComponent->GetSystemInstance())
	 {
		 TrailSystemComponent->GetSystemInstance()->Deactivate();
	 }
}

void AProjectileRocket::DestroyTimerFinished()
{
	Destroy();
}
