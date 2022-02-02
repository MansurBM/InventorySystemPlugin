//Copyright Mansur Bin Mohammad. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
#include "InventorySystemItemData.generated.h"

USTRUCT(BlueprintType)
struct INVENTORYSYSTEM_API FInventorySystemItemData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Default)
	FName ID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Default)
	int Count = 1;
};