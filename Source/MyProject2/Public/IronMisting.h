// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MetallicObject.h"
#include "IronMisting.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT2_API UIronMisting : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UIronMisting();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	float detectRange = 300.0f;
	int maxDetectedObjects = 5;
	void DrawLineBetweenLocations(const FVector& StartLocation, const FVector& EndLocation);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
