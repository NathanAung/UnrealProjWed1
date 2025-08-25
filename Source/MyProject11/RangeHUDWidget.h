// RangeHUDWidget.h
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "RangeHUDWidget.generated.h"

class UTextBlock;

UCLASS()
class MYPROJECT11_API URangeHUDWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    // These will be linked to the Text widgets in the Blueprint
    UPROPERTY(meta = (BindWidget))
    UTextBlock* ScoreText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* TimeText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* GameOverText;

    // Called from C++
    void UpdateScore(int32 NewScore);
    void UpdateTime(int32 NewTime);
    void ShowGameOver();
};
