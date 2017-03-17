// Fill out your copyright notice in the Description page of Project Settings.

#include "EscapeDrone.h"
#include "Room_5DestroyWall.h"


// Sets default values for this component's properties
URoom_5DestroyWall::URoom_5DestroyWall()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URoom_5DestroyWall::BeginPlay()
{
	Super::BeginPlay();
    if(!Door1){UE_LOG(LogTemp, Error, TEXT("Door1 pointer is missing"));}
    if(!Door2){UE_LOG(LogTemp, Error, TEXT("Door2 pointer is missing"));}
    if(!Door3){UE_LOG(LogTemp, Error, TEXT("Door3 pointer is missing"));}
    if(!Door4){UE_LOG(LogTemp, Error, TEXT("Door4 pointer is missing"));}

    RotatorD1 =Door1->GetTransform().Rotator();
    RotatorD2 =Door2->GetTransform().Rotator();
    RotatorD3 =Door3->GetTransform().Rotator();
    RotatorD4 =Door4->GetTransform().Rotator();
	// ...
	
}


// Called every frame
void URoom_5DestroyWall::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
    if(!Door1){return;}
    if(!Door2){return;}
    if(!Door3){return;}
    if(!Door4){return;}
    if ((RotatorD1.Yaw != Door1->GetTransform().Rotator().Yaw)&&
        (RotatorD2.Yaw != Door2->GetTransform().Rotator().Yaw)&&
        (RotatorD3.Yaw != Door3->GetTransform().Rotator().Yaw)&&
        (RotatorD4.Yaw != Door4->GetTransform().Rotator().Yaw)
        )
    {
        DestroyWall();
    }
	// ...
}

void URoom_5DestroyWall::DestroyWall()
{
    AActor* MyWall = GetOwner();
    MyWall->Destroy();
}
