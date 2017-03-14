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
    // Check if a physic handle is attached
    if (PhysicsHandle->GrabbedComponent)
    {
        PhysicsHandle->SetTargetLocation(GetLineReachEnd());
        
    }
}
void UGrabbingSystem::Grab()
{
    UPrimitiveComponent* ComponentToGrab = LastPhyscBodyHit().GetComponent();
    if (LastPhyscBodyHit().GetActor()!= nullptr) {
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
    if (PhysicsHandle->GrabbedComponent)
    {
        PhysicsHandle->ReleaseComponent();
    }
    return;
}
void UGrabbingSystem::FindPhysicsHandleComponent()
{
    PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if(PhysicsHandle==nullptr)
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
    FHitResult HitResult;
    FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
    GetWorld()->LineTraceSingleByObjectType(
                                            OUT HitResult,
                                            GetLineReachStart(),
                                            GetLineReachEnd(),
                                            FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
                                            TraceParameters
                                            );
    return HitResult;
}

FVector UGrabbingSystem::GetLineReachStart()
{
    FVector ViewPointLocation;
    FRotator ViewPointRotation;
    DefaultPawn->GetPlayerViewPoint(
                                    OUT ViewPointLocation,
                                    OUT ViewPointRotation
                                    );
    return ViewPointLocation;

}
FVector UGrabbingSystem::GetLineReachEnd()
{
    FVector ViewPointLocation;
    FRotator ViewPointRotation;
    DefaultPawn->GetPlayerViewPoint(
                                    OUT ViewPointLocation,
                                    OUT ViewPointRotation
                                    );
    return ViewPointLocation + ViewPointRotation.Vector() * Reach;
}

