#include <raylib.h>

const int height = 700;
const int width  = 500;

struct
entity {
	Vector2 pos; // position
	Vector2 siz; // size
	Vector2 spd; // speed
	int jog;
	Texture2D image;
};

enum keyenum {
	up,
	down,
	left,
	right,
	jogl,
	jogr,
};

const char keymap[6] = {'W','S','A','D','L','K'};

void
move(struct entity* e)
{ // todo : use delta t
	e->pos.y -= IsKeyDown(keymap[up])    ? e->spd.y : 0 ;
	e->pos.y += IsKeyDown(keymap[down])  ? e->spd.y : 0 ;
	e->pos.x -= IsKeyDown(keymap[left])  ? e->spd.x : 0 ;
	e->pos.x += IsKeyDown(keymap[right]) ? e->spd.x : 0 ;

	e->pos.x -= IsKeyUp(keymap[jogl]) ? e->jog : 0 ;
	e->pos.x += IsKeyUp(keymap[jogr]) ? e->jog : 0 ;
}


void
bound(struct entity* e)
{ /* normalize to screen borders */
	if(e->pos.y + e->siz.y > height) {
		e->pos.y = height - e->siz.y;
	} else if (e->pos.y < 0) {
		e->pos.y = 0;
	}
	if(e->pos.x + e->siz.x > width) {
		e->pos.x = width - e->siz.x;
	} else if (e->pos.x < 0) {
		e->pos.x = 0;
	}
}


int
main()
{
	InitWindow(width, height, "Win");
	SetTargetFPS(60);


	struct entity e = {
		.spd = {10, 10},
		.siz = {width / 8, height / 8},
		.pos = {width / 2 - width/16, height / 1.4},
		.jog = 30,
	};

	Image img = LoadImage("art/flota.png");
	ImageResize(&img, e.siz.x, e.siz.y);
	e.image = LoadTextureFromImage(img);
	UnloadImage(img);

	struct entity f[10];

	while(!WindowShouldClose()){
		BeginDrawing();

		ClearBackground(BLACK);

		move(&e);
		bound(&e);

		DrawTexture(
			e.image,
			e.pos.x,
			e.pos.y,
			LIGHTGRAY);

		EndDrawing();
	}

	UnloadTexture(e.image);
	CloseWindow();
	return 0;
}
