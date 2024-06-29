// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerInputComponent.h"
#include "InputMappingContext.h"
#include "InputModifiers.h"
#include "InputAction.h"


void UPlayerInputComponent::SetupInputBindings()
{
    PlayerMappingContext = NewObject<UInputMappingContext>(this);
    MoveInput = NewObject<UInputAction>(this);
    JumpInput = NewObject<UInputAction>(this);

    MoveInput->ValueType = EInputActionValueType::Axis1D;
    PlayerMappingContext->MapKey(MoveInput, EKeys::Right);
    FEnhancedActionKeyMapping& Mapping = PlayerMappingContext->MapKey(MoveInput, EKeys::Left);
    UInputModifierNegate* Negate = NewObject<UInputModifierNegate>(this);
    Mapping.Modifiers.Add(Negate);

    JumpInput->ValueType = EInputActionValueType::Boolean;
    PlayerMappingContext->MapKey(JumpInput, EKeys::Up);
}
