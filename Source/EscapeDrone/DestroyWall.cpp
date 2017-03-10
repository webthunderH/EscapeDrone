// Fill out your copyright notice in the Description page of Project Settings.

#include "EscapeDrone.h"
#include "DestroyWall.h"


// Sets default values for this component's properties
UDestroyWall::UDestroyWall()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;
    
    // ...
}


// Called when the game starts
void UDestroyWall::BeginPlay()
{
    Super::BeginPlay();
    ActorThatDestroyWall= GetWorld()->GetFirstPlayerController()->GetPawn();
    // ...
    
}


// Called every frame
void UDestroyWall::TickComponent(
                                 float DeltaTime,
                                 ELevelTick TickType,
                                 FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    if (PressurePlate->IsOverlappingActor(ActorThatDestroyWall))
    {
        DestroyTheWall();
    }
    // ...
}

void UDestroyWall::DestroyTheWall()
{
    AActor* MyWall = GetOwner();
    MyWall->Destroy();
}

