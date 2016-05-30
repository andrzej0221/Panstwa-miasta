#include "stdafx.h"
#include "ChoosePlayerScreen.h"
#include "ButtonView.h"
#include "Game.h"

ChoosePlayerScreen::ChoosePlayerScreen()
{
}


ChoosePlayerScreen::~ChoosePlayerScreen()
{
}


int ChoosePlayerScreen::Run(sf::RenderWindow & App, Game &game)
{
	sf::Event event;
	bool running = true;
	windowWidth = App.getSize().x;
	windowHeight = App.getSize().y;

	sf::Font font;
	if (!font.loadFromFile("fonts/arial.ttf"))
		std::cerr << "Problem with loading fonts" << std::endl;

	const float BACK_MENU_BUTTON_POS_X = 0.08;
	const float BACK_MENU_BUTTON_POS_Y = 0.10;
	sf::String backToMenuButtonPath("image/MenuButton.png");
	sf::String backToMenuHoverButtonPath("image/MenuButtonShadow.png");
	ButtonView backToMenuButton(backToMenuButtonPath, backToMenuHoverButtonPath, false);
	float backToMenuButtonWidth = backToMenuButton.getGlobalBounds().width;
	float backToMenuButtonHeight = backToMenuButton.getGlobalBounds().height;
	float backToMenuButtonPosX = windowWidth * BACK_MENU_BUTTON_POS_X - backToMenuButtonWidth * 0.5;
	float backToMenuButtonPosY = windowHeight * BACK_MENU_BUTTON_POS_Y - backToMenuButtonHeight * 0.5;
	backToMenuButton.setPosition(sf::Vector2f(backToMenuButtonPosX, backToMenuButtonPosY));

	const int MAX_PLAYERS = 6;
	vector<string> players;

	std::string choosePlayerText = "Wpisz nazwe gracza";
	sf::Text choosePlayerLabel(choosePlayerText, font, 50);
	choosePlayerLabel.setColor(sf::Color(255, 255, 255, 255));
	float choosePlayerPosX = windowWidth * 0.50 - choosePlayerLabel.getGlobalBounds().width * 0.5;
	float choosePlayerPosY = windowHeight * 0.10 - choosePlayerLabel.getGlobalBounds().height * 0.5;
	choosePlayerLabel.setPosition(choosePlayerPosX, choosePlayerPosY);


	std::string playerName;
	sf::Text playerNameTextField(playerName, font, 35);
	playerNameTextField.setColor(sf::Color::Black);
	playerNameTextField.setColor(sf::Color(255, 255, 255, 255));
	float playerNamePosX = windowWidth * 0.35 - playerNameTextField.getGlobalBounds().width * 0.5;
	float playerNamePosY = windowHeight * 0.32 - playerNameTextField.getGlobalBounds().height * 0.5;
	playerNameTextField.setPosition(sf::Vector2f(playerNamePosX, playerNamePosY));

	sf::RectangleShape rectangle(sf::Vector2f(310, 45));
	rectangle.setPosition(sf::Vector2f(playerNamePosX-5, playerNamePosY));

	sf::String addPlayerButtonPath("image/Accept.png");
	sf::String addPlayerHoverButtonPath("image/AcceptShadow.png");
	ButtonView addPlayerButton(addPlayerButtonPath, addPlayerHoverButtonPath, false);
	float addPlayerButtonPosX = windowWidth * 0.70 - addPlayerButton.getGlobalBounds().width * 0.5;
	float addPlayerButtonPosY = windowHeight * 0.35 - addPlayerButton.getGlobalBounds().height * 0.5;
	addPlayerButton.setPosition(addPlayerButtonPosX, addPlayerButtonPosY);

	std::string playerText = "Wprowadz nazwy graczy";
	sf::Text playerLabel(playerText, font, 30);
	playerLabel.setColor(sf::Color(255, 255, 255, 255));
	float playerLabelPosX = windowWidth * 0.50 - playerLabel.getGlobalBounds().width * 0.5;
	float playerLabelPosY = windowHeight * 0.50 - playerLabel.getGlobalBounds().height * 0.5;
	playerLabel.setPosition(playerLabelPosX, playerLabelPosY);

	sf::String nextButtonPath("image/ForwardButton.png");
	ButtonView nextButton(nextButtonPath, nextButtonPath, false);
	float nextButtonPosX = windowWidth * 0.80 - nextButton.getGlobalBounds().width * 0.5;
	float nextButtonPosY = windowHeight * 0.80 - nextButton.getGlobalBounds().height * 0.5;
	nextButton.setPosition(nextButtonPosX, nextButtonPosY);

	while (running)
	{
		while (App.pollEvent(event))
		{
			sf::Mouse mouse;
			sf::Vector2i mousePos = mouse.getPosition(App);

			switch (event.type)
			{
			case  sf::Event::Closed:
				App.close();
				break;
			case sf::Event::MouseMoved:

				if (backToMenuButton.isButtonHoverd(mousePos) && mouse.isButtonPressed(sf::Mouse::Left))
					return (0);

				if (nextButton.isButtonHoverd(mousePos) && mouse.isButtonPressed(sf::Mouse::Left))
					return (1);
				
				if (addPlayerButton.isButtonHoverd(mousePos) && mouse.isButtonPressed(sf::Mouse::Left) && playerName.size() > 0) {
					players.push_back(playerName);
					playerName = "";
					playerNameTextField.setString(playerName);
					playerText = "";
					for (string name : players)
					{
						if (players.size() < MAX_PLAYERS || name != players.back())
							playerText += name + " vs ";
						else
							playerText += name;					
					}
					playerLabel.setString(playerText);
					playerLabelPosX = windowWidth * 0.50 - playerLabel.getGlobalBounds().width * 0.5;
					playerLabel.setPosition(playerLabelPosX, playerLabelPosY);
				}
				break;
			case sf::Event::TextEntered:
				if (event.text.unicode >= 32 && event.text.unicode < 126 && playerName.size() < 17)
					playerName += (char)event.text.unicode;
				else if (event.text.unicode == 8 && playerName.size() > 0) 
					playerName = playerName.substr(0, playerName.length() - 1);
	
				playerNameTextField.setString(playerName);
				playerNameTextField.setColor(sf::Color::Black);
				break;
			default:
				break;
			}
		}

		App.clear(sf::Color(56, 134, 185, 255));	
		App.draw(rectangle);
		App.draw(playerLabel);
		App.draw(choosePlayerLabel);
		App.draw(backToMenuButton);
		App.draw(playerNameTextField);
		if (!addPlayerButton.isHidden()) App.draw(addPlayerButton);
		if (players.size() >= 2) App.draw(nextButton);
		App.display();

	}
	return (-1);
}

