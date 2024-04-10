#include <vector>
#include <functional>

using namespace std;

class Camera {
public:
  float x, y, z, theta, phi;
  float fov;
  int width, height;
  Scene scene;
  float collisionThreshold;
  vector<vector<Ray>> rays;

  Camera(float x_in, float y_in, float z_in, float theta_in, float phi_in,
	 float fov_in, int width_in, int height_in,
	 Scene scene_in, float collisionThreshold_in) :
    x(x_in), y(y_in), z(z_in), theta(theta_in), phi(phi_in),
    fov(fov_in), width(width_in), height(height_in),
    scene(scene_in), collisionThreshold(collisionThreshold_in) {};
	 
  void InitializeRays() {
    rays.resize(width, vector<Ray>(height));
    float inverseAspectRatio = float(height)/width;
    float halfFov = 0.5*fov;
    Color sceneColor = scene.color;
    for (int i = 0; i < width; i++) {
      for (int j = 0; j < height; j++) {
	rayTheta = -halfFov + fov*float(i)/width;
	rayPhi = inverseAspectRatio * (-halfFov + fov*float(j)/height);
	rays.at(i).at(j) = new Ray(x,y,z,theta + rayTheta, phi+rayPhi, sceneColor);
      }
    }
  }
};

class Ray {
public:
  float x, y, z, theta, phi;
  Color color;

  Ray(float x_in, float y_in, float z_in, float theta_in, float phi_in, Color color_in) :
    x(x_in), y(y_in), theta(theta_in), phi(phi_in), color(color_in) {};

  void March(float d) {
    
  }
}

enum class SceneObjectType {OPAQUE, TRANSLUCENT, LENSE};
class SceneObject {
public:
  SceneObjectType type;
  Color color;
  function< float(float, float, float) > sDF; //Positional data stored in SDF equation

  SceneObject(SceneObjectType type_in, Color color_in, function< float(float, float, float) > sDF_in) :
    type(type_in), color(color_in), sDF(sDF_in) {};
};

class Scene {
public:
  vector<SceneObject> objects;
  Color backgroundColor;

  Scene(vector<SceneObject> objects_in, Color backgroundColor_in) :
    objects(objects_in), backgroundColor(backgroundColor_in) {};
};

class Color {
public:
  int r, g, b;

  Color(int r_in, int g_in, int b_in) :
    r(r_in), g(g_in), b(b_in) {};
};

int main() {
  
  return 0;
}
