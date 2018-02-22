#pragma once

#include <memory>
#include <variant>
#include <optional>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <common.hpp>
#include <shader.hpp>
#include <texture.hpp>

#define MAX_RECT_COUNT 1024

struct Viewport {
    glm::mat4 projection;
    u32 width = 0;
    u32 height = 0;

    GLuint ubo = 0;
};

struct ColoredRect {
    Position pos;
    Size size;
    Color color;

    ColoredRect(Position pos, Size size, Color color) :
        pos(pos), size(size), color(color) {};
};

struct TexturedRect {
    Position pos;
    Size size;
    SpriteId active_sprite;

    TexturedRect(Position pos, Size size, SpriteId active_sprite) :
        pos(pos), size(size), active_sprite(active_sprite) {};
};

using Rect = std::variant<ColoredRect, TexturedRect>;

enum struct RenderGroupType {
    Primitive = 0,
    Sprite
};

struct RenderGroup {
    // TODO: this storage should be transient and
    // filled from game state every frame
    std::vector<Rect> rects = {};

    GLuint vao = 0;
    GLuint vbo = 0;
    GLuint ebo = 0;

    RenderGroupType type;

    std::shared_ptr<Shader> shader;
    std::optional<std::shared_ptr<Texture>> texture;

    RenderGroup();
    ~RenderGroup();

    static std::shared_ptr<RenderGroup> primitive(
        Viewport viewport
    );
    static std::shared_ptr<RenderGroup> sprite(
        Viewport viewport,
        std::shared_ptr<Texture> texture
    );

    void draw() const;

    void push_rect(ColoredRect rect);
    void push_rect(TexturedRect rect);
};

