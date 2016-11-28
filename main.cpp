/*
    Final Project: Graphs in SFML
    Luis Barajas
    Mauricio Rico
    Data Structures
    30/11/16
    A01370934@itesm.mx
    A01370874@itesm.mx
*/


#include <SFML/Graphics.hpp>
#include <iostream>
#include "Graph.hpp"
#include <math.h>

#define PI 3.141592

void configureSFML(sf::VideoMode *desktop, sf::RenderWindow *window);
void mainDraw(sf::RenderWindow *window, Graph<std::string, float> *graph);
void createVertex(sf::Vector2i & position, Graph<std::string, float> *graph, sf::RenderWindow *window, std::string & textUserInteraction);
void drawVertex(sf::RenderWindow *window, Vertex<std::string, float> * vertex, sf::Color color);
Vertex<std::string, float> * getClickedVertex(Graph<std::string, float> *graph, sf::Vector2i & position);
void createEdge(sf::RenderWindow *window, Graph<std::string, float> *graph, Vertex<std::string, float> * clickedVertex, std::string & textUserInteraction);
void drawEdge(sf::RenderWindow *window, Vertex<std::string, float> * originVertex, Vertex<std::string, float> * destinationVertex, sf::Color color);
void createPath(sf::RenderWindow *window, Graph<std::string, float> *graph, Vertex<std::string, float> * originVertex, Vertex<std::string, float> * destinationVertex, std::string *textCountriesNumber, std::string *textUserInteraction);

int main(){

    //Global Variables
    Graph<std::string, float> graph;
    sf::VideoMode desktop;
    sf::RenderWindow window;

    configureSFML(&desktop, &window);
    mainDraw(&window, &graph);

    return 0;
}

void configureSFML(sf::VideoMode *desktop, sf::RenderWindow *window){

    *desktop = sf::VideoMode::getDesktopMode();
    window->create(sf::VideoMode(1024, 768, desktop->bitsPerPixel), "Graphs");

}

void mainDraw(sf::RenderWindow *window, Graph<std::string, float> *graph){
    //Configure the background
    sf::Texture texture;
    if (!texture.loadFromFile("world.jpg"))
    {
        std::cout << "Error: loading the background image!" << '\n';
    }
    sf::Sprite background(texture);

    window->clear(sf::Color::White);
    // Set background to image
    window->draw(background);

    //Configure the font
    sf::Font font;
    font.loadFromFile("Akashi.ttf");

    //Rectangle for the background in the title
    sf::RectangleShape rec(sf::Vector2f(1024,80));
    rec.setPosition(0,0);
    rec.setFillColor(sf::Color::White);

    // Configure the countriesNumber object
    std::string textCountriesNumber;
    sf::Text countriesNumber;
    countriesNumber.setFont(font);
    countriesNumber.setCharacterSize(24);
    countriesNumber.setColor(sf::Color::Black);
    countriesNumber.setPosition(sf::Vector2f(20, 10));

    // Configure the userInteraction object
    std::string textUserInteraction = "";
    sf::Text userInteraction;
    userInteraction.setFont(font);
    userInteraction.setCharacterSize(18);
    userInteraction.setColor(sf::Color::Black);
    userInteraction.setPosition(sf::Vector2f(20, 52));

    //Configure button for path
    //Background for the button
    sf::RectangleShape pathBackground(sf::Vector2f(130,35));
    pathBackground.setPosition(825,25);
    pathBackground.setFillColor(sf::Color::Black);
    //text for the button
    sf::Text pathBtnTitle;
    pathBtnTitle.setFont(font);
    pathBtnTitle.setCharacterSize(16);
    pathBtnTitle.setColor(sf::Color::White);
    pathBtnTitle.setPosition(850,32);
    pathBtnTitle.setString("New Path");

    textCountriesNumber = "There are " + std::to_string(graph->getVerticesLength()) + " countries.";
    textUserInteraction = "Click wherever you want a new country or click the button path";

    //Variables for accepting & assigning the input text
    bool createAVertex = false;
    bool createAnEdge = false;
    bool setEdgeCost = false;
    bool createAPath = false;

    //Variable for getting the position of the Mouse when clicked
    sf::Vector2i position;

    //Variable for saving the clicked Vertices
    Vertex<std::string, float> * clickedVertex = nullptr;
    Vertex<std::string, float> * originVertex = nullptr;
    Vertex<std::string, float> * destinationVertex = nullptr;

    while (window->isOpen())
    {
        countriesNumber.setString(textCountriesNumber);
        userInteraction.setString(textUserInteraction);

        sf::Event event;
        while (window->pollEvent(event))
        {
            switch (event.type){
                case sf::Event::Closed:
                    std::cout << "Window closed" << '\n';
                    window->close();
                    break;
                case sf::Event::MouseButtonReleased:
                {
                    if(createAnEdge){
                        position = sf::Mouse::getPosition(*window);
                        clickedVertex = getClickedVertex(graph, position);
                        //Only set the cost if there was a clicked vertex
                        if (clickedVertex != nullptr){
                            createAnEdge = false;
                            setEdgeCost = true;
                            // Change the text displayed
                            textCountriesNumber = "Enter the cost for the connection: ";
                            textUserInteraction = "";
                        }else{
                            textCountriesNumber = "No country was selected, try again";
                            textUserInteraction = "";
                        }
                    }else if (createAPath){
                        if(originVertex == nullptr){
                            position = sf::Mouse::getPosition(*window);
                            originVertex = getClickedVertex(graph, position);
                            //Only request the destination if there was an origin selected
                            if (originVertex != nullptr){

                                // Change the text displayed
                                textCountriesNumber = "Select the destination";
                                textUserInteraction = "";

                            }else{
                                textCountriesNumber = "No country was selected, try again";
                                textUserInteraction = "";
                            }
                        }else{
                            position = sf::Mouse::getPosition(*window);
                            destinationVertex = getClickedVertex(graph, position);

                            //Only create a path if there was an origin and destination selected
                            if (destinationVertex != nullptr){
                                createPath(window,graph,originVertex,destinationVertex,&textCountriesNumber,&textUserInteraction);
                            }else{
                                textCountriesNumber = "No country was selected, try again";
                                textUserInteraction = "";
                            }
                        }
                    }else{
                        //Check if the click is in the title bar
                        if (sf::Mouse::getPosition(*window).y <= 80){
                            //Check if button path was clicked
                            if(sf::Mouse::getPosition(*window).x >= pathBackground.getPosition().x
                                && sf::Mouse::getPosition(*window).x <= pathBackground.getPosition().x + pathBackground.getSize().x
                                && sf::Mouse::getPosition(*window).y >= pathBackground.getPosition().y
                                && sf::Mouse::getPosition(*window).y <= pathBackground.getPosition().y + pathBackground.getSize().y){

                                    createAPath = true;

                                    // Change the text displayed
                                    textCountriesNumber = "Select the origin";
                                    textUserInteraction = "";

                                }
                        }else{

                            // get the local mouse position (relative to window)
                            position = sf::Mouse::getPosition(*window);

                            // Change the text displayed
                            textCountriesNumber = "Enter the name for the country: ";
                            textUserInteraction = "";
                            // Toggle the boolean so it accepts input
                            createAVertex = true;

                        }
                    }

                }

                break;
                case sf::Event::TextEntered:
                    if ( createAVertex ){
                        //Delete the last character
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)){
                            if(textUserInteraction.length() > 0){
                                textUserInteraction.pop_back();
                            }
                        }else
                        // it's a printable char
                        if ( event.text.unicode < 0x80 ) {
                            char letter = (char) event.text.unicode;
                            textUserInteraction += letter;
                        }
                        //Submit the entered text
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
                            createVertex(position, graph, window, textUserInteraction);
                            createAVertex = false;
                            //textCountriesNumber = "There are " + std::to_string(graph->getVerticesLength()) + " countries.";
                            //textUserInteraction = "Click wherever you want a new country or click the button path";
                            if(graph->getVerticesLength() > 1){
                                textCountriesNumber = "Select the countries to make a connection";
                                textUserInteraction = "Press escape when you are finished";
                                createAnEdge = true;
                            }else{
                                createAnEdge = false;
                                textCountriesNumber = "There are " + std::to_string(graph->getVerticesLength()) + " countries.";
                                textUserInteraction = "Click wherever you want a new country or click the button path";
                            }
                        }
                    }else if (createAnEdge){
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                            createAnEdge = false;
                            textCountriesNumber = "There are " + std::to_string(graph->getVerticesLength()) + " countries.";
                            textUserInteraction = "Click wherever you want a new country or click the button path";
                        }
                    }else if (setEdgeCost){
                        //Delete the last character
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)){
                            if(textUserInteraction.length() > 0){
                                textUserInteraction.pop_back();
                            }
                        }else
                        // it's a printable char
                        if ( event.text.unicode < 0x80 ) {
                            char letter = (char) event.text.unicode;
                            textUserInteraction += letter;
                        }
                        //Submit the entered text
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
                            createEdge(window, graph, clickedVertex, textUserInteraction);
                            createAVertex = false;
                            setEdgeCost = false;
                            createAnEdge = true;
                            textCountriesNumber = "Select the countries to make a connection";
                            textUserInteraction = "Press escape when you are finished";
                        }
                    }else if(createAPath){
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                            createAPath = false;
                            textCountriesNumber = "There are " + std::to_string(graph->getVerticesLength()) + " countries.";
                            textUserInteraction = "Click wherever you want a new country or click the button path";

                            //Restart the scene as was
                            window->clear(sf::Color::White);
                            window->draw(background);
                            //Draw all the vertices & edges in white again
                            LinkedList<Vertex<std::string, float> *> * vertices = graph->getVerticesList();
                            int length = vertices->getLength();
                        }
                    }
                    break;
            }
        }
        //Draw title section
        window->draw(rec);

        window->draw(countriesNumber);
        window->draw(userInteraction);

        window->draw(pathBackground);
        window->draw(pathBtnTitle);

        window->display();

    }

}
//Method for creating a new vertex
void createVertex(sf::Vector2i & position, Graph<std::string, float> *graph, sf::RenderWindow *window, std::string & textUserInteraction){

    int x = position.x - 10;
    int y = position.y - 10;
    // Add vertex ti graph
    Vertex<std::string, float> * newVertex = new Vertex<std::string, float>(textUserInteraction);
    newVertex->setX(x);
    newVertex->setY(y);

    graph->addVertex(newVertex);

    drawVertex(window,newVertex,sf::Color::White);
}

//Method for drawing a vertex in SFML
void drawVertex(sf::RenderWindow *window, Vertex<std::string, float> * vertex, sf::Color color){
    int x = vertex->getX();
    int y = vertex->getY();
    std::string data = vertex->getData();

    //Draw the vertex in the place pressed
    sf::CircleShape circle(10.f);
    circle.setFillColor(color);
    circle.setPosition(x,y);
    window->draw(circle);

    //Configure the font
    sf::Font font;
    font.loadFromFile("Akashi.ttf");

    //Draw its name next to it
    sf::Text name;
    name.setFont(font);
    name.setCharacterSize(12);
    name.setColor(color);
    name.setPosition(sf::Vector2f(x-5, y-15));
    name.setString(data);
    window->draw(name);
}

// Method for getting the clicked Vertex
Vertex<std::string, float> * getClickedVertex(Graph<std::string, float> *graph, sf::Vector2i & position){
    LinkedList<Vertex<std::string, float> *> * vertices = graph->getVerticesList();
    Node<Vertex<std::string, float> *> * vertexNode = vertices->getHead();

    Vertex<std::string, float> * token;

    while (vertexNode != nullptr) {

        token = vertexNode->getData();

        /*sf::RectangleShape rec1(sf::Vector2f(20,20));
        rec1.setPosition(token->getX(),token->getY());
        rec1.setFillColor(sf::Color::Black);

        window->draw(rec1);*/

        if(position.x >= token->getX()
            && position.x <= token->getX() + 20
            && position.y >= token->getY()
            && position.y <= token->getY() + 20){

            return token;
        }

        vertexNode = vertexNode->getNext();
    }

    token = nullptr;


    return token;

}

//Method for creating the new edge
void createEdge(sf::RenderWindow *window, Graph<std::string, float> *graph, Vertex<std::string, float> * clickedVertex, std::string & textUserInteraction){
    Vertex<std::string, float> * originVertex = graph->getVerticesList()->getDataAtTail();
    Vertex<std::string, float> * destinationVertex = clickedVertex;

    //std::cout << destinationVertex->getData() << '\n';

    float cost = std::stof(textUserInteraction);

    graph->addEdge(originVertex,destinationVertex,cost);

    drawEdge(window,originVertex,destinationVertex,sf::Color::White);

}

//Method for drawing an edge in SFML
void drawEdge(sf::RenderWindow *window, Vertex<std::string, float> * originVertex, Vertex<std::string, float> * destinationVertex, sf::Color color){
    //Get the coordinates of the vertices
    float x_o = originVertex->getX();
    float y_o = originVertex->getY();
    float x_i = destinationVertex->getX();
    float y_i = destinationVertex->getY();

    int delta_x = x_i - x_o;
    int delta_y = y_i - y_o;
    float angleToRotate = 0;

    angleToRotate = (atan2 (delta_y,delta_x) * 180) / PI;

    //The length of the edge
    float hypotenuse = delta_y / sin (angleToRotate*PI/180);

    sf::RectangleShape line(sf::Vector2f(hypotenuse,5));
    line.setPosition(x_o + 7.5,y_o + 12.5);
    line.setFillColor(color);
    line.setRotation(angleToRotate);

    window->draw(line);
}

//Create a new path, and display it visually
void createPath(sf::RenderWindow *window, Graph<std::string, float> *graph, Vertex<std::string, float> * originVertex, Vertex<std::string, float> * destinationVertex, std::string *textCountriesNumber, std::string *textUserInteraction){
    LinkedList<Vertex<std::string, float> *> * path = graph->findPath(originVertex,destinationVertex);
    Node<Vertex<std::string, float> *> * vertexNode = path->getHead();
    Node<Vertex<std::string, float> *> * nextVertexNode = vertexNode->getNext();

    Vertex<std::string, float> * vertex;
    Vertex<std::string, float> * nextVertex;

    int length = path->getLength();
    int i = 0;

    std::string pathInText = "";

    std::string vertexData;

    while(nextVertexNode != nullptr){
        vertex = vertexNode->getData();
        nextVertex = nextVertexNode->getData();

        if(i == 0){
            //Draw the vertex on top black

            vertexData = vertex->getData();
            drawVertex(window,vertex,sf::Color::Black);

            pathInText += vertexData;
            pathInText += "->";

        }

        vertexData = nextVertex->getData();


        if(i < length - 2){
            //Draw the vertex in blue
            drawVertex(window,nextVertex,sf::Color(33,53,156));
            pathInText += vertexData;
            pathInText += "->";

        }else{
            //Draw the vertex in black
            drawVertex(window,nextVertex,sf::Color::Black);
            pathInText += vertexData;

        }

        drawEdge(window,vertex,nextVertex,sf::Color(33,53,156));
        vertexNode = vertexNode->getNext();
        nextVertexNode = nextVertexNode->getNext();
        i++;

    }


    *textCountriesNumber = "The cheapest path to follow is: " + pathInText;
    *textUserInteraction = "Press escape to create a new path or create a new country";

}


/* Graph<std::string, float> graph;
Vertex<std::string, float> * vertex;
std::string cities[] = {"Mexico", "Guadalajara", "Puebla", "Queretaro", "Cuernavaca", "Veracruz", "Villahermosa", "Acapulco"};
int num_cities = sizeof cities / sizeof cities[0];
LinkedList<Vertex<std::string, float> *> * path = nullptr;

for (int i=0; i<num_cities; i++)
{
    vertex = new Vertex<std::string, float>(cities[i]);
    graph.addVertex(vertex);
}

graph.setStart("Mexico");
graph.addEdge("Mexico", "Puebla", 2.8);
graph.addEdge("Puebla", "Veracruz", 8.2);
graph.addEdge("Veracruz", "Villahermosa", 5.2);
graph.addEdge("Guadalajara", "Queretaro", 0.7);
graph.addEdge("Mexico", "Cuernavaca", 6.8);
graph.addEdge("Cuernavaca", "Acapulco", 6.8);
graph.addEdge("Mexico", "Guadalajara", 3.2);
graph.addEdge("Queretaro", "Mexico", 2.1);
graph.addEdge("Queretaro", "Acapulco", 5.1);

graph.printBreadthFirst();
graph.printDepthFirst();

path = graph.findPath("Mexico", "Villahermosa");
std::cout << "Resulting path (Mexico to villahermosa):" << std::endl << "\t";
graph.printPath(path);
delete path; */
