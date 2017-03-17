// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Teleport.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEDRONE_API UTeleport : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTeleport();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
    void Teleport(AActor*);
private:
    UPROPERTY(EditAnywhere)
    ATriggerVolume* PlateformPlate=nullptr;
	
    FVector TeleportLocation = FVector(-1450.0f, 1320.0f,385.0f);
    AActor* DefaultPawn = nullptr;
	
};
