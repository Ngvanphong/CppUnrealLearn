// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomerTrigger.h"

// Sets default values for this component's properties
UCustomerTrigger::UCustomerTrigger()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}
// Called when the game starts
void UCustomerTrigger::BeginPlay()
{
	Super::BeginPlay();
	

}

// Called every frame
void UCustomerTrigger::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);
	if (Actors.Num() > 0) {
		FString name = Actors[0]->GetActorNameOrLabel();
		UE_LOG(LogTemp, Warning, TEXT("Overlapping %s"), *name);
	}
}