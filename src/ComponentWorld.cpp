/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Florian Klemme <mail@florianklemme.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "ComponentWorld.h"

#include <cassert>
#include <iostream>
#include <string>

#include "ComponentMenu.h"

void ComponentWorld::setup(const GameComponent* next_to_this) {
    // Load map. TODO!
    const std::string map_path = "resources/levels/test_map.xml";
    if (!m_tilemap.load_from_xml(map_path)) {
        std::cerr << "Could not load tile map \"" << map_path << "\"!" << std::endl;
        return; // TODO: Handle errors
    }
    sf::Vector2f player_pos(100, 100); // TODO: load from map

    // Load player character
    const std::string char_path = "resources/images/tiny-16-basic/boy.xml";
    if (!m_player.load_from_xml(char_path)) {
        std::cerr << "Could not load player character \"" << char_path << "\"!" << std::endl;
        return; // TODO: Handle errors
    }

    // Generate a new (most likely smaller) view
    sf::Vector2f view_size(800, 600);
    m_view = sf::View(player_pos, view_size);

    // Place player character. TODO: fix position and scale
    m_player.get_animated_sprite().setPosition(player_pos);
    m_player.get_animated_sprite().setScale(2, 2);

    // Player looks down by default
    m_player.set_direction(AnimatedCharacter::Direction::DOWN);
}

void ComponentWorld::play() {
    // TODO: Implement
}

void ComponentWorld::pause() {
    // TODO: Implement
}

bool ComponentWorld::rendering_fills_scene() const {
    // The world is always screen filling.
    return true;
}

std::shared_ptr<GameComponent> ComponentWorld::get_loading_screen() const {
    // TODO: Return loading screen.
    return nullptr;
}

void ComponentWorld::render_scene(sf::RenderWindow &window, const sf::Time &frame_time_delta) {
    window.setView(m_view);

    // Draw tile map
    window.draw(m_tilemap);

    // Draw player character
    AnimatedSprite &player_sprite = m_player.get_animated_sprite();
    const auto player_bounds = player_sprite.getLocalBounds();
    const sf::Vector2f player_size(player_bounds.width, player_bounds.height);
    player_sprite.setPosition(m_view.getCenter() - player_size / 2.0f);
    player_sprite.update(frame_time_delta);
    window.draw(player_sprite);

    // TODO: Implement

#ifndef NDEBUG
    // Show frames per second
    const auto milliseconds = frame_time_delta.asMilliseconds();
    sf::Text fps(milliseconds == 0 ? "FPS: >1000" :
        "FPS: " + std::to_string(1000 / frame_time_delta.asMilliseconds()),
        m_game_manager->get_font());
    fps.setPosition(m_view.getCenter() - m_view.getSize() / 2.0f);
    window.draw(fps);
#endif
}

void ComponentWorld::handle_event(sf::Event &event) {
    assert(m_game_manager != nullptr);

    // TODO: Implement everthing

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape)
            // Open up a menu
            m_game_manager->push_component(std::make_shared<ComponentMenu>());
    }
}

void ComponentWorld::handle_other() {
    // TODO: Implement
}