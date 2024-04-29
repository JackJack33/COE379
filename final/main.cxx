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
	      // individual ray
        bool terminate = false;
      	for (int k = 0; k < iter && !terminate; k++) {
	        *Ray rayRef = &rays.at(i).at(j);
          SceneObject minObject = scene.closestObject(rayRef->x, rayRef->y, rayRef->z);
          float d = abs(minObject.sDF(rayRef->x, rayRef->y, rayRef->z));
          if (d < collisionThreshold) {
            switch(minObject.type) {
              case OPAQUE:
                // end ray
                terminate = true;
                rayRef->color += minObject.color;
                break;
              case TRANSPARENT:
                // move forward to iterate through object
                rayRef->color += minObject.color;
                break;
              case LENSE:
                // extraParam.at(0) = refractive index
                // refract from normal to iterate through object
                rayRef->color += minObject.color;
                break;
              case MIRROR:
                // reflect from normal
                rayRef->color += minObject.color;
                break;
            }
          }
          if (!terminate) {
            rayRef->Cast(d);
          }
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
  
enum class SceneObjectType {OPAQUE, TRANSPARENT, LENSE, MIRROR, LAST};
class SceneObject {
public:
  SceneObjectType type;
  Color color;
  vector<float> extraParam;
  function< float(float, float, float) > sDF; //Positional data stored in SDF equation
  
  SceneObject(SceneObjectType type_in, Color color_in, function< float(float, float, float) > sDF_in) :
    type(type_in), color(color_in), sDF(sDF_in) {};

  SceneObject(SceneObjectType type_in, Color color_in, vector<float> extraParam_in, function< float(float, float, float) > sDF_in) :
    type(type_in), color(color_in), extraParam(extraParam_in) sDF(sDF_in) {};
};

class Scene {
public:
  vector<SceneObject> objects;
  Color backgroundColor;
  
  Scene(vector<SceneObject> objects_in, Color backgroundColor_in) :
    objects(objects_in), backgroundColor(backgroundColor_in) {};

  // Good place for allreduce(min)  
  SceneObject closestObject(float x, float y, float z) {
    float minDist = FLOAT.MAX;
    SceneObject minObject = NULL;
    for (SceneObject object : objects) {
      d = object.sDF(x, y, z);
      if (d < minDist) {
        minDist = d;
        minObject = object;
      }
    }
    return minObject;
  };
};
  
class Color {
public:
  int r, g, b;

  Color(int r_in, int g_in, int b_in) :
    r(r_in), g(g_in), b(b_in) {};


  // define += operator
};

int main() {
  
  return 0;
}
