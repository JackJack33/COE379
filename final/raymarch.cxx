#include "raymarch.h"
#include <cmath>
#include <limits>
#include <sstream>
#include <string>
#include <iostream>

Color::Color() {};

Color::Color(int r_in, int g_in, int b_in) : r(r_in), g(g_in), b(b_in) {};

Color Color::Interpolate(Color color1, Color color2, float t) {
  int r = static_cast<int>(color1.r * (1.0f - t) + color2.r * t);
  int g = static_cast<int>(color1.g * (1.0f - t) + color2.g * t);
  int b = static_cast<int>(color1.b * (1.0f - t) + color2.b * t);
  std::cout << r << " " << g << " " << b << std::endl;
  return Color(r,g,b);
}

SceneObject::SceneObject() {};

SceneObject::SceneObject(SceneObjectType type_in, Color color_in, std::function<float(float, float, float)> sDF_in) :
  type(type_in), color(color_in), sDF(sDF_in) {};

SceneObject::SceneObject(SceneObjectType type_in, Color color_in, std::vector<float> extraParam_in, std::function<float(float, float, float)> sDF_in) :
  type(type_in), color(color_in), extraParam(extraParam_in), sDF(sDF_in) {};

Ray::Ray() {};

Ray::Ray(float x_in, float y_in, float z_in, float theta_in, float phi_in, Color color_in) :
  x(x_in), y(y_in), z(z_in), theta(theta_in), phi(phi_in), color(color_in) { iterations = 0; }

void Ray::Cast(float d) {
  x += d * cos(theta) * cos(phi);
  y += d * sin(theta);
  z += d * cos(theta) * sin(phi);
};

Scene::Scene() {};

Scene::Scene(std::vector<SceneObject> objects_in, Color color_in) :
  objects(objects_in), color(color_in) {};

SceneObject Scene::closestObject(float x, float y, float z) {
  float minDist = std::numeric_limits<float>::max();
  SceneObject minObject;
  for (SceneObject object : objects) {
    float d = object.sDF(x, y, z);
    if (d < minDist) {
      minDist = d;
      minObject = object;
    }
  }
  return minObject;
};

Camera::Camera() {};

Camera::Camera(float x_in, float y_in, float z_in, float theta_in, float phi_in,
               float fov_in, int width_in, int height_in,
               Scene scene_in, float collisionThreshold_in, float distanceCutoff_in) :
  x(x_in), y(y_in), z(z_in), theta(theta_in), phi(phi_in),
  fov(fov_in), width(width_in), height(height_in),
  scene(scene_in), collisionThreshold(collisionThreshold_in), distanceCutoff(distanceCutoff_in) {}

void Camera::InitializeRays() {
  rays.resize(width, std::vector<Ray>(height));
  float inverseAspectRatio = float(height) / width;
  float halfFov = 0.5 * fov;
  Color sceneColor = scene.color;
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      float rayTheta = -halfFov + fov * float(i) / width;
      float rayPhi = inverseAspectRatio * (-halfFov + fov * float(j) / height);
      rays.at(i).at(j) = Ray(x, y, z, theta + rayTheta, phi + rayPhi, sceneColor);
    }
  }
};

void Camera::March(int iter) {
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      bool terminate = false;
      for (int k = 0; k < iter && !terminate; k++) {
	Ray *rayRef = &rays.at(i).at(j);

	SceneObject minObject = scene.closestObject(rayRef->x, rayRef->y, rayRef->z);
	float d = abs(minObject.sDF(rayRef->x, rayRef->y, rayRef->z));

	if (d < collisionThreshold) {

	  float t = 1 + -1 / (float(rayRef->iterations + 1));
	  Color finalColor = Color::Interpolate(minObject.color, Color(0,0,0), t); // Ambient Occlusion
	  
	  float squaredDistanceToCamera = SquaredDistanceToCamera(rayRef->x, rayRef->y, rayRef->z);
	  t = squaredDistanceToCamera / (distanceCutoff*distanceCutoff);
	  finalColor = Color::Interpolate(finalColor, scene.color, t); // Distance Fog
	  
	  switch (minObject.type) {
	  case SceneObjectType::OPAQUE:
	    terminate = true;
	    rayRef->color = finalColor;
	    break;
	  case SceneObjectType::TRANSPARENT:
	    rayRef->color = minObject.color;
	    break;
	  case SceneObjectType::LENSE:
	    rayRef->color = minObject.color;
	    break;
	  case SceneObjectType::MIRROR:
	    rayRef->color = minObject.color;
	    break;
	  }
	}
	if (!terminate) {
	  rayRef->Cast(d);
	  rayRef->iterations++;
	}
      }
    }
  }
};

float Camera::SquaredDistanceToCamera(float x_in, float y_in, float z_in) {
  float dx = x_in - x;
  float dy = y_in - y;
  float dz = z_in - z;
  return dx + dy + dz;
};

std::string Camera::ExportRayColors() {
  std::stringstream ss;
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      Ray ray = rays[i][j];
      ss << "Ray[" << i << "][" << j << "] Color: (" << ray.color.r << ", " << ray.color.g << ", " << ray.color.b << ")\n";
    }
  }
  return ss.str();
};
