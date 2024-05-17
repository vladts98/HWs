// Fill out your copyright notice in the Description page of Project Settings.


#include "CppBaseActor.h"

// Sets default values
ACppBaseActor::ACppBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mash = CreateDefaultSubobject<UStaticMeshComponent>("Mash");
	SetRootComponent(Mash);
	Amplitude = 0;
	Frequency = 0;
	InitialLocation = FVector(0,0,0);
}

// Called when the game starts or when spawned
void ACppBaseActor::BeginPlay()
{
	Super::BeginPlay();
	InitialLocation = GetActorLocation();
}

// Called every frame
void ACppBaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ACppBaseActor::SinMovement()
{
	InitialLocation.Z = Amplitude * sin(Frequency * GetWorld()->GetTimeSeconds()) + InitialLocation.Z;
	return InitialLocation;
}
