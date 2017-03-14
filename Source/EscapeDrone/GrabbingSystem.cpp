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
    FindPhysicsHandleComponent();
    SetupInputComponent();
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
    
    FVector LineTraceEnd = ViewPointLocation + ViewPointRotation.Vector() * Reach;

    // Check if a physic handle is attached
    if (PhysicsHandle->GrabbedComponent)
    {
        // move the actor. To the end of the reachLine 
        PhysicsHandle->SetTargetLocation(LineTraceEnd);
        
    }
}
void UGrabbingSystem::Grab()
{
    UE_LOG(LogTemp,
           Warning,
           TEXT("I press grab key")
           );
    FHitResult LastHit= LastPhyscBodyHit();
    UPrimitiveComponent* ComponentToGrab = LastHit.GetComponent();
    auto ActorHit = LastHit.GetActor();
    if (ActorHit!= nullptr) {
        PhysicsHandle->GrabComponent(
            ComponentToGrab,
            NAME_None,
            ComponentToGrab->GetOwner()->GetActorLocation(),
            true //that allow rotation
        );
    }
    
    return;

}
void UGrabbingSystem::Released()
{
    UE_LOG(LogTemp,
           Warning,
           TEXT("I Released grab key")
           );
    if (PhysicsHandle->GrabbedComponent)
    {
        PhysicsHandle->ReleaseComponent();
    }
    return;
}
void UGrabbingSystem::FindPhysicsHandleComponent()
{
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
    return;
}
void UGrabbingSystem::SetupInputComponent()
{
    InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
    if(InputComponent)
    {
        UE_LOG(LogTemp, Warning,
               TEXT("Input Component is active on %s"), *(GetOwner()->GetName())
               );
        InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabbingSystem::Grab);
        InputComponent->BindAction("Grab", IE_Released, this, &UGrabbingSystem::Released);

    }
    else
    {
        UE_LOG(LogTemp, Error,
               TEXT("%s missing Input Component"), *(GetOwner()->GetName())
               );
    }
    return;
}

const FHitResult UGrabbingSystem::LastPhyscBodyHit()
{
    FVector ViewPointLocation;
    FRotator ViewPointRotation;
    DefaultPawn->GetPlayerViewPoint(
                                    OUT ViewPointLocation,
                                    OUT ViewPointRotation
                                    );
    
    FVector LineTraceEnd = ViewPointLocation + ViewPointRotation.Vector() * Reach;
    
    
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
    return HitResult;
}

void UGrabbingSystem::MyDebugLine()
{
    FVector ViewPointLocation;
    FRotator ViewPointRotation;
    DefaultPawn->GetPlayerViewPoint(
                                    OUT ViewPointLocation,
                                    OUT ViewPointRotation
                                    );
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
}

