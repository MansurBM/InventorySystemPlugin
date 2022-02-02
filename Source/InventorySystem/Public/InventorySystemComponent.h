//Copyright Mansur Bin Mohammad. All Rights Reserved.

#pragma once
#include "Components/ActorComponent.h"

#include "InventorySystemItemDataMap.h"
#include "InventorySystemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInventorySystem_OnSlotsChangedDelegate, const TArray<int>&, Slot);

UCLASS(Blueprintable)
class INVENTORYSYSTEM_API UInventorySystemComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
    void SetItem(int Index, FInventorySystemItemData Data, bool bReplicated = true);
	
	UFUNCTION(Server, WithValidation, Reliable)
	void ServerSetItem(int Index, FInventorySystemItemData Data);
	
	UFUNCTION(BlueprintCallable)
    void AddCount(int Index, int Count, bool bReplicated = true);
	
	UFUNCTION(Server, WithValidation, Reliable)
    void ServerAddCount(int Index, int Count);
	
	UFUNCTION(BlueprintCallable)
	void RemoveItem(int Index, bool bReplicated = true);
	
	UFUNCTION(Server, WithValidation, Reliable)
	void ServerRemoveItem(int Index);
	
	UFUNCTION(BlueprintCallable)
	void RemoveCount(int Index, int Count, bool bReplicated = true);
	
	UFUNCTION(Server, WithValidation, Reliable)
    void ServerRemoveCount(int Index, int Count);
	
	UFUNCTION(BlueprintPure)
    bool GetFirstAvailableSlot(int& OutIndex) const;
	
	UFUNCTION(BlueprintCallable)
	void SwapItems(int FirstIndex, int SecondIndex, bool bReplicated = true);
	
	UFUNCTION(Server, WithValidation, Reliable)
    void ServerSwapItems(int FirstIndex, int SecondIndex);
	
	UFUNCTION(BlueprintCallable)
	void ClearItems(bool bReplicated = true);
	
	UFUNCTION(BlueprintCallable)
	void SetMaxItems(int MaxNum, bool bReplicated = true);
	
	UFUNCTION(Server, WithValidation, Reliable)
    void ServerSetMaxItems(int MaxNum);
	
	UFUNCTION(BlueprintPure)
	int GetMaxItems() const;
	
	UFUNCTION(Server, WithValidation, Reliable)
    void ServerClearItems();

	UFUNCTION(BlueprintCallable)
	void MarkItemDirty(int Index);

	UFUNCTION()
	virtual void OnRep();
public:
	UPROPERTY(BlueprintAssignable)
	FInventorySystem_OnSlotsChangedDelegate OnSlotsChanged;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	FInventorySystemItemDataMap InventoryItems;

	UPROPERTY(BlueprintReadOnly, Replicated)
	TArray<int> DirtyFlags;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep)
	int DirtyFlagIndex = 0;

	UPROPERTY(BlueprintReadOnly)
	int LocalDirtyFlagIndex = 0;

	UPROPERTY()
	int LocalMaxNum = 1;
};
