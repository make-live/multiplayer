// Built with ❤ by Make Live

#pragma once

#include "CoreMinimal.h"
#include "GameInstanceBase.h"
#include "Structs/Online/OnlineSessionWrapper.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineGameInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSessionFoundDelegate, const TArray<FOnlineSessionWrapper>&, Session);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSessionFoundErrorDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLoginErrorDelegate, FString, ErrorMessage);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLoginSuccessDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLogoutSuccessDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLogoutErrorDelegate);

UCLASS()
class MAKELIVEMULTIPLAYER_API UOnlineGameInstance : public UGameInstanceBase
{
	GENERATED_BODY()
	
public:
	UOnlineGameInstance();

	virtual void Init() override;

	virtual void Shutdown() override;

	UFUNCTION(BlueprintCallable)
	void CreateSession();

	UFUNCTION(BlueprintCallable)
	void DestroySession(bool bShutdown);

	UFUNCTION(BlueprintCallable)
	void FindSessions();

	UFUNCTION(BlueprintCallable)
	void JoinOnlineSession(FOnlineSessionWrapper Session);

	UFUNCTION(BlueprintCallable)
	void Login(FString Username);

	UFUNCTION(BlueprintCallable)
	void Logout();

	UPROPERTY(BlueprintAssignable)
	FSessionFoundDelegate OnSessionsFound;

	UPROPERTY(BlueprintAssignable)
	FSessionFoundErrorDelegate OnSessionsFoundError;

	UPROPERTY(BlueprintAssignable)
	FLoginSuccessDelegate OnLoginSuccess;

	UPROPERTY(BlueprintAssignable)
	FLoginErrorDelegate OnLoginError;

	UPROPERTY(BlueprintAssignable)
	FLogoutErrorDelegate OnLogoutSuccess;

	UPROPERTY(BlueprintAssignable)
	FLogoutErrorDelegate OnLogoutError;

	UPROPERTY(BlueprintReadOnly)
	bool bIsLoggedIn;

private:
	FName LocalServerSessionName;

	FName LocalClientSessionName;

	bool bShouldShutdown;

	class IOnlineSubsystem* OnlineSubsystem;

	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

	void OnLoginComplete(int ControllerIndex, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& ErrorString);

	void OnLogoutComplete(int ControllerIndex, bool bWasSuccessful);

	void OnSessionCreated(FName SessionName, bool bWasSuccess);

	void OnSessionDestroyed(FName SessionName, bool bWasSuccess);

	void OnFindSessionsComplete(bool bWasSuccess);

	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
};
