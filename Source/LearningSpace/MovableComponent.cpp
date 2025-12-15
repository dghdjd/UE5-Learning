// Fill out your copyright notice in the Description page of Project Settings.


#include "MovableComponent.h"

// Sets default values for this component's properties
UMovableComponent::UMovableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMovableComponent::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetOwner()->GetActorLocation();
	// ...
	
}

void UMovableComponent::MoveActor(float DeltaTime)
{
	FVector CurrLocation = GetOwner()->GetActorLocation();
	CurrLocation += Velocity * DeltaTime;

	double CurrDistance = FVector::Dist(StartLocation, CurrLocation);

	if (CurrDistance >= MoveDistance)
	{
		StartLocation = StartLocation + Velocity.GetSafeNormal() * MoveDistance;  //normally you would do StartLocation = CurrLocation but there is overflow sometimes
		Velocity *= -1;
		GetOwner()->SetActorLocation(StartLocation);
	}
	else GetOwner()->SetActorLocation(CurrLocation);
}

void UMovableComponent::RotateActor(float DeltaTime)
{
	GetOwner()->AddActorLocalRotation(Rotation * DeltaTime);
}


// Called every frame
void UMovableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ShouldMove) MoveActor(DeltaTime);
	if (ShouldRotate) RotateActor(DeltaTime);


	// ...
}

