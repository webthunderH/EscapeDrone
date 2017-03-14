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
        OpenDoor();
        LastTimeOpenDoor = GetWorld()->GetTimeSeconds();
    }
    
    if((LastTimeOpenDoor + DelayCloseDoor)< GetWorld()->GetTimeSeconds())
    {
        CloseDoor();
    }
    // ...
}
void UOpenDoor::OpenDoor()
{
    Owner->SetActorRotation(FRotator(0.0f,OpenAngle,0.0f));
}
void UOpenDoor::CloseDoor()
{
    Owner->SetActorRotation(FRotator(0.0f, CloseAngle, 0.0f));
}
float UOpenDoor::GetMassOnTriggerVolume()
{
    float Result=0;
    TArray<AActor*> Overlapping;
    PressurePlate->GetOverlappingActors(OUT Overlapping);
    for(const auto* Actor : Overlapping)
    {
        float Mass =Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
        Result+=Mass;
        UE_LOG(LogTemp, Warning, TEXT("%s weight is %s"),*(Actor->GetName(), *Mass);
    }
    return Result;
}


