#include "SceneGame.h"
#include "singletons.h"



SceneGame::SceneGame() : Scene(){

}

SceneGame::~SceneGame(){

}

void SceneGame::preLoad(){

}

void SceneGame::unLoad(){
	
}

void SceneGame::init(){
	
	player = new Link();
	Wall_sprite_id = sResManager->getSpriteID("Assets/Wall.png");
	Floor_sprite_id = sResManager->getSpriteID("Assets/Floor.png");
	Gem_img_id = sResManager->getSpriteID("Assets/Gem.png");
	Key_img_id = sResManager->getSpriteID("Assets/KeyHud.png");
	Key_HUD_img_id = sResManager->getSpriteID("Assets/KeyHudFalse.png");
	Heart_img_id = sResManager->getSpriteID("Assets/Heart.png");
	Zero_img_id = sResManager->getSpriteID("Assets/Zero.png");
	One_img_id = sResManager->getSpriteID("Assets/One.png");
	Two_img_id = sResManager->getSpriteID("Assets/Two.png");
	Three_img_id = sResManager->getSpriteID("Assets/Three.png");
	Four_img_id = sResManager->getSpriteID("Assets/Four.png");
	Five_img_id = sResManager->getSpriteID("Assets/Five.png");
	Six_img_id = sResManager->getSpriteID("Assets/Six.png");
	Seven_img_id = sResManager->getSpriteID("Assets/Seven.png");
	Eight_img_id = sResManager->getSpriteID("Assets/Eight.png");
	Nine_img_id = sResManager->getSpriteID("Assets/Nine.png");
	Ten_img_id = sResManager->getSpriteID("Assets/Ten.png");
	Eleven_img_id = sResManager->getSpriteID("Assets/Eleven.png");;
	Twelve_img_id = sResManager->getSpriteID("Assets/Twelve.png");;
	ThirdTeen_img_id = sResManager->getSpriteID("Assets/Thirdteen.png");;
	FourTeen_img_id = sResManager->getSpriteID("Assets/Fourteen.png");;
	FiveTeen_img_id = sResManager->getSpriteID("Assets/FiveTeen.png");;

	
	Wall_sprite_rect = C_Rectangle{ 0,0,32, 32 };

	Floor_sprite_rect = C_Rectangle{ 0,0,32, 32 };

	Heart_img_sprite_rect = C_Rectangle{ 0,0,32, 32 };
	Heart_img_sprite_x = 3 * TILE_SIZE;
	Heart_img_sprite_y = 15.5f * TILE_SIZE;

	Gem_img_sprite_rect = C_Rectangle{0,0,32, 32 };
	Gem_img_sprite_x = 13* TILE_SIZE;
	Gem_img_sprite_y = 15.5f * TILE_SIZE;

	Heart_num_img_sprite_rect = C_Rectangle{0,0,32, 32 };
	Heart_num_img_sprite_x = 5* TILE_SIZE;
	Heart_num_img_sprite_y = 15.5f * TILE_SIZE;

	Gem_num_img_sprite_rect = C_Rectangle{ 0,0,32, 32 };
	Gem_num_img_sprite_x = 15 * TILE_SIZE;
	Gem_num_img_sprite_y = 15.5f * TILE_SIZE;

	Key_img_sprite_rect = C_Rectangle{ 0,0,64, 64 };
	Key_img_sprite_x = 25 * TILE_SIZE;
	Key_img_sprite_y = 15 * TILE_SIZE;

	/* --!
	* Dependiendo de lo que se haya seleccionado se derivan 2 acciones
	* continuar la partida
	* Empezar de cero, borrar todos los mapas de anteriores partidas y el estado del jugador
	*/

	CurrentMap = "Maps/map_1.txt";
	StartGame();
	initMap();

}

void SceneGame::updateBegin(){
	
}

void SceneGame::update() {
	
	int playerPosX = 0;
	int playerPosY = 0;
	chestTimePassed += global_delta_time;
	if (player->isAlive())
	{
		player->update();
		playerPosX = player->GetMapPosX() * TILE_SIZE;
		playerPosY = player->GetMapPosY() * TILE_SIZE;
	}

	if (TotalEnemies != EnemiesDead)
	{
		EnemiesDead = 0;
		for (size_t i = 0; i < mEntities.size(); i++)
		{
			switch (mEntities[i]->getClassName()) {
			case MELE:
			case RANDOM:
				if (!mEntities[i]->isAlive())
				{
					EnemiesDead++;
				}
				break;

			default:
				break;
			}
		}
	}

	if (sInput->isKeyPressed(Input::ESCAPE)) {
		SaveLastMapStaus();
		sDirector->goBack();
	}

	int Size = mEntities.size();
	for (size_t i = 0; i < Size; i++){
		if (mEntities[i]->isAlive()) {

			switch (mEntities[i]->getClassName()){
			case MELE:
				mEntities[i]->SetTargetPos(playerPosX, playerPosY);
				mEntities[i]->update();
				break;
			case RANDOM:
				mEntities[i]->update();
				break;
			case DOOR:
				mEntities[i]->update();
				if (TotalEnemies <= EnemiesDead)
				{
					int y = mEntities[i]->GetMapPosY();
					int x = mEntities[i]->GetMapPosX();

					if (mpCollisionMap[y][x] == true)
					{
						mpCollisionMap[y][x] = false;
						Door* oDoor = new Door;
						oDoor->OpenDoor();

					}

				}
				
				break;
			case GEMS:
				mEntities[i]->update();
				break;
			case KEY:
				mEntities[i]->update();
				break;
			case CHEST:
				mEntities[i]->update();
				break;

			default:
				break;
			}

			mEntities[i]->update();
			C_Rectangle rectEntity = mEntities[i]->getRect();

			int HittedEnemy = player->EnemyHitted(mEntities[i]);

			switch (HittedEnemy)
			{
			case MELE:
				mEntities[i]->TakeHit();
				break;
			case RANDOM:
				mEntities[i]->TakeHit();
				break;
			default:
				break;
			}

			
			int collision = player->collidesWithEntity(mEntities[i]);
			switch (collision)
			{
			default:
				break;

			case MELE:
				player->TakeHit();
				//quitar vida al player
				break;
			case RANDOM:
				player->TakeHit();
				//quitar vida al player
				break;
			case DOOR:
					player->RestartPlayerPos(height, width);	
					SaveCurrentMap();
					LoadNextMap(mEntities[i]);
					initMap();
					//SetNewPlayerPos();
				break;
			case GEMS:
				sSoundManager->playSound("assets/Audios/ItemTake.wav");
				player->AddGem();
				mEntities[i]->setAlive(false);
				break;
			case CHEST:
				if (player->CheckKey())
				{
					sSoundManager->playSound("assets/Audios/OpenChest.wav");
					sDirector->changeScene(SceneDirector::WIN, false);
					//Win
				}else{
					if (chestTimePassed > chestTime)
					{
						sSoundManager->playSound("assets/Audios/ChestClosed.wav");
						chestTimePassed = 0;
					}
				}
				
				break;
			case KEY:
				sSoundManager->playSound("assets/Audios/ItemTake.wav");
				player->AddKey();
				mEntities[i]->setAlive(false);
				break;
				
			}

			
		}
	}
	

	if (player->GetHP() < 1)
	{
		sDirector->changeScene(SceneDirector::GAME_OVER, false);

		//cargar escena final
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
			
			if (mpCollisionMap[i][j] == true && map[i][j] != '1' && map[i][j] != '2' && map[i][j] != '3' && map[i][j] != '4' && map[i][j] != '5' && map[i][j] != '6')
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
	for (size_t i = 0; i < mEntities.size(); i++)
	{
		if (mEntities[i]->isAlive())
		{
			mEntities[i]->render();
		}
	}

	if (player->isAlive())
	{
		player->render();
	}
	//sRenderer->drawRectangle(rect2 , Color{ 0,255,0 });
	
	sRenderer->drawSprite(Heart_img_id, Heart_img_sprite_x, Heart_img_sprite_y, Heart_img_sprite_rect);

	switch (player->GetGems())
	{
	case 0:
		sRenderer->drawSprite(Zero_img_id, Gem_num_img_sprite_x, Gem_img_sprite_y, Gem_img_sprite_rect);
		break;
	case 1:
		sRenderer->drawSprite(One_img_id, Gem_num_img_sprite_x, Gem_img_sprite_y, Gem_img_sprite_rect);

		break;
	case 2:
		sRenderer->drawSprite(Two_img_id, Gem_num_img_sprite_x, Gem_img_sprite_y, Gem_img_sprite_rect);

		break;
	case 3:
		sRenderer->drawSprite(Three_img_id, Gem_num_img_sprite_x, Gem_img_sprite_y, Gem_img_sprite_rect);

		break;
	case 4:
		sRenderer->drawSprite(Four_img_id, Gem_num_img_sprite_x, Gem_img_sprite_y, Gem_img_sprite_rect);

		break;
	case 5:
		sRenderer->drawSprite(Five_img_id, Gem_num_img_sprite_x, Gem_img_sprite_y, Gem_img_sprite_rect);

		break;
	case 6:
		sRenderer->drawSprite(Six_img_id, Gem_num_img_sprite_x, Gem_img_sprite_y, Gem_img_sprite_rect);

		break;
	case 7:
		sRenderer->drawSprite(Seven_img_id, Gem_num_img_sprite_x, Gem_img_sprite_y, Gem_img_sprite_rect);

		break;
	case 8:
		sRenderer->drawSprite(Eight_img_id, Gem_num_img_sprite_x, Gem_img_sprite_y, Gem_img_sprite_rect);

		break;
	case 9:
		sRenderer->drawSprite(Nine_img_id, Gem_num_img_sprite_x, Gem_img_sprite_y, Gem_img_sprite_rect);

		break;
	case 10:
		sRenderer->drawSprite(Ten_img_id, Gem_num_img_sprite_x, Gem_img_sprite_y, Gem_img_sprite_rect);

		break;
	case 11:
		sRenderer->drawSprite(Eleven_img_id, Gem_num_img_sprite_x, Gem_img_sprite_y, Gem_img_sprite_rect);

		break;
	case 12:
		sRenderer->drawSprite(Twelve_img_id, Gem_num_img_sprite_x, Gem_img_sprite_y, Gem_img_sprite_rect);

		break;
	case 13:
		sRenderer->drawSprite(ThirdTeen_img_id, Gem_num_img_sprite_x, Gem_img_sprite_y, Gem_img_sprite_rect);

		break;
	case 14:
		sRenderer->drawSprite(FourTeen_img_id, Gem_num_img_sprite_x, Gem_img_sprite_y, Gem_img_sprite_rect);

		break;

	case 15:
		sRenderer->drawSprite(FiveTeen_img_id, Gem_num_img_sprite_x, Gem_img_sprite_y, Gem_img_sprite_rect);

		break;
	default:
		break;
	}

	sRenderer->drawSprite(Gem_img_id, Gem_img_sprite_x, Gem_img_sprite_y, Gem_img_sprite_rect);
	switch (player->GetHP())
	{
	case 0:
		sRenderer->drawSprite(Zero_img_id, Heart_num_img_sprite_x, Gem_img_sprite_y, Gem_img_sprite_rect);

	case 1:
		sRenderer->drawSprite(One_img_id, Heart_num_img_sprite_x, Gem_img_sprite_y, Gem_img_sprite_rect);

		break;
	case 2:
		sRenderer->drawSprite(Two_img_id, Heart_num_img_sprite_x, Gem_img_sprite_y, Gem_img_sprite_rect);

		break;
	case 3:
		sRenderer->drawSprite(Three_img_id, Heart_num_img_sprite_x, Gem_img_sprite_y, Gem_img_sprite_rect);

		break;
	case 4:
		sRenderer->drawSprite(Four_img_id, Heart_num_img_sprite_x, Gem_img_sprite_y, Gem_img_sprite_rect);

		break;
	case 5:
		sRenderer->drawSprite(Five_img_id, Heart_num_img_sprite_x, Gem_img_sprite_y, Gem_img_sprite_rect);

		break;
	case 6:
		sRenderer->drawSprite(Six_img_id, Heart_num_img_sprite_x, Gem_img_sprite_y, Gem_img_sprite_rect);

		break;
	case 7:
		sRenderer->drawSprite(Seven_img_id, Heart_num_img_sprite_x, Gem_img_sprite_y, Gem_img_sprite_rect);

		break;
	case 8:
		sRenderer->drawSprite(Eight_img_id, Heart_num_img_sprite_x, Gem_img_sprite_y, Gem_img_sprite_rect);

		break;
	case 9:
		sRenderer->drawSprite(Nine_img_id, Heart_num_img_sprite_x, Gem_img_sprite_y, Gem_img_sprite_rect);

		break;
	case 10:
		sRenderer->drawSprite(Ten_img_id, Heart_num_img_sprite_x, Gem_img_sprite_y, Gem_img_sprite_rect);

	default:
		break;
	}

	if (player->CheckKey())
	{
		sRenderer->drawSprite(Key_img_id, Key_img_sprite_x, Key_img_sprite_y, Key_img_sprite_rect);
		
	}
	else
	{
		sRenderer->drawSprite(Key_HUD_img_id, Key_img_sprite_x, Key_img_sprite_y, Key_img_sprite_rect);
	}

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
	map.resize(height);

	for (int i = 0; i < height; i++)
	{
		mpCollisionMap[i].resize(width, false);
		map[i].resize(width);
		std::getline(Map, line);
		for (int j = 0; j < width; j++)
		{
			mpCollisionMap[i][j] = false;

			char a_char = line[j];
			switch (a_char) {
			case '#':
				mpCollisionMap[i][j] = true;
				map[i][j] = '#';
				break;
			case 'P':
				//crear Player
				player->init(j * TILE_SIZE, i * TILE_SIZE);
				player->setCollisionsMap(&mpCollisionMap, width, height);

				break;
			case 'G':
				{
				Gems* aGem = new Gems();
				aGem->init(j * TILE_SIZE, i * TILE_SIZE);
				background.push_back(aGem);
				//crear Gema
				}	
				break;


			case 'O':
			{
				TotalEnemies++;
				//crear Enemigo 1
				Mele* aMele = new Mele();
				aMele->init(j * TILE_SIZE, i * TILE_SIZE);
				aMele->setCollisionsMap(&mpCollisionMap, width, height);
				foreground.push_back(aMele);
			}	break;
			case 'F':
			{
				TotalEnemies++;
				Random* aRandom = new Random();
				aRandom->init(j * TILE_SIZE, i * TILE_SIZE);
				aRandom->setCollisionsMap(&mpCollisionMap, width, height);
				foreground.push_back(aRandom);
				//crear Enemigo 2

			}	break;

			case 'K':
			{
				//crear Llave
				Key* aKey = new Key();
				aKey->init(j * TILE_SIZE, i * TILE_SIZE);
				background.push_back(aKey);

			}	break;
			case 'C':
			{
				//crear Cofre
				Chest* aChest = new Chest();
				aChest->init(j * TILE_SIZE, i * TILE_SIZE);
				background.push_back(aChest);

			}	break;
			case '1':
			{
				//new Door
				Door* aDoor1 = new Door();
				aDoor1->init(j * TILE_SIZE, i * TILE_SIZE);				
				aDoor1->SetNextMap(1);
				mpCollisionMap[i][j] = true;
				map[i][j] = '1';
				foreground.push_back(aDoor1);
			}	break;
			case '2':
			{
				Door* aDoor2 = new Door();
				aDoor2->init(j * TILE_SIZE, i * TILE_SIZE);
				aDoor2->SetNextMap(2);
				mpCollisionMap[i][j] = true;
				map[i][j] = '2';
				foreground.push_back(aDoor2);
			}	break;
			case '3':
				{
				Door* aDoor3 = new Door();
				aDoor3->init(j * TILE_SIZE, i * TILE_SIZE);
				aDoor3->SetNextMap(3);
				mpCollisionMap[i][j] = true;
				map[i][j] = '3';
				foreground.push_back(aDoor3);
				}break;
			case '4':
			{
				Door* aDoor4 = new Door();
				aDoor4->init(j * TILE_SIZE, i * TILE_SIZE);
				aDoor4->SetNextMap(4);
				mpCollisionMap[i][j] = true;
				map[i][j] = '4';
				foreground.push_back(aDoor4);
			}	break;
			case '5':
			{
				Door* aDoor5 = new Door();
				aDoor5->init(j * TILE_SIZE, i * TILE_SIZE);
				aDoor5->SetNextMap(5);
				mpCollisionMap[i][j] = true;
				map[i][j] = '5';
				foreground.push_back(aDoor5);
			}	break;
			case '6':
			{
				Door* aDoor6 = new Door();
				aDoor6->init(j * TILE_SIZE, i * TILE_SIZE);
				aDoor6->SetNextMap(6);
				mpCollisionMap[i][j] = true;
				map[i][j] = '6';
				foreground.push_back(aDoor6);
			}	break;
			
			}
		}


	}

	int BGsize = background.size();
	int FGsize = foreground.size();

	
	for (int i = 0; i < BGsize; i++)
	{
		mEntities.push_back(background[i]);
	}
	for (int i = 0; i < FGsize; i++)
	{
		mEntities.push_back(foreground[i]);
	}

	for (int i = 0; i < BGsize; i++)
	{
		background.pop_back();;
	}

	for (int i = 0; i < FGsize; i++)
	{
		foreground.pop_back();;
	}


	std::getline(Map, line);
	loadedMap = atoi(line.c_str());

	if (CurrentMap == "Maps/LastMapSaved.txt")
	{
		std::getline(Map, line);
		player->SetGems(atoi(line.c_str()));

		std::getline(Map, line);
		player->SetHP(atoi(line.c_str()));

		int haveKey;

		std::getline(Map, line);
		haveKey = atoi(line.c_str());

		if (haveKey == 1)
		{
			player->AddKey();
		}

	}

	Map.close();
}

void SceneGame::StartGame(){

	if (sDirector->checkCurrentScene('R'))
	{
		CurrentMap = "Maps/LastMapSaved.txt";
		//load player status
	}else if (sDirector->checkCurrentScene('N'))
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
		CurrentSaveMap = "Maps/map_1_saved.txt";
		break;
	case 2:
		CurrentSaveMap = "Maps/map_2_saved.txt";
		break;
	case 3:
		CurrentSaveMap = "Maps/map_3_saved.txt";
		break;
	case 4:
		CurrentSaveMap = "Maps/map_4_saved.txt";
		break;
	case 5:
		CurrentSaveMap = "Maps/map_5_saved.txt";
		break;
	case 6:
		CurrentSaveMap = "Maps/map_6_saved.txt";
		break;

	default:
		break;
	}

	SaveMap.open(CurrentSaveMap, std::ios::out | std::ios::trunc);
	std::cout << "Guardando mapa " << loadedMap << std::endl;

	SaveMap << width << "\n";
	SaveMap << height;

	for (int i = 0; i < height; i++) {
		SaveMap << "\n";
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
				if (mEntities[c]->GetMapPosX() == j && mEntities[c]->GetMapPosY() == i && mEntities[c]->isAlive()) {
					switch (mEntities[c]->getClassName()) {
					case GEMS:
						map[i][j] = 'G';
						break;

					case CHEST:
						map[i][j] = 'C';
						break;
					case KEY:
						map[i][j] = 'K';
						break;

					default:
						break;
					}
				}

			}

			if (map[i][j] != '1' && map[i][j] != '2' && map[i][j] != '3' && map[i][j] != '4' && map[i][j] != '5' && map[i][j] != '6'){
				if (mpCollisionMap[i][j] == true){
					map[i][j] = '#';
				}
			}

			SaveMap << map[i][j];
		}
	}
	
	SaveMap << "\n" << loadedMap; 
	SaveMap.close();


}

void SceneGame::LoadNextMap(Entity* ent) {

	
	NextMap = ent->GetNextMap();

	switch (NextMap){
	case 1:
		NextLoadMap = "Maps/map_1.txt";
		NextLoadSavedMap = "Maps/map_1_saved.txt";
		break;
	case 2:
		NextLoadMap = "Maps/map_2.txt";
		NextLoadSavedMap = "Maps/map_2_saved.txt";
		break;
	case 3:
		NextLoadMap = "Maps/map_3.txt";
		NextLoadSavedMap = "Maps/map_3_saved.txt";
		break;
	case 4:
		NextLoadMap = "Maps/map_4.txt";
		NextLoadSavedMap = "Maps/map_4_saved.txt";
		break;
	case 5:
		NextLoadMap = "Maps/map_5.txt";
		NextLoadSavedMap = "Maps/map_5_saved.txt";
		break;
	case 6:
		NextLoadMap = "Maps/map_6.txt";
		NextLoadSavedMap = "Maps/map_6_saved.txt";
		break;

	default:
		break;
	}
	std::fstream LoadMap;
	std::string TotalNextMap;
	LoadMap.open(NextLoadSavedMap, std::ios::in);
	if (!LoadMap.is_open())
	{
		LoadMap.open(NextLoadMap, std::ios::in);
		TotalNextMap = NextLoadMap;
	}
	else
	{
		TotalNextMap = NextLoadSavedMap;
	}

	if (LoadMap.is_open())
	{
		//cargar mapa
		CurrentMap = TotalNextMap;
	}
	else{
		std::cout << "Error Loading Map" << std::endl;
	}


	for (size_t i = 0; i < mEntities.size(); i++)
	{
		mEntities[i]->setAlive(false);

	}

	LoadMap.close();

	
}

void SceneGame::SaveLastMapStaus(){
	//Guardar el estado del mapa (enemigos, objetos ...) en el archivo de Maps/LastMapSaved.txt
	//Guardar el estado del jugador(Posicion, objetos, vida ...)
	
	std::fstream SaveMap;
	std::string CurrentNextMap;

	SaveMap.open("Maps/LastMapSaved.txt", std::ios::out | std::ios::trunc);
	if (!SaveMap.is_open()) {
		std::cout << "Error Guardando el mapa" << std::endl;
	}
	SaveMap << width << "\n";
	SaveMap << height;

	for (int i = 0; i < height; i++) {
		SaveMap << "\n";
		for (int j = 0; j < width; j++)
		{
			if (map[i][j] != '1' && map[i][j] != '2' && map[i][j] != '3' && map[i][j] != '4' && map[i][j] != '5' && map[i][j] != '6')
			{
				map[i][j] = '*';

			}
			
			for (int c = 0; c < mEntities.size(); c++)
			{
				if (mEntities[c]->GetMapPosX() == j && mEntities[c]->GetMapPosY() == i && mEntities[c]->isAlive()) {
					switch (mEntities[c]->getClassName()) {
					case MELE:
						map[i][j] = 'O';
						break;
					case RANDOM:
						map[i][j] = 'F';
						break;
					case GEMS:
						map[i][j] = 'G';
						break;

					case CHEST:
						map[i][j] = 'C';
						break;

					case KEY:
						map[i][j] = 'K';
						break;

					default:
						break;
					}
				}
			}
			if (player->GetMapPosX() == j && player->GetMapPosY() == i)
			{
				map[i][j] = 'P';
			}
			if (map[i][j] != '1' && map[i][j] != '2' && map[i][j] != '3' && map[i][j] != '4' && map[i][j] != '5' && map[i][j] != '6')
			{
				if (mpCollisionMap[i][j] == true)
				{
					map[i][j] = '#';
				}
			}
			SaveMap << map[i][j];
		}
		

	}

	for (int e = 0; e < mEntities.size(); e++){


		mEntities.pop_back();
	}
	SaveMap << "\n" << loadedMap << "\n" << player->GetGems() << "\n" << player->GetHP() << "\n" << player->CheckKey();

	//guardar inventario
	SaveMap.close();


}

