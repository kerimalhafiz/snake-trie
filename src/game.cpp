using namespace std;
#include"game.hpp"
#include <fstream>




// la fonction sle chargement des des image via la fonction load_image(window,name);
void init_view(Window*window,Game *game){
   game->view =new WorldView;
    game->view->food_green=load_image(window,"food_green.png");
    game->view->food_red=load_image(window,"food_red.png");
    game->view->food_star=load_image(window,"food_star.png");
    game->view->food_blue=load_image(window,"food_blue.png");
    game->view->background=load_image(window,"background.png");
     game->snakeview=new SnakeView;
    game->snakeview->body_blue=load_image(window,"body_blue.png");
    game->snakeview->body_green=load_image(window,"body_green.png");
    game->snakeview->body_red=load_image(window,"body_red.png");
    game->snakeview->head_close_down=load_image(window,"head_close_down.png");
    game->snakeview->head_close_right=load_image(window,"head_close_right.png");
    game->snakeview->head_close_left=load_image(window,"head_close_left.png");
    game->snakeview->head_close_up=load_image(window,"head_close_up.png");
    game->snakeview->head_open_down=load_image(window,"head_open_down.png");
    game->snakeview->head_open_right=load_image(window,"head_open_right.png");
    game->snakeview->head_open_left=load_image(window,"head_open_left.png");
    game->snakeview->head_open_up=load_image(window,"head_open_up.png");



}
// movement  du serpent et liason du tete avec l anneau pour former le corp du sepent
bool move_snake(Game *game){ 
    int prev_x=game->snake->head_x;
    int prev_y=game->snake->head_y;

    write(game->world,prev_x, prev_y, Empty);

  
  
    // Déplace la tête selon la direction
    switch (game->snake->diremplacement) {
        case North:game-> snake->head_y--; break;
        case South: game->snake->head_y++; break;
        case West:game-> snake->head_x--; break;
        case East:game-> snake->head_x++; break;
        default: break;
    }
       // Passage secret en bas à gauche → en haut à droite
    if (game->snake->head_x == 0 && game->snake->head_y == game->world->height - 1) {
        game->snake->head_x = game->world->width - 1;
        game->snake->head_y = 0;

          draw_text(game->window,"passage secret",100,100);
        refresh_window(game->window);
        SDL_Delay(500);  
    }

    // Rebond au milieu du haut
    else if (game->snake->head_y == 0 && game->snake->head_x == game->world->width / 2) {
        game->snake->diremplacement = South;  // Rebond vers le bas
        game->snake->head_y += 1;

        draw_text(game->window,"rebond au milieu",100,100);
        refresh_window(game->window);
        SDL_Delay(500);  
    }
  
    // Vérification de la collision avec les bords
    if (game->snake->head_x < 0 || game->snake->head_x >= game->world->width || game->snake->head_y < 0 ||game-> snake->head_y >= game->world->height) {
        return true;
    }
  
    // Vérification de la collision avec soi-même  si la tete touche une autre anneau que le premier 
    Anneau* current = game->snake->first;
    while (current != NULL  && current->next !=NULL) {
        if (current->next->anneau_x == game->snake->head_x && current->next->anneau_y ==game-> snake->head_y) {
            return true;
        }
        current = current->next;
    }
  
    // Vérification si on mange de la nourriture

    check_and_eat_food(game);
    current =game-> snake->first;
    while (current != NULL) {
        int temp_x = current->anneau_x;
        int temp_y = current->anneau_y;
        current->anneau_x = prev_x;
        current->anneau_y = prev_y;
  
        prev_x = temp_x;
        prev_y = temp_y;
  
        current = current->next;
    }
  
  
    //la tête à la nouvelle position
    write(game->world, game->snake->head_x,game-> snake->head_y, Empty); 

  
    return false; 
  }
  // la fonction  verifie si la tete touche une nouriture et le mange 
  void check_and_eat_food(Game* game) {
    int head_x = game->snake->head_x;
    int head_y =game-> snake->head_y;
    
    // lis la case sous la tête du serpent
    Block food_type = read(game->world, head_x, head_y);
  
    // Vérifie  si la tête touche un aliment
    if (food_type != Empty) {
         game->snake->mouth_open=true;
         //  je calcul la taille du serpent
           int  snake_size=1;
           Anneau *snake_s=game->snake->first;
           while (snake_s!=NULL)
           {
               snake_size++;
               snake_s=snake_s->next;
           }
           
        
        // Ajoute d un anneau en fonction de la nourriture mangée si le type n'est pas StarFood
        if (food_type != StarFood) {
            Anneau* new_anneau = new Anneau;
            new_anneau->anneau_x = head_x;
            new_anneau->anneau_y = head_y;
            new_anneau->val = food_type;
            new_anneau->next = game->snake->first;
            if (game->snake->first != NULL) {
                game->snake->first->prev = new_anneau;
            }
            game->snake->first = new_anneau;
            game->snake->second_last = new_anneau;
            game->score += 1+snake_size; // le score augment  1+ la taille du serpent 
        } else {
            remove_middle_anneau(game);
            game->score -= 4; 
        }

        
  
        // Ajout d' une nouvelle nourriture a un position  aléatoire
        int x = rand() % game->world->width;
        int y = rand() % game->world->height;
        if (food_type!=Empty)
        {
            while (read(game->world, x, y) != Empty) {
                x = rand() %game-> world->width;  // Si la case est occupée, on génère une nouvelle position
                y = rand() % game->world->height;
            }
            add_food(game->world, x, y, food_type);
        }
        
        
       
    }
    else{
        game->snake->mouth_open=false;
    }
  }
//  la fonction sauvegarde le jeu dans un fichier 
bool save_game(Game*game ,string filename){
    ofstream file(filename);
    if (!file)
    {
        cout<<"erreur du fichier "<<endl;
      return false;
    }
    
   // Sauvegarde la taille du monde
   file << game->world->width << " " << game->world->height << endl;

   // Sauvegarde la position et direction de la tête du serpent
   file << game->snake->head_x << " " << game->snake->head_y << " " << game->snake->diremplacement << endl;
    file<<game->score<<endl;
   // Sauvegarde les anneaux du corps
   Anneau* current = game->snake->first;
   while (current != NULL) {
       file << current->anneau_x << " " << current->anneau_y << " " << current->val << endl;
       current = current->next;
   }
   file << "fin_anneaux" << endl;

   // Sauvegarde toutes les nourritures en parcourant toute la grille
   file << "debut_foods" << endl;
   for (int i = 0; i < game->world->height; i++) {
       for (int j = 0; j < game->world->width; j++) {
           Block bloc = read(game->world, j, i); // fonction read(world, x, y)
           if (bloc == GreenFood || bloc == RedFood || bloc == BlueFood || bloc == StarFood) {
               file << j << " " << i << " " << bloc << endl;
           }
       }
   }
   file << "fin_foods" << endl;

   file.close();
   draw_text(game->window, "Partie sauvegardee. Voulez-vous continuer?(o/n) : ", 100, 100);
   refresh_window(game->window);
     SDL_Event evt;
     while (SDL_WaitEvent(&evt)) {
         if (evt.type == SDL_KEYDOWN) {
             switch (evt.key.keysym.sym)
             {
             case   SDLK_n:
                 return true;
                 break;
             case SDLK_o:
               return   false;
             default:
                 break;
             }
            }
        }
    
            return false;
}
// la fonction sert a supprimer l anneau du milieu si les 3 anneau ont la  couleur du sepent au global
void remove_middle_anneau(Game* game) {
    if (!game->snake || !game->snake->first || !game->snake->first->next || !game->snake->first->next->next)
        return;

    Anneau* first = game->snake->first;
    Anneau* second = first->next;
    Anneau* third = second->next;

    while (third != NULL) {
        if (first->val == second->val && second->val == third->val) {
            first->next = third;
            third->prev = first;
            delete second;

            second = third;
            third = third->next;
// passage aux anneau suivant
        } else {
            first = second;
            second = third;
            third = third->next;
        }
    }

}
void change_statut(Game* game) {
    switch (game->statut) {
        case Begin:
            game->statut = Play;  
            draw_text(game->window, "Debut du jeu!", 100, 100); 
            refresh_window(game->window);
            SDL_Delay(500);  
            break;
        case Play:
            game->statut = Pause; 
            draw_text(game->window, "Jeu en pause. Appuyez sur espace pour reprendre", 100, 100);
            refresh_window(game->window);
            SDL_Delay(500); 
            break;
        case Pause:
            game->statut = Play;  
            draw_text(game->window, "Reprise du jeu!", 100, 100);
            refresh_window(game->window);
            SDL_Delay(500);  
            break;
        case GameOver:
            game->statut = Begin;  
            draw_text(game->window, "Fin du jeu. Appuyez sur espace pour recommencer", 100, 100);
            refresh_window(game->window);
            SDL_Delay(500);  
            break;
        default:
            break;
    }
}

bool load_game(Game* game, string filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Erreur : impossible d'ouvrir le fichier." << endl;
        return false;
    }

    if (game->world) {
        free_world(game->world); // Libère l'ancien monde si nécessaire
    }
    if (game->snake) {
        free_anneaux(game); // Libère les anciens anneaux du serpent
    }

    // Lire les dimensions du monde
    int width, height;
    file >> width >> height;

    // Initialisation du monde
    game->world = new World;
    init_world(game->world, width, height);

    // Lire la position de la tête du serpent et sa direction
    file >> game->snake->head_x >> game->snake->head_y;
    int dir;
    file >> dir;
    game->snake->diremplacement = static_cast<Direction>(dir);//conversion du position en entier j ai eu l'idee du mr arthur

    // Lire le score
    file >> game->score;

    // Lire les anneaux du serpent
    Anneau* prev = nullptr;
    string token;
    while (file >> token && token != "fin_anneaux") {
        Anneau* ann = new Anneau;
        ann->anneau_x = stoi(token); // Conversion du token en entier
        file >> ann->anneau_y >> ann->val;
        ann->prev = prev;
        ann->next = nullptr;

        if (prev) {
            prev->next = ann;
        } else {
            game->snake->first = ann;
        }
        prev = ann;
    }
    game->snake->second_last = prev;

    file >> token; 
    while (file >> token && token != "fin_foods") {
        int x = stoi(token);
        int y, val;
        file >> y >> val;
        add_food(game->world, x, y, static_cast<Block>(val)); //j 'etais obliger à l utiliser le pour convertir
    }

    game->statut = Play; 
    file.close(); 
    return true;
}

void free_anneaux(Game *game) {
    Anneau* current = game->snake->first;
    while (current) {
        Anneau* next = current->next;
        delete current;
        current = next;
    }
    game->snake->first = nullptr;
    game->snake->second_last = nullptr;
}
