// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	
	PrimaryComponentTick.bCanEverTick = true;
	SetComponentTickEnabled(false);


	//UE_LOG(LogTemp, Error, TEXT("Mover %s is alive"), *GetOwner()->GetActorNameOrLabel());
	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	MoverStartLocation = GetOwner()->GetActorLocation();

	MoverSpeed = FVector::Dist(MoverStartLocation, MoverStartLocation + MoverMoveOffset) / MoverMoveTime;

	// ...

}

void UMover::UpdateLocation(FVector& CurrLocation, FVector TargetLocation, float DeltaTime)
{
	
	
	FVector NewLocation = FMath::VInterpConstantTo(CurrLocation, TargetLocation, DeltaTime, MoverSpeed);

	GetOwner()->SetActorLocation(NewLocation);
}

void UMover::SetMoverShouldMove(bool m)
{
	MoverShouldMove = m;
	
	UE_LOG(LogTemp, Error, TEXT(" %s is Setting Tick"), *this->GetOwner()->GetFullName());
	SetComponentTickEnabled(true);
}

// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector CurrLocation = GetOwner()->GetActorLocation();
	FVector TargetLocation;
	

	if (MoverShouldMove)
	{
		TargetLocation = MoverStartLocation + MoverMoveOffset;
		UpdateLocation(CurrLocation, TargetLocation, DeltaTime);
	}
	else
	{
		TargetLocation = MoverStartLocation;
		UpdateLocation(CurrLocation, TargetLocation, DeltaTime);
	}

	if (FVector::Dist(CurrLocation, TargetLocation) <= MoverDistTolerance)
	{
		SetComponentTickEnabled(false);
		UE_LOG(LogTemp, Warning, TEXT("Mover stopped ticking"));
	}
	// ...
}







