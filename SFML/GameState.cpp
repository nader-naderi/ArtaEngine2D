#include "GameState.hpp"
#include <sstream>

#include "DEFINITIONS.hpp"
#include "PuaseState.hpp"
#include <iostream>

namespace NDR
{
	GameState::GameState(GameDataRef data) : _data(data)
	{

	}


	void GameState::Init()
	{
		gameState = STATE_PLAYING;
		turn = PLAYER_PIECE;

		this->_data->assets.LoadTexture("Pause Button", PUASE_BUTTON);
		this->_data->assets.LoadTexture("Grid Sprite", GRID_SPRITE_FILEPATH);
		this->_data->assets.LoadTexture("X Piece", X_PIECE_FILEPATH);
		this->_data->assets.LoadTexture("O Piece", O_PIECE_FILEPATH);

		this->_background.setTexture(this->_data->assets.GetTexture("Background"));
		this->_pauseButton.setTexture(this->_data->assets.GetTexture("Pause Button"));
		this->_gridSprite.setTexture(this->_data->assets.GetTexture("Grid Sprite"));


		this->_pauseButton.setPosition(this->_data->window.getSize().x - this->_pauseButton.getLocalBounds().width,
			this->_pauseButton.getPosition().y);

		this->_gridSprite.setPosition((SCREEN_WIDTH / 2) - (_gridSprite.getGlobalBounds().width / 2), 
			(SCREEN_HEIGHT / 2) - (_gridSprite.getGlobalBounds().height / 2));

		InitGridPieces();

		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				gridArray[x][y] = EMPTY_PIECE;
			}
		}
	}


	void GameState::HandleInput()
	{
		sf::Event e;
		while (this->_data->window.pollEvent(e))
		{
			if (sf::Event::Closed == e.type)
			{
				this->_data->window.close();
			}

			if (this->_data->input.isSpriteClicked(this->_pauseButton, sf::Mouse::Left, this->_data->window))
			{
				std::cout << "Puase the Game\n";
				this->_data->machine.AddState(StateRef(new PauseState(_data)), false);
			}
			else if (this->_data->input.isSpriteClicked(this->_gridSprite, sf::Mouse::Left, this->_data->window))
			{
				this->CheckAndPlacePiece();
			}
		}
	}


	void GameState::Update(float deltaTime)
	{

	}


	void GameState::Draw(float deltaTime)
	{
		this->_data->window.clear();

		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_pauseButton);
		this->_data->window.draw(this->_gridSprite);

		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				this->_data->window.draw(this->_gridPieces[x][y]);
			}
		}

		this->_data->window.display();

	}

	void GameState::InitGridPieces()
	{
		sf::Vector2u tempSpriteSize = this->_data->assets.GetTexture("X Piece").getSize();

		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				_gridPieces[x][y].setTexture(this->_data->assets.GetTexture("X Piece"));

				_gridPieces[x][y].setPosition(_gridSprite.getPosition().x + (tempSpriteSize.x * x) - 7,
					_gridSprite.getPosition().y + (tempSpriteSize.y * y) - 7);


				_gridPieces[x][y].setColor(sf::Color(255, 255, 255, 255));
			}
		}
	}

	
	void GameState::CheckAndPlacePiece()
	{
		sf::Vector2i touchPoint = this->_data->input.GetMousePosition(this->_data->window);
		
		sf::FloatRect gridSize = _gridSprite.getGlobalBounds();
		
		sf::Vector2f gapOutsideOfGrid = sf::Vector2f((SCREEN_WIDTH - gridSize.width) / 2, (SCREEN_HEIGHT - gridSize.height) / 2);
		
		sf::Vector2f gridLocalTouchPos = sf::Vector2f(touchPoint.x - gapOutsideOfGrid.x, touchPoint.y - gapOutsideOfGrid.y);

		sf::Vector2f gridSctionSize = sf::Vector2f(gridSize.width / 3, gridSize.height / 3);

		int column, row;

		if (gridLocalTouchPos.x < gridSctionSize.x)
		{
			column = 1;
		}
		else if (gridLocalTouchPos.x < gridSctionSize.x * 2)
		{
			column = 2;
		}
		else if (gridLocalTouchPos.x < gridSize.width)
		{
			column = 3;
		}

		if (gridLocalTouchPos.y < gridSctionSize.y)
		{
			row = 1;
		}
		else if (gridLocalTouchPos.y < gridSctionSize.y * 2)
		{
			row = 2;
		}
		else if (gridLocalTouchPos.y < gridSize.height)
		{
			row = 3;
		}

		if (gridArray[column - 1][row - 1] == EMPTY_PIECE)
		{
			gridArray[column - 1][row - 1] == turn;

			if (PLAYER_PIECE == turn) {
				_gridPieces[column - 1][row - 1].setTexture(this->_data->assets.GetTexture("X Piece"));

				turn = AI_PIECE;
			}
			else if (AI_PIECE == turn) {
				_gridPieces[column - 1][row - 1].setTexture(this->_data->assets.GetTexture("O Piece"));

				turn = PLAYER_PIECE;
			}

			_gridPieces[column - 1][row - 1].setColor(sf::Color(255, 255, 255, 255));
		}
	}


}