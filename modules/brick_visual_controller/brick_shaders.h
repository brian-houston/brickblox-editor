#ifndef BRICK_SHADERS_H
#define BRICK_SHADERS_H

String get_brick_shader_code() {
    return R"(
shader_type spatial;
  
varying flat vec3 color;

vec3 toLinear(vec3 sRGB)
{
    bvec3 cutoff = lessThan(sRGB, vec3(0.04045));
    vec3 higher = pow((sRGB + vec3(0.055))/vec3(1.055), vec3(2.4));
    vec3 lower = sRGB/vec3(12.92);

    return vec3(mix(higher, lower, cutoff));
}

void vertex() {
    int bits = floatBitsToInt(INSTANCE_CUSTOM.r);
    int b = (bits >> 8) & 0xff;
    int g = (bits >> 16) & 0xff;
    int r = (bits >> 24) & 0xff;
    color = toLinear(vec3(float(r), float(g), float(b)) / 255.0);
}

void fragment() {
    ALBEDO = color;
}  
    )";
}

String get_brick_alpha_shader_code() {
    return R"(
shader_type spatial;
  
varying flat vec4 color;

vec3 toLinear(vec3 sRGB)
{
    bvec3 cutoff = lessThan(sRGB, vec3(0.04045));
    vec3 higher = pow((sRGB + vec3(0.055))/vec3(1.055), vec3(2.4));
    vec3 lower = sRGB/vec3(12.92);

    return vec3(mix(higher, lower, cutoff));
}

void vertex() {
    int bits = floatBitsToInt(INSTANCE_CUSTOM.r);
    int a =  bits & 0xff;
    int b = (bits >> 8) & 0xff;
    int g = (bits >> 16) & 0xff;
    int r = (bits >> 24) & 0xff;
    color = vec4(toLinear(vec3(float(r), float(g), float(b)) / 255.0), float(a) / 255.0);
}

void fragment() {
    ALBEDO = color.rgb;
    ALPHA = color.a;
}  
    )";
}

#endif