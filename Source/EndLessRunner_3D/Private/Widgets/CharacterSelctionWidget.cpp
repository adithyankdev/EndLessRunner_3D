// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CharacterSelctionWidget.h"
#include "Components/Button.h"


//Binding Buttons And Functions
void UCharacterSelctionWidget::NativeConstruct()
{
	NextCharacterButton->OnClicked.AddDynamic(this, &UCharacterSelctionWidget::ChangeCharacterButtonClicked);

	SelectCharacter->OnClicked.AddDynamic(this, &UCharacterSelctionWidget::OnSelectCharacter);
}

void UCharacterSelctionWidget::ChangeCharacterButtonClicked()
{
	ChangeCharcter.ExecuteIfBound();
}

void UCharacterSelctionWidget::OnSelectCharacter()
{
	CharacterSelected.ExecuteIfBound();
}
