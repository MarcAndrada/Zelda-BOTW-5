#include "SceneGame.h"
#include "singletons.h"

SceneGame::SceneGame() : Scene(){
	init();
}

SceneGame::~SceneGame(){

}

void SceneGame::preLoad(){

}

void SceneGame::unLoad()
{
}

void SceneGame::init(){
	/*sprite_id = sResManager->getSpriteID("Assets/link.png");
	sprite_rect = C_Rectangle{ 0,0,78, 82 };
	sprite_frame = 0;
	sprite_frame_time = 0;
	sprite_x = 50;
	sprite_y = 50;
	rect1 = C_Rectangle{ 20,30,200,100 };
	rect2 = C_Rectangle{ 60,200,50,100 };*/
	player = new Link();
}

void SceneGame::updateBegin(){
	/*sprite_frame_time += global_delta_time;
	if (sprite_frame_time > 150)
	{
		sprite_frame_time = 0;
		sprite_frame++;
		if (sprite_frame >= 8 )
		{
			sprite_frame = 0;
		}
		sprite_rect.x = sprite_rect.w * sprite_frame;
	}
	*/
	
}

void SceneGame::update() {
	sprite_rect.y = 0;
	player->update();

	if (sInput->isKeyPressed(Input::BACKSPACE)) {
		sDirector->goBack();
	}

	if (sInput->isKeyPressed(Input::ARROW_RIGHT)) {
		sprite_x += 10;
	}
	if (sInput->isKeyPressed(Input::ARROW_LEFT)) {
		sprite_x -= 10;
	}
	if (sInput->isKeyPressed(Input::ARROW_DOWN)) {
		sprite_y += 10;
	}
	if (sInput->isKeyPressed(Input::ARROW_UP)) {
		sprite_y -= 10;
	}
	
}

void SceneGame::updateEnd(){

}

void SceneGame::renderBegin(){

}

void SceneGame::render(){
	sRenderer->drawSprite(sprite_id, sprite_x, sprite_y, sprite_rect);
	player->render();
	//sRenderer->drawRectangle(rect2 , Color{ 0,255,0 });
}

void SceneGame::renderEnd(){

}

void SceneGame::renderGUI(){

}

void SceneGame::initMap(){
	std::fstream Map;
	Map.open("map.txt", std::ios::in);
	if (!Map.is_open()) {
		std::cout << "Error" << std::endl;
		system("pause");
		exit(0);
	}
	std::string line;
	std::getline(Map, line);
	int width = atoi(line.c_str());
	std::getline(Map, line);
	int height = atoi(line.c_str());

	std::vector<Entity*> background;
	std::vector<Entity*> foreground;

	mpCollisionMap.resize(height);
	for (size_t i = 0; i < height; i++)
	{
		mpCollisionMap[i].resize(width, false);
		std::getline(Map, line);
		for (size_t j = 0; j < width; j++)
		{
			char a_char = line[j];
			switch (a_char) {
			case '#':
				mpCollisionMap[i][j] = true;
				break;
			case 'P':
				//crear Pacman
				player->init(j * TILE_SIZE, i * TILE_SIZE);
				player->setCollisionsMap(&mpCollisionMap, width, height);
				break;
			case '.':
			{
				//crear punto
				
			}break;

			case 'O':
			{
				//crear powerup
				
			}break;
			case 'F':
				//crear Fantasma
				
				break;
			}
		}
	}
	Map.close();
}
