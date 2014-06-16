// Primary Deferred Shader
new GFXStateBlockData( AL_DeferredShadingState )
{
   zDefined = true;
   zEnable = false;
   zWriteEnable = false;

   samplersDefined = true;
   samplerStates[0] = SamplerClampPoint; // depth    
   samplerStates[1] = SamplerClampLinear; // viz color lookup
};

new ShaderData( AL_DeferredShader )
{
   DXVertexShaderFile = "shaders/common/postFx/postFxV.hlsl";
   DXPixelShaderFile  = "shaders/common/lighting/advanced/deferredShadingP.hlsl";

   samplerNames[0] = "color";
   samplerNames[1] = "lightInfoBuffer";
   pixVersion = 2.0;
};

singleton PostEffect( AL_DeferredShading )
{   
   shader = AL_DeferredShader;
   stateBlock = AL_DeferredShadingState;
   texture[0] = "#color";
   texture[1] = "#lightinfo";
   target = "$backBuffer";
   renderPriority = 10000;
};

// Debug Shaders.
new ShaderData( AL_ColorBufferShader )
{
   DXVertexShaderFile = "shaders/common/postFx/postFxV.hlsl";
   DXPixelShaderFile  = "shaders/common/lighting/advanced/dbgColorBufferP.hlsl";

   samplerNames[0] = "color";
   pixVersion = 2.0;
};

singleton PostEffect( AL_ColorBufferVisualize )
{   
   shader = AL_ColorBufferShader;
   stateBlock = AL_DefaultVisualizeState;
   texture[0] = "#color";
   target = "$backBuffer";
   renderPriority = 9999;
};

/// Toggles the visualization of the AL lighting specular power buffer.
function toggleColorBufferViz( %enable )
{   
   if ( %enable $= "" )
   {
      $AL_ColorBufferShaderVar = AL_ColorBufferVisualize.isEnabled() ? false : true;
      AL_ColorBufferVisualize.toggle();
   }
   else if ( %enable )
      AL_ColorBufferVisualize.enable();
   else if ( !%enable )
      AL_ColorBufferVisualize.disable();    
}