#include "view.hpp"
#include <new>

// la fonction affiche le monde avec les nourriture de base 
void draw_world(Window* window, World* world, WorldView* view,int score) {
    int col = window->width / world->width;
    int lig = window->height / world->height;
    draw_texture(window, view->background, 0, 0,window->width, window->height);
    string score_text = "Score: " + to_string(score);
    set_color(&window->background,255,255,255,255);
    set_color(&window->foreground,12,13,45,66);
    draw_text(window, score_text, 1,1);
      

    // Parcourir chaque case du monde
    for (int i = 0; i < world->height; i++) {
        for (int j = 0; j < world->width; j++) {
            Block b = read(world, j, i);

            //   si une case contient de la nouriiture on affiche la nourriture en  fonction de l image donner 
            switch (b) {
                case GreenFood:
                    draw_texture(window, view->food_green, j * col, i * lig, col, lig);
                    break;
                case RedFood:
                    draw_texture(window, view->food_red, j * col, i * lig, col, lig);
                    break;
                case BlueFood:
                    draw_texture(window, view->food_blue, j * col, i * lig, col, lig);
                    break;
                case StarFood:
                    draw_texture(window, view->food_star, j * col, i * lig, col, lig);
                    break;
                default:

                    break; 
            }

        }
    }
}
// affiche la tete du serpent 
void draw_snake(Window* window, Snake* snake, SnakeView* snakeview, World* world) {
    int cell_w = window->width / world->width;  
    int cell_h = window->height / world->height;

          Anneau* current = snake->first;
          while (current != NULL) {
              switch (current->val) {
                  case RedFood:
                      draw_texture(window, snakeview->body_red, current->anneau_x * cell_w, current->anneau_y * cell_h, cell_w, cell_h);
                      break;
                  case GreenFood:
                      draw_texture(window, snakeview->body_green, current->anneau_x * cell_w, current->anneau_y * cell_h, cell_w, cell_h);
                      break;
                  case BlueFood:
                      draw_texture(window, snakeview->body_blue, current->anneau_x * cell_w, current->anneau_y * cell_h, cell_w, cell_h);
                      break;
                  default:
                      break;
              }
              current = current->next;
          }
    if (snake->mouth_open) {
        switch (snake->diremplacement) {
            case North:
                draw_texture(window, snakeview->head_open_up, snake->head_x * cell_w, snake->head_y * cell_h, cell_w, cell_h);
                break;
            case South:
                draw_texture(window, snakeview->head_open_down, snake->head_x * cell_w, snake->head_y * cell_h, cell_w, cell_h);
                break;
            case East:
                draw_texture(window, snakeview->head_open_right, snake->head_x * cell_w, snake->head_y * cell_h, cell_w, cell_h);
                break;
            case West:
                draw_texture(window, snakeview->head_open_left, snake->head_x * cell_w, snake->head_y * cell_h, cell_w, cell_h);
                break;
            default:
                break;
        }
    } else {
        switch (snake->diremplacement) {
            case North:
                draw_texture(window, snakeview->head_close_up, snake->head_x * cell_w, snake->head_y * cell_h, cell_w, cell_h);
                break;
            case South:
                draw_texture(window, snakeview->head_close_down, snake->head_x * cell_w, snake->head_y * cell_h, cell_w, cell_h);
                break;
            case East:
                draw_texture(window, snakeview->head_close_right, snake->head_x * cell_w, snake->head_y * cell_h, cell_w, cell_h);
                break;
            case West:
                draw_texture(window, snakeview->head_close_left, snake->head_x * cell_w, snake->head_y * cell_h, cell_w, cell_h);
                break;
            default:
                break;
        }
    }

    
  
}
