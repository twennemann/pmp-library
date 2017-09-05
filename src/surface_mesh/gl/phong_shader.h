
#ifndef __EMSCRIPTEN__  // standard version (OpenGL 3.2 and higher)


static const char* phong_vshader =
    "#version 150\n"
    "\n"
    "in vec4 v_position;\n"
    "in vec3 v_normal;\n"
    "out vec3 v2f_normal;\n"
    "out vec3 v2f_view;\n"
    "uniform mat4 modelview_projection_matrix;\n"
    "uniform mat4 modelview_matrix;\n"
    "uniform mat3 normal_matrix;\n"
    "\n"
    "void main()\n"
    "{\n"
    "   v2f_normal  = normal_matrix * v_normal;\n"
    "   v2f_view    = -(modelview_matrix*v_position).xyz;\n"
    "   gl_Position = modelview_projection_matrix * v_position;\n"
    "} \n";


static const char* phong_fshader = 
    "#version 150\n"
    "\n"
    "in vec3 v2f_normal;\n"
    "in vec3 v2f_view;\n"
    "\n"
    "uniform bool   use_lighting = true;\n"
    "uniform vec3   front_color  = vec3(0.6, 0.6, 0.6);\n"
    "uniform vec3   back_color   = vec3(0.5, 0.0, 0.0);\n"
    "uniform float  ambient      = 0.1;\n"
    "uniform float  diffuse      = 0.8;\n"
    "uniform float  specular     = 0.6;\n"
    "uniform float  shininess    = 100.0;\n"
    "uniform vec3   light1       = vec3( 1.0, 1.0, 1.0);\n"
    "uniform vec3   light2       = vec3(-1.0, 1.0, 1.0);\n"
    "\n"
    "out vec4 f_color;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    vec3 color = gl_FrontFacing ? front_color : back_color;\n"
    "    vec3 rgb;\n"
    "\n"
    "    if (use_lighting)\n"
    "    {\n"
    "        vec3 L1 = normalize(light1);\n"
    "    	vec3 L2 = normalize(light2);\n"
    "        vec3 N  = normalize(v2f_normal);\n"
    "    	vec3 V  = normalize(v2f_view);\n"
    "   \n"
    "        if (!gl_FrontFacing) N = -N;\n"
    "\n"
    "        vec3  R;\n"
    "        float NL, RV;\n"
    "\n"
    "        rgb = ambient * 0.1 * color;\n"
    "\n"
    "        NL = dot(N, L1);\n"
    "        if (NL > 0.0)\n"
    "        {\n"
    "            rgb += diffuse * NL * color;\n"
    "            R  = normalize(-reflect(L1, N));\n"
    "            RV = dot(R, V);\n"
    "            if (RV > 0.0) \n"
    "            {\n"
    "                rgb += vec3( specular * pow(RV, shininess) );\n"
    "            }\n"
    "        }\n"
    "\n"
    "        NL = dot(N, L2);\n"
    "        if (NL > 0.0)\n"
    "        {\n"
    "            rgb += diffuse * NL * color;\n"
    "            R  = normalize(-reflect(L2, N));\n"
    "            RV = dot(R, V);\n"
    "            if (RV > 0.0) \n"
    "            {\n"
    "                rgb += vec3( specular * pow(RV, shininess) );\n"
    "            }\n"
    "        }\n"
    "    }\n"
    "\n"
    "    // do not use lighting\n"
    "    else\n"
    "    {\n"
    "        rgb = color;\n"
    "    }\n"
    "\n"
    "    f_color = vec4(rgb, 1.0);\n"
    "}";


#else // emscripten WebGL-friendly version


static const char* phong_vshader = 
    "attribute vec4 v_position;\n"
    "attribute vec3 v_normal;\n"
    "varying vec3 v2f_normal;\n"
    "varying vec3 v2f_view;\n"
    "uniform mat4 modelview_projection_matrix;\n"
    "uniform mat4 modelview_matrix;\n"
    "uniform mat3 normal_matrix;\n"
    "\n"
    "void main()\n"
    "{\n"
    "   gl_PointSize = 5.0;\n"
    "   v2f_normal  = normal_matrix * v_normal;\n"
    "   v2f_view    = -(modelview_matrix*v_position).xyz;\n"
    "   gl_Position = modelview_projection_matrix * v_position;\n"
    "}\n";

static const char* phong_fshader = 
    "precision highp float;\n"
    "varying vec3 v2f_normal;\n"
    "varying vec3 v2f_view;\n"
    "uniform bool   use_lighting;\n"
    "uniform vec3   front_color;\n"
    "uniform vec3   back_color;\n"
    "uniform vec3   light1;\n"
    "uniform vec3   light2;\n"
    "float  ambient      = 0.1;\n"
    "float  diffuse      = 0.8;\n"
    "float  specular     = 0.6;\n"
    "float  shininess    = 100.0;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    vec3 color = gl_FrontFacing ? front_color : back_color;\n"
    "    vec3 rgb;\n"
    "\n"
    "    if (use_lighting)\n"
    "    {\n"
    "        vec3 L1 = normalize(light1);\n"
    "    	vec3 L2 = normalize(light2);\n"
    "        vec3 N  = normalize(v2f_normal);\n"
    "    	vec3 V  = normalize(v2f_view);\n"
    "   \n"
    "        if (!gl_FrontFacing) N = -N;\n"
    "\n"
    "        vec3  R;\n"
    "        float NL, RV;\n"
    "\n"
    "        rgb = ambient * 0.1 * color;\n"
    "\n"
    "        NL = dot(N, L1);\n"
    "        if (NL > 0.0)\n"
    "        {\n"
    "            rgb += diffuse * NL * color;\n"
    "            R  = normalize(-reflect(L1, N));\n"
    "            RV = dot(R, V);\n"
    "            if (RV > 0.0) \n"
    "            {\n"
    "                rgb += vec3( specular * pow(RV, shininess) );\n"
    "            }\n"
    "        }\n"
    "\n"
    "        NL = dot(N, L2);\n"
    "        if (NL > 0.0)\n"
    "        {\n"
    "            rgb += diffuse * NL * color;\n"
    "            R  = normalize(-reflect(L2, N));\n"
    "            RV = dot(R, V);\n"
    "            if (RV > 0.0) \n"
    "            {\n"
    "                rgb += vec3( specular * pow(RV, shininess) );\n"
    "            }\n"
    "        }\n"
    "    }\n"
    "\n"
    "    // do not use lighting\n"
    "    else\n"
    "    {\n"
    "        rgb = color;\n"
    "    }\n"
    "\n"
    "    gl_FragColor = vec4(rgb, 1.0);\n"
    "}";


#endif
