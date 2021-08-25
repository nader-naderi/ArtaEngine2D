#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace NDR
{
	class MainMenuState : public State
	{
	public:
		MainMenuState(GameDataRef data);

		void Init();

		void HandleInput();

		void Update(float deltaTime);

		void Draw(float deltaTime);

	private:
		GameDataRef _data;

		sf::Sprite _background;

		sf::Sprite _playButton;

		sf::Sprite _playButtonOuter;

		sf::Sprite _title;
	};
}