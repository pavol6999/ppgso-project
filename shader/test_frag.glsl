#version 330
// A texture is expected as program attribute
uniform sampler2D Texture;

// (optional) Transparency
uniform float Transparency;

// (optional) Texture offset
uniform vec2 TextureOffset;

uniform vec3 objectColor;
uniform vec3 lightColor;

// The vertex shader will feed this input
in vec2 texCoord;

// The final color
out vec4 FragmentColor;

void main() {
  // Lookup the color in Texture on coordinates given by texCoord
  // NOTE: Texture coordinate is inverted vertically for compatibility with OBJ

  FragmentColor = vec4(lightColor * objectColor, 1.0);
  FragmentColor = texture(Texture, vec2(texCoord.x, 1.0 - texCoord.y) + TextureOffset);
}