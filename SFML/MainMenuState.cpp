#include "MainMenuState.hpp"
#include <sstream>

#include "DEFINITIONS.hpp"
#include "GameState.hpp"
#include <iostream>

namespace NDR
{
	MainMenuState::MainMenuState(GameDataRef data) : _data(data)
	{

	}

	
	void MainMenuState::Init()
	{
		this->_data->assets.LoadTexture("Background", MAIN_MENU_BACKGROUND_FILEPATH);

		this->_data->assets.LoadTexture("Play Button", MAIN_MENU_PLAY_BUTTON);

		this->_data->assets.LoadTexture("Play Button Outer", MAIN_MENU_PLAY_BUTTON_OUTER);

		this->_data->assets.LoadTexture("Game Title", MAIN_MENU_TITLE_PATH);

		this->_background.setTexture(this->_data->assets.GetTexture("Background"));

		this->_playButton.setTexture(this->_data->assets.GetTexture("Play Button"));

		this->_playButtonOuter.setTexture(this->_data->assets.GetTexture("Play Button Outer"));

		this->_title.setTexture(this->_data->assets.GetTexture("Game Title"));

		this->_playButton.setPosition((SCREEN_WIDTH / 2) - (this->_playButton.getGlobalBounds().width / 2),
			(SCREEN_HEIGHT / 2) - (this->_playButton.getGlobalBounds().height / 2));

		this->_playButtonOuter.setPosition((SCREEN_WIDTH / 2) - (this->_playButtonOuter.getGlobalBounds().width / 2),
			(SCREEN_HEIGHT / 2) - (this->_playButtonOuter.getGlobalBounds().height / 2));

		this->_title.setPosition((SCREEN_WIDTH / 2) - (this->_title.getGlobalBounds().width / 2),
			(SCREEN_HEIGHT / 2) - (this->_title.getGlobalBounds().height * 0.1f));
	}

	
	void MainMenuState::HandleInput()
	{
		sf::Event e;
		while (this->_data->window.pollEvent(e))
		{
			if (sf::Event::Closed == e.type)
			{
				this->_data->window.close();
			}

			if (this->_data->input.isSpriteClicked(this->_playButton, sf::Mouse::Left, this->_data->window))
			{
				std::cout << "Go to Game Screen\n";
				this->_data->machine.AddState(StateRef(new GameState(_data)), true);
			}
		}
	}

	
	void MainMenuState::Update(float deltaTime)
	{

	}

	
	void MainMenuState::Draw(float deltaTime)
	{
		this->_data->window.clear();

		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_playButton);
		this->_data->window.draw(this->_playButtonOuter);
		this->_data->window.draw(this->_title);

		this->_data->window.display();

	}

	
}