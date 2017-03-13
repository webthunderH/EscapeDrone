// Fill out your copyright notice in the Description page of Project Settings.

#include "EscapeDrone.h"
#include "GrabbingSystem.h"


// Sets default values for this component's properties
UGrabbingSystem::UGrabbingSystem()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;
    
    // ...
}


// Called when the game starts
void UGrabbingSystem::BeginPlay()
{
    Super::BeginPlay();
    DefaultPawn = GetWorld()->GetFirstPlayerController();
    PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if(PhysicsHandle)
    {
        // Nothing to do It's just a test if the pointer is
    }
    else
    {
        UE_LOG(LogTemp, Error,
               TEXT("%s missing component physics Handle"), *(GetOwner()->GetName())
               );
    }
    // ...
    
}


// Called every frame
void UGrabbingSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    FVector ViewPointLocation;
    FRotator ViewPointRotation;
    DefaultPawn->GetPlayerViewPoint(
        OUT ViewPointLocation,
        OUT ViewPointRotation
    );
    /*UE_LOG(LogTemp,
           Warning,
           TEXT("The viewPoint of the Pawn is : %s, %s"),
           *ViewPointLocation.ToString(),
           *ViewPointRotation.ToString());*/
    FVector LineTraceEnd = ViewPointLocation + ViewPointRotation.Vector() * Reach;
    DrawDebugLine(
        GetWorld(),
        ViewPointLocation,
        LineTraceEnd,
        FColor(255,0,0),
        false,
        0.0f,
        0.0f,
        10.0
    );
    
    FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
    
    FHitResult HitResult;
    GetWorld()->LineTraceSingleByObjectType(
        OUT HitResult,
        ViewPointLocation,
        LineTraceEnd,
        FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
        TraceParameters
    );
    
    AActor* HitActor = HitResult.GetActor();
    if(HitActor)
    {
        UE_LOG(LogTemp,
            Warning,
            TEXT("I'm touching with the AKA-Ray cast : %s"), *(HitActor->GetName())
            );
    }
        
    
    // ...
    
}


