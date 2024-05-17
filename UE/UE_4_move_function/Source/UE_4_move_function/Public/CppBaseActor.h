// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CppBaseActor.generated.h"

UCLASS()
class UE_4_MOVE_FUNCTION_API ACppBaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACppBaseActor();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mash;

	UPROPERTY(EditAnywhere)
	int Frequency = 0;

	UPROPERTY(EditAnywhere)
	int Amplitude = 0;

	UFUNCTION(BlueprintCallable)
	FVector SinMovement();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FVector InitialLocation;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
