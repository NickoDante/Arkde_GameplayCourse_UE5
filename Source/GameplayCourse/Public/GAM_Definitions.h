// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(Blueprintable)
enum class EGAM_Difficulty : uint8
{
	Easy,
	Medium,
	Hard
};

static FName GetDifficultyAsName(const EGAM_Difficulty Difficulty)
{
	FName Result = NAME_None;
	switch (Difficulty)
	{
		case EGAM_Difficulty::Easy:
			Result = FName("Easy");
			break;
		case EGAM_Difficulty::Medium:
			Result = FName("Medium");
			break;
		case EGAM_Difficulty::Hard:
			Result = FName("Hard");
			break;
		default:
			break;
	}
	
	return Result;
}