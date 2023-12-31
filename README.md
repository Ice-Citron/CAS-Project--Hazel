# CAS-Project-C-Hazel-Engine-
This is my IB DP CAS Project. In which I will be recreating the Hazel game engine, following the tutorial made by "The Cherno". This game engine will gradually be used to create a Minecraft replica. 

Below will contain my notes regarding OpenGL, so that I can refer back to them in the future.

-------------------------------------------------------------------------------------
Episode 4: Vertex Buffers and Drawing a Triangle in OpenGL


Vertex Buffers (VBOs) and Vertex Arrays (VAOs) in OpenGL
    
--- Vertex Buffer Objects (VBOs)
    
    - Purpose: Store vertex data (like positions, colors, texture coordinates) in GPU memory.
    - Usage:
      1. Create and bind a VBO.
      2. Upload vertex data to the VBO from the CPU.
      3. Data in VBOs can be rendered directly by the GPU.
    - Advantage: Reduces CPU-GPU data transfer, enhancing rendering performance.
    
--- Vertex Array Objects (VAOs)
    
    - Purpose: Store the state/configuration for rendering the vertex data. They reference VBOs but do not store vertex data themselves.
    - Usage:
      1. Create and bind a VAO.
      2. Configure how to interpret the vertex data in VBOs (like attribute layout, stride).
      3. Bind the VAO when drawing to use its configuration.
    - Advantage: Simplifies rendering calls by storing vertex attribute configurations, reducing repetitive state setup.
    
--- Workflow
    
    - Create VBOs: Store actual vertex data in GPU memory.
    - Set Up VAOs: Define how the vertex data in VBOs should be interpreted for rendering.
    - Render: Bind the necessary VAO and issue draw calls. The VAO state guides how OpenGL processes vertex data from VBOs.



OpenGL Shaders

- Definition: Small programs written in OpenGL Shading Language (GLSL) that run on the GPU. They are used to control various stages of the graphics rendering pipeline in OpenGL.

--- Types of Shaders

    1. Vertex Shaders:
       - Process each vertex of 3D geometry.
       - Handle tasks like vertex transformations and lighting calculations.
    
    2. Fragment Shaders (Pixel Shaders):
       - Run for each pixel to be rendered.
       - Determine pixel color, texture mapping, and lighting effects.
    
    3. Geometry Shaders:
       - Process entire primitives (e.g., triangles, lines).
       - Capable of adding or modifying vertices.
    
    4. Tessellation Shaders:
       - Control subdivision of geometry.
       - Used for detailed surface representation.

--- How They Are Used

    -- Written in GLSL: Shaders are coded in GLSL, a C-like language specifically for graphics programming.
    -- Compilation and Linking:
       4.1 Shaders are compiled.
       4.2 Linked into a shader program.
    -- Execution:
       - Run on the GPU for efficient graphics processing.
       - Vertex and fragment shaders are essential, while geometry and tessellation shaders are optional.

--- Usage in Rendering Pipeline

    -- Control Over Rendering: Provide programmability at various stages of the rendering pipeline, allowing custom rendering effects.
    -- Shader Programs: Multiple shaders are combined into a shader program, which is then used to render graphics.

--- Benefits

    -- Flexibility: Custom control over the appearance of 3D scenes.
    -- Performance: Execution on the GPU offers high performance, especially for complex rendering tasks.



Binding and Unbinding in OpenGL

-- Binding in OpenGL

   -- Definition: Setting an object as the current active object of its type.
   -- Process:
     1. Bind an object to a specific target (like a texture to GL_TEXTURE_2D).
     2. Subsequent OpenGL calls affect this bound object.
   -- Uses:
     1. Texture Binding: Apply a texture to geometry.
     2. Buffer Binding: Prepare buffers for drawing operations.
     3. Shader Program Binding: Activate shaders for rendering.

-- Unbinding in OpenGL

   -- Definition: Detaching an object from its target, effectively deactivating it.
   -- Process:
     1. Unbind by setting the target to 0 or NULL.
     2. Indicates no object of that type should currently be active.
   -- Uses:
     1. Prevent Side Effects: Avoid unintended operations on objects.
     2. Resource Management: Free up resources and improve performance.

-- Binding and Unbinding Workflow

   -- Bind: Activate an object (e.g., texture, buffer, shader program) for use.
   -- Operate: Perform the desired operations while the object is bound.
   -- Unbind: Deactivate the object to prevent accidental modifications.

-- Importance

   -- State Management: Essential for managing OpenGL’s state-centric architecture.
   -- Error Prevention: Helps avoid bugs by ensuring correct object usage.
   -- Performance: Efficient binding and unbinding can optimize rendering performance.

-------------------------------------------------------------------------------------