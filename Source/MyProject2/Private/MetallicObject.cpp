// Fill out your copyright notice in the Description page of Project Settings.


#include "MetallicObject.h"


TArray<UMetallicObject*> UMetallicObject::metallicObjects;

// Sets default values for this component's properties
UMetallicObject::UMetallicObject()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMetallicObject::BeginPlay()
{
	Super::BeginPlay();
	metallicObjects.Add(this);
	
}


// Called every frame
void UMetallicObject::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

void UMetallicObject::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	metallicObjects.Remove(this);
}