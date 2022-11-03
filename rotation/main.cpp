#include <ljgl.hpp>
#include "ArduinoSerialIO/arduinoSerial.hpp"

int main(){
    arduinoSerial Serial("/dev/ttyACM0"); // Create a arduinoSerial object
    Serial.begin(B1000000); // Actually sets up the serial port (configures everything)
    GLFWwindow* window = LJGL::init(1024, 1024, "Digital clone", 3, 3); // Creates a window and initialize OpenGL
    LJGL::world w(window); // Creates a "world" which can be used to easily manage objects
    unsigned int suzanne = w.createAddModel_EBO("suzanne"); // Creates a model and adds it to the world. Returns the ID of the model (position in the world's LJGL::model* vector)
    w.models[suzanne]->m_shader.createShader("GLSL/shader.vert.glsl", "GLSL/shader.frag.glsl"); // Compiles and links a shader program
    w.models[suzanne]->m_shader.setUniform3f("lightPos", 1.0f, 2.0f, 3.0f); // Set the position of the light source
    w.models[suzanne]->m_shader.setUniform3f("objectColor", 0.7f, 0.8f, 0.1f); // Make the suzanne a cool colour
    while(!glfwWindowShouldClose(window)){ // Main loop
        Serial.print('X'); // Request the X rotation value from the arduino
        int angleX = atoi(Serial.readStringUntil('\n').c_str()); // Read the value from the arduino and convert it to an int
        Serial.flush(); // Flush the serial buffer
        Serial.print('Y');
        int angleY = atoi(Serial.readStringUntil('\n').c_str());
        Serial.flush();
        Serial.print('Z');
        int angleZ = atoi(Serial.readStringUntil('\n').c_str());
        Serial.flush();
        w.models[suzanne]->m_model = glm::mat4(1.0f); // Reset the model matrix
        w.models[suzanne]->m_model = glm::rotate(w.models[suzanne]->m_model, glm::radians((float)angleX), glm::vec3(1.0f, 0.0f, 0.0f)); // Rotate the model matrix (X axis)
        w.models[suzanne]->m_model = glm::rotate(w.models[suzanne]->m_model, glm::radians((float)angleY), glm::vec3(0.0f, 1.0f, 0.0f));
        w.models[suzanne]->m_model = glm::rotate(w.models[suzanne]->m_model, glm::radians((float)angleZ), glm::vec3(0.0f, 0.0f, 1.0f));
        w.processInput(); // Process input (Camera movement, etc.)
        w.render(); // Render the world (draws all the models)
    }

    return 0;
}
