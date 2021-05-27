#ifndef SCENEGAME_H
#define SCENEGAME_H

#include "Scene.h"
#include "Link.h"
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
		void LoadNextMap(char NextMap);
		void SaveCurrentMap(char NextMap);
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

		int				Door_sprite_id;
		int				Door_sprite_x;
		int				Door_sprite_y;
		C_Rectangle		Door_sprite_rect;

		std::vector<std::vector <char> > map;
		std::vector<std::vector<bool>> mpCollisionMap;
		std::string CurrentMap;


		Link* player;
};



#endif
