//
//  main.cpp
//  rigid_simul
//
//  Created by 이재현 on 2020/10/17.
//

#include <iostream>
#include <GL/glew.h>
#include <GL/GLU.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include "Sphere.hpp"

GLFWwindow* window;

int WINDOW_WIDTH=0;
int WINDOW_HEIGHT=0;


int init(){
    if (!glfwInit()) {
        std::cout << "glfw init failed!!\n";
        return 1;
    }
    
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    
    WINDOW_WIDTH=1000;
    WINDOW_HEIGHT=1000;
    
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "opengl_playground", NULL, NULL);
    
    if (!window) {
        std::cout << "window creation failed!\n";
        glfwTerminate();
        return 1;
    }
    
    glfwMakeContextCurrent(window);
    
    
    glewExperimental = GL_TRUE;
    
    GLenum errorCode = glewInit();
    if (GLEW_OK != errorCode) {
        
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    
    
    glClearColor( 0.9, 0.9, 0.9, 1.0f);
    

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    
    
    
    
    return 0;
}




void setCamera(){
    //set camera
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, float(400)/float(400), 0.1, 1000.0);
    gluLookAt(250, 150, 30, 0, 0, 30, 0, 0, 1);
    glPopMatrix();
    
    glFlush();
    
    
    
}
void drawCoord(){
    //draw x,y,z, coordinate



    glPushMatrix();
    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    glVertex3f(0, 0, -1000);
    glVertex3f(0, 0, 1000);
    glEnd();
    glPopMatrix();
    
    glPushMatrix();
    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    glVertex3f(0, -1000, -50);
    glVertex3f(0, 1000, -50);
    glEnd();
    glPopMatrix();
    
    glPushMatrix();
    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    glVertex3f(-1000, 0, -50);
    glVertex3f(1000, 0, -50);
    glEnd();
    glPopMatrix();
    
    
}

void drawCube(){
    //draw cube

    glPushMatrix();
    glColor3f(1.0f, 153.f/255, 1.0f);
    glRectf(-100, -100, 100, 100);
    glPopMatrix();
    glFlush();
    
    glPushMatrix();
    glColor3f(1.0f,0, 1.0f);
    glBegin(GL_QUADS);
    glVertex3f(100, 100, 0);
    glVertex3f(100, 100, -100);
    glVertex3f(100, -100, -100);
    glVertex3f(100, -100, 0);
    glEnd();
    glPopMatrix();
    glFlush();
    
    glPushMatrix();
    glColor3f(0.0f,1.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex3f(100, 100, 0);
    glVertex3f(100, 100, -100);
    glVertex3f(-100, 100, -100);
    glVertex3f(-100, 100, 0);
    glEnd();
    glPopMatrix();
    glFlush();
}

void setLight(){
    
    glPushMatrix();
    
    // 0번 광원 배치.
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    GLfloat ambient[4] = {1.0, 1.0, 1.0, 0.0};
    GLfloat diffuse[4] = {1.0, 1.0, 1.0, 0.0};
    GLfloat specular[4] = {0, 0, 0, 0.0};
    GLfloat position[4] = {30, 30, 30, 1};
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    
    glPopMatrix();
    
    
}
int main(int argc, char ** argv) {
  
   //init glfw and glew 
    init();
    
    
    Sphere sphere;

    //set gravity
    glm::vec3 gravity(0,0,-9.8);
    
    while (!glfwWindowShouldClose(window)) {
        setCamera();
        setLight();
  
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        sphere.applyForce(gravity*sphere.mass);
        sphere.step();
        sphere.render();

        //sphere.dump();
            
        drawCube();
        //drawCoord();
        
     
        
        
        
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }
    
    
    
    return 0;
}
