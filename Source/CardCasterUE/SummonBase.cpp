// Fill out your copyright notice in the Description page of Project Settings.


#include "SummonBase.h"
#include "CardDefinition.h"
#include "Components/SkeletalMeshComponent.h"

ASummonBase::ASummonBase()
{
 	PrimaryActorTick.bCanEverTick = true;
}

void ASummonBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASummonBase::InitUnit(UCardDefinition* CardData)
{
	if (!CardData) return;

	this->Force = CardData->Force;

	if (!CardData->MinionMesh.IsNull())
	{
		USkeletalMesh* NewMesh = CardData->MinionMesh.LoadSynchronous();
		if (NewMesh)
		{
			GetMesh()->SetSkeletalMesh(NewMesh);
		}
	
	}

}

