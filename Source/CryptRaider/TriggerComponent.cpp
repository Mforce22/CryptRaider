// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"



// Sets default values for this component's properties
UTriggerComponent::UTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
    UE_LOG(LogTemp, Display, TEXT("New component"));
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    AActor* Key = GetAcceptableActor();

    if(Mover == nullptr){
        UE_LOG(LogTemp, Error, TEXT("No mover found"));
        return;
    }

    if(Key != nullptr){
        
        UPrimitiveComponent* component = Cast<UPrimitiveComponent>(Key->GetRootComponent());
        if(component != nullptr){
            component->SetSimulatePhysics(false);
        }

        Key->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
        Mover->SetShouldMove(true);
    }
    else{
        
        Mover->SetShouldMove(false);
    }
}

AActor* UTriggerComponent::GetAcceptableActor() const
{
    TArray<AActor*> OverlappingActors;
    GetOverlappingActors(OverlappingActors);

    if(OverlappingActors.Num() > 0){
        for(AActor* Actor : OverlappingActors){
            bool hasTag = Actor->ActorHasTag(TargetTag);
            bool isGrabbed = Actor->ActorHasTag("Grabbed");
            if(hasTag && !isGrabbed){
                return Actor;
            }

        }
    }
    return nullptr;
}

void UTriggerComponent::setMover(UMover* mover)
{
    this->Mover = mover;
}