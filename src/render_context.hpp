#pragma once

#include <memory>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <common.hpp>
#include <render_group.hpp>

#define MAX_RENDER_GROUP_COUNT 10

struct RenderContext {
    i32 viewport_width = 0;
    i32 viewport_height = 0;

    const GLubyte* renderer_string;
    const GLubyte* version_string;

    std::shared_ptr<RenderGroup> render_groups[MAX_RENDER_GROUP_COUNT];
    u32 render_group_count = 0;
    glm::mat4 projection;

    RenderContext(GLFWwindow* window);
    ~RenderContext();

    void draw() const;

    std::shared_ptr<RenderGroup> create_primitive_render_group();
    std::shared_ptr<RenderGroup> create_sprite_render_group(
        const std::string& texture_name
    );
};
