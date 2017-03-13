// Fill out your copyright notice in the Description page of Project Settings.

#include "EscapeDrone.h"
#include "Dead.h"


// Sets default values for this component's properties
UDead::UDead()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDead::BeginPlay()
{
	Super::BeginPlay();
    Owner = GetWorld()->GetFirstPlayerController()->GetPawn();
	// ...
	
}


// Called every frame
void UDead::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
    if(KillZone1->IsOverlappingActor(Owner))
    {
        Owner->Destroy();
        //TODO end the game;
    }
	// ...
}

