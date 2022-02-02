//Copyright Mansur Bin Mohammad. All Rights Reserved.

#include "InventorySystemComponent.h"
#include "Net/UnrealNetwork.h"

void UInventorySystemComponent::SetItem(int Index, FInventorySystemItemData Data, bool bReplicated)
{
	if(bReplicated && ENetRole::ROLE_Authority != GetOwnerRole())
	{
		ServerSetItem(Index, Data);
	}
	else
	{
		InventoryItems.Add(Index, Data);
		MarkItemDirty(Index);
		OnRep();
	}
}

void UInventorySystemComponent::ServerSetItem_Implementation(int Index, FInventorySystemItemData Data)
{
	SetItem(Index, Data, false);
}

bool UInventorySystemComponent::ServerSetItem_Validate(int Index, FInventorySystemItemData Data)
{
	return true;
}
void UInventorySystemComponent::AddCount(int Index, int Count, bool bReplicated)
{
	//#TODO: Account for maxStackCount
	if(Count < 0)
	{
		RemoveCount(Index, -Count, bReplicated);
		return;
	}
	if(bReplicated && ENetRole::ROLE_Authority != GetOwnerRole())
	{
		ServerAddCount(Index, Count);
	}
	else
	{
		FInventorySystemItemData InventoryItemData;
		if(InventoryItems.Get(Index, InventoryItemData))
		{
			InventoryItemData.Count += Count;
			InventoryItems.Add(Index,InventoryItemData);
		}
		MarkItemDirty(Index);
		OnRep();
	}
}

void UInventorySystemComponent::ServerAddCount_Implementation(int Index, int Count)
{
	AddCount(Index, Count, false);
}

bool UInventorySystemComponent::ServerAddCount_Validate(int Index, int Count)
{
	return true;
}

void UInventorySystemComponent::RemoveItem(int Index, bool bReplicated)
{
	if(bReplicated && ENetRole::ROLE_Authority != GetOwnerRole())
	{
		ServerRemoveItem(Index);
	}
	else
	{
		InventoryItems.Remove(Index);
		MarkItemDirty(Index);
		OnRep();
	}
}

void UInventorySystemComponent::ServerRemoveItem_Implementation(int Index)
{
	RemoveItem(Index, false);
}

bool UInventorySystemComponent::ServerRemoveItem_Validate(int Index)
{
	return true;
}
void UInventorySystemComponent::RemoveCount(int Index, int Count, bool bReplicated)
{
	if(Count < 0)
	{
		AddCount(Index, -Count, bReplicated);
		return;
	}
	if(bReplicated && ENetRole::ROLE_Authority != GetOwnerRole())
	{
		ServerRemoveCount(Index, Count);
	}
	else
	{
		FInventorySystemItemData InventoryItemData;
		if(InventoryItems.Get(Index, InventoryItemData))
		{
			InventoryItemData.Count -= Count;
			if(InventoryItemData.Count <= 0)
			{
				InventoryItems.Remove(Index);
			}
			else
			{
				InventoryItems.Add(Index,InventoryItemData);
			}
		}
		MarkItemDirty(Index);
		OnRep();
	}
}

void UInventorySystemComponent::ServerRemoveCount_Implementation(int Index, int Count)
{
	RemoveCount(Index, Count, false);
}

bool UInventorySystemComponent::ServerRemoveCount_Validate(int Index, int Count)
{
	return true;
}

void UInventorySystemComponent::SwapItems(int FirstIndex, int SecondIndex, bool bReplicated)
{
	if(bReplicated && ENetRole::ROLE_Authority != GetOwnerRole())
	{
		ServerSwapItems(FirstIndex, SecondIndex);
	}
	else
	{
		InventoryItems.Swap(FirstIndex, SecondIndex);
		MarkItemDirty(FirstIndex);
		MarkItemDirty(SecondIndex);
		OnRep();
	}
}

void UInventorySystemComponent::ServerSwapItems_Implementation(int FirstIndex, int SecondIndex)
{
	SwapItems(FirstIndex, SecondIndex, false);
}

bool UInventorySystemComponent::ServerSwapItems_Validate(int FirstIndex, int SecondIndex)
{
	return true;
}

void UInventorySystemComponent::ClearItems(bool bReplicated)
{
	if(bReplicated && ENetRole::ROLE_Authority != GetOwnerRole())
	{
		ServerClearItems();
	}
	else
	{
		TArray<int> Indexes = InventoryItems.GetKeys();
		for(const int Index : Indexes)
		{
			MarkItemDirty(Index);
		}
		InventoryItems.Values.Empty();
		OnRep();
	}
}

void UInventorySystemComponent::ServerClearItems_Implementation()
{
	ClearItems(false);
}

bool UInventorySystemComponent::ServerClearItems_Validate()
{
	return true;
}
void UInventorySystemComponent::SetMaxItems(int MaxNum, bool bReplicated)
{
	if(bReplicated && ENetRole::ROLE_Authority != GetOwnerRole())
	{
		ServerClearItems();
	}
	else
	{
		InventoryItems.MaxNum = MaxNum;
		if(ENetRole::ROLE_Authority != GetOwnerRole())
		{
			++DirtyFlagIndex;
		}
		else
		{
			--LocalDirtyFlagIndex;
		}
		OnRep();
	}
}

void UInventorySystemComponent::ServerSetMaxItems_Implementation(int MaxNum)
{
	SetMaxItems(MaxNum, false);
}

bool UInventorySystemComponent::ServerSetMaxItems_Validate(int MaxNum)
{
	return true;
}

void UInventorySystemComponent::MarkItemDirty(int Index)
{
	if(ENetRole::ROLE_Authority != GetOwnerRole())
	{
		++DirtyFlagIndex;
	}
	else
	{
		--LocalDirtyFlagIndex;
	}
	DirtyFlags.AddUnique(Index);
}

void UInventorySystemComponent::OnRep()
{
	if(DirtyFlagIndex != LocalDirtyFlagIndex)
	{
		if(ENetRole::ROLE_Authority == GetOwnerRole())
		{
			if(LocalMaxNum != InventoryItems.MaxNum)
			{
				for(int i = LocalMaxNum; i < InventoryItems.MaxNum; ++i)
				{
					InventoryItems.Remove(i);
					DirtyFlags.AddUnique(i);
				}
			}
		}
		LocalMaxNum = InventoryItems.MaxNum;

		if(DirtyFlags.Num() > 0)
		{
			OnSlotsChanged.Broadcast(DirtyFlags);
		}
		
		DirtyFlags.Empty();
		LocalDirtyFlagIndex = DirtyFlagIndex;
	}
}
bool UInventorySystemComponent::GetFirstAvailableSlot(int& OutIndex) const
{
	for(int i = 0; i < InventoryItems.MaxNum; ++i)
	{
		if(!InventoryItems.Has(i))
		{
			OutIndex = i;
			return true;
		}
	}
	return false;
}
int UInventorySystemComponent::GetMaxItems() const
{
	return InventoryItems.MaxNum;
}

void UInventorySystemComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UInventorySystemComponent, InventoryItems);
	DOREPLIFETIME(UInventorySystemComponent, DirtyFlags);
	DOREPLIFETIME(UInventorySystemComponent, DirtyFlagIndex);
}