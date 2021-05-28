#ifndef INCLUDES_H
#define INCLUDES_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <map>
#include <stack>
#include "math.h"

#define WINDOW_TITLE "Zelda Breath of The Wild 5"
#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 540

#define TILE_SIZE 32


enum Classes { NOTHING, ENTITY, LINK, MELE, RANDOM, DOOR, GEMS };

//! Struct C_Rectangle.
typedef struct { 
	  int x;
	  int y;
	  unsigned int w;
	  unsigned int h;
} C_Rectangle;

//! Struct Color
typedef struct {
	unsigned char r;
	unsigned char g;
	unsigned char b;

}Color;
//! Struct Point.
/*! A point in 2D. */
struct Point { 
	int x;
	int y;

	bool operator==(const Point& a) const
	{
		return (x == a.x && y == a.y);
	}
	bool operator!=(const Point& a) const
	{
		return (x != a.x || y != a.y);
	}
};

//! Struct Triangle.
/*! Struct that consists of 3 points. */
typedef struct { 
	Point a;
	Point b;
	Point c;
} C_Triangle;

// Tiempo pasado entre frames
extern unsigned int global_delta_time;


//Eliminar vectores de punteros
template <class C> void FreeClear( C & cntr ) {
    for ( typename C::iterator it = cntr.begin(); 
              it != cntr.end(); ++it ) {
    	delete * it;
    }
    cntr.clear();
	cntr.shrink_to_fit(); //Hace que la memoria reservada sea la necesaria para el nuevo tama�o (0)
}

#endif
