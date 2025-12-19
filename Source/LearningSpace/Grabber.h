// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/World.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEARNINGSPACE_API UGrabber : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	FRotator Rotation;
	USpringArmComponent* SpringArm;
	UPhysicsHandleComponent* PhysicsHandle;

	bool Grabbing = false;

	float GrabDistance = 0;
	float HoldDistance = 0;
	float GrabRadius = 100;

	//Functions:

	UFUNCTION(BlueprintCallable)
	void Grab();


	UFUNCTION(BlueprintCallable)
	void Release();

	void SetSpringArmComponent();
	void SetupGrab();
	void SetPhysicsHandle();

	bool GetGrabbableInReach(FHitResult& HitResult) const;

};
