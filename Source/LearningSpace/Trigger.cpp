// Fill out your copyright notice in the Description page of Project Settings.


#include "Trigger.h"

UTrigger::UTrigger()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTrigger::BeginPlay()
{
	Super::BeginPlay();

	SetMover();
	if(!Mover) UE_LOG(LogTemp, Warning, TEXT("Mover Not Found!!!"));

	OnComponentBeginOverlap.AddDynamic(this, &UTrigger::OnOverlapBegin); //Bind event
	OnComponentEndOverlap.AddDynamic(this, &UTrigger::OnOverlapEnd);
}

AActor* UTrigger::FindAcceptableActor(TArray<AActor*> Actors) const
{
	for (AActor* Actor : Actors)
	{
		if (Actor->ActorHasTag(AcceptableTag)) return Actor;
	}

	return nullptr;
}

void UTrigger::SetMoverBP(UMover* NewMover)
{
	Mover = NewMover;
}
void UTrigger::SetMover()
{
	Mover = GetOwner()->FindComponentByClass<UMover>();
}

void UTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	// Not efficient !!
	//TArray<AActor*> Actors;
	//GetOverlappingActors(Actors);
	//AActor* AcceptableActor = FindAcceptableActor(Actors);
	//if (AcceptableActor)
	//{
	//	if (Mover)   //!!! Move only if its not grabbed
	//	{
	//		Mover->SetShouldMove(true);
	//	}
	//	else UE_LOG(LogTemp, Warning, TEXT("Mover Not Found!!!"));
	//}

	UE_LOG(LogTemp, Warning, TEXT("OnOverlapBegin!!!"));
	if (OtherActor->ActorHasTag(AcceptableTag) && Mover) Mover->SetMoverShouldMove(true);


}

void UTrigger::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("OnOverlapEnd!!!"));
	if (OtherActor->ActorHasTag(AcceptableTag) && Mover) Mover->SetMoverShouldMove(false);
}









// Called every frame
//void UTrigger::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//	TArray<AActor*> Actors;
//	GetOverlappingActors(Actors);
//	if (Actors.Num() > 0)
//	{
//		for (AActor* Actor : Actors)
//		{
//			UE_LOG(LogTemp, Warning, TEXT("%s is overlapping"), *Actor->GetActorNameOrLabel());
//		}
//	}
//
//}