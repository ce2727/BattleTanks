// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "TankPlayerController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	if (GetControlledTank())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is possessing: %s"), *GetName(), *GetControlledTank()->GetName());
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is not possessing a tank"), *GetName());
	}

	UE_LOG(LogTemp,Warning,TEXT("%s finds the player tank as: %s"),*GetName(), *GetPlayerTank()->GetName())
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	ATankPlayerController* PlayerController = Cast<ATankPlayerController>(GetWorld()->GetFirstPlayerController());

	//Check that cast worked
	if (PlayerController) //Success cast
	{ 
		return Cast<ATank>(PlayerController->GetPawn());
	}
	else  //Failed cast
	{
		UE_LOG(LogTemp, Error, TEXT("%s could not get player controller due to failed cast!"), *GetName())

	}
	return nullptr;
}