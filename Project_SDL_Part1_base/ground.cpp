#include "application.h"

/**
 * @brief Construct a new ground
 *
 * @param renderer the renderer of the window
 * @param score the vector of score objects
 */
ground::ground(SDL_Renderer *renderer,
               std::vector<std::shared_ptr<rendered_object>> score)
{
    this->renderer = renderer;
    this->score = score;
}

/**
 * @brief Destroy the ground
 *
 */
ground::~ground()
{}

/**
 * @brief Return the moving objects on the ground
 *
 * @return std::vector<std::shared_ptr<moving_object>>
 */
std::vector<std::shared_ptr<moving_object>> ground::get_objects()
{
    return moving_objects;
}

/**
 * @brief Add a new moving object on the ground
 *
 * @param moving_object
 */
void ground::add_object(std::shared_ptr<moving_object> moving_object)
{
    moving_objects.push_back(moving_object);
}

/**
 * @brief Draw the current score at the left-up corner
 *
 * @param n_sheep the number of sheep on the ground
 */
void ground::draw_score(size_t n_sheep)
{
    score[10]->draw();
    int offset = 220;
    if (n_sheep > 999)
        n_sheep = 999;
    if (n_sheep < 100)
    {
        score[0]->set_xy(offset, 50, false);
        offset += 30;
        score[0]->draw();
    }
    if (n_sheep < 10)
    {
        score[0]->set_xy(offset, 50, false);
        offset += 30;
        score[0]->draw();
    }
    std::string s = std::to_string(n_sheep);
    for (char c : s)
    {
        score[c - '0']->set_xy(offset, 50, false);
        offset += 30;
        score[c - '0']->draw();
    }
}

/**
 * @brief Update all moving object, their interactions and position
 *
 * @param window_ptr
 */
void ground::update(SDL_Window *window_ptr)
{
    SDL_RenderClear(renderer); // Clear the renderer
    SDL_SetRenderDrawColor(renderer, 50, 188, 50, 255); // Nice green color
    SDL_RenderFillRect(renderer, NULL); // All ground to green

    size_t n_sheep = 0;

    for (size_t i = 0; i < moving_objects.size(); i++)
    {
        moving_objects[i]->move(); // move the object
        moving_objects[i]->draw(); // draw the object

        moving_objects[i]->set_dist(max_dist); // reset distance recorded
        moving_objects[i]->set_hunted(false); // reset hunted status
        for (std::shared_ptr<moving_object> obj : moving_objects)
            moving_objects[i]->interact_with_object(
                obj); // interact with others

        if (moving_objects[i]->getBirth()) // If a new birth
        {
            std::shared_ptr<moving_object> new_obj =
                moving_objects[i]->bear(renderer); // the object bear
            moving_objects.push_back(new_obj); // Add the new object
            moving_objects[i]->setBirth(false); // The birth is finished
        }

        if (!moving_objects[i]->isAlive()) //  If object is not alive
            moving_objects.erase(moving_objects.cbegin()
                                 + i); // Remove it from the vector

        if (moving_objects[i]->get_type() == SHEEP) // If object is a sheep
            n_sheep++; // Count it for scoring
    }
    draw_score(n_sheep); // Draw the score
    SDL_RenderPresent(renderer); // Print the renderer
}