// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEDRONE_API UOpenDoor : public UActorComponent
{
    GENERATED_BODY()
    
public:
    // Sets default values for this component's properties
    UOpenDoor();
    void OpenDoor();
    void CloseDoor();
protected:
    // Called when the game starts
    virtual void BeginPlay() override;
    
public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    private :
    UPROPERTY(EditAnywhere)
    float OpenAngle = 180.0f;
    UPROPERTY(EditAnywhere)
    float CloseAngle = 90.0f;
    
    UPROPERTY(EditAnywhere)
    ATriggerVolume* PressurePlate;
    UPROPERTY(EditAnywhere)
    float DelayCloseDoor=1.0f;
    
    float LastTimeOpenDoor;
    AActor* Owner;
    AActor* ActorThatOpenDoor;
    
};
