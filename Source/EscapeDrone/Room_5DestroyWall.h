// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Room_5DestroyWall.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEDRONE_API URoom_5DestroyWall : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URoom_5DestroyWall();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
    void DestroyWall();
private :
    UPROPERTY(EditAnywhere)
    AActor* Door1=nullptr;
    UPROPERTY(EditAnywhere)
    AActor* Door2=nullptr;
    UPROPERTY(EditAnywhere)
    AActor* Door3=nullptr;
    UPROPERTY(EditAnywhere)
    AActor* Door4=nullptr;
    
    FRotator RotatorD1;
    FRotator RotatorD2;
    FRotator RotatorD3;
    FRotator RotatorD4;
    
};
