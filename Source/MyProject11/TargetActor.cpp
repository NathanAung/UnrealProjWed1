// TargetActor.cpp
#include "TargetActor.h"

ATargetActor::ATargetActor()
{
   PrimaryActorTick.bCanEverTick = true;
}

void ATargetActor::BeginPlay()
{
   Super::BeginPlay();
   StartLocation = GetActorLocation();
}

void ATargetActor::Tick(float DeltaTime)
{
   Super::Tick(DeltaTime);
   FVector NewLocation = StartLocation;
   float Time = GetWorld()->GetTimeSeconds();
   if (bMoveHorizontal)
       NewLocation.X += FMath::Sin(Time * MoveSpeed) * MoveRange;
   if (bMoveVertical)
       NewLocation.Z += FMath::Sin(Time * MoveSpeed) * MoveRange;
   SetActorLocation(NewLocation);
}