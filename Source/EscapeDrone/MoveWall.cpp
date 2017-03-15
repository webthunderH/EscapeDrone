// Fill out your copyright notice in the Description page of Project Settings.

#include "EscapeDrone.h"
#include "MoveWall.h"


// Sets default values for this component's properties
UMoveWall::UMoveWall()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMoveWall::BeginPlay()
{
	Super::BeginPlay();
    DefaultPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
    Owner = GetOwner();
    CurrentLocation= GetOwner()->GetActorLocation();
	// ...
	
}


// Called every frame
void UMoveWall::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
    if(!PressurePlateForWall)
    {
        UE_LOG(LogTemp,Warning, TEXT("PressurePlateForWall is missings"));
        return;
    }
    if (PressurePlateForWall->IsOverlappingActor(DefaultPawn))
    {
        Owner->SetActorLocation(CurrentLocation + Movement);
        LastTimeOpenWall = GetWorld()->GetTimeSeconds();
    }
    if((LastTimeOpenWall + DelayCloseWall)< GetWorld()->GetTimeSeconds())
    {
        Owner->SetActorLocation(CurrentLocation);
    }
	// ...
}
