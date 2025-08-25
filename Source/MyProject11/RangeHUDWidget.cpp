// RangeHUDWidget.cpp
#include "RangeHUDWidget.h"

void URangeHUDWidget::UpdateScore(int32 NewScore)
{
    if (ScoreText)
    {
        ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"), NewScore)));
    }
}

void URangeHUDWidget::UpdateTime(int32 NewTime)
{
    if (TimeText)
    {
        TimeText->SetText(FText::FromString(FString::Printf(TEXT("Time: %d"), NewTime)));
    }
}

void URangeHUDWidget::ShowGameOver()
{
    if (GameOverText)
    {
        GameOverText->SetVisibility(ESlateVisibility::Visible);
        GameOverText->SetText(FText::FromString(TEXT("GAME OVER")));
    }
}
