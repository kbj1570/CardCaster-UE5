#include "HandManager.h"
#include "CardActor.h"        // 카드 액터 헤더 필요
#include "CardDefinition.h"   // 데이터 에셋 헤더 필요
#include "Kismet/KismetMathLibrary.h" // 수학 라이브러리

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
	// 방어 코드: 데이터나 클래스 설정이 없으면 중단
	if (!CardData || !CardActorClass) return;

	// 1. 카드 생성 (위치는 일단 내 위치)
	FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotation = GetActorRotation();

	// SpawnActor를 사용해 카드 실체화
	ACardActor* NewCard = GetWorld()->SpawnActor<ACardActor>(CardActorClass, SpawnLocation, SpawnRotation);

	if (NewCard)
	{
		// 2. C++에서는 여기서 'Init'을 호출하지 않고, 리턴만 해주거나 블루프린트에서 처리하도록 유도합니다.
		// (만약 ACardActor에 InitCard 함수가 C++로 있다면 여기서 호출 가능)
		// NewCard->InitCard(CardData); 

		// 3. 배열에 추가
		CurrentHand.Add(NewCard);

		// 4. 즉시 정렬 실행
		UpdateHandLayout();
	}
}

void AHandManager::UpdateHandLayout()
{
	// 카드가 없으면 정렬할 필요 없음
	if (CurrentHand.Num() == 0) return;

	int32 NumCards = CurrentHand.Num();
	// 전체 폭 계산 (카드 개수 - 1 * 간격)
	float TotalWidth = (NumCards - 1) * CardSpacing;

	FVector CenterPos = GetActorLocation();
	FVector RightVec = GetActorRightVector(); // 액터의 오른쪽 방향

	// 시작점 (중심에서 왼쪽으로 절반만큼 이동)
	FVector StartPos = CenterPos - (RightVec * (TotalWidth / 2.0f));

	for (int32 i = 0; i < NumCards; i++)
	{
		ACardActor* Card = CurrentHand[i];

		// 방어 코드: 카드가 파괴되었거나 유효하지 않으면 건너뜀
		if (!IsValid(Card)) continue;

		// 목표 위치: 시작점 + (오른쪽 * 순서 * 간격)
		FVector TargetPos = StartPos + (RightVec * (i * CardSpacing));

		// 위치 이동 (부드러운 이동은 나중에 보간(Lerp) 적용 가능)
		Card->SetActorLocation(TargetPos);
	}
}