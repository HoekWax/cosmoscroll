#ifndef I18N_HPP
#define I18N_HPP

#include <map>
#include <string>

#include "StringUtils.hpp"

// macro shortcut
#define _t(key) (I18n::getInstance().translate(key))

/**
 * Static class for loading languages files
 */
class I18n
{
public:
	static I18n& getInstance();
	void setDataPath(const std::string& path);

	/**
	 * Get translated text
	 * @param key: text identifier
	 * @return translated string
	 */
	const std::wstring& translate(const char* key) const;
	const std::wstring& translate(const std::string& key) const;

	/**
	 * Load the language file corresponding to the system's locale
	 * @return true if language file found
	 */
	bool loadSystemLanguage();

	/**
	 * Get the language code currently used
	 * @return 2 lower-case characters
	 */
	const char* getLangCode() const;

	/**
	 * Load a language file
	 */
	bool loadFromFile(const char* filename);

	/**
	 * Load a language file from a language code (2 chars)
	 */
	bool loadFromCode(const std::string& code);

	/**
	 * Translate a label and remplace a template by a given value
	 * @param key: label's key
	 * @param search: search templated (ex: "{name}")
	 * @param value: template value
	 * @return translated text with template \a search replaced by \a value
	 */
	template <typename T>
	static std::wstring templatize(const char* key, const std::string& search, T value)
	{
		return str_replace(getInstance().translate(key),
		                   std::wstring(search.begin(), search.end()),
		                   std::to_wstring(value));
	}

	template <typename T1, typename T2>
	static std::wstring templatize(const char* key, const std::string& search1, T1 value1,
													const std::string& search2, T2 value2)
	{
		std::wstring s = str_replace(getInstance().translate(key), std::wstring(search1.begin(), search1.end()), std::to_wstring(value1));
		str_self_replace(s, std::wstring(search2.begin(), search2.end()), std::to_wstring(value2));
		return s;
	}

private:
	I18n();
	I18n(const I18n&);

	typedef std::map<std::string, std::wstring> TextMap;
	TextMap     m_content;
	char        m_code[3];
	std::string m_path;
};

#endif // I18N_HPP
