#include "raymarch.h"
#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>

float sphereSDF(float x, float y, float z, float r) {
  return std::sqrt( x*x + y*y + z*z) - r;
}

float planeSDF(float x, float y, float z, float h) {
  return y - h;
}

int main() {

  Color red(255, 0, 0);
  Color blue(0, 0, 255);
  Color black(0, 0, 0);

  SceneObject redSphere(SceneObjectType::OPAQUE, red,
			[](float x, float y, float z) { return sphereSDF(x, y, z, 2); });
  SceneObject bluePlane(SceneObjectType::OPAQUE, blue,
			[](float x, float y, float z) { return planeSDF(x, y, z, -1); });

  std::vector<SceneObject> objects = {redSphere,
				      bluePlane};

  Scene scene(objects, black);
  Camera camera(0, 0, 0, 0, 0, 70, 8, 8, scene, 0.001);

  camera.InitializeRays();
  camera.March(10);

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
