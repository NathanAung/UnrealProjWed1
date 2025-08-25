// TargetActor.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "TargetActor.generated.h"

UENUM(BlueprintType)
enum class ETargetMovementType : uint8
{
    Stationary UMETA(DisplayName = "Stationary"),
    Horizontal UMETA(DisplayName = "Horizontal"),
    Vertical UMETA(DisplayName = "Vertical")
};

UCLASS()

class MYPROJECT11_API ATargetActor : public AActor
{

    GENERATED_BODY()

public:
    ATargetActor();

    // Is this target red or green
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsRed = true;

    // Niagara effects for hit feedback
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
    UNiagaraSystem* RedNiagaraEffect;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
    UNiagaraSystem* BlueNiagaraEffect;

    // Particle effects for hit feedback
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
    UParticleSystem* RedHitEffect;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
    UParticleSystem* BlueHitEffect;

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target")
    ETargetMovementType MovementType = ETargetMovementType::Stationary;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target")
    float MovementSpeed = 100.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target")
    float MovementRange = 200.f;

private:
    FVector StartLocation;
};