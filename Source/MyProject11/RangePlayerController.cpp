// RangePlayerController.cpp
#include "RangePlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "TargetActor.h"
#include "MyCharacter.h"

ARangePlayerController::ARangePlayerController()
{
   bShowMouseCursor = false;
   bEnableClickEvents = true;
   bEnableMouseOverEvents = true;

   static ConstructorHelpers::FClassFinder<URangeHUDWidget> WidgetBPClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/WBP_HUD.WBP_HUD'"));
   if (WidgetBPClass.Succeeded())
   {
       HUDWidgetClass = WidgetBPClass.Class;
   }
}

void ARangePlayerController::BeginPlay()
{
    Super::BeginPlay();

    APawn* MyPawn = GetPawn();
    if (!MyPawn)
    {
        MyPawn = GetWorld()->SpawnActor<AMyCharacter>(AMyCharacter::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
        Possess(MyPawn);
    }

    // Create HUD
    if (HUDWidgetClass)
    {
        HUDWidget = CreateWidget<URangeHUDWidget>(this, HUDWidgetClass);
        if (HUDWidget)
        {
            HUDWidget->AddToViewport();
            HUDWidget->UpdateScore(Score);
            HUDWidget->UpdateTime(FMath::CeilToInt(RemainingTime));
        }
    }

    // Start game timer
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
            UNiagaraSystem* EffectToSpawn = Target->bIsRed ? Target->RedNiagaraEffect : Target->BlueNiagaraEffect;
            if (EffectToSpawn)
            {
                UNiagaraFunctionLibrary::SpawnSystemAtLocation(
                    GetWorld(),
                    EffectToSpawn,
                    Target->GetActorLocation(),
                    FRotator::ZeroRotator,
                    FVector(1.f) // scale
                );
            }

            if (Target->bIsRed) {
                Score += 10;
            }
            else {
                Score = FMath::Max(0, Score - 5);
            }
                

            Target->Destroy();

            if (HUDWidget)
                HUDWidget->UpdateScore(Score);
        }
    }
}

void ARangePlayerController::TickTimer()
{
    RemainingTime -= 1.f;
    if (HUDWidget)
        HUDWidget->UpdateTime(FMath::CeilToInt(RemainingTime));

    if (RemainingTime <= 0.f)
    {
        GetWorld()->GetTimerManager().ClearTimer(GameTimerHandle);
        DisableInput(this);

        if (HUDWidget)
        {
            HUDWidget->ShowGameOver();
        }
    }
}