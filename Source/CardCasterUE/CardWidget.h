// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CardWidget.generated.h"

class UCardDefinition;
class UTextBlock;
class UImage;

UCLASS()
class CARDCASTERUE_API UCardWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// 카드의 데이터를 받아서 화면을 갱신하는 함수
	UFUNCTION(BlueprintCallable, Category = "UI")
	void UpdateCardWidget(UCardDefinition* CardData);

protected:
	// [중요] 에디터 UMG에 있는 위젯 이름과 변수 이름이 똑같아야 연결됨!

	// 이름 텍스트
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_Name;

	// 설명 텍스트
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_Desc;

	// 포스(Force) 텍스트
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_Force;

	// 마나 비용 텍스트
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_Cost;

	// 카드 일러스트 이미지
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Art;
};
