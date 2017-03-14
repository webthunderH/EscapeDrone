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
    InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
    if(InputComponent)
    {
        UE_LOG(LogTemp, Warning,
               TEXT("Input Component is active on %s"), *(GetOwner()->GetName())
               );
        InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabbingSystem::Grab);
        InputComponent->BindAction("Released", IE_Released, this, &UGrabbingSystem::Released);
    }
    else
    {
        UE_LOG(LogTemp, Error,
               TEXT("%s missing Input Component"), *(GetOwner()->GetName())
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
void UGrabbingSystem::Grab()
{
    UE_LOG(LogTemp,
           Warning,
           TEXT("I press grab key")
           );

}
void UGrabbingSystem::Released()
{
    UE_LOG(LogTemp,
           Warning,
           TEXT("I Released grab key")
           );
}


