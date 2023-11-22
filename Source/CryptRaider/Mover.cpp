// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Math/UnrealMathUtility.h"


FString Name;
FVector Location;
FString LocationString;
// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();

	Name = (*Owner).GetActorNameOrLabel();

	Location = Owner->GetActorLocation();

	LocationString = Location.ToCompactString();

	StartLocation = Location;
	
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//UE_LOG(LogTemp, Display, TEXT("Owner name: %s"), *Name);
	//UE_LOG(LogTemp, Display, TEXT("%s location: %s"), *Name, *LocationString);

	FVector TargetLocation = StartLocation;
	if (ShouldMove){
		
		TargetLocation = StartLocation + MoveOffset;
		
	}
	FVector CurrentLocation = Owner->GetActorLocation();
	float speed = MoveOffset.Length() / MoveTime;

	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, speed);

	GetOwner()->SetActorLocation(NewLocation);
}

void UMover::SetShouldMove(bool NewShouldMove)
{
	ShouldMove = NewShouldMove;
	//UE_LOG(LogTemp, Display, TEXT("setted to %d") ,NewShouldMove);
}


