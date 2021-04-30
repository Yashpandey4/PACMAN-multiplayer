/**
 * This file decides the animations in the character sprites
 */

#include "Animation.h"

/**
 *
 * @return
 */
sf::IntRect *Animation::getBoundaries() const {
    return boundaries;
}

/**
 *
 * @param rect
 * @param framesNumber
 */
Animation::Animation(sf::IntRect *rect, int framesNumber) {
    boundaries = rect;
    frames = framesNumber;
    resetValue = rect->left;
}

/**
 *
 */
void Animation::changeFrame() {
    if (clock.getElapsedTime().asSeconds() >= 0.1f) {
        if (boundaries->left >= (resetValue + 15 * (frames - 1))) {
            boundaries->left = resetValue;
        }
        else {
            boundaries->left += 15;
        }
        clock.restart();
    }
}
