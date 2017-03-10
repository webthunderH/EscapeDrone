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
    UE_LOG(LogTemp,
           Warning,
           TEXT("The viewPoint of the Pawn is : %s, %s"),
           *ViewPointLocation.ToString(),
           *ViewPointRotation.ToString());
    // ...
}


