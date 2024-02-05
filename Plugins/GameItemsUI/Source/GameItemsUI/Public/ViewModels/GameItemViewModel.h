﻿// Copyright Bohdon Sayre, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "GameItemViewModel.generated.h"

class UGameItem;


/**
 * A view-model for a UGameItem.
 */
UCLASS()
class GAMEITEMSUI_API UGameItemViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	UGameItemViewModel();

	/** Return the current item. */
	UGameItem* GetItem() const { return Item; }

	/** Set the game item for this view model .*/
	UFUNCTION(BlueprintCallable)
	void SetItem(UGameItem* NewItem);

	/** Return the quantity of the item. */
	UFUNCTION(BlueprintPure, FieldNotify)
	int32 GetCount() const;

	/** Return true if count is above 1. */
	UFUNCTION(BlueprintPure, FieldNotify)
	bool HasMultiple() const;

	/** Return the display name of the item. */
	UFUNCTION(BlueprintPure, FieldNotify)
	FText GetDisplayName() const;

protected:
	/** The game item. */
	UPROPERTY(Transient, BlueprintReadOnly, FieldNotify, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UGameItem> Item;

	void OnCountChanged(int32 NewCount, int32 OldCount);
};
