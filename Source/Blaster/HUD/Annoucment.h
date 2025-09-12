// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Annoucment.generated.h"

/**
 * 
 */
UCLASS()
class BLASTER_API UAnnoucment : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* WarmupTime;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* AnnouncementText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* infoText;
};
