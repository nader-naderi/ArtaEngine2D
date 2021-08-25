#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace NDR
{
	class SplashState : public State
	{
	public:
		SplashState(GameDataRef data);

		void Init();

		void HandleInput();

		void Update(float deltaTime);

		void Draw(float deltaTime);

	private :
		GameDataRef _data;
		
		sf::Clock _clock;

		sf::Sprite _background;

	};
}