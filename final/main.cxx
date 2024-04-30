#include "raymarch.h"
#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>

float sphereSDF(float x_in, float y_in, float z_in,
		float x, float y, float z, float r) {
  float dx = (x - x_in);
  float dy = (y - y_in);
  float dz = (z - z_in);
  return std::sqrt( dx*dx + dy*dy + dz*dz) - r;
}

float planeSDF(float x, float y, float z, float h) {
  return y - h;
}

int main() {

  Color red(255, 0, 0);
  Color green(0, 255, 0);
  Color blue(0, 0, 255);
  Color black(0, 0, 0);
  
  SceneObject redSphere(SceneObjectType::OPAQUE, red,
			[](float x, float y, float z) { return sphereSDF(x, y, z, 5, 0, 0, 1); });
  SceneObject greenSphere(SceneObjectType::OPAQUE, green,
			  [](float x, float y, float z) {return sphereSDF(x, y, z, 15, -3, 0, 3); });
  SceneObject blueSphere(SceneObjectType::OPAQUE, blue,
			 [](float x, float y, float z) { return sphereSDF(x, y, z, 8, 1, 1, 2.5); });
  SceneObject mirrorPlane(SceneObjectType::OPAQUE, red,
			   [](float x, float y, float z) { return planeSDF(x, y, z, -4); });

  std::vector<SceneObject> objects = {greenSphere, mirrorPlane};

  Scene scene(objects, black);
  Camera camera(0, 0, 0, 0, 0, M_PI / 2.0, 256, 256, scene, 0.00001, 1000);

  camera.InitializeRays();
  camera.March(20);

  std::string output = camera.ExportRayColors();

  std::ofstream outputFile("output.txt");
  if (outputFile.is_open()) {
    outputFile << output;
    outputFile.close();
    std::cout << "Output written to output.txt" << std::endl;
  }
  else {
    std::cout << "Unable to write to output.txt" << std::endl;
  }
  
  return 0;
}
