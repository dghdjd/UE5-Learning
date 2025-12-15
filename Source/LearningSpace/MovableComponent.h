// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MovableComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEARNINGSPACE_API UMovableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMovableComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	FVector StartLocation;
	UPROPERTY(EditAnywhere)
	float MoveDistance = 200.f;

	UPROPERTY(EditAnywhere, Category = "Translation")
	bool ShouldMove = false;

	UPROPERTY(EditAnywhere, Category = "Translation", meta = (EditCondition = "ShouldMove"))
	FVector Velocity = FVector(0.f, 0.f, 0.f);


	UPROPERTY(EditAnywhere, CateGory = "Rotation")
	bool ShouldRotate = false;

	UPROPERTY(EditAnywhere, Category = "Rotation", meta = (EditCondition = "ShouldRotate"))
	FRotator Rotation = FRotator(0.f, 0.f, 0.f);

	void MoveActor(float DeltaTime);
	void RotateActor(float DeltaTime);

		
};
