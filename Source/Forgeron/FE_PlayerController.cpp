// Fill out your copyright notice in the Description page of Project Settings.


#include "FE_PlayerController.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "OnlineSubsystemTypes.h"
#include "Interfaces/OnlineIdentityInterface.h"

AFE_PlayerController::AFE_PlayerController() {

}

void AFE_PlayerController::BeginPlay() {
	Super::BeginPlay();
	Login();
}

void AFE_PlayerController::Login() {
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();

	FUniqueNetIdPtr NetId = Identity->GetUniquePlayerId(0);

	if (NetId != nullptr && Identity->GetLoginStatus(0) == ELoginStatus::LoggedIn) {
		return;
	}

	LoginDelegateHandle = Identity->AddOnLoginCompleteDelegate_Handle(0, FOnLoginCompleteDelegate::CreateUObject(this, &ThisClass::HandleLoginCompleted));

	FString AuthType;
	FParse::Value(FCommandLine::Get(), TEXT("AUTH_TYPE="), AuthType);

	if (!AuthType.IsEmpty()) {
		UE_LOG(LogTemp, Log, TEXT("[ONLINE][EOS] Logging into EOS..."));

		if (!Identity->AutoLogin(0)) {
			UE_LOG(LogTemp, Warning, TEXT("[ONLINE][EOS] Failed to login... "));

			Identity->ClearOnLoginCompleteDelegate_Handle(0, LoginDelegateHandle);
			LoginDelegateHandle.Reset();
		}
	}
	else {
		FOnlineAccountCredentials Credentials("AccountPortal", "", "");

		UE_LOG(LogTemp, Log, TEXT("[ONLINE][EOS] Logging into EOS..."));

		if (!Identity->Login(0, Credentials)) {
			UE_LOG(LogTemp, Warning, TEXT("[ONLINE][EOS] Failed to login..."));

			Identity->ClearOnLoginCompleteDelegate_Handle(0, LoginDelegateHandle);
			LoginDelegateHandle.Reset();
		}
	}
}

void AFE_PlayerController::HandleLoginCompleted(int32 LocalUserNum, bool bWasSuccessfull, const FUniqueNetId & UserId, const FString & Error) {
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();
	if (bWasSuccessfull) {
		UE_LOG(LogTemp, Log, TEXT("[ONLINE][EOS] Login callback completed !"));
	} else {
		UE_LOG(LogTemp, Log, TEXT("[ONLINE][EOS] Login callback failed !"));
	}

	Identity->ClearOnLoginCompleteDelegate_Handle(LocalUserNum, LoginDelegateHandle);
	LoginDelegateHandle.Reset();
}