<?php /* Smarty version 2.6.18, created on 2014-09-04 17:02:57
         compiled from vc2010_lib_proj.tpl */ ?>
<?php echo '<?xml'; ?>
 version="1.0" encoding="utf-8"<?php echo '?>'; ?>

<!-- Library Project Template -->
<Project DefaultTargets="Build" ToolsVersion="4.0" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
  <ItemGroup Label="ProjectConfigurations">
    <ProjectConfiguration Include="Debug|Win32">
      <Configuration>Debug</Configuration>
      <Platform>Win32</Platform>
    </ProjectConfiguration>
    <ProjectConfiguration Include="Optimized Debug|Win32">
      <Configuration>Optimized Debug</Configuration>
      <Platform>Win32</Platform>
    </ProjectConfiguration>
    <ProjectConfiguration Include="Release|Win32">
      <Configuration>Release</Configuration>
      <Platform>Win32</Platform>
    </ProjectConfiguration>
  </ItemGroup>
  <PropertyGroup Label="Globals">
    <ProjectGuid><?php echo $this->_tpl_vars['GUID']; ?>
</ProjectGuid>
  </PropertyGroup>
  <Import Project="$(VCTargetsPath)\Microsoft.Cpp.Default.props" />
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Release|Win32'" Label="Configuration">
    <ConfigurationType>StaticLibrary</ConfigurationType>
    <UseOfMfc>false</UseOfMfc>
  </PropertyGroup>
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Optimized Debug|Win32'" Label="Configuration">
    <ConfigurationType>StaticLibrary</ConfigurationType>
    <UseOfMfc>false</UseOfMfc>
  </PropertyGroup>
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'" Label="Configuration">
    <ConfigurationType>StaticLibrary</ConfigurationType>
    <UseOfMfc>false</UseOfMfc>
  </PropertyGroup>
  <Import Project="$(VCTargetsPath)\Microsoft.Cpp.props" />
  <ImportGroup Label="ExtensionSettings">
  </ImportGroup>
  <ImportGroup Condition="'$(Configuration)|$(Platform)'=='Release|Win32'" Label="PropertySheets">
    <Import Project="Torque.Cpp.$(Platform).user.props" Condition="exists('Torque.Cpp.$(Platform).user.props')" Label="LocalAppDataPlatform" />
  </ImportGroup>
  <ImportGroup Condition="'$(Configuration)|$(Platform)'=='Optimized Debug|Win32'" Label="PropertySheets">
    <Import Project="Torque.Cpp.$(Platform).user.props" Condition="exists('Torque.Cpp.$(Platform).user.props')" Label="LocalAppDataPlatform" />
  </ImportGroup>
  <ImportGroup Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'" Label="PropertySheets">
    <Import Project="Torque.Cpp.$(Platform).user.props" Condition="exists('Torque.Cpp.$(Platform).user.props')" Label="LocalAppDataPlatform" />
  </ImportGroup>
  <PropertyGroup Label="UserMacros" />
  <PropertyGroup>
    <_ProjectFileVersion>10.0.30319.1</_ProjectFileVersion>
    <OutDir Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'"><?php echo $this->_tpl_vars['libDir']; ?>
/compiled/$(Configuration).$(Platform)/</OutDir>
    <IntDir Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'"><?php echo $this->_tpl_vars['projectOffset']; ?>
../Link/VC2010.$(Configuration).$(PlatformName)/$(ProjectName)/</IntDir>
    <TargetName Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'"><?php echo $this->_tpl_vars['projOutName']; ?>
_DEBUG</TargetName>
    <OutDir Condition="'$(Configuration)|$(Platform)'=='Optimized Debug|Win32'"><?php echo $this->_tpl_vars['libDir']; ?>
/compiled/$(Configuration).$(Platform)/</OutDir>
    <IntDir Condition="'$(Configuration)|$(Platform)'=='Optimized Debug|Win32'"><?php echo $this->_tpl_vars['projectOffset']; ?>
../Link/VC2010.$(Configuration).$(PlatformName)/$(ProjectName)/</IntDir>
    <TargetName Condition="'$(Configuration)|$(Platform)'=='Optimized Debug|Win32'"><?php echo $this->_tpl_vars['projOutName']; ?>
_OPTIMIZEDDEBUG</TargetName>
    <OutDir Condition="'$(Configuration)|$(Platform)'=='Release|Win32'"><?php echo $this->_tpl_vars['libDir']; ?>
/compiled/$(Configuration).$(Platform)/</OutDir>
    <IntDir Condition="'$(Configuration)|$(Platform)'=='Release|Win32'"><?php echo $this->_tpl_vars['projectOffset']; ?>
../Link/VC2010.$(Configuration).$(PlatformName)/$(ProjectName)/</IntDir>
    <TargetName Condition="'$(Configuration)|$(Platform)'=='Release|Win32'"><?php echo $this->_tpl_vars['projOutName']; ?>
</TargetName>
  </PropertyGroup>
  <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'">
    <ClCompile>
      <AdditionalOptions>/MP %(AdditionalOptions)</AdditionalOptions>
      <Optimization>Disabled</Optimization>
      <IntrinsicFunctions>true</IntrinsicFunctions>
      <AdditionalIncludeDirectories><?php $_from = $this->_tpl_vars['projIncludes']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?><?php echo $this->_tpl_vars['def']; ?>
;<?php endforeach; endif; unset($_from); ?>%(AdditionalIncludeDirectories)</AdditionalIncludeDirectories>
      <PreprocessorDefinitions><?php $_from = $this->_tpl_vars['projDefines']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?><?php echo $this->_tpl_vars['def']; ?>
;<?php endforeach; endif; unset($_from); ?>TORQUE_DEBUG;TORQUE_DEBUG_GUARD;D3D_DEBUG_INFO;TORQUE_NET_STATS;UNICODE;_CRT_SECURE_NO_DEPRECATE;_CRT_SECURE_NO_WARNINGS;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <ExceptionHandling>
      </ExceptionHandling>
      <BasicRuntimeChecks>Default</BasicRuntimeChecks>
      <StringPooling>true</StringPooling>
      <RuntimeLibrary><?php if ($this->_tpl_vars['projRuntimeDebug'] == 1): ?>MultiThreadedDebug<?php else: ?>MultiThreadedDebugDLL<?php endif; ?></RuntimeLibrary>
      <BufferSecurityCheck>false</BufferSecurityCheck>
      <FunctionLevelLinking>true</FunctionLevelLinking>
      <TreatWChar_tAsBuiltInType>false</TreatWChar_tAsBuiltInType>
      <RuntimeTypeInfo>true</RuntimeTypeInfo>
      <PrecompiledHeader>
      </PrecompiledHeader>
      <PrecompiledHeaderOutputFile>$(OutDir)$(ProjectName)_DEBUG.pch</PrecompiledHeaderOutputFile>
      <AssemblerListingLocation>$(OutDir)</AssemblerListingLocation>
      <ProgramDataBaseFileName>$(OutDir)$(ProjectName)_DEBUG.pdb</ProgramDataBaseFileName>
      <WarningLevel>Level3</WarningLevel>
      <SuppressStartupBanner>true</SuppressStartupBanner>
      <DebugInformationFormat>EditAndContinue</DebugInformationFormat>
      <CompileAs>Default</CompileAs>
      <DisableSpecificWarnings><?php $_from = $this->_tpl_vars['projDisabledWarnings']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?><?php echo $this->_tpl_vars['def']; ?>
;<?php endforeach; endif; unset($_from); ?>4244;4305;4530;4355;%(DisableSpecificWarnings)</DisableSpecificWarnings>      
    </ClCompile>
    <ResourceCompile>
      <PreprocessorDefinitions>_DEBUG;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <Culture>0x0409</Culture>
    </ResourceCompile>
    <Lib>
      <OutputFile>$(OutDir)<?php echo $this->_tpl_vars['projOutName']; ?>
_DEBUG.lib</OutputFile>
      <SuppressStartupBanner>true</SuppressStartupBanner>
    </Lib>
  </ItemDefinitionGroup>
  <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Optimized Debug|Win32'">
    <ClCompile>
      <AdditionalOptions>/MP %(AdditionalOptions)</AdditionalOptions>
      <Optimization>Full</Optimization>
      <InlineFunctionExpansion>AnySuitable</InlineFunctionExpansion>
      <IntrinsicFunctions>true</IntrinsicFunctions>
      <AdditionalIncludeDirectories><?php $_from = $this->_tpl_vars['projIncludes']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?><?php echo $this->_tpl_vars['def']; ?>
;<?php endforeach; endif; unset($_from); ?>%(AdditionalIncludeDirectories)</AdditionalIncludeDirectories>
      <PreprocessorDefinitions><?php $_from = $this->_tpl_vars['projDefines']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?><?php echo $this->_tpl_vars['def']; ?>
;<?php endforeach; endif; unset($_from); ?>TORQUE_DEBUG;TORQUE_DEBUG_GUARD;D3D_DEBUG_INFO;TORQUE_NET_STATS;UNICODE;_CRT_SECURE_NO_DEPRECATE;_CRT_SECURE_NO_WARNINGS;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <ExceptionHandling>
      </ExceptionHandling>
      <BasicRuntimeChecks>Default</BasicRuntimeChecks>
      <StringPooling>true</StringPooling>
      <RuntimeLibrary><?php if ($this->_tpl_vars['projRuntimeDebug'] == 1): ?>MultiThreadedDebug<?php else: ?>MultiThreadedDebugDLL<?php endif; ?></RuntimeLibrary>
      <BufferSecurityCheck>false</BufferSecurityCheck>
      <FunctionLevelLinking>true</FunctionLevelLinking>
      <TreatWChar_tAsBuiltInType>false</TreatWChar_tAsBuiltInType>
      <RuntimeTypeInfo>true</RuntimeTypeInfo>
      <PrecompiledHeader>
      </PrecompiledHeader>
      <PrecompiledHeaderOutputFile>$(OutDir)$(ProjectName)_OPTIMIZEDDEBUG.pch</PrecompiledHeaderOutputFile>
      <AssemblerListingLocation>$(OutDir)</AssemblerListingLocation>
      <ProgramDataBaseFileName>$(OutDir)$(ProjectName)_OPTIMIZEDDEBUG.pdb</ProgramDataBaseFileName>
      <WarningLevel>Level3</WarningLevel>
      <SuppressStartupBanner>true</SuppressStartupBanner>
      <DebugInformationFormat>ProgramDatabase</DebugInformationFormat>
      <CompileAs>Default</CompileAs>
      <DisableSpecificWarnings><?php $_from = $this->_tpl_vars['projDisabledWarnings']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?><?php echo $this->_tpl_vars['def']; ?>
;<?php endforeach; endif; unset($_from); ?>4244;4305;4530;4355;%(DisableSpecificWarnings)</DisableSpecificWarnings>
    </ClCompile>
    <ResourceCompile>
      <PreprocessorDefinitions>_DEBUG;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <Culture>0x0409</Culture>
    </ResourceCompile>
    <Lib>
      <OutputFile>$(OutDir)<?php echo $this->_tpl_vars['projOutName']; ?>
_OPTIMIZEDDEBUG.lib</OutputFile>
      <SuppressStartupBanner>true</SuppressStartupBanner>
    </Lib>
  </ItemDefinitionGroup>
  <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Release|Win32'">
    <ClCompile>
      <AdditionalOptions>/MP %(AdditionalOptions)</AdditionalOptions>
      <Optimization>Full</Optimization>
      <InlineFunctionExpansion>AnySuitable</InlineFunctionExpansion>
      <AdditionalIncludeDirectories><?php $_from = $this->_tpl_vars['projIncludes']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?><?php echo $this->_tpl_vars['def']; ?>
;<?php endforeach; endif; unset($_from); ?>%(AdditionalIncludeDirectories)</AdditionalIncludeDirectories>
      <PreprocessorDefinitions><?php $_from = $this->_tpl_vars['projDefines']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?><?php echo $this->_tpl_vars['def']; ?>
;<?php endforeach; endif; unset($_from); ?>UNICODE;_CRT_SECURE_NO_DEPRECATE;_CRT_SECURE_NO_WARNINGS;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <ExceptionHandling>
      </ExceptionHandling>
      <BasicRuntimeChecks>Default</BasicRuntimeChecks>
      <StringPooling>true</StringPooling>
      <RuntimeLibrary><?php if ($this->_tpl_vars['projRuntimeRelease'] == 0): ?>MultiThreaded<?php else: ?>MultiThreadedDLL<?php endif; ?></RuntimeLibrary>
      <BufferSecurityCheck>false</BufferSecurityCheck>
      <FunctionLevelLinking>true</FunctionLevelLinking>
      <TreatWChar_tAsBuiltInType>false</TreatWChar_tAsBuiltInType>
      <RuntimeTypeInfo>true</RuntimeTypeInfo>
      <PrecompiledHeader>
      </PrecompiledHeader>
      <PrecompiledHeaderOutputFile>$(OutDir)$(ProjectName).pch</PrecompiledHeaderOutputFile>
      <AssemblerListingLocation>$(OutDir)</AssemblerListingLocation>
      <ProgramDataBaseFileName>$(OutDir)$(ProjectName).pdb</ProgramDataBaseFileName>
      <WarningLevel>Level3</WarningLevel>
      <SuppressStartupBanner>true</SuppressStartupBanner>
      <CompileAs>Default</CompileAs>
      <DisableSpecificWarnings><?php $_from = $this->_tpl_vars['projDisabledWarnings']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?><?php echo $this->_tpl_vars['def']; ?>
;<?php endforeach; endif; unset($_from); ?>4244;4305;4530;4355;%(DisableSpecificWarnings)</DisableSpecificWarnings>
    </ClCompile>
    <ResourceCompile>
      <PreprocessorDefinitions>NDEBUG;%(PreprocessorDefinitions)</PreprocessorDefinitions>
    </ResourceCompile>
    <Lib>
      <OutputFile>$(OutDir)/<?php echo $this->_tpl_vars['projOutName']; ?>
.lib</OutputFile>
      <SuppressStartupBanner>true</SuppressStartupBanner>
    </Lib>
  </ItemDefinitionGroup>
  <ItemGroup>
<?php $this->assign('dirWalk', $this->_tpl_vars['fileArray']); ?>
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "vc2010_fileRecurse.tpl", 'smarty_include_vars' => array('dirWalk' => $this->_tpl_vars['dirWalk'],'depth' => 1,'dirPath' => $this->_tpl_vars['projOutput']->base_dir)));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>
  </ItemGroup>
  <ItemGroup>
  <?php $_from = $this->_tpl_vars['projDepend']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['dep']):
?>
    <ProjectReference Include="<?php echo $this->_tpl_vars['projectDepends'][$this->_tpl_vars['dep']]->name; ?>
.vcxproj">
      <Project><?php echo $this->_tpl_vars['projectDepends'][$this->_tpl_vars['dep']]->guid; ?>
</Project>
      <ReferenceOutputAssembly>false</ReferenceOutputAssembly>
    </ProjectReference>
   <?php endforeach; endif; unset($_from); ?>
  </ItemGroup>
  <Import Project="$(VCTargetsPath)\Microsoft.Cpp.targets" />
  <ImportGroup Label="ExtensionTargets">
  </ImportGroup>
</Project>