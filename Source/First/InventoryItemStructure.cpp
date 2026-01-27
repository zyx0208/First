// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItemStructure.h"

FInventoryItemStructure::FInventoryItemStructure()
{
	ItemID = 0;
	Stack = 0;
}

FInventoryItemStructure::FInventoryItemStructure(int ItemIDValue, int StackValue)
{
	if (!ItemIDValue)
	{
		ItemID = 0;
	}
	else
	{
		ItemID = ItemIDValue;
	}
	if (!StackValue)
	{
		Stack = 0;
	}
	else
	{
		Stack = StackValue;
	}
}
