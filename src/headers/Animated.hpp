#pragma once

template <typename T>
class Animated {
    protected:
        // Variables
        T _animationState;
        sf::Clock _animationTimer;
        sf::IntRect _animationFrame;

        virtual void initAnimations() = 0;
        virtual void updateAnimations() = 0;
};