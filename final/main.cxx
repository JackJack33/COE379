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

  void March(int iter) {
    for (int i = 0; i < width; i++) {
      for (int j = 0; j < height; j++) {
      ray:
	// individual ray
	for (int k = 0; k < iter; k++) {
	  Ray newRay = rays.at(i).at(j);
	  vector<float> typedMinSDFs = scene.typedMinSDFs(newRay.x, newRay.y, newRay.z);
	  for (int l = 0; l < typedMinSDFs.size(); l++) {
	    if (abs(typedMinSDFs.at(l)) <= collisionThreshold) {
	      // collided
	      goto ray;
	  }
	  newRay.Cast();
	}
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

  void Cast(float d) {
    x += d * cos(theta) * cos(phi);
    y += d * sin(theta);
    z += d * cos(theta) * sin(phi);
  } 
};
  
enum class SceneObjectType {OPAQUE, TRANSLUCENT, LENSE, MIRROR, LAST};
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
  
  vector<float> typedMinSDFs(float x, float y, float z) {
    vector<float> dv;
    for (int i = 0; i < SceneObjectType.LAST; i++) {
      float d = FLOAT.MAX;
      for (SceneObject object : objects) {
	if (object.type != type) { continue; }
	d = min(d, object.sDF(x,y,z));
      }
      dv.push_back(d);
    }
    return dv;
  }
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
