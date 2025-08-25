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

   // Schedule destruction after 3 seconds
   SetLifeSpan(5.0f);
}

void ATargetActor::Tick(float DeltaTime)
{
   Super::Tick(DeltaTime);
   FVector NewLocation = StartLocation;
   switch (MovementType)
   {
   case ETargetMovementType::Horizontal:
   {
       float Offset = FMath::Sin(GetWorld()->GetTimeSeconds() * MovementSpeed) * MovementRange;
       NewLocation.Y += Offset;
       break;
   }
   case ETargetMovementType::Vertical:
   {
       float Offset = FMath::Sin(GetWorld()->GetTimeSeconds() * MovementSpeed) * MovementRange;
       NewLocation.Z += Offset;
       break;
   }
   default:
       break;
   }
   SetActorLocation(NewLocation);
}