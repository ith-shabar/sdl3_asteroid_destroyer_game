#include "variables.h"

int game_running = 1;

int player_speed = 400;
int player_health = 100;
int player_damage = 100;
int score = 0;
int score_obtained = 0;

static const int default_player_speed = 400;
static const int default_player_health = 100;
static const int default_player_damage = 100;
static const int default_score = 0;

int bullet_speed = 800;
int bullet_spread = 5;
int bullet_delay = 200;

static const int default_bullet_speed = 800;
static const int default_bullet_spread = 5;
static const int default_bullet_delay = 200;

int asteroid_speed = 200;
int asteroid_delay = 500;
int asteroid_min_delay = 100;
int asteroid_max_count = 20;
int asteroid_max_speed = 500;
int asteroid_max_size = 4;

static const int default_asteroid_speed = 200;
static const int default_asteroid_delay = 500;
static const int default_asteroid_min_delay = 100;
static const int default_asteroid_max_count = 20;
static const int default_asteroid_max_speed = 500;
static const int default_asteroid_max_size = 4;

game_mode mode = start;
levels level;

bool keyW = false;
bool keyA = false;
bool keyS = false;
bool keyD = false;
bool keySpace = false;
bool keyMouseButtonLeft = false;

int multi_key_press = 0;


void reset(){
    player_speed = default_player_speed;
    player_health = default_player_health;
    player_damage = default_player_damage;
    score = default_score;

    bullet_speed = default_bullet_speed;
    bullet_spread = default_bullet_spread;
    bullet_delay = default_bullet_delay;

    asteroid_speed = default_asteroid_speed;
    asteroid_delay = default_asteroid_delay;
    asteroid_min_delay = default_asteroid_min_delay;
    asteroid_max_count = default_asteroid_max_count;
    asteroid_max_speed = default_asteroid_max_speed;
    asteroid_max_size = default_asteroid_max_size;

    keyW = false;
    keyA = false;
    keyS = false;
    keyD = false;
    keySpace = false;
    keyMouseButtonLeft = false;
}
