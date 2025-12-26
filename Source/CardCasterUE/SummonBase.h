// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SummonBase.generated.h"
class UCardDefinition;

UCLASS()
class CARDCASTERUE_API ASummonBase : public ACharacter
{
	GENERATED_BODY()
	
public:	
	ASummonBase();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = "Unit")
	  void InitUnit(UCardDefinition* CardData);

	  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
	  int32 Force;

};
