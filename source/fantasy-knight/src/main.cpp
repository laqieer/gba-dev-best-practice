#include "bn_core.h"
#include "bn_math.h"
#include "bn_keypad.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_double_size_mode.h"
#include "bn_sprite_items_fantasy_knight.h"
#include "bn_sprite_tiles_items_fantasy_knight_running.h"
#include "bn_sprite_animate_actions.h"
#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_items_futurism_background.h"
#include "bn_affine_bg_ptr.h"
#include "bn_affine_bg_items_mystical_symbol.h"

bn::sprite_ptr *sprite;
bn::sprite_animate_action<10> *sprite_action;
bn::regular_bg_ptr *regular_bg;
bn::affine_bg_ptr *affine_bg;

void init_sprite();
void init_regular_bg();
void init_affine_bg();
void reset_sprite();
void reset_regular_bg();
void reset_affine_bg();
void handle_user_input();
void update_actions();

int main()
{
    bn::core::init();
    init_sprite();
    init_regular_bg();
    init_affine_bg();

    while(true)
    {
        handle_user_input();
        update_actions();
        bn::core::update();
    }
}

void init_sprite()
{
    sprite = new bn::sprite_ptr(bn::sprite_items::fantasy_knight.create_sprite(0, 0));
    sprite->set_double_size_mode(bn::sprite_double_size_mode::ENABLED);
    sprite->set_bg_priority(0);
    sprite_action = new bn::sprite_animate_action<10>(bn::create_sprite_animate_action_forever(*sprite, 3, bn::sprite_tiles_items::fantasy_knight_running, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9));
}

void init_regular_bg()
{
    regular_bg = new bn::regular_bg_ptr(bn::regular_bg_items::futurism_background.create_bg(0, 0));
}

void init_affine_bg()
{
    affine_bg = new bn::affine_bg_ptr(bn::affine_bg_items::mystical_symbol.create_bg(0, 0));
    affine_bg->set_priority(2);
    affine_bg->set_wrapping_enabled(false);
}

void reset_sprite()
{
    sprite->set_position(0, 0);
    sprite->set_horizontal_flip(false);
}

void reset_regular_bg()
{
    regular_bg->set_y(0);
}

void reset_affine_bg()
{
    affine_bg->set_position(0, 0);
    affine_bg->set_horizontal_flip(false);
    affine_bg->set_scale(1);
    affine_bg->set_rotation_angle(0);
}

void handle_user_input()
{
    // Start键: 复位
    if(bn::keypad::start_pressed())
    {
        reset_sprite();
        reset_regular_bg();
        reset_affine_bg();
    }

    // 十字键向上
    if(bn::keypad::up_held())
    {
        // 按住L键: 场景下移
        if(bn::keypad::l_held())
        {
            if(regular_bg->y() < 48)
            {
                regular_bg->set_y(regular_bg->y() + 1);
                sprite->set_y(sprite->y() + 1);
                affine_bg->set_y(sprite->y());
            }
        }
        // 否则: 人物上移
        else
        {
            if(sprite->y() > regular_bg->y())
            {
                sprite->set_y(sprite->y() - 1);
                affine_bg->set_y(sprite->y());
            }
        }
    }

    // 十字键向下
    if(bn::keypad::down_held())
    {
        // 按住L键: 场景上移
        if(bn::keypad::l_held())
        {
            if(regular_bg->y() > -48)
            {
                regular_bg->set_y(regular_bg->y() - 1);
                sprite->set_y(sprite->y() - 1);
                affine_bg->set_y(sprite->y());
            }
        }
        // 否则: 人物下移
        else
        {
            if(sprite->y() - regular_bg->y() < 96)
            {
                sprite->set_y(sprite->y() + 1);
                affine_bg->set_y(sprite->y());
            }
        }
    }

    // 十字键向左: 左移
    if(bn::keypad::left_held() && sprite->x() > -120)
    {
        sprite->set_x(sprite->x() - 1);
        affine_bg->set_x(sprite->x());
        sprite->set_horizontal_flip(true);
        affine_bg->set_horizontal_flip(true);
    }

    // 十字键向右: 右移
    if(bn::keypad::right_held() && sprite->x() < 120)
    {
        sprite->set_x(sprite->x() + 1);
        affine_bg->set_x(sprite->x());
        sprite->set_horizontal_flip(false);
        affine_bg->set_horizontal_flip(false);
    }

    // A键: 魔法阵放大
    if(bn::keypad::a_held() && affine_bg->horizontal_scale() < 2)
    {
        affine_bg->set_scale(affine_bg->horizontal_scale() + 0.1);
    }

    // B键: 魔法阵缩小
    if(bn::keypad::b_held() && affine_bg->horizontal_scale() > 0.1)
    {
        affine_bg->set_scale(affine_bg->horizontal_scale() - 0.1);
    }

    // Select键: 魔法阵旋转
    if(bn::keypad::select_held())
    {
        affine_bg->set_rotation_angle((affine_bg->rotation_angle().integer() + 5) % 360);
    }
}

void update_actions()
{
    sprite_action->update();
}