#include <SFML/Graphics.hpp>
#include "AnimatedSprite.h"
#include <iostream>


int main()
{
    // setup window
    sf::Vector2i screenDimensions(800,600);
    sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Animations!");
    window.setFramerateLimit(60);

    // load texture (spritesheet)
    sf::Texture texture;
     if (!texture.loadFromFile("patos.png"))
    {
        std::cout << "Failed to load player spritesheet!" << std::endl;
        return 1;
    }

    // set up the animations for all four directions (set spritesheet and push frames)
    Animation walkingAnimationDown;
    walkingAnimationDown.setSpriteSheet(texture);
    walkingAnimationDown.addFrame(sf::IntRect(24, 0, 24, 24));
    walkingAnimationDown.addFrame(sf::IntRect(48, 0, 24, 24));
    walkingAnimationDown.addFrame(sf::IntRect(24, 0, 24, 24));
    walkingAnimationDown.addFrame(sf::IntRect( 0, 0, 24, 24));

    Animation walkingAnimationLeft;
    walkingAnimationLeft.setSpriteSheet(texture);
    walkingAnimationLeft.addFrame(sf::IntRect(24, 58, 24, 24));
    walkingAnimationLeft.addFrame(sf::IntRect(48, 58, 24, 24));
    walkingAnimationLeft.addFrame(sf::IntRect(24, 58, 24, 24));
    walkingAnimationLeft.addFrame(sf::IntRect( 0, 58, 24, 24));

    Animation walkingAnimationRight;
    walkingAnimationRight.setSpriteSheet(texture);
    walkingAnimationRight.addFrame(sf::IntRect(24, 142, 24, 24));
    walkingAnimationRight.addFrame(sf::IntRect(51, 142, 24, 24));
    walkingAnimationRight.addFrame(sf::IntRect(24, 142, 24, 24));
    walkingAnimationRight.addFrame(sf::IntRect( 0, 142, 24, 24));

    Animation walkingAnimationUp;
    walkingAnimationUp.setSpriteSheet(texture);
    walkingAnimationUp.addFrame(sf::IntRect(24, 30, 24, 24));
    walkingAnimationUp.addFrame(sf::IntRect(48, 30, 24, 24));
    walkingAnimationUp.addFrame(sf::IntRect(24, 30, 24, 24));
    walkingAnimationUp.addFrame(sf::IntRect( 0, 30, 24, 24));

    Animation walkingAnimationUpLeft;
    walkingAnimationUpLeft.setSpriteSheet(texture);
    walkingAnimationUpLeft.addFrame(sf::IntRect(28, 116, 24, 24));
    walkingAnimationUpLeft.addFrame(sf::IntRect(51, 116, 24, 24));
    walkingAnimationUpLeft.addFrame(sf::IntRect(28, 116, 24, 24));
    walkingAnimationUpLeft.addFrame(sf::IntRect( 4, 116, 24, 24));

    Animation walkingAnimationUpRight;
    walkingAnimationUpRight.setSpriteSheet(texture);
    walkingAnimationUpRight.addFrame(sf::IntRect(28, 200, 24, 24));
    walkingAnimationUpRight.addFrame(sf::IntRect(50, 200, 24, 24));
    walkingAnimationUpRight.addFrame(sf::IntRect(28, 200, 24, 24));
    walkingAnimationUpRight.addFrame(sf::IntRect( 4, 200, 24, 24));

    Animation walkingAnimationDownLeft;
    walkingAnimationDownLeft.setSpriteSheet(texture);
    walkingAnimationDownLeft.addFrame(sf::IntRect(24, 86, 24, 24));
    walkingAnimationDownLeft.addFrame(sf::IntRect(52, 86, 24, 24));
    walkingAnimationDownLeft.addFrame(sf::IntRect(24, 86, 24, 24));
    walkingAnimationDownLeft.addFrame(sf::IntRect( 0, 86, 24, 24));

    Animation walkingAnimationDownRight;
    walkingAnimationDownRight.setSpriteSheet(texture);
    walkingAnimationDownRight.addFrame(sf::IntRect(24, 170, 24, 24));
    walkingAnimationDownRight.addFrame(sf::IntRect(48, 170, 24, 24));
    walkingAnimationDownRight.addFrame(sf::IntRect(24, 170, 24, 24));
    walkingAnimationDownRight.addFrame(sf::IntRect( 0, 170, 24, 24));

    Animation* currentAnimation = &walkingAnimationDown;

    // set up AnimatedSprite
    AnimatedSprite animatedSprite(sf::seconds(0.2), true, false);
    animatedSprite.setPosition(sf::Vector2f(screenDimensions / 2));

    sf::Clock frameClock;

    float speed = 80.f;
    bool noKeyWasPressed = true;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
        }

        sf::Time frameTime = frameClock.restart();

        // if a key was pressed set the correct animation and move correctly
        sf::Vector2f movement(0.f, 0.f);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))){
            currentAnimation = &walkingAnimationUpLeft;
            movement.y -= speed;
            movement.x -= speed;
            noKeyWasPressed = false;
        }else
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))){
            currentAnimation = &walkingAnimationUpRight;
            movement.y -= speed;
            movement.x += speed;
            noKeyWasPressed = false;
        }else
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))){
            currentAnimation = &walkingAnimationDownLeft;
            movement.y += speed;
            movement.x -= speed;
            noKeyWasPressed = false;
        }else
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))){
            currentAnimation = &walkingAnimationDownRight;
            movement.y += speed;
            movement.x += speed;
            noKeyWasPressed = false;
        }else
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            currentAnimation = &walkingAnimationDown;
            movement.y += speed;
            noKeyWasPressed = false;
        }else
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            currentAnimation = &walkingAnimationUp;
            movement.y -= speed;
            noKeyWasPressed = false;
        }else
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            currentAnimation = &walkingAnimationLeft;
            movement.x -= speed;
            noKeyWasPressed = false;
        }else
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            currentAnimation = &walkingAnimationRight;

            movement.x += speed;
            noKeyWasPressed = false;
        }


        animatedSprite.play(*currentAnimation);
        animatedSprite.move(movement * frameTime.asSeconds());

        // if no key was pressed stop the animation
        if (noKeyWasPressed)
        {
            animatedSprite.stop();
        }
        noKeyWasPressed = true;

        // update AnimatedSprite
        animatedSprite.update(frameTime);

        // draw
        window.clear();
        window.draw(animatedSprite);
        window.display();
    }

    return 0;
}
