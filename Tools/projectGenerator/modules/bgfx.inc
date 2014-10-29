<?php
if( inProjectConfig() )  
{  
  includeLib( 'bgfx' );
  addEngineSrcDir( 'gfx/BGFX' );
  addLibIncludePath( 'bgfx/include' );
  addProjectDependency( 'bgfx' );  
  addSolutionProjectRef( 'bgfx' );  
} 
?>