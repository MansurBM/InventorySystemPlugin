//Copyright Mansur Bin Mohammad. All Rights Reserved.

#include "InventorySystemItemDataMap.h"

void FInventorySystemItemDataMap::Add(int Index, FInventorySystemItemData Value)
{
	if(Index >= MaxNum)
	{
		return;
	}
	
	auto FindByIndexPred = [Index](const FIntInventorySystemItemDataPair& Pair){ return Pair.Key == Index;};
	
	if(Values.ContainsByPredicate(FindByIndexPred))
	{
		for(FIntInventorySystemItemDataPair& Pair : Values)
		{
			Pair.Value = Value;
		}
	}
	else
	{
		Values.Add({Index, Value});
	}
}
void FInventorySystemItemDataMap::Remove(int Index)
{
	auto FindByIndexPred = [Index](const FIntInventorySystemItemDataPair& Pair){ return Pair.Key == Index;};
	
	if(Values.ContainsByPredicate(FindByIndexPred))
	{
		Values.RemoveAll(FindByIndexPred);
	}
}
bool FInventorySystemItemDataMap::Get(int Index, FInventorySystemItemData& OutValue) const
{
	auto FindByIndexPred = [Index](const FIntInventorySystemItemDataPair& Pair){ return Pair.Key == Index;};

	if(Index >= MaxNum)
	{
		return false;
	}
	if(Values.ContainsByPredicate(FindByIndexPred))
	{
		OutValue = GetUnsafe(Index);
		return true;
	}
	return false;
}
FInventorySystemItemData FInventorySystemItemDataMap::GetUnsafe(int Index) const
{
	auto FindByIndexPred = [Index](const FIntInventorySystemItemDataPair& Pair){ return Pair.Key == Index;};
	return Values.FindByPredicate(FindByIndexPred)->Value;;
}
bool FInventorySystemItemDataMap::GetPtr(int Index, FInventorySystemItemData*& OutValue)
{
	OutValue = nullptr;
	if(Index >= MaxNum)
	{
		return false;
	}
	
	auto FindByIndexPred = [Index](const FIntInventorySystemItemDataPair& Pair){ return Pair.Key == Index;};

	if(Values.ContainsByPredicate(FindByIndexPred))
	{
		OutValue = &(Values.FindByPredicate(FindByIndexPred)->Value);
		return true;
	}
	return false;
}
bool FInventorySystemItemDataMap::Has(int Index) const
{
	if(Index >= MaxNum)
	{
		return false;
	}
	auto FindByIndexPred = [Index](const FIntInventorySystemItemDataPair& Pair){ return Pair.Key == Index;};

	if(Values.ContainsByPredicate(FindByIndexPred))
	{
		return true;
	}
	return false;
}
void FInventorySystemItemDataMap::Swap(int FirstIndex, int SecondIndex)
{
	if(FirstIndex >= MaxNum || SecondIndex >= MaxNum)
	{
		return;
	}
	
	auto FindByFirstIndexPredicate = [FirstIndex](const FIntInventorySystemItemDataPair& Pair){ return Pair.Key == FirstIndex;};
	auto FindBySecondIndexPredicate = [SecondIndex](const FIntInventorySystemItemDataPair& Pair){ return Pair.Key == SecondIndex;};

	const bool bHasFirstIndex = Values.ContainsByPredicate(FindByFirstIndexPredicate);
	const bool bHasSecondIndex = Values.ContainsByPredicate(FindBySecondIndexPredicate);
	
	if(bHasFirstIndex && bHasSecondIndex)
	{
		const FInventorySystemItemData Temp = Values.FindByPredicate(FindBySecondIndexPredicate)->Value;
		Values.RemoveAll(FindBySecondIndexPredicate);
		Values.Add({SecondIndex, Values.FindByPredicate(FindByFirstIndexPredicate)->Value});
		Values.RemoveAll(FindByFirstIndexPredicate);
		Values.Add({FirstIndex, Temp});
	}
	else if(bHasFirstIndex && !bHasSecondIndex)
	{
		Values.Add({SecondIndex, Values.FindByPredicate(FindByFirstIndexPredicate)->Value});
		Values.RemoveAll(FindByFirstIndexPredicate);
	}
	else if(!bHasFirstIndex && bHasSecondIndex)
	{
		Values.Add({FirstIndex, Values.FindByPredicate(FindBySecondIndexPredicate)->Value});
		Values.RemoveAll(FindBySecondIndexPredicate);
	}
}
void FInventorySystemItemDataMap::Clear()
{
	Values.Empty();
}
void FInventorySystemItemDataMap::Copy(const FInventorySystemItemDataMap& Other)
{
	Values = Other.Values;
	MaxNum = Other.MaxNum;
}
TMap<int, FInventorySystemItemData> FInventorySystemItemDataMap::ToMap() const
{
	TMap<int, FInventorySystemItemData> ReturnValues;
	
	for(const FIntInventorySystemItemDataPair& Pair: Values)
	{
		if(!ReturnValues.Contains(Pair.Key))
		{
			ReturnValues.Add(Pair.Key, Pair.Value);
		}
	}
	return ReturnValues;
}
TArray<int> FInventorySystemItemDataMap::GetKeys() const
{
	TArray<int> ReturnValues;
	
	for(const FIntInventorySystemItemDataPair& Pair: Values)
	{
		ReturnValues.Add(Pair.Key);
	}
	return ReturnValues;
}
TArray<FInventorySystemItemData> FInventorySystemItemDataMap::GetValues() const
{
	TArray<FInventorySystemItemData> ReturnValues;
	
	for(const FIntInventorySystemItemDataPair& Pair: Values)
	{
		ReturnValues.Add(Pair.Value);
	}
	return ReturnValues;
}