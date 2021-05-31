#ifndef SCENEGAME_H
#define SCENEGAME_H

#include "Scene.h"
#include "Utils.h"
#include "Link.h"
#include "Door.h"
#include "Mele.h"
#include "Random.h"
#include "Gems.h"
#include "Key.h"
#include "Chest.h"
#include "Entity.h"

class SceneGame : public Scene
{
	public:
		SceneGame();
		~SceneGame();
		

		virtual void preLoad();
		virtual void unLoad();

	protected:
		virtual void init();

		virtual void updateBegin();
		virtual void update();
		virtual void updateEnd();

		virtual void renderBegin();
		virtual void render();
		virtual void renderEnd();

		virtual void renderGUI();
		
		void initMap();
		void StartGame();
		void SaveCurrentMap();
		void LoadNextMap(Entity* ent);
		void SaveLastMapStaus();


	private:
		C_Rectangle		rect1;
		C_Rectangle		rect2;
		int				sprite_id;
		C_Rectangle		sprite_rect;
		int				sprite_frame;
		int				sprite_frame_time;
		int				sprite_x;
		int				sprite_y;
		int				width;
		int				height;

		int				Wall_sprite_id;
		int				Wall_sprite_x;
		int				Wall_sprite_y;
		C_Rectangle		Wall_sprite_rect;

		int				Floor_sprite_id;
		int				Floor_sprite_x;
		int				Floor_sprite_y;
		C_Rectangle		Floor_sprite_rect;

		int			Gem_img_id;
		int			Gem_img_sprite_x;
		int			Gem_img_sprite_y;
		C_Rectangle Gem_img_sprite_rect;
		
		int Key_img_id;
		int Key_HUD_img_id;
		int Key_img_sprite_x;
		int Key_img_sprite_y;
		C_Rectangle Key_img_sprite_rect;

		int			Heart_img_id;
		int			Heart_img_sprite_x;
		int			Heart_img_sprite_y;
		C_Rectangle Heart_img_sprite_rect;
		
		int Zero_img_id;
		int One_img_id;
		int Two_img_id;
		int Three_img_id;
		int Four_img_id;
		int Five_img_id;
		int Six_img_id;
		int Seven_img_id;
		int Eight_img_id;
		int Nine_img_id;
		int Ten_img_id;
		int Eleven_img_id;
		int Twelve_img_id;
		int ThirdTeen_img_id;
		int FourTeen_img_id;
		int FiveTeen_img_id;
		
		int  Heart_num_img_sprite_x;
		int  Heart_num_img_sprite_y;
		C_Rectangle Heart_num_img_sprite_rect;

		int  Gem_num_img_sprite_x;
		int  Gem_num_img_sprite_y;
		C_Rectangle Gem_num_img_sprite_rect;



		std::string		NextLoadMap;
		std::string		NextLoadSavedMap;
		int				NextMap;

		int				TotalEnemies;
		int				EnemiesDead;

		std::vector<std::vector <char> > map;
		std::vector<std::vector<bool>> mpCollisionMap;
		int EnemiesVectorPos[10];
		std::string CurrentMap;
		int loadedMap;

		Link* player;
		std::vector<Entity*>mEntities;
		int chestTimePassed;
		int chestTime = 2000;

};



#endif
