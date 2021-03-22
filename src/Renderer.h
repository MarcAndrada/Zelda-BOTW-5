#pragma once

#ifndef RENDERER_H

#define RENDERER_H

#include"includes.h"
#include <SFML/Graphics.hpp>


class Renderer
{
	public:
		Renderer();
		~Renderer();
		
		/*!
		* Inits the screen
		*/
		void initWindow();
		
		/*!
		* Clean the Window
		*/
		void WindowClear();

		/*!
		* Performs Screen Draw (screen flip)
		*/
		void WindowRefresh();
		
		/*!
		* Return true if the screen is open
		*/
		bool WindowIsOpen();


		void drawRectangle(C_Rectangle rect, Color col, bool outline = false );

		//!SpriteDraw
		void drawSprite(int ID, int posX, int posY, C_Rectangle rect);

		void setFramerate(int framerate);
		/*!
		* Returns the Window Pointer
		*/
		sf::RenderWindow* getWindow() { return mWindow; };
		/*!
		* Returns the Window Pointer
		*/
		static Renderer* getInstance();
	private:
		static Renderer* instance;
		sf::RenderWindow* mWindow;
		int mWindowWidth;
		int mWindowHeight;
		
};

#endif
