// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "BlasterGameMode.generated.h"

/**
*	Match States
*/
namespace MatchState
{
	extern BLASTER_API const FName Cooldown; // Match duration has been reached. Display Cooldown Timer
}


/**
 * 
 */
UCLASS()
class BLASTER_API ABlasterGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	ABlasterGameMode();
	virtual void Tick(float DeltaTime) override;
	virtual void PlayerEliminated(class ABlasterCharacter* ElimmedCharacter, class ABlasterPlayerController* VictimController, ABlasterPlayerController* AttackerController);
	virtual void RequestRespawn(class ACharacter* ElimmedCharacter, AController* ElimmedController);

	UPROPERTY(EditAnywhere, Category = "Match State | Time")
	float MatchTime = 120.f;
	UPROPERTY(EditAnywhere, Category = "Match State | Time")
	float WarmupTime = 10.f;
	UPROPERTY(EditAnywhere, Category = "Match State | Time")
	float CountdownTime = 10.f;
	float LevelStartingTime = 0.f;

protected:
	virtual void BeginPlay() override;
	virtual void OnMatchStateSet() override;

private:

};
