// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterSelctionWidget.generated.h"

DECLARE_DELEGATE(FOnButtonClicked)

class UButton;

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_3D_API UCharacterSelctionWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

 	void NativeConstruct() override;

public:

	/*Button For Changing CharacterMesh*/
	UPROPERTY(meta = (BindWidget))
    UButton* NextCharacterButton;

	/*Button For Finalising CharacterMesh*/
	UPROPERTY(meta = (BindWidget))
	UButton* SelectCharacter;

	/*Function Binding To Buttons*/
	UFUNCTION()
	void ChangeCharacterButtonClicked();

	UFUNCTION()
	void OnSelectCharacter();

	//Delegates
	FOnButtonClicked ChangeCharcter;
	FOnButtonClicked CharacterSelected;

	
};
