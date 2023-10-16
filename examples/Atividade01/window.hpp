#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <vector>
#include <glm/glm.hpp>
#include "abcgOpenGL.hpp"

class Window : public abcg::OpenGLWindow {
protected:
  void onCreate() override;
  void onPaint() override;
  void onPaintUI() override;
  void onResize(glm::ivec2 const &size) override;
  void onDestroy() override;

private:
  glm::ivec2 m_viewportSize{};

  GLuint m_VAO{};
  GLuint m_VBOVertices{};
  GLuint m_program{};

  std::vector<glm::vec2> m_Points;
  size_t m_Index{};
  
  std::vector<glm::vec3> m_pointColors;
  int m_numPoints{1000}; 
  float m_scale{0.001f};
  float m_angle{0.1f};

  void generateSpiral();
  void generateReverseSpiral();
  void setupModel();
};

#endif
