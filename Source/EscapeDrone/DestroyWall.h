// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "DestroyWall.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEDRONE_API UDestroyWall : public UActorComponent
{
    GENERATED_BODY()
    
public:
    // Sets default values for this component's properties
    UDestroyWall();
    void DestroyTheWall();
protected:
    // Called when the game starts
    virtual void BeginPlay() override;
    
public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    private :
    UPROPERTY(EditAnywhere)
    ATriggerVolume* PressurePlate;
    
    AActor* ActorThatDestroyWall;
    
    
};
