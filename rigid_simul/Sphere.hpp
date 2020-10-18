//
//  Sphere.hpp
//  rigid_simul
//
//  Created by 이재현 on 2020/10/17.
//

#ifndef Sphere_hpp
#define Sphere_hpp

#include <stdio.h>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>

class Sphere{
    
    
public:
    
    GLUquadricObj *obj;
    float restitution=0.8f;
    float mass=2.0f;
    float radius=8.0f;
    float timeStep=1.f/10;
    
    float time=0.0f;
    float cycle=1.0f;
    glm::vec3 velocity;
    glm::vec3 acceleration;
    glm::vec3 position;
    glm::vec3 force;
    
    std::vector<glm::vec3> pos_stack;
    
    
    
    
    
    void applyForce(glm::vec3 force);
    void applyImpulse(glm::vec3 impulse);
    void checkCollision(glm::vec3& newvelocity,glm::vec3& newposition);
    void step();
    
    
    void render();
    void dump();
    
    

    Sphere();

    
    
};




#endif /* Sphere_hpp */
