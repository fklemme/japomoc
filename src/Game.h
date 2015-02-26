#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class GameComponent;

class Game {
    public:
        Game();

        /*! Pushes a game component which then will be rendered and used to
         *  handle events. */
        void push_component(const std::shared_ptr<GameComponent>&);

        /*! Called by the render thread to pass control of what will be drawn to
         *  the game. */
        void dispatch_rendering(sf::RenderWindow&) const;
        /*! Called by the main thread to handle events. */
        void dispatch_event(sf::Event&);
        /*! Called by the main thread to give the game a chance to handle other
         *  things like querying the keyboard. */
        void dispatch_other() const;

        /*! Get the common game font. */
        const sf::Font& font() const;

        /*! Returns true if the game is about to end. This might be due to a
        *  user input. */
        bool exit() const;

    private:
        std::vector<std::shared_ptr<GameComponent>> m_comp_stack;
        sf::Font m_font; //!< Common game font
        bool     m_exit; //!< Whether the game is about to quit or not
};
