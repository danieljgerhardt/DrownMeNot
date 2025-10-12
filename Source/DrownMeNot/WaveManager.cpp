// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveManager.h"

// Sets default values
AWaveManager::AWaveManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWaveManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWaveManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWaveManager::StartNextWave()
{
	CurrentWave++;
	switch (OverallWaveType)
	{
	case EOverallWaveType::ProcedurallyGenerated:
		StartNextProceduralWave(CurrentWave * 3);
		break;
	case EOverallWaveType::EasyWavePreset:
		StartNextEasyWavePreset(CurrentWave);
		break;
	}
}

void AWaveManager::StartNextProceduralWave(int EnemyCount)
{
	SpawnEnemiesForWave(EnemyCount);
}

void AWaveManager::StartNextEasyWavePreset(int WaveNumber)
{
	switch (WaveNumber)
	{
	case 1:
		SpawnEnemiesForWave(2);
		break;
	}
}

void AWaveManager::SpawnEnemiesForWave(int EnemyCount)
{
	if (EnemyPool.Num() == 0 || SpawnPoints.Num() == 0) return;
	for (int i = 0; i < EnemyCount; i++)
	{
		int EnemyIndex = FMath::RandRange(0, EnemyPool.Num() - 1);
		int SpawnPointIndex = FMath::RandRange(0, SpawnPoints.Num() - 1);
		FVector SpawnLocation = SpawnPoints[SpawnPointIndex];
		EnemyPool[EnemyIndex]->SetActorLocation(SpawnLocation);
	}
}


