#include "orbiter.h"

#include <bn_fixed.h>
#include <bn_random.h>
#include "Center.h"
#include "bn_sprite_items_dot.h"
#include "bn_sprite_items_planetone.h"
#include "bn_sprite_items_planetthree.h"
#include "bn_sprite_items_planettwo.h"
#include "bn_sprite_items_planetfour.h"

// A scaling factor by which to reduce the force applied when orbiting
// Important for numerical stability
static constexpr bn::fixed FORCE_SCALE = 10;

Orbiter::Orbiter(bn::fixed_point starting_location,
                 bn::fixed_point starting_velocity,
                 Center& center,
                 int planet_id) :
    _sprite(bn::sprite_items::planetone.create_sprite(starting_location)), 
    _velocity(starting_velocity),
    _center(center)
{
    if(planet_id == 1) {
        _sprite = bn::sprite_items::planettwo.create_sprite(starting_location);
    } else if(planet_id == 2) {
        _sprite = bn::sprite_items::planetthree.create_sprite(starting_location);
    } else if(planet_id == 3) {
        _sprite = bn::sprite_items::planetfour.create_sprite(starting_location);
    }
}

void Orbiter::update()
{
    bn::fixed_point delta = _center.position() - _sprite.position();

    bn::fixed_point force = delta * _center.mass();
    force /= FORCE_SCALE;

    _velocity += force;
    _sprite.set_position(_sprite.position() + _velocity);
}