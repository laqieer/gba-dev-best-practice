#include "bn_core.h"
#include "bn_math.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_double_size_mode.h"
#include "bn_sprite_items_fantasy_knight.h"

int main()
{
    bn::core::init();
    bn::sprite_ptr sprite = bn::sprite_items::fantasy_knight.create_sprite(0, 0);
    bn::sprite_ptr sprite_horizontal_flipped = bn::sprite_items::fantasy_knight.create_sprite(0, 0);
    bn::sprite_ptr sprite_vertical_flipped = bn::sprite_items::fantasy_knight.create_sprite(0, 0);
    bn::sprite_ptr sprite_scaled = bn::sprite_items::fantasy_knight.create_sprite(0, 0);
    bn::sprite_ptr sprite_rotated_45 = bn::sprite_items::fantasy_knight.create_sprite(0, 0);
    bn::sprite_ptr sprite_rotated_90 = bn::sprite_items::fantasy_knight.create_sprite(0, 0);
    sprite.set_position(-120 + 16, 80 - 32);
    sprite_horizontal_flipped.set_position(sprite.x() + 32, 80 - 32);
    sprite_vertical_flipped.set_position(sprite_horizontal_flipped.x() + 32, 80 - 32 + 64 - 40);
    sprite_scaled.set_position(sprite_vertical_flipped.x() + 32, 80 - 32 * 2);
    sprite_rotated_45.set_position(sprite_scaled.x() + 32, 80 - 32);
    sprite_rotated_90.set_position(sprite_rotated_45.x() + 32, 80 - 32);
    sprite_horizontal_flipped.set_horizontal_flip(true);
    sprite_vertical_flipped.set_vertical_flip(true);
    sprite_scaled.set_scale(2);
    sprite_rotated_45.set_rotation_angle(45);
    sprite_rotated_90.set_rotation_angle(90);
    sprite_rotated_90.set_double_size_mode(bn::sprite_double_size_mode::ENABLED);

    while(true)
    {
        bn::core::update();
    }
}
