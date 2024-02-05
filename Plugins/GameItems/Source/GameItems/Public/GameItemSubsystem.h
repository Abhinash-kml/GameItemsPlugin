﻿// Copyright Bohdon Sayre, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DisplayDebugHelpers.h"
#include "GameplayTagContainer.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameItemSubsystem.generated.h"

class AHUD;
class IGameItemContainerInterface;
class UCanvas;
class UGameItem;
class UGameItemContainer;
class UGameItemDef;
class UGameItemFragment;


/**
 * Subsystem for working with game items.
 */
UCLASS(Config = Game)
class GAMEITEMS_API UGameItemSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	/** Create and return a new game item from definition. */
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "GameItems")
	UGameItem* CreateItem(UObject* Outer, TSubclassOf<UGameItemDef> ItemDef, int32 Count = 1);

	/**
	 * Create a new game item and add it to a container.
	 * @return The newly created items, which may have been split depending on the container rules.
	 */
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "GameItems")
	TArray<UGameItem*> CreateItemInContainer(UGameItemContainer* Container, TSubclassOf<UGameItemDef> ItemDef, int32 Count = 1);

	/** Duplicate and return a new game item. If count is > 0, set a new count for the item, otherwise use the original item count. */
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "GameItems")
	UGameItem* DuplicateItem(UObject* Outer, UGameItem* Item, int32 Count = -1);

	/**
	 * Split a game item and return a new item with part of the original quantity.
	 * The split item will not be added to any container. Will return null if the item cannot be split.
	 */
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "GameItems")
	UGameItem* SplitItem(UObject* Outer, UGameItem* Item, int32 Count = 1);

	/**
	 * Move an item from one container to another. If bAllowPartial is true, allow moving only some
	 * of the item if the target container can't receive the full amount.
	 * @return The item or items that were moved into the target container.
	 */
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "GameItems")
	TArray<UGameItem*> MoveItem(UGameItemContainer* FromContainer, UGameItemContainer* ToContainer, UGameItem* Item, bool bAllowPartial = true);

	/**
	 * Move multiple items from one container to another. If bAllowPartial is true, allow moving only some
	 * of each item if the target container can't receive the full amount.
	 * @return The item or items that were moved into the target container.
	 */
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "GameItems")
	TArray<UGameItem*> MoveItems(UGameItemContainer* FromContainer, UGameItemContainer* ToContainer, TArray<UGameItem*> Items, bool bAllowPartial = true);

	/**
	 * Find a return an item fragment by class.
	 * Convenience function that uses the GameItemSubsystem.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure = false, Meta = (DeterminesOutputType = "FragmentClass"), Category = "GameItems")
	const UGameItemFragment* FindFragment(TSubclassOf<UGameItemDef> ItemDef, TSubclassOf<UGameItemFragment> FragmentClass) const;

	/** Return all game item containers from an actor, using the IGameItemContainerInterface if possible. */
	UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "GameItems")
	TArray<UGameItemContainer*> GetAllContainersForActor(AActor* Actor) const;

	/** Return a game item container from an actor, using the IGameItemContainerInterface if possible. */
	UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "GameItems")
	UGameItemContainer* GetContainerForActor(AActor* Actor, FGameplayTag ContainerId) const;

	/** Return the default container from an actor, using the IGameItemContainerInterface if possible. */
	UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "GameItems")
	UGameItemContainer* GetDefaultContainerForActor(AActor* Actor) const;

protected:
	/** Return the a game item container interface object, either as the actor or a potential component. */
	virtual IGameItemContainerInterface* GetContainerInterfaceForActor(AActor* Actor) const;

	void OnShowDebugInfo(AHUD* HUD, UCanvas* Canvas, const FDebugDisplayInfo& DisplayInfo, float& YL, float& YPos);
};
