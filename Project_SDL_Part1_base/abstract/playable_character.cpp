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
            continue;
        }
        // If button down of keyboard
        if (event.type != SDL_KEYDOWN)
            continue;
        switch (event.key.keysym.sym)
        {
        case SDLK_q: // Q button
        case SDLK_LEFT: // Left arrow
            set_flip(SDL_FLIP_NONE);
            set_xy(x - speed_x, y, true);
            break;
        case SDLK_d: // D button
        case SDLK_RIGHT: // Right arrow
            set_flip(SDL_FLIP_HORIZONTAL);
            set_xy(x + speed_x, y, true);
            break;
        case SDLK_z: // Z button
        case SDLK_UP: // Up arrow
            set_xy(x, y - speed_y, true);
            break;
        case SDLK_s: // S button
        case SDLK_DOWN: // Down arrow
            set_xy(x, y + speed_y, true);
            break;
        default:
            break;
        }
    }
}