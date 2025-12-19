// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/World.h"
#include "Mover.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEARNINGSPACE_API UMover : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMover();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetMoverShouldMove(bool Move);
	

private:

	bool MoverShouldMove = false;

	UPROPERTY(EditAnywhere)
	FVector MoverMoveOffset;

	UPROPERTY(EditAnywhere)
	float MoverMoveTime = 4;

	float MoverSpeed = 0;

	float MoverDistTolerance = 3.f;

	FVector MoverStartLocation;

	void UpdateLocation(FVector& CurrLocation, FVector TargetLocation, float DeltaTime);
};
