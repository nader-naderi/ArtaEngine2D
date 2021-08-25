#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace NDR
{
	class GameState : public State
	{
	public:
		GameState(GameDataRef data);

		void Init();

		void HandleInput();

		void Update(float deltaTime);

		void Draw(float deltaTime);

	private:
		void InitGridPieces();

		void CheckAndPlacePiece();

		GameDataRef _data;

		sf::Sprite _background;

		sf::Sprite _pauseButton;

		sf::Sprite _gridSprite;

		sf::Sprite _gridPieces[3][3];
		int gridArray[3][3];

		int turn;
		int gameState;
	};
}