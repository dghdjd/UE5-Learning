// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Mover.h"
#include "Trigger.generated.h"

/**
 * 
 */
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LEARNINGSPACE_API UTrigger : public UBoxComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTrigger();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	//Dependency Injection using blueprint, Since we are sure that our owner has only one Mover
	//We can just use FindComponentByClass<UMover> instead;
	UFUNCTION(BlueprintCallable)
	void SetMoverBP(UMover* NewMover);
	void SetMover();
	

private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	AActor* FindAcceptableActor(TArray<AActor*> Actors) const;


	UPROPERTY(EditAnywhere, Category = "Tag")
	FName AcceptableTag;
	UMover* Mover;
	
};
