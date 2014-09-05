<?php /* Smarty version 2.6.18, created on 2014-09-04 17:03:04
         compiled from vc2010_shared.tpl */ ?>
<?php echo '<?xml'; ?>
 version="1.0" encoding="utf-8"<?php echo '?>'; ?>

<!-- Shared Template -->
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
   <RootNamespace><?php echo $this->_tpl_vars['projName']; ?>
</RootNamespace>
    <ProjectGuid><?php echo $this->_tpl_vars['GUID']; ?>
</ProjectGuid>
  </PropertyGroup>
  <Import Project="$(VCTargetsPath)\Microsoft.Cpp.Default.props" />
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Release|Win32'" Label="Configuration">
    <ConfigurationType>Application</ConfigurationType>
    <UseOfMfc>false</UseOfMfc>
  </PropertyGroup>
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Optimized Debug|Win32'" Label="Configuration">
    <ConfigurationType>Application</ConfigurationType>
    <UseOfMfc>false</UseOfMfc>
  </PropertyGroup>
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'" Label="Configuration">
    <ConfigurationType>Application</ConfigurationType>
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
    <OutDir Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'"><?php echo $this->_tpl_vars['projectOffset']; ?>
../../<?php echo $this->_tpl_vars['gameFolder']; ?>
/</OutDir>
    <IntDir Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'"><?php echo $this->_tpl_vars['projectOffset']; ?>
../Link/VC2010.$(Configuration).$(PlatformName)/$(ProjectName)/</IntDir>
    <LinkIncremental Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'">true</LinkIncremental>
    <TargetName Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'"><?php echo $this->_tpl_vars['projOutName']; ?>
_DEBUG</TargetName>
    <OutDir Condition="'$(Configuration)|$(Platform)'=='Optimized Debug|Win32'"><?php echo $this->_tpl_vars['projectOffset']; ?>
../../<?php echo $this->_tpl_vars['gameFolder']; ?>
/</OutDir>
    <IntDir Condition="'$(Configuration)|$(Platform)'=='Optimized Debug|Win32'"><?php echo $this->_tpl_vars['projectOffset']; ?>
../Link/VC2010.$(Configuration).$(PlatformName)/$(ProjectName)/</IntDir>
    <LinkIncremental Condition="'$(Configuration)|$(Platform)'=='Optimized Debug|Win32'">false</LinkIncremental>
    <TargetName Condition="'$(Configuration)|$(Platform)'=='Optimized Debug|Win32'"><?php echo $this->_tpl_vars['projOutName']; ?>
_OPTIMIZEDDEBUG</TargetName>
    <OutDir Condition="'$(Configuration)|$(Platform)'=='Release|Win32'"><?php echo $this->_tpl_vars['projectOffset']; ?>
../../<?php echo $this->_tpl_vars['gameFolder']; ?>
/</OutDir>
    <IntDir Condition="'$(Configuration)|$(Platform)'=='Release|Win32'"><?php echo $this->_tpl_vars['projectOffset']; ?>
../Link/VC2010.$(Configuration).$(PlatformName)/$(ProjectName)/</IntDir>
    <LinkIncremental Condition="'$(Configuration)|$(Platform)'=='Release|Win32'">false</LinkIncremental>
    <TargetName Condition="'$(Configuration)|$(Platform)'=='Release|Win32'"><?php echo $this->_tpl_vars['projOutName']; ?>
</TargetName>
  </PropertyGroup>
  <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'">
    <Midl>
      <TypeLibraryName>$(IntDir)Torque 3D.tlb</TypeLibraryName>
      <HeaderFileName>
      </HeaderFileName>
    </Midl>
    <ClCompile>
      <AdditionalOptions>/MP4 %(AdditionalOptions)</AdditionalOptions>
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
      <ExceptionHandling>Sync</ExceptionHandling>
      <BasicRuntimeChecks>Default</BasicRuntimeChecks>
      <StringPooling>true</StringPooling>
      <RuntimeLibrary><?php if ($this->_tpl_vars['projRuntimeDebug'] == 1): ?>MultiThreadedDebug<?php else: ?>MultiThreadedDebugDLL<?php endif; ?></RuntimeLibrary>
      <BufferSecurityCheck>false</BufferSecurityCheck>
      <FunctionLevelLinking>true</FunctionLevelLinking>
      <TreatWChar_tAsBuiltInType>false</TreatWChar_tAsBuiltInType>
      <RuntimeTypeInfo>true</RuntimeTypeInfo>
      <PrecompiledHeader>
      </PrecompiledHeader>
      <AssemblerListingLocation>$(IntDir)</AssemblerListingLocation>
      <WarningLevel>Level4</WarningLevel>
      <SuppressStartupBanner>true</SuppressStartupBanner>
      <DebugInformationFormat>EditAndContinue</DebugInformationFormat>
      <CompileAs>Default</CompileAs>
      <DisableSpecificWarnings><?php $_from = $this->_tpl_vars['projDisabledWarnings']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?><?php echo $this->_tpl_vars['def']; ?>
;<?php endforeach; endif; unset($_from); ?>4018;4100;4121;4127;4130;4244;4245;4389;4511;4512;4800;%(DisableSpecificWarnings)</DisableSpecificWarnings>
    </ClCompile>
    <ResourceCompile>
      <PreprocessorDefinitions>_DEBUG;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <Culture>0x0409</Culture>
      <AdditionalIncludeDirectories><?php $_from = $this->_tpl_vars['projIncludes']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?><?php echo $this->_tpl_vars['def']; ?>
;<?php endforeach; endif; unset($_from); ?>%(AdditionalIncludeDirectories)</AdditionalIncludeDirectories>
    </ResourceCompile>
    <Link>
      <AdditionalDependencies><?php $_from = $this->_tpl_vars['projLibsDebug']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?><?php echo $this->_tpl_vars['def']; ?>
;<?php endforeach; endif; unset($_from); ?>%(AdditionalDependencies)</AdditionalDependencies>
      <OutputFile>$(OutDir)<?php echo $this->_tpl_vars['projOutName']; ?>
_DEBUG.exe</OutputFile>
      <SuppressStartupBanner>true</SuppressStartupBanner>
      <AdditionalLibraryDirectories><?php $_from = $this->_tpl_vars['projLibDirs']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?><?php echo $this->_tpl_vars['def']; ?>
;<?php endforeach; endif; unset($_from); ?><?php echo $this->_tpl_vars['projectOffset']; ?>
../Link/VC2010.$(Configuration).$(PlatformName);%(AdditionalLibraryDirectories)</AdditionalLibraryDirectories>
      <IgnoreSpecificDefaultLibraries>LIBC;LIBCD;<?php $_from = $this->_tpl_vars['projLibsIgnore']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?><?php echo $this->_tpl_vars['def']; ?>
;<?php endforeach; endif; unset($_from); ?>%(IgnoreSpecificDefaultLibraries)</IgnoreSpecificDefaultLibraries>
      <GenerateDebugInformation>true</GenerateDebugInformation>
      <ProgramDatabaseFile>$(IntDir)$(ProjectName).pdb</ProgramDatabaseFile>
      <SubSystem><?php if ($this->_tpl_vars['projSubSystem'] == 1): ?>Console<?php else: ?>Windows<?php endif; ?></SubSystem>
      <TargetMachine>MachineX86</TargetMachine>
      <RandomizedBaseAddress>false</RandomizedBaseAddress>
      <DataExecutionPrevention>
      </DataExecutionPrevention>
      <ProfileGuidedDatabase>$(IntDir)$(ProjectName).pgd</ProfileGuidedDatabase>
    </Link>
  </ItemDefinitionGroup>
  <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Optimized Debug|Win32'">
    <Midl>
      <TypeLibraryName>$(IntDir)Torque 3D.tlb</TypeLibraryName>
      <HeaderFileName>
      </HeaderFileName>
    </Midl>
    <ClCompile>
      <AdditionalOptions>/MP4 %(AdditionalOptions)</AdditionalOptions>
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
      <ExceptionHandling>Sync</ExceptionHandling>
      <BasicRuntimeChecks>Default</BasicRuntimeChecks>
      <StringPooling>true</StringPooling>
      <RuntimeLibrary><?php if ($this->_tpl_vars['projRuntimeDebug'] == 1): ?>MultiThreadedDebug<?php else: ?>MultiThreadedDebugDLL<?php endif; ?></RuntimeLibrary>
      <BufferSecurityCheck>false</BufferSecurityCheck>
      <FunctionLevelLinking>true</FunctionLevelLinking>
      <TreatWChar_tAsBuiltInType>false</TreatWChar_tAsBuiltInType>
      <RuntimeTypeInfo>true</RuntimeTypeInfo>
      <PrecompiledHeader>
      </PrecompiledHeader>
      <AssemblerListingLocation>$(IntDir)</AssemblerListingLocation>
      <WarningLevel>Level4</WarningLevel>
      <SuppressStartupBanner>true</SuppressStartupBanner>
      <DebugInformationFormat>ProgramDatabase</DebugInformationFormat>
      <CompileAs>Default</CompileAs>
      <DisableSpecificWarnings><?php $_from = $this->_tpl_vars['projDisabledWarnings']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?><?php echo $this->_tpl_vars['def']; ?>
;<?php endforeach; endif; unset($_from); ?>4018;4100;4121;4127;4130;4244;4245;4389;4511;4512;4800;%(DisableSpecificWarnings)</DisableSpecificWarnings>
    </ClCompile>
    <ResourceCompile>
      <PreprocessorDefinitions>_DEBUG;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <Culture>0x0409</Culture>
      <AdditionalIncludeDirectories><?php $_from = $this->_tpl_vars['projIncludes']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?><?php echo $this->_tpl_vars['def']; ?>
;<?php endforeach; endif; unset($_from); ?>%(AdditionalIncludeDirectories)</AdditionalIncludeDirectories>
    </ResourceCompile>
    <Link>
      <AdditionalDependencies><?php $_from = $this->_tpl_vars['projLibsDebug']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?><?php echo $this->_tpl_vars['def']; ?>
;<?php endforeach; endif; unset($_from); ?>%(AdditionalDependencies)</AdditionalDependencies>
      <OutputFile>$(OutDir)<?php echo $this->_tpl_vars['projOutName']; ?>
_OPTIMIZEDDEBUG.exe</OutputFile>
      <SuppressStartupBanner>true</SuppressStartupBanner>
      <AdditionalLibraryDirectories><?php $_from = $this->_tpl_vars['projLibDirs']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?><?php echo $this->_tpl_vars['def']; ?>
;<?php endforeach; endif; unset($_from); ?><?php echo $this->_tpl_vars['projectOffset']; ?>
../Link/VC2010.$(Configuration).$(PlatformName);%(AdditionalLibraryDirectories)</AdditionalLibraryDirectories>
      <IgnoreSpecificDefaultLibraries>LIBC;LIBCD;<?php $_from = $this->_tpl_vars['projLibsIgnore']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?><?php echo $this->_tpl_vars['def']; ?>
;<?php endforeach; endif; unset($_from); ?>%(IgnoreSpecificDefaultLibraries)</IgnoreSpecificDefaultLibraries>
      <GenerateDebugInformation>true</GenerateDebugInformation>
      <ProgramDatabaseFile>$(IntDir)$(ProjectName).pdb</ProgramDatabaseFile>
      <SubSystem><?php if ($this->_tpl_vars['projSubSystem'] == 1): ?>Console<?php else: ?>Windows<?php endif; ?></SubSystem>
      <TargetMachine>MachineX86</TargetMachine>
      <RandomizedBaseAddress>false</RandomizedBaseAddress>
      <DataExecutionPrevention>
      </DataExecutionPrevention>
      <ProfileGuidedDatabase>$(IntDir)$(ProjectName).pgd</ProfileGuidedDatabase>
    </Link>
  </ItemDefinitionGroup>
  <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Release|Win32'">
    <Midl>
      <TypeLibraryName>$(IntDir)Torque 3D.tlb</TypeLibraryName>
      <HeaderFileName>
      </HeaderFileName>
    </Midl>
    <ClCompile>
      <AdditionalOptions>/MP4 %(AdditionalOptions)</AdditionalOptions>
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
;<?php endforeach; endif; unset($_from); ?>UNICODE;_CRT_SECURE_NO_DEPRECATE;_CRT_SECURE_NO_WARNINGS;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <ExceptionHandling>Sync</ExceptionHandling>
      <BasicRuntimeChecks>Default</BasicRuntimeChecks>
      <StringPooling>true</StringPooling>
      <RuntimeLibrary><?php if ($this->_tpl_vars['projRuntimeRelease'] == 0): ?>MultiThreaded<?php else: ?>MultiThreadedDLL<?php endif; ?></RuntimeLibrary>
      <BufferSecurityCheck>false</BufferSecurityCheck>
      <FunctionLevelLinking>true</FunctionLevelLinking>
      <TreatWChar_tAsBuiltInType>false</TreatWChar_tAsBuiltInType>
      <RuntimeTypeInfo>true</RuntimeTypeInfo>
      <PrecompiledHeader>
      </PrecompiledHeader>
      <AssemblerListingLocation>$(IntDir)</AssemblerListingLocation>
      <WarningLevel>Level4</WarningLevel>
      <SuppressStartupBanner>true</SuppressStartupBanner>
      <DebugInformationFormat>ProgramDatabase</DebugInformationFormat>
      <CompileAs>Default</CompileAs>
      <DisableSpecificWarnings><?php $_from = $this->_tpl_vars['projDisabledWarnings']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?><?php echo $this->_tpl_vars['def']; ?>
;<?php endforeach; endif; unset($_from); ?>4018;4100;4121;4127;4130;4244;4245;4389;4511;4512;4800;%(DisableSpecificWarnings)</DisableSpecificWarnings>
    </ClCompile>
    <ResourceCompile>
      <PreprocessorDefinitions>NDEBUG;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <Culture>0x0409</Culture>
      <AdditionalIncludeDirectories><?php $_from = $this->_tpl_vars['projIncludes']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?><?php echo $this->_tpl_vars['def']; ?>
;<?php endforeach; endif; unset($_from); ?>%(AdditionalIncludeDirectories)</AdditionalIncludeDirectories>
    </ResourceCompile>
    <Link>
      <AdditionalDependencies><?php $_from = $this->_tpl_vars['projLibs']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?><?php echo $this->_tpl_vars['def']; ?>
;<?php endforeach; endif; unset($_from); ?>%(AdditionalDependencies)</AdditionalDependencies>
      <OutputFile>$(OutDir)<?php echo $this->_tpl_vars['projOutName']; ?>
.exe</OutputFile>
      <SuppressStartupBanner>true</SuppressStartupBanner>
      <AdditionalLibraryDirectories><?php $_from = $this->_tpl_vars['projLibDirs']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?><?php echo $this->_tpl_vars['def']; ?>
;<?php endforeach; endif; unset($_from); ?><?php echo $this->_tpl_vars['projectOffset']; ?>
../Link/VC2010.$(Configuration).$(PlatformName);%(AdditionalLibraryDirectories)</AdditionalLibraryDirectories>
      <IgnoreSpecificDefaultLibraries>LIBC;LIBCD;<?php $_from = $this->_tpl_vars['projLibsIgnore']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?><?php echo $this->_tpl_vars['def']; ?>
;<?php endforeach; endif; unset($_from); ?>%(IgnoreSpecificDefaultLibraries)</IgnoreSpecificDefaultLibraries>
      <GenerateDebugInformation>false</GenerateDebugInformation>
      <ProgramDatabaseFile>$(IntDir)$(ProjectName).pdb</ProgramDatabaseFile>
      <SubSystem><?php if ($this->_tpl_vars['projSubSystem'] == 1): ?>Console<?php else: ?>Windows<?php endif; ?></SubSystem>
      <TargetMachine>MachineX86</TargetMachine>
      <RandomizedBaseAddress>false</RandomizedBaseAddress>
      <DataExecutionPrevention>
      </DataExecutionPrevention>
      <ProfileGuidedDatabase>$(IntDir)$(ProjectName).pgd</ProfileGuidedDatabase>
    </Link>
  </ItemDefinitionGroup>
  <ItemGroup>
    <ResourceCompile Include="Torque.rc" />
  </ItemGroup>
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