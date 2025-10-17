// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveManager.h"

// Sets default values
AWaveManager::AWaveManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = RootComp;

	SpawnPointSceneComponents.Reserve(NumSpawnPoints);

	for (int i = 0; i < NumSpawnPoints; i++) {
		USceneComponent* NewSpawnPoint = CreateDefaultSubobject<USceneComponent>(*FString::Printf(TEXT("SpawnPoint%d"), i));
		NewSpawnPoint->SetupAttachment(RootComponent);
		NewSpawnPoint->SetRelativeLocation(FVector(i * 200.0f, 0.0f, 0.0f)); // Example spacing
		SpawnPointSceneComponents.Add(NewSpawnPoint);
	}
}

// Called when the game starts or when spawned
void AWaveManager::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < NumSpawnPoints; i++) {
		if (SpawnPointSceneComponents.IsValidIndex(i) && SpawnPointSceneComponents[i]) {
			SpawnPointLocations.Add(SpawnPointSceneComponents[i]->GetComponentLocation());
		}
	}

	StartNextWave();
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
		SpawnEnemiesForWave(6);
		break;
	}
}

void AWaveManager::SpawnEnemiesForWave(int EnemyCount)
{
	for (int i = 0; i < EnemyCount; i++)
	{
		int SpawnPointIndex = FMath::RandRange(0, SpawnPointLocations.Num() - 1);
		FVector SpawnLocation = SpawnPointLocations[SpawnPointIndex];
		
		//create new enemy of random class from pool
		if (EnemyClassPool.Num() > 0)
		{
			int EnemyClassIndex = FMath::RandRange(0, EnemyClassPool.Num() - 1);
			TSubclassOf<ACharacterBase> EnemyClass = EnemyClassPool[EnemyClassIndex];
			ACharacterBase* NewEnemy = GetWorld()->SpawnActor<ACharacterBase>(EnemyClass, SpawnLocation, FRotator::ZeroRotator);
			NewEnemy->OnDeath.AddDynamic(this, &AWaveManager::OnCharacterDied);

		}
	}
}

void AWaveManager::OnCharacterDied()
{
	//print debug message for testing

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Hello from AddOnScreenDebugMessage!"));
}


