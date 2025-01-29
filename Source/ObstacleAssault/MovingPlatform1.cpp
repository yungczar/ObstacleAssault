// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform1.h"

// Sets default values
AMovingPlatform1::AMovingPlatform1()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform1::BeginPlay()
{
	Super::BeginPlay();

	

	StartLocation = GetActorLocation();

	FString Name = GetName();

	UE_LOG(LogTemp, Display, TEXT("BeginPlay: %s"),*Name);
	

	
}

// Called every frame
void AMovingPlatform1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);

}

	


void AMovingPlatform1::MovePlatform(float DeltaTime){


	if(ShouldPlatformReturn()){

		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation + MoveDirection * MovedDistance;
		SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity;

	}

	else
	{	
			
		FVector CurrentLocation = GetActorLocation();
		CurrentLocation = CurrentLocation + (PlatformVelocity * DeltaTime);
		SetActorLocation(CurrentLocation);
	}
}

void AMovingPlatform1::RotatePlatform(float DeltaTime)
{
	
	AddActorLocalRotation(RotationVelocity * DeltaTime);

}

bool AMovingPlatform1::ShouldPlatformReturn() const
{	
	return GetMovedDistance() > MovedDistance;
}

float AMovingPlatform1::GetMovedDistance() const
{
	return FVector::Dist(StartLocation, GetActorLocation());
}


