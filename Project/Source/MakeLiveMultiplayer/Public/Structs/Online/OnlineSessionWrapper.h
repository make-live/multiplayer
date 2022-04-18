// Built with ❤ by Make Live

#pragma once

#include "CoreMinimal.h"
#include "OnlineSessionSettings.h"
#include "OnlineSessionWrapper.generated.h"

USTRUCT(BlueprintType)
struct MAKELIVEMULTIPLAYER_API FOnlineSessionWrapper
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	FString ConnectionString;

	UPROPERTY(BlueprintReadOnly)
	int PingInMs;

	UPROPERTY(BlueprintReadOnly)
	FString OwnerUsername;

	UPROPERTY(BlueprintReadOnly)
	FString SessionId;

	FOnlineSessionSearchResult OnlineResult;
};