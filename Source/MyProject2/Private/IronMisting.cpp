// Fill out your copyright notice in the Description page of Project Settings.

#include "DrawDebugHelpers.h"
#include "IronMisting.h"

// Sets default values for this component's properties
UIronMisting::UIronMisting()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UIronMisting::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UIronMisting::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector myLocation=GetOwner()->GetActorLocation();
	TArray <UMetallicObject*> metallicObjects;
	
	ProcessMetalObjects(&metallicObjects, UIronMisting::detectRange, UIronMisting::maxDetectedObjects);

	for( UMetallicObject* metallicObject : metallicObjects)
	{
		FVector metalLocation = metallicObject->GetOwner()->GetActorLocation();
		// Draw the debug line between the start and end locations
		DrawDebugLine(
			GetWorld(),
			myLocation,
			metalLocation,
			FColor::Blue, // Color of the line (you can change this to any other color)
			false, // Persistent lines (false means the line will disappear after one frame)
			-1.0f, // Lifetime (how long the line will persist, -1 means infinite)
			0,
			1.0f // Thickness of the line
		);
	}
	// ...
}


void UIronMisting::ProcessMetalObjects(TArray <UMetallicObject*> *metalObjects, float _detectRange, int _maxDetectedObjects)
{
	FVector myLocation=GetOwner()->GetActorLocation();

	for (UMetallicObject *metallicObject:UMetallicObject::metallicObjects)
	{
		FVector metallicLocation = metallicObject->GetOwner()->GetActorLocation();
		if(	abs(myLocation.X-metallicLocation.X) < _detectRange &&
			abs(myLocation.Y-metallicLocation.Y) < _detectRange &&
			abs(myLocation.Z-metallicLocation.Z) < _detectRange)
		{
			metalObjects->Add(metallicObject);
		}
	}

	metalObjects->Sort([myLocation](const UMetallicObject& A, const UMetallicObject& B)
	{
		float DistanceA = FVector::DistSquared((&A)->GetOwner()->GetActorLocation(), myLocation);
		float DistanceB = FVector::DistSquared((&B)->GetOwner()->GetActorLocation(), myLocation);
		return DistanceA < DistanceB;
	});

	if(metalObjects->Num()> _maxDetectedObjects)
	{
		metalObjects->SetNum(_maxDetectedObjects);
	}
}

