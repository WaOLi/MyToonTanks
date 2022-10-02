// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	capsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = capsuleComp;

	Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base"));
	Base->SetupAttachment(capsuleComp);

	Turret = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret"));
	Turret->SetupAttachment(Base);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(Turret);
}

void ABasePawn::RotateTurret(const FVector& lookAt, float turnSpeed)
{
    FVector dirVec = lookAt - Turret->GetComponentLocation();
	FRotator turretOri = FRotator(0.f, dirVec.Rotation().Yaw, 0.f);
	FRotator temp = FMath::RInterpConstantTo(Turret->GetComponentRotation(), turretOri, UGameplayStatics::GetWorldDeltaSeconds(this), turnSpeed);
	Turret->SetWorldRotation(temp);
}

void ABasePawn::Fire()
{
	DrawDebugBox(GetWorld(), ProjectileSpawnPoint->GetComponentLocation(), FVector(20.f, 20.f, 20.f), FColor::Red, false, 10);
}