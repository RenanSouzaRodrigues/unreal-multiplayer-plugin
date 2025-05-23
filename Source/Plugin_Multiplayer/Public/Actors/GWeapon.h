﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GWeapon.generated.h"

// Enum used to defined the current state of the weapon. -Renan
UENUM(Blueprintable, BlueprintType)
enum class EGWeaponState : uint8 {
	Default,
	Equipped,
	Dropped,
};

// Enum used to define the weapon type of fire
UENUM(Blueprintable, BlueprintType)
enum class EGWeaponFireType : uint8 {
	Rifle,
	Assault,
	Rocket
};

UCLASS()
class PLUGIN_MULTIPLAYER_API AGWeapon : public AActor {
	GENERATED_BODY()

	// ==================================================
	// Unreal Methods
	// ==================================================
public:
	AGWeapon();
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	
	// ==================================================
	// Actor Core Components
	// ==================================================
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Actor Components")
	TObjectPtr<class USphereComponent> PlayerDetectionSphere;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Actor Components")
	TObjectPtr<class UStaticMeshComponent> WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Actor Components")
	TObjectPtr<class UWidgetComponent> PickupWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Actor Components")
	EGWeaponFireType WeaponFireType { EGWeaponFireType::Rifle };

public:
	FORCEINLINE EGWeaponFireType GetWeaponFireType() { return this->WeaponFireType; }
	

	
	// ==================================================
	// Weapon State
	// ==================================================
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, ReplicatedUsing=OnRep_SetWeaponState)
	EGWeaponState CurrentWeaponState { EGWeaponState::Default };

public:
	UFUNCTION(BlueprintCallable)
	void SetWeaponState(EGWeaponState newState);

protected:
	UFUNCTION()
	void OnRep_SetWeaponState(EGWeaponState lastState);
	

	
	// ==================================================
	// Pickup Widget
	// ==================================================
public:
	UFUNCTION()
	virtual void OnDetectPlayerSphereBeginOverlap(class UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnDetectPlayerSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);
	
	UFUNCTION(BlueprintCallable)
	void ShowInteractionHud(bool value); // This is a bad way of doing things, but replication is on the character at this points. -Renan



	// ==================================================
	// Weapon Fire
	// ==================================================
public:
	virtual void Fire(const FVector_NetQuantize& hitTarget);
};
