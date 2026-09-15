#include <SFML/Graphics.hpp>
#include <thread>
#include <atomic>
#include <iostream>
#include "ship.h" 

// Assets that persist 
// Wrap them via unique_ptr to ensure they are cleaned up in the main thread properly.
std::unique_ptr<Ship> ship;

void renderingThread(sf::RenderWindow& window, std::atomic<bool>& running, std::atomic<bool>& contextReady)
{
    
    if (!window.setActive(true)) {
        std::cerr << "CRITICAL: Thread failed to claim context!" << std::endl;
        contextReady = true;
        return;
    }
    contextReady = true;
    
    // We'll use OpenGL later on. Let's match match OpenGL's -1 to 1 
    // canonical view with the Y axis pointing up.
	// Passing a negative height (-2.f) flips the Y-axis upside down!
	// Now: Top-Left is (-1.0, 1.0) and Bottom-Right is (1.0, -1.0)
	sf::View view(sf::Vector2f(0.f, 0.f), sf::Vector2f(2.f, -2.f));
	window.setView(view);

    // the game and rendering loop
    std::cout << "Entering game loop..." << std::endl;

    // We'll use a clock to control timing for updates and rendering. 
    // This is a common pattern in games to ensure smooth motion and consistent behavior across different hardware.
    sf::Clock clock;
    
    while(running) {
        // draw calls go here
		
        window.clear();

        // determine the elapsed time since the last frame. This will be used to update the ship's position and orientation.
        float dt = clock.restart().asSeconds();

        // draw the ship after updating its position and heading based on the elapsed time.   
        // TO DO - Your code here.
        // ...
        
        // end the current frame
        window.display();
    }

	window.setActive(false);
}


int main() {

	sf::RenderWindow window(
    	sf::VideoMode({800, 600}), 
    	"Asteroids Game",
        sf::Style::Default, 
    	sf::State::Windowed
	);
    window.setActive(false); // Deactivate the window in the main thread to allow the rendering thread to claim it.

    // set additional window properties
    window.setKeyRepeatEnabled(false); // Disable key repeat to avoid multiple key press events when a key is held down.
    
    // DO NOT LIMIT FRAME RATE! Use elapsed time to control updates. 
    // This results in smoother motion and more consistent behavior across different hardware.
    // Updates are handled by a clock in the rendering thread. 
    

    // Create assets in the main thread to ensure proper cleanup when the window is closed.
    ship = std::make_unique<Ship>();

    // Multi-threading to separate the rendering from the event loop. 
    // This is a common pattern in games to avoid stalling the rendering when processing events. 

	std::atomic<bool> running(true);
    std::atomic<bool> contextReady(false);

    // Launch the rendering thread
    std::thread thread(renderingThread, std::ref(window), std::ref(running), std::ref(contextReady));

    // CRUCIAL: Pause the main thread until the rendering thread has successfully claimed the context.
    // This prevents pollEvent() from clashing with setActive(true) during initialization.
    while (!contextReady) {
        std::this_thread::yield(); 
    }

    // the event/logic/whatever loop
    while (window.isOpen()) {
		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() ) {
				running = false; 
                
                // Wait for the rendering thread to safely deactivate and exit
                if (thread.joinable()) {
                    thread.join();
                }

                // Cleanup assets here before closing the window
                ship.reset();
                
                window.close();
			}

            // Additional event handling for key presses and releases will go here.
            // ...

            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                
                // Up key controls acceleration
                if (keyPressed->scancode == sf::Keyboard::Scan::Up) {
                    ship->accelerate();
                }

                // Left and right keys controls turns
                if (keyPressed->scancode == sf::Keyboard::Scan::Left) {
                    ship->toggleTurn();
                }
                if (keyPressed->scancode == sf::Keyboard::Scan::Right) {
                    ship->toggleTurn( false );
                }
            }

            if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>()) {
                
                // Up key when released triggers decceleration
                if (keyReleased->scancode == sf::Keyboard::Scan::Up) {
                    ship->deccelerate();
                }
                // left and right keys when released will stop turning
                if (keyReleased->scancode == sf::Keyboard::Scan::Left || keyReleased->scancode == sf::Keyboard::Scan::Right ) {
                    ship->toggleTurn();
                }

            }
		}
    }
}
