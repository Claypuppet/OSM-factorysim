//
// Created by don on 28-5-18.
//

#include <utils/Logger.h>
#include "PlayState.h"

namespace filestates {

void PlayState::doActivity() {

}
void PlayState::entryAction() {
  utils::Logger::log(__PRETTY_FUNCTION__);
}

void PlayState::exitAction() {

}

PlayState::PlayState(file::FileApplication &application)
    : FileState(application) {

}

}
