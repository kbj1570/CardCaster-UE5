#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HandManager.generated.h"

class ACardActor;
class UCardDefinition;

UCLASS()
class CARDCASTERUE_API AHandManager : public AActor
{
	GENERATED_BODY()

public:
	AHandManager();

protected:
	virtual void BeginPlay() override;

public:
	// 1. Draw 1 Card
	UFUNCTION(BlueprintCallable, Category = "Hand")
	void AddCardToHand(UCardDefinition* CardData);

	// 2. 손패 정렬 함수 (핵심!)
	UFUNCTION(BlueprintCallable, Category = "Hand")
	void UpdateHandLayout();

protected:
	// 생성할 카드 액터의 원본 (블루프린트 클래스를 넣을 변수)
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<ACardActor> CardActorClass;

	// 카드 사이의 간격
	UPROPERTY(EditAnywhere, Category = "Layout")
	float CardSpacing = 250.0f;

	// 현재 손에 들고 있는 카드들 목록
	UPROPERTY(VisibleAnywhere, Category = "State")
	TArray<ACardActor*> CurrentHand;
};