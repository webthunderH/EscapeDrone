// Fill out your copyright notice in the Description page of Project Settings.

#include "EscapeDrone.h"
#include "OpenDoor.h"
#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;
    
    // ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
    Super::BeginPlay();
    Owner = GetOwner();
    // ...
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    if(GetMassOnTriggerVolume()>MaxMass)
    {
        OnOpen.Broadcast();
    }
    else
    {
        OnClose.Broadcast();
    }
}

float UOpenDoor::GetMassOnTriggerVolume()
{
    float TotalMass=0.0f;
    TArray<AActor*> Overlapping;
    if(!PressurePlate)
    {
        UE_LOG(LogTemp,Warning,TEXT("Got A problem On pressure plate"));
        return TotalMass;
    }
    PressurePlate->GetOverlappingActors(OUT Overlapping);
    for(const auto& Actor : Overlapping)
    {
        TotalMass+=Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();;
        UE_LOG(LogTemp,Warning,TEXT("%s is on pressure plate"),*(Actor->GetName()));
    }
    return TotalMass;
}


