#include "SoundManager.h"
#include "Messages.h"
#include "SDLApp.h"

SoundManager::SoundManager(SDLApp* game) {
	// TODO Auto-generated constructor stub
	app = game;
}

SoundManager::~SoundManager() {
	// TODO Auto-generated destructor stub
}

void SoundManager::update() {

	while (!eventQueue.empty()) {//nos guardamos el efecto de sonido actual
		actualSoundEffect = app->getResources()->getSoundEffect(eventQueue.front().idSoundE_);
		actualSoundEffect->play(eventQueue.front().numReps_);
		eventQueue.pop();
	}
}

void SoundManager::receive(Mensaje* msg) {
	if (!mute) {
		switch (msg->id_) {
			//reproduce musica dado un id
		case PLAY_MUSIC: {
			PlayMusic* m = static_cast<PlayMusic*>(msg);
			actualMusicId = m->idMusic_;
			stopMusic = true;
			app->getResources()->getMusic(actualMusicId)->play();
			break;
		}
		case STOP_ACTUAL_MUSIC: {
			if (stopMusic) {
				app->getResources()->getMusic(actualMusicId)->stop();
				stopMusic = false;
			}
			break;
		}
						 //para la musica dado un id
		case STOP_MUSIC: {
			StopMusic* m = static_cast<StopMusic*>(msg);
			app->getResources()->getMusic(m->idMusic_)->stop();
			break;
		}
						 //pausa la musica dado un id
		case PAUSE_MUSIC: {
			PauseMusic* m = static_cast<PauseMusic*>(msg);
			app->getResources()->getMusic(m->idMusic_)->pause();
			break;
		}
						  //reanuda la musica dado un id
		case RESUME_MUSIC: {
			ResumeMusic* m = static_cast<ResumeMusic*>(msg);
			app->getResources()->getMusic(m->idMusic_)->resume();
			break;
		}
						   //reproduce un efecto de sonido dado un id
		case PLAY_SOUNDEFFECT: {
			PlaySoundE* m = static_cast<PlaySoundE*>(msg);
			eventQueue.push(*m);
			break;
		}
							   //establece el volumen de la musica dada
		case MUSIC_VOLUME: {
			MusicVolume* m = static_cast<MusicVolume*>(msg);
			app->getResources()->getMusic(m->idMusic_)->setVolume(m->volume_);
			break;
		}
						   //establece el volumen del sound effect dado
		case SOUNDEFFECT_VOLUME: {
			SoundEffectVolume* m = static_cast<SoundEffectVolume*>(msg);
			app->getResources()->getSoundEffect(m->idSound_)->setVolume(m->volume_);
			break;
		}
								 //para todos los efectos de sonido
		case STOP_ALL_SOUNDEFFECT: {
			actualSoundEffect->stopAll();//stop del actual que ya esta sonando (ya no se encuentra en la cola de eventos)
			break;//ese stop manda parar todos los canales (soundEffects)
		}
		case STOP_SOUND_EFFECT: {
			StopSoundEffect* m = static_cast<StopSoundEffect*>(msg);
			app->getResources()->getSoundEffect(m->idSound_)->stop();
			break;
		}
		}
	}
}

void SoundManager::changeMute() { mute = !mute; if (!mute) { app->getResources()->getMusic(actualMusicId)->play(); stopMusic = true; } };