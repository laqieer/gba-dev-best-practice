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
#include "bn_affine_bg_actions.h"
#include "bn_music_items.h"
#include "bn_sound_items.h"
#include "bn_string_view.h"
#include "bn_sprite_text_generator.h"
#include "hanamin_sprite_font.h"
#include "bn_camera_ptr.h"
#include "bn_sram.h"

bn::sprite_ptr *sprite;
bn::sprite_animate_action<10> *sprite_action;
bn::regular_bg_ptr *regular_bg;
bn::affine_bg_ptr *affine_bg;
bn::affine_bg_rotate_by_action *affine_bg_action;
bn::sprite_text_generator *text_generator;
bn::vector<bn::sprite_ptr, 10> *text_sprites;
bn::camera_ptr *camera;
struct {
    int position_x;
    int position_y;
    int camera_x;
    int camera_y;
} progress;

void init_sprite();
void init_regular_bg();
void init_affine_bg();
void init_text();
void init_camera();
void reset_sprite();
void reset_regular_bg();
void reset_affine_bg();
void reset_camera();
void handle_user_input();
void update_actions();
void restore_progress();
void save_progress();

int main()
{
    bn::core::init();
    init_sprite();
    init_regular_bg();
    init_affine_bg();
    init_text();
    init_camera();
    restore_progress();
    bn::music_items::age_of_time.play(0.25);
    bn::sound_items::evil_monster_kevangc.play();

    while(true)
    {
        handle_user_input();
        update_actions();
        bn::core::update();
        save_progress();
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
    affine_bg_action = new bn::affine_bg_rotate_by_action(*affine_bg, 5);
}

void init_text()
{
    text_generator = new bn::sprite_text_generator(hanamin_sprite_font);
    text_sprites = new bn::vector<bn::sprite_ptr, 10>();
    text_generator->generate(0, -70, "GBA开发最佳实践", *text_sprites);
}

void init_camera()
{
    camera = new bn::camera_ptr(bn::camera_ptr::create(0, 0));
    regular_bg->set_camera(*camera);
    sprite->set_camera(*camera);
    affine_bg->set_camera(*camera);
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

void reset_camera()
{
    camera->set_position(0, 0);
}

void handle_user_input()
{
    // Start键: 复位
    if(bn::keypad::start_pressed())
    {
        reset_sprite();
        reset_regular_bg();
        reset_affine_bg();
        reset_camera();
    }

    // 十字键向上
    if(bn::keypad::up_held())
    {
        // 按住L键: 镜头上移
        if(bn::keypad::l_held() || sprite->y() > 0)
        {
            if(camera->y() > -48)
            {
                camera->set_y(camera->y() - 1);
            }
        }
        // 否则: 人物上移
        if(!bn::keypad::l_held())
        {
            if(sprite->y() > 0)
            {
                sprite->set_y(sprite->y() - 1);
                affine_bg->set_y(sprite->y());
            }
        }
    }

    // 十字键向下
    if(bn::keypad::down_held())
    {
        // 按住L键: 镜头下移
        if(camera->y() < 48)
        {
            camera->set_y(camera->y() + 1);
        }
        // 否则: 人物下移
        if(!bn::keypad::l_held())
        {
            if(sprite->y() < 96)
            {
                sprite->set_y(sprite->y() + 1);
                affine_bg->set_y(sprite->y());
            }
        }
    }

    // 十字键向左
    if(bn::keypad::left_held())
    {
        // 镜头左移
        camera->set_x(camera->x() - 1);
        // 人物左移
        if(!bn::keypad::l_held())
        {
            sprite->set_x(sprite->x() - 1);
            affine_bg->set_x(sprite->x());
            sprite->set_horizontal_flip(true);
            affine_bg->set_horizontal_flip(true);
        }
    }

    // 十字键向右
    if(bn::keypad::right_held())
    {
        // 镜头右移
        camera->set_x(camera->x() + 1);
        // 人物右移
        if(!bn::keypad::l_held())
        {
            sprite->set_x(sprite->x() + 1);
            affine_bg->set_x(sprite->x());
            sprite->set_horizontal_flip(false);
            affine_bg->set_horizontal_flip(false);
        }
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
}

void update_actions()
{
    sprite_action->update();
    affine_bg_action->update();
}

void restore_progress()
{
    bn::sram::read(progress);
    sprite->set_position(progress.position_x, progress.position_y);
    affine_bg->set_position(sprite->position());
    camera->set_position(progress.camera_x, progress.camera_y);
}

void save_progress()
{
    progress.position_x = sprite->x().integer();
    progress.position_y = sprite->y().integer();
    progress.camera_x = camera->x().integer();
    progress.camera_y = camera->y().integer();
    bn::sram::write(progress);
}