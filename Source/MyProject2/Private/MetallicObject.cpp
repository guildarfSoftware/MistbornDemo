// Fill out your copyright notice in the Description page of Project Settings.


#include "MetallicObject.h"


TArray<USceneComponent*> UMetallicObject::metallicObjectPositions;

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
	metallicObjectPositions.Add(GetOwner()->GetRootComponent());
	UE_LOG(LogTemp, Warning, TEXT("New Metallic object created"));
	    // Loop through the array and display the content on the screen
    for (int32 Index = 0; Index < metallicObjectPositions.Num(); Index++)
    {
        USceneComponent* SceneComponent = metallicObjectPositions[Index];
        if (SceneComponent)
        {
            // Format the message with the index and position of the component
            FString Message = FString::Printf(TEXT("Index: %d, Position: %s"), Index, *SceneComponent->GetComponentLocation().ToString());

            // Display the message on the screen using OnScreenDebugMessage
            FColor Color = FColor::Green;
            float TimeToDisplay = 5.0f;
            FVector2D ScreenPosition = FVector2D(2.0f, 2.0f);

            GEngine->AddOnScreenDebugMessage(Index, TimeToDisplay, Color, Message, false, ScreenPosition);
        }
    }
	// ...
	
}


// Called every frame
void UMetallicObject::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

void UMetallicObject::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	AActor *actor = GetOwner();
	metallicObjectPositions.Remove((actor->GetRootComponent()));
}