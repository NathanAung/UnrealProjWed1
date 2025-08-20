// RangePlayerController.cpp
#include "RangePlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "TargetActor.h"

ARangePlayerController::ARangePlayerController()
{
   bShowMouseCursor = false;
}

void ARangePlayerController::BeginPlay()
{
   Super::BeginPlay();
   GetWorld()->GetTimerManager().SetTimer(GameTimerHandle, this, &ARangePlayerController::TickTimer, 1.0f, true);
}

void ARangePlayerController::SetupInputComponent()
{
   Super::SetupInputComponent();
   InputComponent->BindAction("Fire", IE_Pressed, this, &ARangePlayerController::Shoot);
}

void ARangePlayerController::Shoot()
{
   FVector CameraLoc;
   FRotator CameraRot;
   GetPlayerViewPoint(CameraLoc, CameraRot);
   FVector Start = CameraLoc;
   FVector End = Start + (CameraRot.Vector() * 10000.f);
   FHitResult Hit;
   if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility))
   {
       if (ATargetActor* Target = Cast<ATargetActor>(Hit.GetActor()))
       {
           if (Target->bIsRed)
               Score += 10;
           else
               Score -= 5;
           Target->Destroy();
       }
   }
}

void ARangePlayerController::TickTimer()
{
   RemainingTime -= 1.f;
   if (RemainingTime <= 0.f)
   {
       // End Game: Disable input
       GetWorld()->GetTimerManager().ClearTimer(GameTimerHandle);
       DisableInput(this);
   }
}