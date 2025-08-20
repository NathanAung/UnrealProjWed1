// TargetActor.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetActor.generated.h"

UCLASS()

class MYPROJECT11_API ATargetActor : public AActor
{

    GENERATED_BODY()

public:
    ATargetActor();
    // Is this target red or green
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsRed = true;

    // Which movement
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bMoveHorizontal = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bMoveVertical = false;

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

private:
    FVector StartLocation;
    float MoveRange = 200.f;
    float MoveSpeed = 1.5f;
};