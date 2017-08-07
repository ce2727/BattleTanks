// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"


void ATankPlayerController::BeginPlay()
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
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
	
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; //Out parameter
	if (GetSightRayHitLocation(HitLocation)) //Has side effect, it's going to linetrace
	{
		GetControlledTank()->AimAt(HitLocation);
	}

}

//Get world location of linetrace through crosshair
bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const
{
	//Find crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX,ViewportSizeY); //Get viewport scaling data

	float ScreenX = CrosshairXLocation * ViewportSizeX;
	float ScreenY = CrosshairYLocation * ViewportSizeY;//Apply it to the crosshair's screen proportions
	auto CrosshairScreenLocation = FVector2D(ScreenX, ScreenY);
	//Deproject from screen to return a look direction

	FVector OutLookDirection;
	GetLookVectorDirection(CrosshairScreenLocation, OutLookDirection);//Set outlookdirection
	GetLookVectorHitLocation(OutLookDirection, OutHitLocation);//Apply outlookdirection to set outhitlocation
	return true;
}

//Set look direction using engine de-project
bool ATankPlayerController::GetLookVectorDirection(FVector2D ScreenLocation, FVector &LookDirection) const
{
	FVector LookLocation; 	//Discarded
	if (!DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, LookLocation, LookDirection)) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Unable to deproject from screen (TankPlayerController::GetLookLocation)"))
	}
	return true;
}


bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const
{
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + (LookDirection * LineTraceRange);
	FHitResult HitResult;

	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResult.Location;
	}
	return false;
	



	HitLocation = HitResult.Location;
	return true;
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

