#include "bn_core.h"
#include "bn_math.h"
#include "bn_keypad.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_double_size_mode.h"
#include "bn_sprite_items_fantasy_knight.h"

bn::sprite_ptr *sprite;

void init_sprite();
void handle_user_input();

int main()
{
    bn::core::init();
    init_sprite();

    while(true)
    {
        handle_user_input();
        bn::core::update();
    }
}

void init_sprite()
{
    sprite = new bn::sprite_ptr(bn::sprite_items::fantasy_knight.create_sprite(0, 0));
    sprite->set_double_size_mode(bn::sprite_double_size_mode::ENABLED);
}

void handle_user_input()
{
    // Start键: 复位
    if(bn::keypad::start_pressed())
    {
        sprite->set_position(0, 0);
        sprite->set_horizontal_flip(false);
        sprite->set_vertical_flip(false);
        sprite->set_scale(1);
        sprite->set_rotation_angle(0);
    }

    // 十字键向上: 上移
    if(bn::keypad::up_held() && sprite->y() > -80)
    {
        sprite->set_y(sprite->y() - 1);
    }

    // 十字键向下: 下移
    if(bn::keypad::down_held() && sprite->y() < 80)
    {
        sprite->set_y(sprite->y() + 1);
    }

    // 十字键向左: 左移
    if(bn::keypad::left_held() && sprite->x() > -120)
    {
        sprite->set_x(sprite->x() - 1);
    }

    // 十字键向右: 右移
    if(bn::keypad::right_held() && sprite->x() < 120)
    {
        sprite->set_x(sprite->x() + 1);
    }

    // L键: 水平翻折
    if(bn::keypad::l_pressed())
    {
        sprite->set_horizontal_flip(!sprite->horizontal_flip());
    }

    // R键: 垂直翻折
    if(bn::keypad::r_pressed())
    {
        sprite->set_vertical_flip(!sprite->vertical_flip());
    }

    // A键: 放大
    if(bn::keypad::a_held() && sprite->horizontal_scale() < 2)
    {
        sprite->set_scale(sprite->horizontal_scale() + 0.1);
    }

    // B键: 缩小
    if(bn::keypad::b_held() && sprite->horizontal_scale() > 0.1)
    {
        sprite->set_scale(sprite->horizontal_scale() - 0.1);
    }

    // Select键: 旋转
    if(bn::keypad::select_held())
    {
        sprite->set_rotation_angle((sprite->rotation_angle().integer() + 5) % 360);
    }
}