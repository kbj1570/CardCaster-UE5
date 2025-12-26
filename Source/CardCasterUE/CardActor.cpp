// Fill out your copyright notice in the Description page of Project Settings.



#include "CardActor.h"
#include "CardDefinition.h"
#include "CardWidget.h"
#include "Components/WidgetComponent.h"

ACardActor::ACardActor()
{
	PrimaryActorTick.bCanEverTick = true;

	// 위젯 컴포넌트 생성 및 설정
	CardWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("CardWidgetComp"));
	RootComponent = CardWidgetComp;

	// 카드는 양면이 아니라 앞면만 보이게 설정 (Screen 모드 or World 모드)
	CardWidgetComp->SetWidgetSpace(EWidgetSpace::World);
	CardWidgetComp->SetDrawSize(FVector2D(200, 300)); // 카드 크기 (예시)
}

void ACardActor::BeginPlay()
{
	Super::BeginPlay();
}

void ACardActor::InitCard(UCardDefinition* Data)
{
	if (!Data) return;
	this->CardData = Data;

	// 위젯 컴포넌트에서 실제 UCardWidget 가져오기
	UCardWidget* Widget = Cast<UCardWidget>(CardWidgetComp->GetUserWidgetObject());

	if (Widget)
	{
		Widget->UpdateCardWidget(Data);
	}
}


