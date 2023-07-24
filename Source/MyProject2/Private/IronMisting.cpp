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

// Function to calculate the squared distance between two FVectors
float SquaredDistance(const FVector& A, const FVector& B)
{
    return (A - B).SizeSquared();
}

// Custom sorting function to sort FVector array based on distance to a reference FVector
bool SortByDistance(const FVector& A, const FVector& B, const FVector& ReferenceVector)
{
    return SquaredDistance(A, ReferenceVector) < SquaredDistance(B, ReferenceVector);
}

void UIronMisting::DrawLineBetweenLocations(const FVector& StartLocation, const FVector& EndLocation)
{
    // Draw the debug line between the start and end locations
    DrawDebugLine(
        GetOwner()->GetWorld(),
        StartLocation,
        EndLocation,
        FColor::Blue, // Color of the line (you can change this to any other color)
        false, // Persistent lines (false means the line will disappear after one frame)
        -1.0f, // Lifetime (how long the line will persist, -1 means infinite)
        0,
        1.0f // Thickness of the line
    );
}

// Called every frame
void UIronMisting::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	UE_LOG(LogTemp, Warning, TEXT("Start frame"));
	FVector myLocation=GetOwner()->GetRootComponent()->GetComponentLocation();
	TArray <FVector> locations;
	for (int i =0; i<UMetallicObject::metallicObjectPositions.Num();i++)
	{
		FVector metallicLocation = UMetallicObject::metallicObjectPositions[i]->GetComponentLocation();
		if(	abs(myLocation.X-metallicLocation.X) < detectRange &&
			abs(myLocation.Y-metallicLocation.Y) < detectRange &&
			abs(myLocation.Z-metallicLocation.Z) < detectRange
		)
			locations.Add(metallicLocation);
	}
	locations.Sort([myLocation](const FVector& A, const FVector& B)
    {
        return SortByDistance(A, B, myLocation);
    });
	//if(locations.Num()!=0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Mylocation: X = %f, Y = %f, Z = %f"), myLocation.X, myLocation.Y, myLocation.Z);
	}
	for( int i =0 ; i < 5 && i< locations.Num(); i++)
	{
		FVector location = locations[i];
		UE_LOG(LogTemp, Warning, TEXT("Vector: X = %f, Y = %f, Z = %f"), location.X, location.Y, location.Z);
		DrawLineBetweenLocations(myLocation,location);
	} 
	UE_LOG(LogTemp, Warning, TEXT("End frame"));
	// ...
}

