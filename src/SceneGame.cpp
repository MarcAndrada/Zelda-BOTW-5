#include "SceneGame.h"
#include "singletons.h"
#include "SceneDirector.h"



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
/* --!
	*
	*
	*/
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

	/* --!
	* Dependiendo de lo que se haya seleccionado se derivan 2 acciones
	* continuar la partida
	* Empezar de cero, borrar todos los mapas de anteriores partidas y el estado del jugador
	*/

	CurrentMap = "Maps/map_1.txt";
	initMap();
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
	
	if (sInput->isKeyPressed(Input::ESCAPE))
	{


		sDirector->changeScene(SceneDirector::MAIN_MENU, false);
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
	Map.open(CurrentMap, std::ios::in);
	if (!Map.is_open()) {
		std::cout << "Error Map not found" << std::endl;
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
				//crear Player
				player->init(j * TILE_SIZE, i * TILE_SIZE);
				player->setCollisionsMap(&mpCollisionMap, width, height);
				break;
			case '.':
			
				//crear Gema
				break;
			

			case 'O':
			
				//crear Enemigo 1
				
				break;
			case 'F':
				//crear Enemigo 2
				
				break;

			
			case 'J':
				//crear Enemigo 3

				break;

			case 'K':
				//crear Llave

				break;
			case 'C':
				//crear Cofre

				break;
				
			}
		}
	}
	Map.close();
}

void SceneGame::StartGame(){

	if (sDirector->checkCurrentScene('R'))
	{
		CurrentMap = "Maps/LastMapSaved.txt";
		//load player status
	}
	else if (sDirector->checkCurrentScene('N'))
	{
		CurrentMap = "Maps/map_1.txt";
		//borrar mapas guardados (LastMapSaved.txt, Map_1_saved.txt ...)
		// Y borrar player status
	}
}

void SceneGame::SaveLastMapStaus(){
	//Guardar el estado del mapa (enemigos, objetos ...) en el archivo de Maps/LastMapSaved.txt
	//Guardar el estado del jugador(Posicion, objetos, vida ...)
}

