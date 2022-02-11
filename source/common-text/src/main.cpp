#include "bn_core.h"
#include "bn_math.h"
#include "bn_sprite_ptr.h"
#include "bn_string_view.h"
#include "bn_sprite_text_generator.h"

#include "common_variable_8x16_sprite_font.h"
#include "common_sc_variable_16x16_sprite_font.h"
#include "common_tc_variable_16x16_sprite_font.h"
#include "common_hc_variable_16x16_sprite_font.h"
#include "common_jp_variable_16x16_sprite_font.h"
#include "common_kr_variable_16x16_sprite_font.h"

#define LEADING 4
#define MAX_SPRITES 32

int main()
{
    bn::core::init();

    bn::sprite_text_generator *text_en_generator = new bn::sprite_text_generator(common::variable_8x16_sprite_font);
    bn::vector<bn::sprite_ptr, MAX_SPRITES> text_en_sprites = text_en_generator->generate<MAX_SPRITES>(-120, -64, "English");

    bn::sprite_text_generator *text_sc_generator = new bn::sprite_text_generator(common::sc::variable_16x16_sprite_font);
    bn::vector<bn::sprite_ptr, MAX_SPRITES> text_sc_sprites = text_sc_generator->generate<MAX_SPRITES>(-120, -48 + LEADING, "sc 简体中文");

    bn::sprite_text_generator *text_tc_generator = new bn::sprite_text_generator(common::tc::variable_16x16_sprite_font);
    bn::vector<bn::sprite_ptr, MAX_SPRITES> text_tc_sprites = text_tc_generator->generate<MAX_SPRITES>(-120, -32 + LEADING * 2, "tc 繁體中文（台灣）");

    bn::sprite_text_generator *text_hc_generator = new bn::sprite_text_generator(common::hc::variable_16x16_sprite_font);
    bn::vector<bn::sprite_ptr, MAX_SPRITES> text_hc_sprites = text_hc_generator->generate<MAX_SPRITES>(-120, -16 + LEADING * 3, "hc 繁體中文（香港）");

    bn::sprite_text_generator *text_jp_generator = new bn::sprite_text_generator(common::jp::variable_16x16_sprite_font);
    bn::vector<bn::sprite_ptr, MAX_SPRITES> text_jp_sprites = text_jp_generator->generate<MAX_SPRITES>(-120, 0 + LEADING * 4, "jp 日本語 にほんご");

    bn::sprite_text_generator *text_kr_generator = new bn::sprite_text_generator(common::kr::variable_16x16_sprite_font);
    bn::vector<bn::sprite_ptr, MAX_SPRITES> text_kr_sprites = text_kr_generator->generate<MAX_SPRITES>(-120, 16 + LEADING * 5, "kr 한국어");

    while(true)
    {
        bn::core::update();
    }
}
