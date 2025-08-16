// Fill out your copyright notice in the Description page of Project Settings.


#include "BlasterPlayerState.h"
#include "Blaster/Character/BlasterCharacter.h"
#include "Blaster/PlayerController/BlasterPlayerController.h"
#include "Net/UnrealNetwork.h"

void ABlasterPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABlasterPlayerState, Defeats);
}

void ABlasterPlayerState::AddToScore(float ScoreAmount)
{
	SetScore(GetScore() + ScoreAmount);
	Character = (Character == nullptr) ? Cast<ABlasterCharacter>(GetPawn()) : Character;
	if (Character)
	{
		Controller = (Controller == nullptr) ? Cast<ABlasterPlayerController>(Character->Controller) : Controller;
		if (Controller)
		{
			Controller->SetHUDScore(FMath::Abs(GetScore()));
		}
	}
}

void ABlasterPlayerState::AddToDefeats(float DefeatAmount)
{
	Defeats += DefeatAmount;
	Character = (Character == nullptr) ? Cast<ABlasterCharacter>(GetPawn()) : Character;
	if (Character)
	{
		Controller = (Controller == nullptr) ? Cast<ABlasterPlayerController>(Character->Controller) : Controller;
		if (Controller)
		{
			Controller->SetHUDDefeats(Defeats);
		}
	}
}

void ABlasterPlayerState::OnRep_Score()
{
	Super::OnRep_Score();

	Character = (Character == nullptr) ? Cast<ABlasterCharacter>(GetPawn()) : Character;
	if (Character)
	{
		Controller = (Controller == nullptr) ? Cast<ABlasterPlayerController>(Character->Controller) : Controller;
		if (Controller)
		{
			Controller->SetHUDScore(FMath::Abs(GetScore()));
		}
	}

}

void ABlasterPlayerState::OnRep_Defeats()
{
	Character = (Character == nullptr) ? Cast<ABlasterCharacter>(GetPawn()) : Character;
	if (Character)
	{
		Controller = (Controller == nullptr) ? Cast<ABlasterPlayerController>(Character->Controller) : Controller;
		if (Controller)
		{
			Controller->SetHUDDefeats(Defeats);
		}
	}
}
