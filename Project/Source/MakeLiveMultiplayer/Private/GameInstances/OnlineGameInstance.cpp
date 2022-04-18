// Built with ❤ by Make Live

#include "GameInstances/OnlineGameInstance.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"

UOnlineGameInstance::UOnlineGameInstance()
{
}

void UOnlineGameInstance::Init() {
	Super::Init();

	LocalServerSessionName = FName(TEXT("GameServer"));
	LocalClientSessionName = FName(TEXT("GameClient"));

	OnlineSubsystem = IOnlineSubsystem::Get();
}

void UOnlineGameInstance::Shutdown()
{
	DestroySession(true);
}

void UOnlineGameInstance::Login(FString Username)
{
	UE_LOG(LogTemp, Warning, TEXT("UOnlineGameInstance::Login()"));

	if (OnlineSubsystem)
	{
		if (IOnlineIdentityPtr Identity = OnlineSubsystem->GetIdentityInterface())
		{
			Identity->OnLoginCompleteDelegates->AddUObject(this, &UOnlineGameInstance::OnLoginComplete);
			Identity->Login(0, FOnlineAccountCredentials());
		}
	}
}

void UOnlineGameInstance::OnLoginComplete(int ControllerIndex, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& ErrorString)
{
	UE_LOG(LogTemp, Warning, TEXT("OnLoginComplete: %d"), bWasSuccessful);

	if (IOnlineIdentityPtr IdentityPtr = OnlineSubsystem->GetIdentityInterface())
	{
		IdentityPtr->ClearOnLoginCompleteDelegates(ControllerIndex, this);
	}

	if (ErrorString.Contains(TEXT("already logged in")))
	{
		bIsLoggedIn = true;
		OnLoginSuccess.Broadcast();

		return;
	}

	bIsLoggedIn = bWasSuccessful;

	if (bIsLoggedIn)
	{
		OnLoginSuccess.Broadcast();
		return;
	}

	OnLoginError.Broadcast(ErrorString);
}

void UOnlineGameInstance::Logout()
{
	UE_LOG(LogTemp, Warning, TEXT("UOnlineGameInstance::Logout()"));

	if (OnlineSubsystem)
	{
		if (IOnlineIdentityPtr Identity = OnlineSubsystem->GetIdentityInterface())
		{
			Identity->OnLogoutCompleteDelegates->AddUObject(this, &UOnlineGameInstance::OnLogoutComplete);
			Identity->Logout(0);
		}
	}
}

void UOnlineGameInstance::OnLogoutComplete(int ControllerIndex, bool bWasSuccessful)
{
	UE_LOG(LogTemp, Warning, TEXT("UOnlineGameInstance::OnLogoutComplete(): %d"), bWasSuccessful);

	bIsLoggedIn = !bWasSuccessful;

	if (IOnlineIdentityPtr IdentityPtr = OnlineSubsystem->GetIdentityInterface())
	{
		IdentityPtr->ClearOnLogoutCompleteDelegates(ControllerIndex, this);
	}

	if (!bWasSuccessful)
	{
		OnLogoutError.Broadcast();
	}
	else
	{
		OnLogoutSuccess.Broadcast();
	}
}

void UOnlineGameInstance::CreateSession()
{
	UE_LOG(LogTemp, Warning, TEXT("UOnlineGameInstance::CreateSession()"));

	if (!bIsLoggedIn)
	{
		UE_LOG(LogTemp, Warning, TEXT("User not logged in."));

		return;
	}

	if (OnlineSubsystem)
	{
		if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
		{
			FOnlineSessionSettings SessionSettings;
			SessionSettings.bIsDedicated = false;
			SessionSettings.bShouldAdvertise = true;
			SessionSettings.bIsLANMatch = true;
			SessionSettings.NumPublicConnections = 5;
			SessionSettings.bAllowJoinInProgress = true;
			SessionSettings.bAllowJoinViaPresence = true;
			SessionSettings.bUsesPresence = true;
			SessionPtr->OnCreateSessionCompleteDelegates.AddUObject(this, &UOnlineGameInstance::OnSessionCreated);
			SessionPtr->CreateSession(0, LocalServerSessionName, SessionSettings);
		}
	}
}

void UOnlineGameInstance::OnSessionCreated(FName SessionName, bool bWasSuccess)
{
	UE_LOG(LogTemp, Warning, TEXT("UOnlineGameInstance::OnSessionCreated: %d"), bWasSuccess);

	if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
	{
		SessionPtr->ClearOnCreateSessionCompleteDelegates(this);
	}

	GetWorld()->ServerTravel(FString(TEXT("DefaultGameOpenWorld?listen")));
}

void UOnlineGameInstance::DestroySession(bool bShutdown)
{
	UE_LOG(LogTemp, Warning, TEXT("UOnlineGameInstance::DestroySession()"));

	if (!bIsLoggedIn)
	{
		UE_LOG(LogTemp, Warning, TEXT("User not logged in."));

		return;
	}

	bShouldShutdown = bShutdown;

	if (OnlineSubsystem)
	{
		if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
		{
			SessionPtr->OnDestroySessionCompleteDelegates.AddUObject(this, &UOnlineGameInstance::OnSessionDestroyed);

			if (GetWorld()->GetNetMode() == ENetMode::NM_ListenServer)
			{
				SessionPtr->DestroySession(LocalServerSessionName);
			}
			else
			{
				SessionPtr->DestroySession(LocalClientSessionName);
			}
		}
	}
}

void UOnlineGameInstance::OnSessionDestroyed(FName SessionName, bool bWasSuccess)
{
	UE_LOG(LogTemp, Warning, TEXT("UOnlineGameInstance::OnSessionDestroyed: %d"), bWasSuccess);

	if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
	{
		SessionPtr->ClearOnDestroySessionCompleteDelegates(this);
	}

	if (bShouldShutdown)
	{
		UE_LOG(LogTemp, Warning, TEXT("UOnlineGameInstance::OnSessionDestroyed: Calling Shutdown"));

		Super::Shutdown();
	}
}

void UOnlineGameInstance::FindSessions()
{
	UE_LOG(LogTemp, Warning, TEXT("UOnlineGameInstance::SearchForSessions()"));

	if (!bIsLoggedIn)
	{
		UE_LOG(LogTemp, Warning, TEXT("User not logged in."));

		return;
	}

	if (OnlineSubsystem)
	{
		if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
		{
			TSharedPtr<FOnlineSessionSearch> SearchSettings;

			SessionSearch = MakeShareable(new FOnlineSessionSearch());

			if (SessionSearch.IsValid())
			{
				SessionSearch->MaxSearchResults = 100;
				SessionPtr->OnFindSessionsCompleteDelegates.AddUObject(this, &UOnlineGameInstance::OnFindSessionsComplete);
				SessionPtr->FindSessions(0, SessionSearch.ToSharedRef());
			}
		}
	}
}

void UOnlineGameInstance::OnFindSessionsComplete(bool bWasSuccess)
{
	UE_LOG(LogTemp, Warning, TEXT("UOnlineGameInstance::OnFindSessionsComplete: %d"), bWasSuccess);

	if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
	{
		SessionPtr->ClearOnFindSessionsCompleteDelegates(this);
	}

	if (bWasSuccess && SessionSearch.IsValid())
	{
		TArray<FOnlineSessionWrapper> Results;

		if (SessionSearch->SearchResults.Num() > 0)
		{
			if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
			{

				for (const FOnlineSessionSearchResult& SearchResult : SessionSearch->SearchResults)
				{
					FOnlineSessionWrapper Result;
					Result.PingInMs = SearchResult.PingInMs;
					Result.OwnerUsername = SearchResult.Session.OwningUserName;
					Result.OnlineResult = SearchResult;
					Result.SessionId = SearchResult.Session.GetSessionIdStr();

					UE_LOG(LogTemp, Warning, TEXT("UOnlineGameInstance::OnFindSessionsComplete: SessionInfo %s"), *SearchResult.Session.SessionInfo->ToDebugString());

					SessionPtr->GetResolvedConnectString(SearchResult, NAME_GamePort, Result.ConnectionString);

					Results.Add(Result);
				}
			}
		}

		OnSessionsFound.Broadcast(Results);

		return;
	}
	
	OnSessionsFoundError.Broadcast();
}

void UOnlineGameInstance::JoinOnlineSession(FOnlineSessionWrapper Result)
{
	UE_LOG(LogTemp, Warning, TEXT("UOnlineGameInstance::JoinSession()"));

	if (!bIsLoggedIn)
	{
		UE_LOG(LogTemp, Warning, TEXT("User not logged in."));

		return;
	}

	if (OnlineSubsystem)
	{
		if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
		{
			SessionPtr->OnJoinSessionCompleteDelegates.AddUObject(this, &UOnlineGameInstance::OnJoinSessionComplete);
			SessionPtr->JoinSession(0, "Test", Result.OnlineResult);

			GetFirstLocalPlayerController()->ClientTravel(Result.ConnectionString, ETravelType::TRAVEL_Absolute);
		}
	}
}

void UOnlineGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	UE_LOG(LogTemp, Warning, TEXT("UOnlineGameInstance::OnJoinSessionComplete"));

	if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
	{
		SessionPtr->ClearOnJoinSessionCompleteDelegates(this);
	}
}
