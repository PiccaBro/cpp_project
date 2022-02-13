#include "../application.h"

/**
 * @brief Move the playable characters
 *
 */
void playable_character::move()
{
    SDL_Event event;
    int x, y, speed_x, speed_y, click_x, click_y;
    get_xy(&x, &y);
    get_xy_speed(&speed_x, &speed_y);
    const Uint8 *kb_states = SDL_GetKeyboardState(NULL);

    // Check for actions
    while (SDL_PollEvent(&event))
    {
        // if click on cross, quit
        if (event.type == SDL_QUIT)
            exit(0);
        // if click left on the ground
        if (event.type == SDL_MOUSEBUTTONDOWN
            && event.button.button == SDL_BUTTON_LEFT)
        {
            SDL_GetMouseState(&click_x,
                              &click_y); // get coordinates of the click
            if (x < frame_boundary)
                x = frame_boundary;
            if (x > frame_width - frame_boundary)
                x = frame_width - frame_boundary;
            if (y < frame_boundary)
                y = frame_boundary;
            if (y > frame_height - frame_boundary)
                y = frame_height - frame_boundary;
            set_click(click_x,
                      click_y); // recorded and make coordinates between bounds
        }
        bool left = (kb_states[SDL_SCANCODE_A] || kb_states[SDL_SCANCODE_LEFT]);
        bool right =
            (kb_states[SDL_SCANCODE_D] || kb_states[SDL_SCANCODE_RIGHT]);
        bool up = (kb_states[SDL_SCANCODE_W] || kb_states[SDL_SCANCODE_UP]);
        bool down = (kb_states[SDL_SCANCODE_S] || kb_states[SDL_SCANCODE_DOWN]);
        if (left && !right)
        {
            set_flip(SDL_FLIP_NONE);
            x -= speed_x;
        }
        else if (right && !left)
        {
            set_flip(SDL_FLIP_HORIZONTAL);
            x += speed_x;
        }
        if (up && !down)
            y -= speed_y;
        else if (down && !up)
            y += speed_y;
        set_xy(x, y, true);
    }
}