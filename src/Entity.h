#pragma once
#include <math.h>
#define ORIGIN 125 //500 / 4
#define PLAYER_MAXSPEED 3

#include <stdio.h>

struct Vector {
	float x;
	float y;
};
struct Entity {
	struct Vector position;
	struct Vector direction;
	float speed;

	/// <summary>
	/// <para>Isto controla o que acontece a duas entidades colidem uma com a outra</para>
	/// <para>0 rigid			</para>
	/// <para>1 player __ -1 friendly hazard	</para>
	/// <para>2 hostile__ -2 hostile  hazard	</para>
	/// <para>3 pickup	</para>
	/// </summary>
	int surface;
	float radius;	//collision box radius
	/// <summary>
	/// <para>0 player						</para>
	/// <para>1 enemy thrower				</para>
	/// <para>2 enemy thrower projectile	</para>
	/// <para>3 enemy blob Small			</para>
	/// <para>4 enemy blob Big				</para>
	/// <para>5 pickup						</para>
	/// <para>6 jar							</para>
	/// <para>7 block						</para>
	/// <para>8 playerSword					</para>
	/// </summary>
	int kind;

	int frame;
	int slot;
};


//Utils
float Distance(struct Vector* pointA, struct Vector* pointB) {
	return sqrt(
		(pointA->x - pointB->x) * (pointA->x - pointB->x) +
		(pointA->y - pointB->y) * (pointA->y - pointB->y)
	);
}
struct Vector SetVectorLength(float x, float y, float length) {
	float magnitude = sqrt(x * x + y * y);
	struct Vector vector;
	vector.x = (x / magnitude) * length/2;
	vector.y = (y / magnitude) * length/2;
	return vector;
}
int IsInsideMyBoundries_Circle(struct Entity* me, struct Entity* him) {
	if (Distance(&me->position, &him->position) < me->radius) return 1;
	else return 0;
}


struct Entity Player() {
	struct Entity entity;
	entity.position.x = ORIGIN;
	entity.position.y = ORIGIN;
	entity.direction.x = 0;
	entity.direction.y = -1;
	entity.speed = 0;

	entity.surface = 1;
	entity.radius = 10;
	entity.kind = 0;
	return entity;
}
struct Entity PlayerSword(struct Entity player) {
	struct Entity entity;
	entity.position.x = player.position.x + player.direction.x * player.radius;
	entity.position.y = player.position.y + player.direction.y * player.radius;
	entity.direction = player.direction;

	entity.surface = -1;
	entity.radius = 15;
	entity.kind = 8;
	entity.frame = 0;
	return entity;
}
struct Entity PickUp(struct Vector position) {
	struct Entity entity;
	entity.position = position;

	entity.surface = 3;
	entity.radius = 10;
	entity.kind = 5;
	return entity;
}
struct Entity Jar(struct Vector position) {
	struct Entity entity;
	entity.position = position;

	entity.surface = 0;
	entity.radius = 10;
	entity.kind = 6;
	return entity;
}
struct Entity Block(struct Vector position) {
	struct Entity entity;
	entity.position = position;

	entity.surface = 0;
	entity.radius = 10;
	entity.kind = 7;
	return entity;
}