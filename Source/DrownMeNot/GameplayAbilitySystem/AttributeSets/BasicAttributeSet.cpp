// Fill out your copyright notice in the Description page of Project Settings.


#include "DrownMeNot/GameplayAbilitySystem/AttributeSets/BasicAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"

UBasicAttributeSet::UBasicAttributeSet()
	: Health(100.f)
	, MaxHealth(100.f)
	, Mana(100.f)
	, MaxMana(100.f)
{
}

void UBasicAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UBasicAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBasicAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBasicAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBasicAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

void UBasicAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute()) {
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	else if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
}

void UBasicAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(GetHealth());
	}
	else if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(GetMana());
	}
}
