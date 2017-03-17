// Fill out your copyright notice in the Description page of Project Settings.

#include "EscapeDrone.h"
#include "Teleport.h"


// Sets default values for this component's properties
UTeleport::UTeleport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTeleport::BeginPlay()
{
	Super::BeginPlay();
    DefaultPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
    if (!DefaultPawn)
    {
        UE_LOG(LogTemp, Error,TEXT("Default Pawn is not found"));
    }
	// ...
}


// Called every frame
void UTeleport::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
    if(!DefaultPawn){return ;}
    if(!PlateformPlate)
    {
        UE_LOG(LogTemp, Error,TEXT("Pointer to Trigger Volume is not found"));
        return;
    }
    if(PlateformPlate->IsOverlappingActor(DefaultPawn))
    {
        Teleport(DefaultPawn);
    }
	// ...
}

void UTeleport::Teleport(AActor* MyPlayer)
{
    MyPlayer->SetActorLocation(TeleportLocation,false);
}

