#include "ship.h"

// Standard double definition
inline constexpr double PI = 3.14159265358979323846;

Ship::Ship() : vertices(sf::PrimitiveType::TriangleStrip, 4)  {
    // define the positions
    vertices[0].position = sf::Vector2f(-0.7071f, -0.7071f);
    vertices[1].position = sf::Vector2f(1.0f, 0.0f);;
    vertices[2].position = sf::Vector2f(0.0f, 0.0f);
    vertices[3].position = sf::Vector2f(-0.7071f, 0.7071f);

    // define the color of the ship. All vertices get the same color
    for (std::size_t i = 0; i < vertices.getVertexCount(); ++i) {
        vertices[i].color = sf::Color::Red;
    }
}

void Ship::draw(sf::RenderTarget& target, sf::RenderStates states) const {   
    target.draw( vertices, getTransform() );    
}


Ship& Ship::operator+=( float dt ) {
        // update position and angle of the ship based on the current speed, acceleration, and angular speed.
        float rangle = angle * PI / 180.;
        pos += sf::Vector2f( u * cos(rangle ) * dt + 0.5f * a * cos(rangle) * dt * dt, 
                             u * sin(rangle ) * dt + 0.5f * a * sin(rangle) * dt * dt );
        angle += w*dt;

        // check for wrap-around of the ship's position
        // wrapAround(pos);

        // update speed
        u += a * dt;

        // check if we need to stop accelerating
        if ( u > MAX_SPEED || u < 0.0f) {
            a = 0.0f;
            if( u > MAX_SPEED ) {
                u = MAX_SPEED;
            }
            if( u < 0.0f ) {
                u = 0.0f;
            }
        }

        // set the transformations of the ship in the following order of function calls: 
        // setPosition, setRotation, setScale.
        setPosition( pos );
        setRotation( sf::degrees( angle ) );
        setScale( sf::Vector2f{ SIZE_SCALE, SIZE_SCALE} );
 
        return *this;
    }


