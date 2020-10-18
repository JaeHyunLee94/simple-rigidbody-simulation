//
//  Sphere.cpp
//  rigid_simul
//
//  Created by 이재현 on 2020/10/17.
//

#include "Sphere.hpp"
#include <iostream>

Sphere::Sphere(){
    
    obj = gluNewQuadric();
    gluQuadricDrawStyle(obj, GLU_FILL); // <2>
    gluQuadricNormals(obj, GLU_SMOOTH); // <3>
    gluQuadricOrientation(obj, GLU_OUTSIDE); // <4>
    gluQuadricTexture(obj, GL_FALSE); // <5>
    
    velocity=glm::vec3(0,5,0);
    position=glm::vec3(0,-80,180);
    acceleration=glm::vec3(0,0,0);
    force= glm::vec3(0,0,0);
    
}

void Sphere::applyForce(glm::vec3 force){
    this->force=force;
}

void Sphere::applyImpulse(glm::vec3 impulse){
    
    
}

void Sphere::step(){
    
    

    pos_stack.push_back(position);
    
    
    acceleration=force/mass;
    
    glm::vec3 newvelocity=velocity+acceleration*timeStep;
    
    glm::vec3 newposition=position+velocity*timeStep;
    
    checkCollision(newvelocity,newposition);
    
    
    
}

void Sphere::render(){
    
   
    glPushMatrix();
    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    for(auto& pos: pos_stack){
        glVertex3f(pos.x, pos.y, pos.z);
    }
    
    glEnd();
    glPopMatrix();
    
    
    
    glPushMatrix();
    glColor3f(0.2f, 0.2f, 1.0f);
    glTranslatef(position.x, position.y, position.z);
    gluSphere(obj, radius, 24, 24); // position
    glPopMatrix();
    
    
    
    
    
}

void Sphere::checkCollision(glm::vec3& newvelocity, glm::vec3& newposition){
    
    
    if(newposition.y<100 && newposition.z<radius){
        newposition.z=radius+0.01;
        newvelocity.z=abs(velocity.z)*restitution;
        
    }
    
    position=newposition;
    velocity=newvelocity;
    
}

void Sphere::dump(){
    
    std::cout << "----------------------------------------------------\n";
    std::cout<<"[position] x: "<<position.x << " y: "<<position.y << " z: "<<position.z<<"\n";
    std::cout<<"[velocity] x: "<<velocity.x << " y: "<<velocity.y << " z: "<<velocity.z<<"\n";
    std::cout<<"[acc] x: "<<acceleration.x << " y: "<<acceleration.y << " z: "<<acceleration.z<<"\n";
    std::cout << "----------------------------------------------------\n";
    
    
    
    
}
