#include "raymarch.h"
#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <omp.h>

float sphereSDF(float x_in, float y_in, float z_in,
		float x, float y, float z, float r) {
  float dx = (x_in - x);
  float dy = (y_in - y);
  float dz = (z_in - z);
  return std::sqrt( dx*dx + dy*dy + dz*dz) - r;
};

float swarmSDF(float x_in, float y_in, float z_in,
	       float x, float y, float z, float r, float spacing) {
  float dx = std::fmod(std::abs(x_in), spacing) - x;
  float dy = std::fmod(std::abs(y_in), spacing) - y;
  float dz = std::fmod(std::abs(z_in), spacing) - z;
  return std::sqrt(dx*dx + dy*dy + dz*dz) - r;
};
  
float planeSDF(float x, float y, float z, float h) {
  return y - h;
};

int main() {

  Color red(255, 0, 0);
  Color green(0, 255, 0);
  Color blue(0, 0, 255);
  Color black(0, 0, 0);

  // be careful not to place objects on top of camera
  
  SceneObject redSphere(SceneObjectType::OPAQUE, red,
			[](float x, float y, float z) { return sphereSDF(x, y, z, 5, 0, 0, 1); });
  SceneObject greenSphere(SceneObjectType::OPAQUE, green,
			  [](float x, float y, float z) {return sphereSDF(x, y, z, 15, -3, 0, 3); });
  SceneObject blueSphere(SceneObjectType::OPAQUE, blue,
			 [](float x, float y, float z) { return sphereSDF(x, y, z, 8, 1, 1, 2.5); });
  SceneObject mirrorPlane(SceneObjectType::MIRROR, red,
			   [](float x, float y, float z) { return planeSDF(x, y, z, -3.5); });
  SceneObject mirrorSphere(SceneObjectType::MIRROR, red,
  			   [](float x, float y, float z) { return sphereSDF(x, y, z, 8, -1, -1, 1); });
  SceneObject redSwarm(SceneObjectType::OPAQUE, red,
		       [](float x, float y, float z) { return swarmSDF(x, y, z, 2.5, 2.5, 2.5, 1, 5); });


  // Collection of Spheres
  //std::vector<SceneObject> objects = {redSphere, blueSphere, greenSphere};
  // Mirror Plane
  //std::vector<SceneObject> objects = {redSphere, blueSphere, greenSphere, mirrorPlane};
  // Mirror Sphere
  //std::vector<SceneObject> objects = {redSphere, blueSphere, greenSphere};
  // Sphere Swarm
  std::vector<SceneObject> objects = {redSwarm};
  
  Scene scene(objects, black);
  Camera camera(0, 0, 0, 0, 0, M_PI / 2, 512, 512, scene, 0.001, 1000);

  std::cout << "Scene Intialized" << std::endl;
  
  camera.InitializeRays();

  std::cout << "Rays Initialized" << std::endl;

  double tstart = omp_get_wtime();
  camera.March(100);
  double duration = omp_get_wtime();

  std::cout << "Marched in time " << std::setprecision(3) << duration-tstart << std::endl;
  
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
