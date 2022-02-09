#include "bn_core.h"
#include "bn_math.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"

#include "common_variable_8x16_sprite_font.h"

#define MAX_SPRITES 32

int main()
{
    bn::core::init();

    bn::sprite_text_generator *text_en_generator = new bn::sprite_text_generator(common::variable_8x16_sprite_font);
    bn::vector<bn::sprite_ptr, MAX_SPRITES> text_sprites = text_en_generator->generate<MAX_SPRITES>(-120, -64, "This is an English text.");

    while(true)
    {
        bn::core::update();
    }
}
