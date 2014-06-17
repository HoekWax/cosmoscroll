#include "PauseMenu.hpp"
#include "core/Input.hpp"
#include "core/Game.hpp"
#include "core/ControlPanel.hpp"
#include "core/ParticleSystem.hpp"
#include "core/SoundSystem.hpp"
#include "entities/EntityManager.hpp"
#include "utils/I18n.hpp"


PauseMenu::PauseMenu()
{
	SetTitle(_t("menu.pause.title"), 120);
	SetBackground(sf::Sprite());

	gui::VBoxLayout layout(210, 200);
	layout.Add(new CosmoButton(this, _t("menu.pause.resume")))->SetCallbackID(1);
	layout.Add(new CosmoButton(this, _t("menu.back_main_menu")))->SetCallbackID(2);
	layout.Add(new CosmoButton(this, _t("menu.pause.quit")))->SetCallbackID(3);
}


void PauseMenu::OnEvent(const sf::Event& event)
{
	Action::ID action = Input::feedEvent(event);
	if (action == Action::PAUSE && event.type != sf::Event::LostFocus) // resume
	{
		Game::getInstance().setNextScene(Game::SC_InGameScene);
		SoundSystem::playMusic();
	}
	else
	{
		BaseMenu::OnEvent(event);
	}
}


void PauseMenu::OnFocus()
{
	Game::getInstance().getWindow().setMouseCursorVisible(true);
	Game::getInstance().getWindow().setKeyRepeatEnabled(true);
}


void PauseMenu::EventCallback(int id)
{
	Game& game = Game::getInstance();
	switch (id)
	{
		case 1:
			game.setNextScene(Game::SC_InGameScene);
			SoundSystem::playMusic();
			break;
		case 2:
			game.setNextScene(Game::SC_MainMenu);
			break;
		case 3:
			game.quit();
			break;
	}
}


void PauseMenu::Update(float frametime)
{
	ParticleSystem::getInstance().update(frametime);
}


void PauseMenu::Show(sf::RenderTarget& target) const
{
	target.draw(ControlPanel::getInstance());
	target.draw(EntityManager::getInstance());
	target.draw(GetTitle());
	gui::Menu::Show(target);
}

