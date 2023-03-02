#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>

using namespace std;
using namespace sf;
using namespace sfp;

int main()
{
	// Create our window and world with gravity 0,1
	RenderWindow window(VideoMode(800, 600), "Bounce");
	World world(Vector2f(0, 1));

	// Create the ball
	PhysicsCircle ball;
	ball.setCenter(Vector2f(200, 150));
	ball.setRadius(20);
	world.AddPhysicsBody(ball);
	ball.applyImpulse(Vector2f(0.2, 0.5));

	// Create the floor
	PhysicsRectangle floor;
	floor.setSize(Vector2f(760, 20));
	floor.setCenter(Vector2f(400, 590));
	floor.setStatic(true);
	world.AddPhysicsBody(floor);

	// Create the walls
	PhysicsRectangle wallleft;
	wallleft.setSize(Vector2f(20, 760));
	wallleft.setCenter(Vector2f(10, 300));
	wallleft.setStatic(true);
	world.AddPhysicsBody(wallleft);

	PhysicsRectangle wallright;
	wallright.setSize(Vector2f(20, 760));
	wallright.setCenter(Vector2f(790, 300));
	wallright.setStatic(true);
	world.AddPhysicsBody(wallright);

	// Crate the ceiling
	PhysicsRectangle ceiling;
	ceiling.setSize(Vector2f(760, 20));
	ceiling.setCenter(Vector2f(400, 10));
	ceiling.setStatic(true);
	world.AddPhysicsBody(ceiling);

	// Create the obstacle
	PhysicsRectangle obstacle;
	obstacle.setSize(Vector2f(100, 100));
	obstacle.setCenter(Vector2f(400, 300));
	obstacle.setStatic(true);
	world.AddPhysicsBody(obstacle);

	//Create thuds
	int thudCount(0);
	int bangCount(0);

	floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		thudCount++;
		cout << "Thud: " << thudCount << endl;
	};

	wallleft.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		thudCount++;
		cout << "Thud: " << thudCount << endl;
	};

	wallright.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		thudCount++;
		cout << "Thud: " << thudCount << endl;
	};

	ceiling.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		thudCount++;
		cout << "Thud: " << thudCount << endl;
	};

	obstacle.onCollision = [&bangCount](PhysicsBodyCollisionResult result) {
		bangCount++;
		cout << "Bang: " << bangCount << endl;
		if (bangCount == 3) {
			exit(0);
		}
	};

	Clock clock;
	Time lastTime(clock.getElapsedTime());

	while (true) {

		// calculate MS since last frame
		Time currentTime(clock.getElapsedTime());
		Time deltaTime(currentTime - lastTime);
		int deltaTimeMS(deltaTime.asMilliseconds());

		if (deltaTimeMS > 0) {
			world.UpdatePhysics(deltaTimeMS);
			lastTime = currentTime;
		}

		window.clear(Color(0, 0, 0));
		window.draw(obstacle);
		window.draw(ceiling);
		window.draw(wallright);
		window.draw(wallleft);
		window.draw(ball);
		window.draw(floor);
		window.display();
	}

	
}
