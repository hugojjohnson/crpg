// #include <SFML/Graphics.hpp>
// #include <filesystem>
// #include <functional>
// #include <iostream>
// #include <string>
// #include <vector>
// #include "../include/utils/Clickable.hpp"
// #include "../include/utils/ClickManager.hpp"

// #define SCREEN_WIDTH 800
// #define SCREEN_HEIGHT 600

// int main2() {
//   // Create the main window
//   sf::RenderWindow window(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "SFML window");
//   window.setFramerateLimit(60);

//   //   Rectangle
//   sf::Color white(255, 255, 255);
//   sf::RectangleShape rect;

//   std::function<void()> cb = []() { std::cout << "Clicked!\n"; };


//   rect.setPosition({300, 200});
//   rect.setSize({200, 200});
//   rect.setFillColor(white);

//   ClickManager manager;
//   manager.add(Clickable(rect, []() { std::cout << "Rectangle clicked\n"; }));

//   // Start the game loop
//   while (window.isOpen()) {
//     // Process events
//     while (const std::optional event = window.pollEvent()) {
//       // Close window: exit
//       if (event->is<sf::Event::Closed>()) {
//         window.close();
//       }
//       if (event->is<sf::Event::MouseButtonPressed>()) {
//         sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
//         // std::cout << "MousePos: " << mousePos.x << ", " << mousePos.y << "\n";
//         manager.processClick(mousePos);
//       }
//     }

//     // Clear screen
//     window.clear(sf::Color(0, 0, 139));

//     // Draw sprite
//     window.draw(rect);

//     // Update the window
//     window.display();
//   }
// }

// // int main() {
// //   int x = 2;
// //   Clickable<int> f(x);
// //   std::cout << "hi";
// // }