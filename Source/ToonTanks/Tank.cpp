// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ATank::ATank()
{
    PrimaryActorTick.bCanEverTick = true;

    spr_comp = CreateDefaultSubobject<USpringArmComponent>(TEXT("camera spring"));
    spr_comp->SetupAttachment(RootComponent);

    cam_comp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    cam_comp->SetupAttachment(spr_comp);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	playerControlRef = Cast<APlayerController>(GetController());
    //playerControlRef->GetHitResultUnderCursor();
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    FHitResult hitRes;
    if(playerControlRef)
    {
        playerControlRef->GetHitResultUnderCursor(
            ECollisionChannel::ECC_Visibility,
            false,
            hitRes
        );
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("NO PLAYERCONTROLLERREFERENCE!"));
    }

    DrawDebugSphere(
        GetWorld(),
        hitRes.ImpactPoint,
        10,
        10,
        FColor::Blue);
    
    RotateTurret(hitRes.ImpactPoint, turnSpeed);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &ATank::Move);
    PlayerInputComponent->BindAxis("Turn", this, &ATank::Turn);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ABasePawn::Fire);
}

void ATank::Move(float status)
{
    //UE_LOG(LogTemp, Display, TEXT("the status is: %f"), status);
    FVector offset(0.f);
    offset.X = status;
    AddActorLocalOffset(speed * UGameplayStatics::GetWorldDeltaSeconds(this) * offset, true);
}

void ATank::Turn(float status)
{
    FRotator rot = FRotator(0.f);
    rot.Yaw += UGameplayStatics::GetWorldDeltaSeconds(this) * RotSpeed * status;
    AddActorLocalRotation(rot);
}