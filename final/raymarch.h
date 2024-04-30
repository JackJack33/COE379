#include <vector>
#include <functional>
#include <string>

class Color {
public:
  int r, g, b;

  Color();
  Color(int r_in, int g_in, int b_in);

  static Color Interpolate(Color color1, Color color2, float t);
};

enum class SceneObjectType { OPAQUE, TRANSPARENT, LENSE, MIRROR, LAST };

class SceneObject {
public:
  SceneObjectType type;
  Color color;
  std::vector<float> extraParam;
  std::function<float(float, float, float)> sDF;
  
  SceneObject();
  SceneObject(SceneObjectType type_in, Color color_in, std::function<float(float, float, float)> sDF_in);
  SceneObject(SceneObjectType type_in, Color color_in, std::vector<float> extraParam_in, std::function<float(float, float, float)> sDF_in);
};

class Ray {
public:
  int iterations;
  float x, y, z, theta, phi;
  Color color;

  Ray();
  Ray(float x_in, float y_in, float z_in, float theta_in, float phi_in, Color color_in);
  
  void Cast(float d);
};

class Scene {
public:
  std::vector<SceneObject> objects;
  Color color;
  
  Scene();
  Scene(std::vector<SceneObject> objects_in, Color color_in);
  
  SceneObject closestObject(float x, float y, float z);
};

class Camera {
public:
  float x, y, z, theta, phi;
  float fov;
  int width, height;
  Scene scene;
  float collisionThreshold;
  float distanceCutoff;
  
  std::vector<std::vector<Ray>> rays;
  
  Camera();
  Camera(float x_in, float y_in, float z_in, float theta_in, float phi_in,
           float fov_in, int width_in, int height_in,
           Scene scene_in, float collisionThreshold_in, float distanceCutoff_in);
  
  void InitializeRays();
  void March(int iter);
  float SquaredDistanceToCamera(float x_in, float y_in, float z_in);
  
  std::string ExportRayColors();
};
