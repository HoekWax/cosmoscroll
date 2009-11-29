#ifndef BASEMENU_HPP
#define BASEMENU_HPP

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

#include "BaseScene.hpp"
#include "../core/Input.hpp"

/**
 * Menu navigable pour sélectionner un choix
 */
class BaseMenu: public BaseScene
{
public:
	BaseMenu();

	// inherited
	void OnEvent(const sf::Event& event);

	// inherited
	void Update(float frametime);

	// inherited
	void Show(sf::RenderTarget& target) const;

	/**
	 * Apparence normale des éléments
	 * @param style: flag sf::String::Style
	 * @param color: couleur
	 */
	void SetNormalLook(unsigned long style, const sf::Color& color);

	/**
	 * Apparence de l'élément pré-sélectionné
	 * @param style: flag sf::String::Style
	 * @param color: couleur
	 */
	void SetHighlightLook(unsigned long style, const sf::Color& color);

	/**
	 * Taille du texte des éléments
	 * @param size: text size
	 */
	void SetTextSize(int size);

	/**
	 * Fixer l'orignie haut-gauche du menu
	 * @param offset: position
	 */
	void SetOffset(const sf::Vector2f& offset);
	void SetOffset(float x, float y);

	/**
	 * Fixer l'intergline entre les éléments
	 * @param linespace: interligne en pixels
	 */
	void SetLineSpace(int linespace);

	/**
	 * Indiquer l'image de fond
	 */
	void SetBackground(const sf::Image& image);

	/**
	 * Ajout d'un élément dans le menu
	 * @param label: texte de l'élément
	 * @param id: identifiant de l'action associée
	 * @param activable: détermine si l'item peut être activé
	 */
	void AddOption(const sf::Unicode::Text& label, int id, bool activable=true);

	/**
	 * Modifier le texte d'un élément du menu
	 * @param text: nouvelle versiond du texte
	 * @param id: id de l'élément à modifier
	 */
	void SetTextOption(const sf::Unicode::Text& text, int id);

	/**
	 * Présélectionne un item du menu
	 * @param index: indice de l'item
	 */
	void SelectItem(int index);

	/**
	 * Supprimer tous les éléments du menu
	 */
	void Clear();

protected:
	virtual void Callback(int id);

	void DrawItems(sf::RenderTarget& target) const;

private:
	/**
	 * Un élément du menu
	 */
	struct MenuItem
	{
		sf::String label;
		int id;
		bool activable;
	};

	/**
	 * Apparence d'un élément
	 */
	struct ItemLook
	{
		sf::Color color;
		unsigned long style;
	};

	/**
	 * Appliquer une apparence sur un élément
	 * @param item: élément à modifier
	 * @param look: apparence à appliquer
	 */
	static void ApplyStyle(MenuItem& item, const ItemLook& look);

	void ResetStyle(MenuItem& item);

	mutable sf::Sprite background_;
	sf::Sprite background2_;
	std::vector<MenuItem> items_;
	sf::Vector2f offset_;
	int selected_; // indice de l'élément sélectionné
	int textsize_;
	int linespace_; // interligne en pixels
	ItemLook highlight_look_;
	ItemLook normal_look_;
	ItemLook unactive_look_;
};

#endif // BASEMENU_HPP
