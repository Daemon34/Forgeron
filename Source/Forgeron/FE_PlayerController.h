// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FE_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FORGERON_API AFE_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AFE_PlayerController();

protected:
	virtual void BeginPlay();

	void Login();

	void HandleLoginCompleted(int32 LocalUserNum, bool bWasSuccessfull, const FUniqueNetId& UserId, const FString& Error);

	FDelegateHandle LoginDelegateHandle;
};
