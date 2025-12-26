// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CardEffect.h"
#include "CardDefinition.generated.h"

UENUM(BlueprintType)
enum class ECardType : uint8
{
	Unit UMETA(DisplayName = "Unit"),
	Spell UMETA(DisplayName = "Spell")
};

/**
 * 
 */
UCLASS(BlueprintType)
class CARDCASTERUE_API UCardDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Identify")
	int32 CardID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Identify")
	ECardType CardType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visual")
	TObjectPtr<UTexture2D> CardImage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visual")
	FText CardName_Preview;

	// [수정] 미리보기용 이름 -> 실제 게임 이름으로 사용
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Text")
	FText CardName;

	// [추가] 카드 설명 텍스트 (이걸 넣어야 에디터에 칸이 생깁니다!)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Text", meta = (MultiLine = "true"))
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats", meta = (ClampMin = "0"))
	int32 Cost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit Stats",
		meta = (EditCondition = "CardType == ECardType::Unit", EditConditionHides))
	int32 Force;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit Spawn",
		meta = (EditCondition = "CardType == ECardType::Unit", EditConditionHides))
	TSoftObjectPtr<USkeletalMesh> MinionMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = "Abilities")
	TArray<TObjectPtr<UCardEffect>> Effects;
};
