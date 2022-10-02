// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
public:
	ATank();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* spr_comp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* cam_comp;
	
	void Move(float status);
	void Turn(float status);

	UPROPERTY(EditInstanceOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float speed;

	UPROPERTY(EditInstanceOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float RotSpeed;

	UPROPERTY(EditInstanceOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float turnSpeed;

	class APlayerController* playerControlRef;
public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
