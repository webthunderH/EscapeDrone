// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "MoveWall.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWallEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEDRONE_API UMoveWall : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMoveWall();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
    UPROPERTY(BlueprintAssignable)
    FWallEvent OpenWall;
    UPROPERTY(BlueprintAssignable)
    FWallEvent CloseWall;
    
private :
    UPROPERTY(EditAnywhere)
    ATriggerVolume* PressurePlateForWall=nullptr;
    
    UPROPERTY(EditAnywhere)
    float MaxMass=10.0f;
    float LastTimeOpenWall;
    UPROPERTY(EditAnywhere)
    float DelayCloseWall = 2.5f;
    UPROPERTY(EditAnywhere)
    FVector Movement = FVector(0.0f,1000.0f,0.0f);
    
    FVector CurrentLocation;
    AActor* Owner = nullptr;
    AActor* DefaultPawn = nullptr;
    
    float GetMassOnTriggerVolume();
	
};
