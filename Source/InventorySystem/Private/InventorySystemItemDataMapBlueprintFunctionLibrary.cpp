//Copyright Mansur Bin Mohammad. All Rights Reserved.

#include "InventorySystemItemDataMapBlueprintFunctionLibrary.h"

FInventorySystemItemDataMap UInventorySystemItemDataMapBlueprintFunctionLibrary::Create(const TArray<FInventorySystemItemData>& Items)
{
	FInventorySystemItemDataMap Map;
	for(int i = 0; i < Items.Num(); ++i)
	{
		Map.Add(i, Items[i]);
	}
	return Map;
}

void UInventorySystemItemDataMapBlueprintFunctionLibrary::Add( UPARAM(Ref) FInventorySystemItemDataMap& Map, int Index, FInventorySystemItemData Value)
{
	Map.Add(Index, Value);
}
void UInventorySystemItemDataMapBlueprintFunctionLibrary::Remove(UPARAM(Ref) FInventorySystemItemDataMap& Map, int Index)
{
	Map.Remove(Index);
}
bool UInventorySystemItemDataMapBlueprintFunctionLibrary::Get(UPARAM(Ref) FInventorySystemItemDataMap& Map, int Index, FInventorySystemItemData& OutValue)
{
	return Map.Get(Index, OutValue);
}

TArray<int> UInventorySystemItemDataMapBlueprintFunctionLibrary::GetKeys(UPARAM(Ref) FInventorySystemItemDataMap& Map)
{
	return Map.GetKeys();
}
TArray<FInventorySystemItemData> UInventorySystemItemDataMapBlueprintFunctionLibrary::GetValues(UPARAM(Ref) FInventorySystemItemDataMap& Map)
{
	return Map.GetValues();
}
TMap<int, FInventorySystemItemData> UInventorySystemItemDataMapBlueprintFunctionLibrary::ToMap(UPARAM(Ref) FInventorySystemItemDataMap& Map)
{
	return Map.ToMap();
}
bool UInventorySystemItemDataMapBlueprintFunctionLibrary::Has(UPARAM(Ref) FInventorySystemItemDataMap& Map, int Index)
{
	return Map.Has(Index);
}
int UInventorySystemItemDataMapBlueprintFunctionLibrary::Count(UPARAM(Ref) FInventorySystemItemDataMap& Map)
{
	return Map.Values.Num();
}
void UInventorySystemItemDataMapBlueprintFunctionLibrary::Swap(UPARAM(Ref) FInventorySystemItemDataMap& Map, int LeftIndex, int RightIndex)
{
	Map.Swap(LeftIndex, RightIndex);
}

void UInventorySystemItemDataMapBlueprintFunctionLibrary::Copy(UPARAM(Ref) FInventorySystemItemDataMap& Map, const FInventorySystemItemDataMap& Other)
{
	Map.Copy(Other);
}

void UInventorySystemItemDataMapBlueprintFunctionLibrary::Clear(UPARAM(Ref) FInventorySystemItemDataMap& Map)
{
	Map.Clear();
}