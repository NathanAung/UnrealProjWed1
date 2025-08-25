#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RangePlayerController.h"
#include "TargetSpawner.generated.h"

class ATargetActor;

UCLASS()
class MYPROJECT11_API ATargetSpawner : public AActor
{
    GENERATED_BODY()

public:
    ATargetSpawner();

protected:
    virtual void BeginPlay() override;

    // Timer handle for spawning
    FTimerHandle SpawnTimerHandle;

    // Function called repeatedly
    void SpawnTarget();

public:
    // List of possible target blueprints
    UPROPERTY(EditAnywhere, Category = "Spawning")
    TArray<TSubclassOf<ATargetActor>> TargetClasses;

    // Spawn interval
    UPROPERTY(EditAnywhere, Category = "Spawning")
    float SpawnInterval = 0.2f;

    // Spawn bounds (relative box)
    UPROPERTY(EditAnywhere, Category = "Spawning")
    FVector SpawnBoxExtent = FVector(1000.f, 1000.f, 500.f);

    // Maximum Z offset (so targets don’t spawn underground)
    UPROPERTY(EditAnywhere, Category = "Spawning")
    float BaseZ = 100.f;

private:
    ARangePlayerController* CachedController;
};
