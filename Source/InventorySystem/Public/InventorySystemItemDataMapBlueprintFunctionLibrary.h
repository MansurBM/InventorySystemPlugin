//Copyright Mansur Bin Mohammad. All Rights Reserved.

#pragma once
#include "InventorySystemItemDataMap.h"
#include "InventorySystemItemDataMapBlueprintFunctionLibrary.generated.h"

UCLASS(meta=(ScriptName="InventorySystemItemDataMapLibrary"))
class INVENTORYSYSTEM_API UInventorySystemItemDataMapBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category="InventorySystem|ItemDataMap", meta=(DisplayName="Create"))
	static FInventorySystemItemDataMap Create(const TArray<FInventorySystemItemData>& Items);
	
	UFUNCTION(BlueprintCallable, Category="InventorySystem|ItemDataMap", meta=(DisplayName="Add"))
	static void Add( UPARAM(Ref) FInventorySystemItemDataMap& Map, int Index, FInventorySystemItemData Value);
	
	UFUNCTION(BlueprintCallable, Category="InventorySystem|ItemDataMap", meta=(DisplayName="Remove"))
	static void Remove(UPARAM(Ref) FInventorySystemItemDataMap& Map, int Index);
	
	UFUNCTION(BlueprintPure, Category="InventorySystem|ItemDataMap", meta=(DisplayName="Get"))
    static bool Get(UPARAM(Ref) FInventorySystemItemDataMap& Map, int Index, FInventorySystemItemData& OutValue);
	
	UFUNCTION(BlueprintPure, Category="InventorySystem|ItemDataMap", meta=(DisplayName="GetKeys"))
	static TArray<int> GetKeys(UPARAM(Ref) FInventorySystemItemDataMap& Map);
	
	UFUNCTION(BlueprintPure, Category="InventorySystem|ItemDataMap", meta=(DisplayName="GetValues"))
    static TArray<FInventorySystemItemData> GetValues(UPARAM(Ref) FInventorySystemItemDataMap& Map);
	
	UFUNCTION(BlueprintPure, Category="InventorySystem|ItemDataMap", meta=(DisplayName="ToMap"))
    static TMap<int, FInventorySystemItemData> ToMap(UPARAM(Ref) FInventorySystemItemDataMap& Map);
	
	UFUNCTION(BlueprintPure, Category="InventorySystem|ItemDataMap", meta=(DisplayName="Has"))
	static bool Has(UPARAM(Ref) FInventorySystemItemDataMap& Map, int Index);
	
	UFUNCTION(BlueprintPure, Category="InventorySystem|ItemDataMap", meta=(DisplayName="Count"))
    static int Count(UPARAM(Ref) FInventorySystemItemDataMap& Map);
	
	UFUNCTION(BlueprintCallable, Category="InventorySystem|ItemDataMap", meta=(DisplayName="Swap"))
	static void Swap(UPARAM(Ref) FInventorySystemItemDataMap& Map, int LeftIndex, int RightIndex);
	
	UFUNCTION(BlueprintCallable, Category="InventorySystem|ItemDataMap", meta=(DisplayName="Copy"))
	static void Copy(UPARAM(Ref) FInventorySystemItemDataMap& Map, const FInventorySystemItemDataMap& Other);
	
	UFUNCTION(BlueprintCallable, Category="InventorySystem|ItemDataMap", meta=(DisplayName="Clear"))
	static void Clear(UPARAM(Ref) FInventorySystemItemDataMap& Map);
};