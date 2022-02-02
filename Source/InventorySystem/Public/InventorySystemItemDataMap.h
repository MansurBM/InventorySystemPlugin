//Copyright Mansur Bin Mohammad. All Rights Reserved.

#pragma once
#include "InventorySystemItemData.h"
#include "InventorySystemItemDataMap.generated.h"

USTRUCT(BlueprintType)
struct INVENTORYSYSTEM_API FIntInventorySystemItemDataPair
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Default)
	int Key = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Default)
	FInventorySystemItemData Value;
};

USTRUCT(BlueprintType)
struct INVENTORYSYSTEM_API FInventorySystemItemDataMap
{
	GENERATED_BODY()

	void Add(int Index, FInventorySystemItemData Value);
	void Remove(int Index);
	bool Get(int Index, FInventorySystemItemData& OutValue) const;
	FInventorySystemItemData GetUnsafe(int Index) const;
	bool GetPtr(int Index, FInventorySystemItemData*& OutValue);
	
	bool Has(int Index) const;
	void Swap(int FirstIndex, int SecondIndex);
	void Clear();
	
	void Copy(const FInventorySystemItemDataMap& Other);

	TMap<int, FInventorySystemItemData> ToMap() const;
	
	TArray<int> GetKeys() const;
	
	TArray<FInventorySystemItemData> GetValues() const;

	//We're not allowed to use a replicated TMap, so we use a TArray instead
	UPROPERTY()
	TArray<FIntInventorySystemItemDataPair> Values;
	
	UPROPERTY(BlueprintReadWrite)
	int MaxNum = 12;
};