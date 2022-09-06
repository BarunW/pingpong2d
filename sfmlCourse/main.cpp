#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<string>
#include<vector>
#include<sstream>

int main()
{
 //Creating the window 
    sf::RenderWindow window(sf::VideoMode(800, 600), "Ping Pong");

    window.setFramerateLimit(80);

    window.setKeyRepeatEnabled(false);

 //EVENT OBJECT HOLDING FOR ALL OBJECT
    sf::Event event;

    // states 
    bool play = true;
    bool up = false;
    bool down = false;
 



    //-----------------Loading Files ---------------------
    //Texture or Images
    sf::Texture backgroundImage;
    sf::Texture ball;
    sf::Texture pad;
    sf::Texture user;
   
    
    if(backgroundImage.loadFromFile("Data/background.png") == 0)
    {
        return 1;
    }

    if (ball.loadFromFile("Data/ball.png") == 0) 
    {
        return 1;
    }
    if (pad.loadFromFile("Data/pad.png") == 0)
    {
        return 1;
    }
    if (user.loadFromFile("Data/user.png") == 0)
    {
        return 1;
    }
   

    //Loading Audio
    sf::Music backgroundMusic;
    if (backgroundMusic.openFromFile("Data/backgroundMusic.ogg") == 0) 
    {
        return 1;
    }
    backgroundMusic.play();
    backgroundMusic.setVolume(50);
    backgroundMusic.setLoop(true);

    sf::SoundBuffer hit;

    if (hit.loadFromFile("Data/hit.wav") == 0) 
    {
        return 1;
    }
    sf::Sound hitSound;
 

    //Loading Fonts and text;
    sf::Font font;
    if (font.loadFromFile("Data/font1.ttf") == 0) {
        return 1;
    }
    sf::Text scoreBoard;
    scoreBoard.setCharacterSize(28);
    scoreBoard.setFont(font);
    scoreBoard.setString("0 : 0");
    scoreBoard.setPosition(350, 5);






//-------------------Creating Shape-----------------------
// Shapes
    sf::RectangleShape background;
    background.setSize(sf::Vector2f(800, 600));
    background.setPosition(0, 0);
    background.setTexture(&backgroundImage);

    sf::RectangleShape pad1;
    pad1.setSize(sf::Vector2f(50, 100));
    pad1.setPosition(20, 100);
    pad1.setTexture(&user);
  

    sf::RectangleShape AiPad;
    AiPad.setSize(sf::Vector2f(50, 100));
    AiPad.setPosition(730, 100);
    AiPad.setTexture(&pad);


    sf::CircleShape Ball;
    Ball.setRadius(25);
    Ball.setPosition(400, 300);
    Ball.setTexture(&ball);

// ----------------Variables----------------------
    float yVelocityPad1  = 0; 
    float yVelocityAiPad = 0;
    
    float xVelocityBall = -4; // speed of ball
    float yVelocityBall = -4; // speed of ball

    int score = 0;
    int AiScore = 0;



 // Game Loop 
    while (play) {

        //EVENTS CHECKER
        while (window.pollEvent(event)) 
        {
            
            if (event.type == sf::Event::Closed) 
            {
                play = false;
            }
            //Key Pressed
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
                up = true;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) {
                down = true;
            }
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Up) {
                up = false;
            }
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Down) {
                down = false;
            }

           
        }
        //LOGIC
        if (up == true) {
            yVelocityPad1 = -5;
        }
        if (down == true) {
            yVelocityPad1 = 5;
        }
        if ((up == true && down == true) || (up == false && down == false)) {
            yVelocityPad1 = 0;
        }
        //move
        pad1.move(0, yVelocityPad1);
        
        // Bounds 
        if(pad1.getPosition().y < 0){

            pad1.setPosition(20, 0);

        }

        if (pad1.getPosition().y > 500) {
            pad1.setPosition(20, 500);

        }
        //Ball
        Ball.move(xVelocityBall, yVelocityBall);
        // Bounds  check
        if (Ball.getPosition().y < 0) {
            yVelocityBall = -yVelocityBall;

        }

        if (Ball.getPosition().y > 500) {
            
            yVelocityBall = -yVelocityBall;

        }

        if (Ball.getPosition().x < -50) {
            
            AiScore++;
            Ball.setPosition(400, 300);
        }

        if (Ball.getPosition().x > 800) {
           
            score++;
            Ball.setPosition(400, 300);
        }
        //Ai
        if (Ball.getPosition().y < AiPad.getPosition().y) {
            
            yVelocityAiPad = -4.3;
        }
        if (Ball.getPosition().y > AiPad.getPosition().y) {

            yVelocityAiPad = 4.3;
        }
        AiPad.move(0, yVelocityAiPad);

        
        
        //Collision For Player
        if (Ball.getGlobalBounds().intersects(pad1.getGlobalBounds()) == true)
        {
            
            xVelocityBall = -xVelocityBall;
  
        }
        // Collision For AI
        if (Ball.getGlobalBounds().intersects(AiPad.getGlobalBounds()) == true)
        {
            xVelocityBall = -xVelocityBall;
        }

        //RENDERING
        window.clear();
        window.draw(background);
        window.draw(pad1);
        window.draw(AiPad);
        window.draw(Ball);

        //Score
        std::stringstream text;

        text <<score <<":"<< AiScore ;
        scoreBoard.setString(text.str());

        window.draw(scoreBoard);
     

        window.display();

        
    }
  
  
    window.close();

    return 0;


  
}