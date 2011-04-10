#include <SFML/Network.hpp>

#include "BestScoresMenu.hpp"
#include "../core/Game.hpp"
#include "../utils/I18n.hpp"
#include "../utils/MediaManager.hpp"


BestScoresMenu::BestScoresMenu()
{
	SetTitle("Meilleurs scores");
	gui::Button* b = new CosmoButton(this, I18n::t("menu.back_main_menu"), 210, 420);
	b->SetCallbackID(1);

	LoadBitmapFont("data/images/gui/mono12-white.png", 10, 10);
	lab_content_ = new gui::BitmapString(*GetBitmapFont());
	lab_content_->SetPosition(120, 100);
}


void BestScoresMenu::EventCallback(int id)
{
	switch (id)
	{
		case 1:
			Game::GetInstance().SetNextScene(Game::SC_MainMenu);
			break;
	}
}


void BestScoresMenu::Show(sf::RenderTarget& target) const
{
	BaseMenu::Show(target);
	target.Draw(*lab_content_);
}


void BestScoresMenu::OnFocus()
{
	// Connect to cosmoscroll scores server
	sf::Http server;
	server.SetHost(COSMO_HOSTNAME);

	// Prepare a request to retrieve the scores
	sf::Http::Request request;
	request.SetMethod(sf::Http::Request::Get);
	request.SetURI(COSMO_URI);

	// Send it and get the response returned by the server
	sf::Http::Response response = server.SendRequest(request);
	switch (response.GetStatus())
	{
		case sf::Http::Response::Ok:
			lab_content_->SetText(response.GetBody());
			std::cout << response.GetBody() << std::endl;
			break;
		case sf::Http::Response::ConnectionFailed:
			lab_content_->SetText("Couldn't connect to CosmoScroll server");
			break;
		default:
			lab_content_->SetText(response.GetBody());
			break;
	}
}
