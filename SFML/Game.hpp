#pragma once

#include <memory>
#include <string>

#include "StateMachine.hpp"
#include "AssetManager.hpp"
#include "InputManager.hpp"
#include "SFML/Graphics.hpp"

namespace NDR
{
	struct GameData
	{
		StateMachine machine;
		sf::RenderWindow window;
		AssetManager assets;
		InputManager input;
	};

	typedef std::shared_ptr<GameData> GameDataRef;

	class Game
	{
	public:
		Game(int width, int height, std::string title);

	private:
		const float deltaTime = 1.0f / 60.0f;
		sf::Clock _clock;

		GameDataRef _data = std::make_shared<GameData>();

		void Run();
	};
}