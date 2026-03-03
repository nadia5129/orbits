#include <bn_core.h>
#include <bn_backdrop.h>
#include <bn_color.h>
#include <bn_keypad.h>
#include <bn_fixed_point.h>
#include <bn_sprite_ptr.h>
#include <bn_vector.h>
#include <bn_random.h>
#include <bn_regular_bg_ptr.h>
#include "bn_regular_bg_items_space.h"
#include <bn_music_items.h>

#include "bn_sprite_items_dot.h"
#include "movement.h"
#include "Center.h"
#include "orbiter.h"


// Maximum number of orbiters allowed on the screen
static constexpr int MAX_ORBITERS = 30;

// Default starting posiiton and velocity for Orbiter
static constexpr bn::fixed_point ORBITER_START_POSIITON = {0, 0};
static constexpr bn::fixed_point ORBITER_START_VELOCITY = {0, 5};



int main() {
    bn::core::init();
    bn::regular_bg_ptr bg = bn::regular_bg_items::space.create_bg(0, 0);
   
    bn::music_items::galaxy.play();

    Center center = Center({30, 40}, .05, 2);
    bn::vector<Orbiter, MAX_ORBITERS> orbiters = {};

    bn::random rng;
    
    while(true) {
        // Add an orbiter when A is pressed if there's room
        if(bn::keypad::a_pressed()) {
            if(orbiters.size() < MAX_ORBITERS) {
                int planet_id = rng.get_int(0, 3); 
        orbiters.push_back(Orbiter(ORBITER_START_POSIITON, ORBITER_START_VELOCITY, center, planet_id));
    }
        }

        // Remove an orbiter when B is pressed if there's at least one
        if (bn::keypad::b_pressed()) {
            if(orbiters.size() > 0) {
                orbiters.pop_back();
            }
        }

        center.update();
        for(Orbiter& orbiter : orbiters) {
            orbiter.update();
        }

        bn::core::update();
    }
}