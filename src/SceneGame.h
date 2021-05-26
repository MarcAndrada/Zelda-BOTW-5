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
		void SaveLastMapStaus();

	private:
		C_Rectangle		rect1;
		C_Rectangle		rect2;
		int				sprite_id;
		C_Rectangle		sprite_rect;
		int				sprite_frame;
		int				sprite_frame_time;
		int sprite_x;
		int sprite_y;
		std::vector<std::vector<bool>> mpCollisionMap;
		std::string CurrentMap;


		Link* player;
};



#endif
