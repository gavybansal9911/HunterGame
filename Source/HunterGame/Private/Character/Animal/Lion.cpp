// Hunter Game by Gamer Guru.


#include "Character/Animal/Lion.h"

ALion::ALion()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ALion::BeginPlay()
{
    Super::BeginPlay();
}

void ALion::Tick(float DeltaSeconds)
{
    // bCanEverTick is set to false
    Super::Tick(DeltaSeconds);
}
