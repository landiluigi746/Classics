#pragma once

#include <raylib.h>
#include <string>
#include <unordered_map>

namespace Classics
{
	enum class AssetType
	{
		Texture,
		Sound,
		Music
	};

	class AssetManager
	{
	public:
		AssetManager(const AssetManager&) = delete;
		AssetManager& operator=(const AssetManager&) = delete;

		static void Init();
		static void Shutdown();

		static Texture2D GetTexture(const std::string& name, const std::string& filename = "");
		static Sound GetSound(const std::string& name, const std::string& filename = "");
		static Music GetMusic(const std::string& name, const std::string& filename = "");
	private:
		template<typename Type>
		using AssetsMap = std::unordered_map<std::string, Type>;

		AssetManager();
		~AssetManager();

		AssetsMap<Texture2D> m_Textures;
		AssetsMap<Sound> m_Sounds;
		AssetsMap<Music> m_Musics;
	};
}