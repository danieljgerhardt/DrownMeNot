// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DrownMeNot/GameplayAbilitySystem/Characters/CharacterBase.h"
#include "Containers/Array.h"
#include "WaveManager.generated.h"

UENUM(BlueprintType)
enum class EOverallWaveType : uint8
{
	ProcedurallyGenerated UMETA(DisplayName = "ProcedurallyGenerated"),
	EasyWavePreset UMETA(DisplayName = "EasyWavePreset"),
};

UCLASS()
class DROWNMENOT_API AWaveManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaveManager();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave Characteristics")
	int TotalWaveCount;
	
	// List of classes an enemy can be spawned from
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave Characteristics")
	TArray<TSubclassOf<ACharacterBase>> EnemyClassPool;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave Characteristics")
	EOverallWaveType OverallWaveType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TArray<USceneComponent*> SpawnPointSceneComponents;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawn Parameters")
	TArray<FVector> SpawnPointLocations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Parameters")
	int NumSpawnPoints = 3;
private:
	int CurrentWave = 0;
	int NumEnemiesKilledThisWave = 0;
	int EnemyCountThisWave = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void StartNextWave();

private:
	void StartNextProceduralWave(int EnemyCount);
	void StartNextEasyWavePreset(int WaveNumber);

	void SpawnEnemiesForWave(int EnemyCount);

	void ProcessWaveEnd();

	UFUNCTION()
	void OnCharacterDied();

};
