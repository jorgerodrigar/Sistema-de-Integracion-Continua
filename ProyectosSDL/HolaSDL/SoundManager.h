#ifndef SRC_SOUNDMANAGER_H_
#define SRC_SOUNDMANAGER_H_

#include "Resources.h"
#include "GameObject.h"
#include "Observer.h"
#include <queue>

/*
*
*/
class SoundManager : public Observer {
public:
	SoundManager() {}
	SoundManager(SDLApp* game);
	virtual ~SoundManager();
	virtual void receive(Mensaje* msg);
	virtual void update();
	void changeMute();
	inline bool const getMute() { return mute; };
	bool isAlreadySounding(Resources::MusicId m) { return actualMusicId == m && stopMusic; }
private:
	struct PlayMessage {
		PlayMessage(Resources::SoundEffectId id, int num) : id_(id), num_(num) {};
		Resources::SoundEffectId id_; //id del sonido a reproducir
		int num_;
	};
	queue<PlaySoundE> eventQueue;
	SDLApp* app;
	SoundEffect* actualSoundEffect = nullptr;
	Resources::MusicId actualMusicId;
	bool stopMusic = false;
	bool mute = false;
};

#endif /* SRC_SOUNDMANAGER_H_ */