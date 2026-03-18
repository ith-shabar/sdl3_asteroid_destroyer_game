#include "variables.h"

int game_running = 1;

int player_speed = 400;
int player_health = 100;
int player_damage = 100;
int score = 0;

int bullet_speed = 800;
int bullet_spread = 5;
int bullet_delay = 200;

int asteroid_speed = 200;
int asteroid_delay = 500;
int asteroid_min_delay = 100;
int asteroid_max_count = 20;
int asteroid_max_speed = 500;

game_mode mode;
levels level;

bool keyW = false;
bool keyA = false;
bool keyS = false;
bool keyD = false;
bool keySpace = false;
bool keyMouseButtonLeft = false;

int multi_key_press = 1;
