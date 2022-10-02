// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::BeginPlay()
{
    Super::BeginPlay();

    tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition , fireRate, true);
}

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(FVector::Dist(tank->GetActorLocation(), GetActorLocation()) < fireDistance)
    {
        RotateTurret(tank->GetActorLocation(), turnSpeed);
    }

}

void ATower::CheckFireCondition()
{
    if(FVector::Dist(tank->GetActorLocation(), GetActorLocation()) < fireDistance)
    {
        Fire();
    }
}