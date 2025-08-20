// RangePlayerController.h
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RangePlayerController.generated.h"


UCLASS()
class MYPROJECT11_API ARangePlayerController : public APlayerController
{
   GENERATED_BODY()

public:
   ARangePlayerController();
   UPROPERTY(EditAnywhere, BlueprintReadWrite)
   float RemainingTime = 180.f;

protected:
   virtual void BeginPlay() override;
   virtual void SetupInputComponent() override;
   void Shoot();
   void TickTimer();
   FTimerHandle GameTimerHandle;

public:
   int32 Score = 0;

};