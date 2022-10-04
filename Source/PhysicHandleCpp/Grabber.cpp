// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

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

}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UPhysicsHandleComponent* physicHandle;
	physicHandle = GetPhysicHandle();
	if (physicHandle!=nullptr&&physicHandle->GetGrabbedComponent()!=nullptr) 
	{
		FVector targetLocaiton = GetComponentLocation() + GetForwardVector() * HoldDistant;
		FRotator rotator = GetComponentRotation();
		physicHandle->SetTargetLocationAndRotation(targetLocaiton, rotator);
	}
}

bool UGrabber::GrabbableInSearch(FHitResult& hitResult) const {
	FVector start = GetComponentLocation();
	FVector end = start + GetForwardVector() * DistanceGrabber;
	DrawDebugLine(GetWorld(), start, end, FColor::Red, false,1.0f);
	FCollisionQueryParams collision;
	return GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECC_GameTraceChannel2, collision);
};

void UGrabber::Grab() {
	FHitResult hitResult;
	bool isHit = GrabbableInSearch(hitResult);
	if (isHit) {
		UPrimitiveComponent* hitComponent = hitResult.GetComponent();
		hitComponent->WakeAllRigidBodies();
		UPhysicsHandleComponent* physicHandler;
		physicHandler = GetPhysicHandle();
		if (physicHandler != nullptr) {
			physicHandler->GrabComponentAtLocationWithRotation(hitResult.GetComponent(), NAME_None, hitResult.Location,
				GetComponentRotation());
		}
	}
}

void UGrabber::Release() {
	UPhysicsHandleComponent* physicHandle = GetPhysicHandle();
	if (physicHandle->GetGrabbedComponent() != nullptr) {
		physicHandle->ReleaseComponent();
	}
}

UPhysicsHandleComponent* UGrabber::GetPhysicHandle() const {
	UPhysicsHandleComponent* physicHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (physicHandle == nullptr) {
		return nullptr;
	}
	else {
		return physicHandle;
	}
}



