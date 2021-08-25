#include <sstream>

#include "SpashState.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>
#include "MainMenuState.hpp"

namespace NDR
{
	SplashState::SplashState(GameDataRef data) : _data(data)
	{

	}

	void SplashState::Init()
	{
		this->_data->assets.LoadTexture("Splash State Background", SPLASH_SCENE_BACKGROUND_FILEPATH);
		_background.setTexture(this->_data->assets.GetTexture("Splash State Background"));
	}

	void SplashState::HandleInput()
	{
		sf::Event evnt;

		while (this->_data->window.pollEvent(evnt))
		{
			if (sf::Event::Closed == evnt.type)
			{
				this->_data->window.close();
			}
		}
	}

	void SplashState::Update(float deltaTime)
	{
		if (this->_clock.getElapsedTime().asSeconds() > SPLASH_SCENE_SHOW_TIME)
		{
			// Switch to the main menu.
			std::cout << "GO to main menu." << std::endl;
			this->_data->machine.AddState(StateRef(new MainMenuState(this->_data)), true);
		}
	}

	
	void SplashState::Draw(float deltaTime)
	{
		this->_data->window.clear(sf::Color::Red);

		this->_data->window.draw(this->_background);

		this->_data->window.display();
	}

	
}