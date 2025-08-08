// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Menu.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERSESSIONS_API UMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void MenuSetup(int32 NumberOfPublicConnection=4, FString TypeOfMatch=FString(TEXT("FreeForAll")), FString LobbyPath = FString(TEXT("/Game/ThirdPerson/Maps/LobbyMap")));
	
protected:
	virtual bool Initialize() override;
	virtual void OnLevelRemovedFromWorld(ULevel* InLevel,UWorld* InWorld);

	// Callbacks for custom delegates on Multiplayer Sessions Subsystem
	UFUNCTION()
	void OnCreateSession(bool bWasSuccessful); 
	void OnFindSession(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful);
	void OnJoinSession(EOnJoinSessionCompleteResult::Type Result);
	UFUNCTION()
	void OnDestroySession(bool bWasSuccessful);
	UFUNCTION()
	void OnStartSession(bool bWasSuccessful);

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* JoinButton;

	void MenuTearDown();

	UFUNCTION()
	void HostButtonClick();
	UFUNCTION()
	void JoinButtonClick();

	// The subsystem designed to handle all online sessions functionalities.
	class UMultiplayerSessionSubsytem* MultiplayerSessionsSubsystem;

	int32 NumPublicConnection{4};
	FString MatchType{TEXT("FreeForAll")};
	FString PathToLobby{ TEXT("") };
};
