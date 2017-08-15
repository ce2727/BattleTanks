// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATank* GetControlledTank() const;
	virtual void BeginPlay() override;

private:
	virtual void Tick(float DeltaTime);

	//Aim the tank's barrel towards where the crosshair intersects the world
	void AimTowardsCrosshair();
	
	//Out params - updates location of where the crosshair hits the environment
	bool GetSightRayHitLocation(FVector &OutHitLocation) const;

	//Updates with look data
	bool GetLookVectorDirection(FVector2D ScreenLocation, FVector &LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const;

	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5;
	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.33333;
	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000;
};
