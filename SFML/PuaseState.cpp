#include "MainMenuState.hpp"
#include <sstream>

#include "DEFINITIONS.hpp"
#include "PuaseState.hpp"
#include "MainMenuState.hpp"
#include <iostream>

namespace NDR
{
	PauseState::PauseState(GameDataRef data) : _data(data)
	{

	}


	void PauseState::Init()
	{
		this->_data->assets.LoadTexture("Pause Background", PAUSE_BACKGROUND_FILEPATH);
		this->_data->assets.LoadTexture("Resume Button", RESUME_BUTTON);
		this->_data->assets.LoadTexture("Home Button", HOME_BUTTON);

		this->_background.setTexture(this->_data->assets.GetTexture("Pause Background"));
		this->_resumeBtn.setTexture(this->_data->assets.GetTexture("Resume Button"));
		this->_homeBtn.setTexture(this->_data->assets.GetTexture("Home Button"));

		this->_resumeBtn.setPosition((this->_data->window.getSize().x / 2) - (this->_resumeBtn.getLocalBounds().width / 2),
			(this->_data->window.getSize().y / 3) - (this->_resumeBtn.getLocalBounds().height / 2));

		this->_homeBtn.setPosition((this->_data->window.getSize().x / 2) - (this->_homeBtn.getLocalBounds().width / 2),
			(this->_data->window.getSize().y / 3 * 2) - (this->_homeBtn.getLocalBounds().height / 2));
	}


	void PauseState::HandleInput()
	{
		sf::Event e;
		while (this->_data->window.pollEvent(e))
		{
			if (sf::Event::Closed == e.type)
			{
				this->_data->window.close();
			}

			if (this->_data->input.isSpriteClicked(this->_resumeBtn, sf::Mouse::Left, this->_data->window))
			{
				this->_data->machine.RemoveState();
			}

			if (this->_data->input.isSpriteClicked(this->_homeBtn, sf::Mouse::Left, this->_data->window))
			{
				this->_data->machine.RemoveState();
				this->_data->machine.AddState(StateRef(new MainMenuState(_data)), true);
			}
		}
	}


	void PauseState::Update(float deltaTime)
	{

	}


	void PauseState::Draw(float deltaTime)
	{
		this->_data->window.clear();

		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_resumeBtn);
		this->_data->window.draw(this->_homeBtn);
		
		this->_data->window.display();

	}


}