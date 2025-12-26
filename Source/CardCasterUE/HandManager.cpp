#include "HandManager.h"
#include "CardActor.h"
#include "CardDefinition.h"

AHandManager::AHandManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AHandManager::BeginPlay()
{
	Super::BeginPlay();
}

void AHandManager::AddCardToHand(UCardDefinition* CardData)
{
	if (!CardData || !CardActorClass) return;

	// 1. 카드 액터 생성 (위치는 일단 내 위치)
	FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotation = GetActorRotation();

	ACardActor* NewCard = GetWorld()->SpawnActor<ACardActor>(CardActorClass, SpawnLocation, SpawnRotation);

	if (NewCard)
	{
		// 2. 데이터 주입
		NewCard->InitCard(CardData);

		// 3. 목록에 추가
		CurrentHand.Add(NewCard);

		// 4. "헤쳐 모여!" (정렬 다시 하기)
		UpdateHandLayout();
	}
}

void AHandManager::UpdateHandLayout()
{
	if (CurrentHand.Num() == 0) return;

	// 중앙을 기준으로 정렬하기 위한 계산
	// 예: 카드가 3장이면 -> -1, 0, +1 위치에 배치
	// 예: 카드가 4장이면 -> -1.5, -0.5, +0.5, +1.5 위치에 배치

	int32 NumCards = CurrentHand.Num();
	float TotalWidth = (NumCards - 1) * CardSpacing; // 전체 길이
	FVector CenterPos = GetActorLocation();
	FVector StartPos = CenterPos - (GetActorRightVector() * (TotalWidth / 2.0f));

	for (int32 i = 0; i < NumCards; i++)
	{
		ACardActor* Card = CurrentHand[i];
		if (!Card) continue;

		// 목표 위치 계산: 시작점 + (오른쪽 방향 * 순서 * 간격)
		FVector TargetPos = StartPos + (GetActorRightVector() * (i * CardSpacing));

		// [임시] 즉시 이동 (나중엔 부드럽게 움직이는 애니메이션 추가 예정)
		Card->SetActorLocation(TargetPos);
	}
}