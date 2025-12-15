// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	SetupGrab();

	SetPhysicsHandle();
	// ...

}

bool UGrabber::GetGrabbableInReach(FHitResult& HitResult) const
{
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * GrabDistance;
	UWorld* World = GetWorld();

	DrawDebugLine(World, Start, End, FColor::Red, false, 5.f);
	DrawDebugSphere(World, End, 10, 10, FColor::Red, false, 5.f);


	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);


	return World->SweepSingleByChannel(HitResult, Start, End, FQuat::Identity, ECC_GameTraceChannel1, Sphere);

}

void UGrabber::Grab()
{
	if (!PhysicsHandle) return;

	//FVector Start = GetComponentLocation();
	//FVector End = Start + GetForwardVector() * GrabDistance;
	//UWorld* World = GetWorld();

	//DrawDebugLine(World, Start, End, FColor::Red, false, 5.f);
	//DrawDebugSphere(World, End, 10, 10, FColor::Red, false, 5.f);

	FHitResult HitResult;
	//FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
	bool HasHit = GetGrabbableInReach(HitResult);

	if (HasHit)
	{
		UE_LOG(LogTemp, Display, TEXT("Hit!!!"));
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 10, FColor::Green, false, 5.f);
		Rotation = HitResult.GetActor()->GetActorRotation();
		PhysicsHandle->GrabComponentAtLocationWithRotation(HitResult.GetComponent(), NAME_None, HitResult.ImpactPoint, Rotation);
		Grabbing = true;
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Nothing Hit"));
	}
}

void UGrabber::Release()
{
	if (!PhysicsHandle) return;
	PhysicsHandle->ReleaseComponent();
	Grabbing = false;
	UE_LOG(LogTemp, Display, TEXT("Released"));
}

void UGrabber::SetSpringArmComponent()
{
	SpringArm = GetOwner()->FindComponentByClass<USpringArmComponent>();
}

void UGrabber::SetPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Warning, TEXT("PhysicsHandle Component Not Found"));
		return;
	}
}


void UGrabber::SetupGrab()
{
	SetSpringArmComponent();
	if (!SpringArm)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spring Arm Component Not Found"));
		return;
	}
	GrabDistance = SpringArm->TargetArmLength * 3;
	HoldDistance = SpringArm->TargetArmLength * 2;
	UE_LOG(LogTemp, Warning, TEXT("Grab Distance %f"), GrabDistance);
	UE_LOG(LogTemp, Warning, TEXT("Hold Distance %f"), HoldDistance);
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Grabbing)
	{
		if (!PhysicsHandle) return;
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}

}

