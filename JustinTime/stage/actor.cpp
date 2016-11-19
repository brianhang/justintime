#include "actor.h"

Actor::~Actor() { }

void Actor::remove() {
    dying = true;
}

bool Actor::isDying() {
    return dying;
}