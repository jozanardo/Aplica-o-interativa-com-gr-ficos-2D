#include "window.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

void Window::onCreate() {
  auto const *vertexShader{R"gl(#version 300 es
    layout(location = 0) in vec2 inPosition;

    void main() { 
      gl_PointSize = 2.0;
      gl_Position = vec4(inPosition, 0, 1); 
    }
  )gl"};

  auto const *fragmentShader{R"gl(#version 300 es
    precision mediump float;
    out vec4 outColor;

    void main() { outColor = vec4(1); }
  )gl"};

  m_program = abcg::createOpenGLProgram(
    {{.source = vertexShader, .stage = abcg::ShaderStage::Vertex},
     {.source = fragmentShader, .stage = abcg::ShaderStage::Fragment}});

  abcg::glClearColor(0, 0, 0, 1);
  abcg::glClear(GL_COLOR_BUFFER_BIT);

  generateSpiral();

  setupModel();
}

void Window::onResize(glm::ivec2 const &size) {
  m_viewportSize = size;
  abcg::glViewport(0, 0, m_viewportSize.x, m_viewportSize.y);
  abcg::glClear(GL_COLOR_BUFFER_BIT);
}

void Window::onDestroy() {
  abcg::glDeleteProgram(m_program);
  abcg::glDeleteBuffers(1, &m_VBOVertices);
  abcg::glDeleteVertexArrays(1, &m_VAO);
}

void Window::onPaint() {
  if (m_Index < m_Points.size()) {
    abcg::glUseProgram(m_program);
    abcg::glBindVertexArray(m_VAO);
    abcg::glDrawArrays(GL_POINTS, 0, m_Index + 1);
    abcg::glBindVertexArray(0);
    abcg::glUseProgram(0);
    ++m_Index;
  }  
}

void Window::onPaintUI() {
  abcg::OpenGLWindow::onPaintUI();

  {
    ImGui::SetNextWindowPos(ImVec2(5, 81));
    ImGui::Begin(" ", nullptr, ImGuiWindowFlags_NoDecoration);

    if (ImGui::Button("Limpar janela", ImVec2(150, 30))) {
      abcg::glClear(GL_COLOR_BUFFER_BIT);
        m_Index = 0;
        m_Points.clear();
        setupModel();
    }

    ImGui::InputInt("Número de pontos", &m_numPoints);

    ImGui::InputFloat("Escala", &m_scale);
    if (m_scale < 0) {
      m_scale = 0.001f;
    }

    ImGui::InputFloat("Ângulo", &m_angle);
    if (m_angle < 0) {
      m_angle = 0.1f;
    }
 
    if (ImGui::Button("Reset", ImVec2(150, 30))) {
      m_numPoints = 1000;
      m_scale = 0.001f;
      m_angle = 0.1f;
    }

    if (ImGui::Button("Gerar Espiral", ImVec2(150, 30))) {
      if (m_numPoints < 0) {
        m_Index = 0;
        m_Points.clear();
        generateReverseSpiral();
        setupModel();
      } else {
        m_Index = 0;
        m_Points.clear();
        generateSpiral();
        setupModel();
      }
    }

    ImGui::End();
  }
}

void Window::setupModel() {
  abcg::glDeleteBuffers(1, &m_VBOVertices);
  abcg::glDeleteVertexArrays(1, &m_VAO);

  abcg::glGenBuffers(1, &m_VBOVertices);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBOVertices);
  abcg::glBufferData(GL_ARRAY_BUFFER, m_Points.size() * sizeof(glm::vec2),
                     m_Points.data(), GL_STATIC_DRAW);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  auto const positionAttribute{abcg::glGetAttribLocation(m_program, "inPosition")};
  abcg::glGenVertexArrays(1, &m_VAO);
  abcg::glBindVertexArray(m_VAO);
  abcg::glEnableVertexAttribArray(positionAttribute);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBOVertices);
  abcg::glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);
  abcg::glBindVertexArray(0);
}

void Window::generateSpiral() {
  m_Points.clear();

  for (int i = 0; i < m_numPoints; ++i) {
    float theta = i * m_angle;
    float radius = m_scale * i;

    float x = radius * std::cos(theta);
    float y = radius * std::sin(theta);

    m_Points.push_back(glm::vec2(x, y));
  }
}

void Window::generateReverseSpiral() {
  m_Points.clear();

  for (int i = 0; i < (m_numPoints * -1); ++i) {
    float theta = i * m_angle;
    float radius = m_scale * i;

    float x = radius * std::cos(-theta);
    float y = radius * std::sin(-theta);

    m_Points.push_back(glm::vec2(x, y));
  }
}
