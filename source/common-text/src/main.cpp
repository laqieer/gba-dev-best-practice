#include "bn_core.h"
#include "bn_math.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"

#include "common_variable_8x16_sprite_font.h"
#include "common_cn_variable_16x16_sprite_font.h"

#define MAX_SPRITES 32

int main()
{
    bn::core::init();

    bn::sprite_text_generator *text_en_generator = new bn::sprite_text_generator(common::variable_8x16_sprite_font);
    bn::vector<bn::sprite_ptr, MAX_SPRITES> text_sprites = text_en_generator->generate<MAX_SPRITES>(-120, -64, "This is an English text.");

    bn::sprite_text_generator *text_cn_generator = new bn::sprite_text_generator(common::cn::variable_16x16_sprite_font);
    bn::vector<bn::sprite_ptr, MAX_SPRITES> text_cn_sprites = text_cn_generator->generate<MAX_SPRITES>(-120, -48, "这是一段中文文本。");

    while(true)
    {
        bn::core::update();
    }
}
