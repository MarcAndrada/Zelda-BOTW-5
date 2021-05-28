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

void SceneGame::unLoad(){
	
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
	Wall_sprite_id = sResManager->getSpriteID("Assets/Wall.png");
	Floor_sprite_id = sResManager->getSpriteID("Assets/Floor.png");
	Wall_sprite_rect = C_Rectangle{ 0,0,32, 32 };
	Floor_sprite_rect = C_Rectangle{ 0,0,32, 32 };

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
	player->update();

	if (sInput->isKeyPressed(Input::ESCAPE)) {
		sDirector->goBack();
	}
	int Size = mEntities.size();
	for (size_t i = 0; i < Size; i++)
	{
		if (mEntities[i]->isAlive()) {
			mEntities[i]->update();
			C_Rectangle rectEntity = mEntities[i]->getRect();
			int collision = player->collidesWithEntity(mEntities[i]);
			switch (collision)
			{
			default:
				break;

			case MELE:
				//quitar vida al player
				break;
			case RANDOM:
				//quitar vida al player
				break;
			case DOOR:
				SaveCurrentMap();
				LoadNextMap();
				//SetNewPlayerPos();
				initMap();
				break;
			case GEMS:

				break;
			}

		}
	}
	
	if (/*Si los enemigos estan muertos abrir las puertas y quitar la colision del mapa*/true)
	{

	}
}

void SceneGame::updateEnd(){

}

void SceneGame::renderBegin(){

}

void SceneGame::render(){
	
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			
			if (mpCollisionMap[i][j] == true)
			{
				Wall_sprite_x = j * TILE_SIZE;
				Wall_sprite_y = i * TILE_SIZE;
				sRenderer->drawSprite(Wall_sprite_id, Wall_sprite_x, Wall_sprite_y, Wall_sprite_rect);
			}
			else
			{
				Floor_sprite_x = j * TILE_SIZE;
				Floor_sprite_y = i * TILE_SIZE;

				sRenderer->drawSprite(Floor_sprite_id, Floor_sprite_x, Floor_sprite_y, Floor_sprite_rect);
			}
		}
	}
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
	width = atoi(line.c_str());
	std::getline(Map, line);
	height = atoi(line.c_str());

	std::vector<Entity*> background;
	std::vector<Entity*> foreground;

	mpCollisionMap.resize(height);
	for (int i = 0; i < height; i++)
	{
		mpCollisionMap[i].resize(width, false);
		std::getline(Map, line);
		for (int j = 0; j < width; j++)
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
			case 'G':
				{
				Gems* aGem = new Gems;
				aGem->init(j * TILE_SIZE, i * TILE_SIZE);
				background.push_back(aGem);

				//crear Gema
				}	
				break;


			case 'O':
			{
				//crear Enemigo 1
				Mele* aMele = new Mele;
				aMele->init(j * TILE_SIZE, i * TILE_SIZE, j * TILE_SIZE, i * TILE_SIZE);
				aMele->setCollisionsMap(&mpCollisionMap, width, height);
				foreground.push_back(aMele);
			}	break;
			case 'F':
			{
				Random* aRandom = new Random;
				aRandom->init(j * TILE_SIZE, i * TILE_SIZE);
				aRandom->setCollisionsMap(&mpCollisionMap, width, height);
				foreground.push_back(aRandom);
				//crear Enemigo 2

			}	break;

			case 'K':
				//crear Llave

				break;
			case 'C':
				//crear Cofre

				break;
			case '1':
			{
				//new Door
				Door* aDoor1 = new Door;
				aDoor1->init(j * TILE_SIZE, i * TILE_SIZE);				
				NextMap = 1;
				mpCollisionMap[i][j] = true;
				map[i][j] = '1';
				foreground.push_back(aDoor1);
			}	break;
			case '2':
			{
				Door* aDoor2 = new Door;
				aDoor2->init(j * TILE_SIZE, i * TILE_SIZE);
				NextMap = 2;
				mpCollisionMap[i][j] = true;
				map[i][j] = '2';
				foreground.push_back(aDoor2);
			}	break;
			case '3':
				{
				Door* aDoor3 = new Door;
				aDoor3->init(j * TILE_SIZE, i * TILE_SIZE);
				NextMap = 3;
				mpCollisionMap[i][j] = true;
				map[i][j] = '3';
				foreground.push_back(aDoor3);
				}break;
			case '4':
			{
				Door* aDoor4 = new Door;
				aDoor4->init(j * TILE_SIZE, i * TILE_SIZE);
				NextMap = 4;
				mpCollisionMap[i][j] = true;
				map[i][j] = '4';
				foreground.push_back(aDoor4);
			}	break;
			case '5':
			{
				Door* aDoor5 = new Door;
				aDoor5->init(j * TILE_SIZE, i * TILE_SIZE);
				NextMap = 5;
				mpCollisionMap[i][j] = true;
				map[i][j] = '5';
				foreground.push_back(aDoor5);
			}	break;
			case '6':
			{
				Door* aDoor6 = new Door;
				aDoor6->init(j * TILE_SIZE, i * TILE_SIZE);
				NextMap = 6;
				mpCollisionMap[i][j] = true;
				map[i][j] = '6';
				foreground.push_back(aDoor6);
			}	break;
			
			}
		}
	}
	std::getline(Map, line);
	loadedMap = atoi(line.c_str());
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

void SceneGame::SaveCurrentMap(){
	
	std::fstream SaveMap;
	std::string CurrentSaveMap;
	switch (loadedMap){
	case 1:
		CurrentSaveMap = "Assets/map_1_saved.txt";
		break;
	case 2:
		CurrentSaveMap = "Assets/map_2_saved.txt";
		break;
	case 3:
		CurrentSaveMap = "Assets/map_3_saved.txt";
		break;
	case 4:
		CurrentSaveMap = "Assets/map_4_saved.txt";
		break;
	case 5:
		CurrentSaveMap = "Assets/map_5_saved.txt";
		break;
	case 6:
		CurrentSaveMap = "Assets/map_6_saved.txt";
		break;

	default:
		break;
	}

	SaveMap.open(CurrentSaveMap, std::ios::out | std::ios::trunc);
	if (!SaveMap.is_open()) {
		std::cout << "Error Guardando el mapa" << std::endl;
	}
	SaveMap << width << "\n";
	SaveMap << height;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++)
		{
			if (map[i][j] != '1' && map[i][j] != '2' && map[i][j] != '3' && map[i][j] != '4' && map[i][j] != '5' && map[i][j] != '6')
			{
				map[i][j] = '*';
				if (mpCollisionMap[i][j] == true)
				{
					map[i][j] = '#';
				}

			}
			
			for (int c = 0; c < mEntities.size(); c++)
			{
				if (mEntities[c]->GetMapPosX() == j && mEntities[c]->GetMapPosY()) {
					switch (mEntities[c]->getClassName()) {
					case GEMS:
						map[i][j] = 'E';
						break;

					default:
						break;
					}
				}
			}
		}
	}
	SaveMap << "\n" << loadedMap; 

	//guardar inventario
	SaveMap.close();

}

void SceneGame::LoadNextMap() {

	switch (NextMap){
	case '1':
		NextLoadMap = "Assets/map_1.txt";
		NextLoadSavedMap = "Assets/map_1_saved.txt";
		break;
	case '2':
		NextLoadMap = "Assets/map_2.txt";
		NextLoadSavedMap = "Assets/map_2_saved.txt";
		break;
	case '3':
		NextLoadMap = "Assets/map_3.txt";
		NextLoadSavedMap = "Assets/map_3_saved.txt";
		break;
	case '4':
		NextLoadMap = "Assets/map_4.txt";
		NextLoadSavedMap = "Assets/map_4_saved.txt";
		break;
	case '5':
		NextLoadMap = "Assets/map_5.txt";
		NextLoadSavedMap = "Assets/map_5_saved.txt";
		break;
	case '6':
		NextLoadMap = "Assets/map_6.txt";
		NextLoadSavedMap = "Assets/map_6_saved.txt";
		break;

	default:
		break;
	}
	std::fstream LoadMap;
	LoadMap.open(NextLoadSavedMap, std::ios::in);
	if (!LoadMap.is_open())
	{
		LoadMap.open(NextLoadMap, std::ios::in);
	}

	if (LoadMap.is_open())
	{
		//cargar mapa
		CurrentMap = NextLoadMap;
	}
	else{
		std::cout << "Error Loading Map" << std::endl;
	}



	LoadMap.close();
}

void SceneGame::SaveLastMapStaus(){
	//Guardar el estado del mapa (enemigos, objetos ...) en el archivo de Maps/LastMapSaved.txt
	//Guardar el estado del jugador(Posicion, objetos, vida ...)

	std::fstream SaveMap;
	std::string CurrentNextMap;

	SaveMap.open("Assets/", std::ios::out | std::ios::trunc);
	if (!SaveMap.is_open()) {
		std::cout << "Error Guardando el mapa" << std::endl;
	}
	SaveMap << width << "\n";
	SaveMap << height;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++)
		{
			map[i][j] = '*';
			if (mpCollisionMap[i][j] == true)
			{
				map[i][j] = '#';
			}
			if (player->GetMapPosX() == j && player->GetMapPosY() == i)
			{
				map[i][j] = 'P';
			}
			for (int c = 0; c < mEntities.size(); c++)
			{
				if (mEntities[c]->GetMapPosX() == j && mEntities[c]->GetMapPosY()) {
					switch (mEntities[c]->getClassName()) {
					case MELE:
						map[i][j] = 'O';
						break;
					case RANDOM:
						map[i][j] = 'F';
						break;
					case DOOR:

						break;
					case GEMS:
						map[i][j] = 'E';
						break;

					default:
						break;
					}
				}
			}
		}
	}
	SaveMap << "\n" << loadedMap;
	SaveMap.close();
}

