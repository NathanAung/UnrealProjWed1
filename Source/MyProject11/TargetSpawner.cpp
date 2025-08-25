#include "TargetSpawner.h"
#include "TargetActor.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "TimerManager.h"

ATargetSpawner::ATargetSpawner()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ATargetSpawner::BeginPlay()
{
    Super::BeginPlay();

    // Cache reference to controller
    CachedController = Cast<ARangePlayerController>(GetWorld()->GetFirstPlayerController());

    GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &ATargetSpawner::SpawnTarget, SpawnInterval, true);
}

void ATargetSpawner::SpawnTarget()
{
    if (!CachedController || CachedController->RemainingTime <= 0.f)
    {
        // Stop spawning once timer is up
        GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
        return;
    }

    if (TargetClasses.Num() == 0) return;

    // Weighted random: Red more common, Blue less common
    TSubclassOf<ATargetActor> ChosenClass;
    float Roll = FMath::FRand(); // 0.0–1.0

    if (TargetClasses.Num() >= 2)
    {
        // Example: 70% Red (index 0), 30% Blue (index 1)
        if (Roll < 0.6f)
            ChosenClass = TargetClasses[0];
        else
            ChosenClass = TargetClasses[1];
    }
    else
    {
        ChosenClass = TargetClasses[0];
    }

    // Generate random position inside the box
    FVector Origin = GetActorLocation();
    FVector RandomOffset = FVector(
        FMath::FRandRange(-SpawnBoxExtent.X, SpawnBoxExtent.X),
        FMath::FRandRange(-SpawnBoxExtent.Y, SpawnBoxExtent.Y),
        FMath::FRandRange(0.f, SpawnBoxExtent.Z)
    );
    FVector SpawnLocation = Origin + RandomOffset;
    FRotator SpawnRotation = FRotator::ZeroRotator;

    // Spawn the target
    ATargetActor* SpawnedTarget = GetWorld()->SpawnActor<ATargetActor>(ChosenClass, SpawnLocation, SpawnRotation);
    if (SpawnedTarget)
    {
        // Random movement type
        int32 RandMove = FMath::RandRange(0, 2);
        SpawnedTarget->MovementType = static_cast<ETargetMovementType>(RandMove);

        // Randomize speed a bit for variation
        SpawnedTarget->MovementSpeed = FMath::FRandRange(1.0f, 2.0f);
        SpawnedTarget->MovementRange = FMath::FRandRange(100.f, 300.f);
    }
}
