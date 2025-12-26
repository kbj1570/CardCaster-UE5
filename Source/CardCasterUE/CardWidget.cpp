#include "CardWidget.h"
#include "CardDefinition.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UCardWidget::UpdateCardWidget(UCardDefinition* CardData)
{
    UE_LOG(LogTemp, Warning, TEXT("[DEBUG] CardWidget: 업데이트 시작!"));

    if (!CardData)
    {
        UE_LOG(LogTemp, Error, TEXT("[DEBUG] CardWidget: 데이터가 Null입니다!"));
        return;
    }

    // 1. 텍스트 상자 연결 확인 (가장 의심되는 부분)
    if (Text_Name == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("[DEBUG] 텍스트 상자 연결 실패: Text_Name is NULL! (이름이 틀렸거나 BindWidget 실패)"));
    }
    else
    {
        FString NameStr = CardData->CardName.ToString();
        UE_LOG(LogTemp, Warning, TEXT("[DEBUG] 이름 적용 중: %s"), *NameStr);
        Text_Name->SetText(CardData->CardName);
    }

    if (Text_Desc == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("[DEBUG] 설명 상자 연결 실패: Text_Desc is NULL!"));
    }
    else
    {
        Text_Desc->SetText(CardData->Description);
    }

    // 2. 숫자(Force) 연결 확인
    if (Text_Force == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("[DEBUG] 포스 상자 연결 실패: Text_Force is NULL!"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("[DEBUG] 포스 적용 중: %d"), CardData->Force);
        Text_Force->SetText(FText::AsNumber(CardData->Force));

        // 보이게 설정
        Text_Force->SetVisibility(ESlateVisibility::Visible);
    }


	if (!CardData) return;

	// 1. 텍스트 갱신 (Force 포함)
	if (Text_Force) Text_Force->SetText(FText::AsNumber(CardData->Force));
	if (Text_Cost) Text_Cost->SetText(FText::AsNumber(CardData->Cost));
	if (Text_Name) Text_Name->SetText(CardData->CardName);

	// [추가] 설명 텍스트 연결 (이게 없어서 안 떴던 것!)
	if (Text_Desc) Text_Desc->SetText(CardData->Description);

	// 2. 이미지 갱신
	if (Image_Art && CardData->CardImage)
	{
		Image_Art->SetBrushFromTexture(CardData->CardImage);
	}

	// 3. 카드 타입에 따라 Force 숨기기 (주문 카드는 Force가 없으니까)
	if (Text_Force)
	{
		// Unit일 때만 보이고, 아니면 숨김
		ESlateVisibility NewVisibility = (CardData->CardType == ECardType::Unit) ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
		Text_Force->SetVisibility(NewVisibility);
	}
}