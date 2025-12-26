// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CardActor.generated.h"

class UWidgetComponent;
class UCardDefinition;

UCLASS()
class CARDCASTERUE_API ACardActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACardActor();

protected:
	virtual void BeginPlay() override;

public:	

	UFUNCTION(BlueprintCallable, Category = "Card")
	void InitCard(UCardDefinition* Data);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Card Data")
	TObjectPtr<UCardDefinition> CardData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UWidgetComponent> CardWidgetComp;



};
