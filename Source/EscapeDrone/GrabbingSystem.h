// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "GrabbingSystem.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEDRONE_API UGrabbingSystem : public UActorComponent
{
    GENERATED_BODY()
    
public:
    // Sets default values for this component's properties
    UGrabbingSystem();
    
protected:
    // Called when the game starts
    virtual void BeginPlay() override;
    
public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    //Getter
    FVector GetLineReachStart();
    FVector GetLineReachEnd();
    
private:
    APlayerController* DefaultPawn= nullptr;
    UPROPERTY(EditAnywhere)
    float Reach= 100.0f;
    UPhysicsHandleComponent* PhysicsHandle = nullptr;
    UInputComponent* InputComponent= nullptr;
    
    void Grab();
    void Released();
    // Find the physics Handle Component
    void FindPhysicsHandleComponent();
    // Setup the attached Input component
    void SetupInputComponent();
    // return the first target hit by the ray cast.
    const FHitResult LastPhyscBodyHit();
    
};
