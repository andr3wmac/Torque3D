<?php /* Smarty version 2.6.18, created on 2014-09-04 17:03:04
         compiled from vc2k8_shared.tpl */ ?>
<?php echo '<?xml'; ?>
 version="1.0" encoding="Windows-1252"<?php echo '?>'; ?>

<VisualStudioProject
	ProjectType="Visual C++"
	Version="9.00"
	Name="<?php echo $this->_tpl_vars['projName']; ?>
"
	RootNamespace="<?php echo $this->_tpl_vars['projName']; ?>
"
  TargetFrameworkVersion="131072"
	ProjectGUID="<?php echo $this->_tpl_vars['GUID']; ?>
">
	<Platforms>
		<Platform
			Name="Win32"
		/>
	</Platforms>
	<ToolFiles>
	</ToolFiles>
	<Configurations>
		<Configuration
			Name="Debug|Win32"
			OutputDirectory="<?php echo $this->_tpl_vars['projectOffset']; ?>
../Link/VC2k8.$(ConfigurationName).$(PlatformName)"
			IntermediateDirectory="$(OutDir)/$(ProjectName)"
			ConfigurationType="1"
			InheritedPropertySheets="$(VCInstallDir)VCProjectDefaults\UpgradeFromVC71.vsprops"
			UseOfMFC="0"
			ATLMinimizesCRunTimeLibraryUsage="false"
			>
			<Tool
				Name="VCPreBuildEventTool"
			/>
			<Tool
				Name="VCCustomBuildTool"
			/>
			<Tool
				Name="VCXMLDataGeneratorTool"
			/>
			<Tool
				Name="VCWebServiceProxyGeneratorTool"
			/>
			<Tool
				Name="VCMIDLTool"
				TypeLibraryName="$(IntDir)/Torque 3D.tlb"
				HeaderFileName=""
			/>
			<Tool
				Name="VCCLCompilerTool"
				AdditionalOptions="/MP4"
				Optimization="0"
				EnableIntrinsicFunctions="1"
				AdditionalIncludeDirectories="<?php $_from = $this->_tpl_vars['projIncludes']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?><?php echo $this->_tpl_vars['def']; ?>
;<?php endforeach; endif; unset($_from); ?>"
				PreprocessorDefinitions="<?php $_from = $this->_tpl_vars['projDefines']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?><?php echo $this->_tpl_vars['def']; ?>
;<?php endforeach; endif; unset($_from); ?>TORQUE_DEBUG;TORQUE_DEBUG_GUARD;D3D_DEBUG_INFO;TORQUE_NET_STATS;UNICODE;_CRT_SECURE_NO_DEPRECATE;_CRT_SECURE_NO_WARNINGS"
				ExceptionHandling="1"
				BasicRuntimeChecks="0"
				StringPooling="true"
				RuntimeLibrary="<?php echo $this->_tpl_vars['projRuntimeDebug']; ?>
"
				BufferSecurityCheck="false"
				EnableFunctionLevelLinking="true"
				TreatWChar_tAsBuiltInType="false"
				RuntimeTypeInfo="true"
				UsePrecompiledHeader="0"
				AssemblerListingLocation="$(OutDir)"
				ProgramDataBaseFileName="$(OutDir)/$(ProjectName)_DEBUG.pdb"
				WarningLevel="4"
				SuppressStartupBanner="true"
				DebugInformationFormat="4"
				CompileAs="0"
				DisableSpecificWarnings="<?php $_from = $this->_tpl_vars['projDisabledWarnings']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?><?php echo $this->_tpl_vars['def']; ?>
;<?php endforeach; endif; unset($_from); ?>4018;4100;4121;4127;4130;4244;4245;4389;4511;4512;4800"
			/>
			<Tool
				Name="VCManagedResourceCompilerTool"
			/>
			<Tool
				Name="VCResourceCompilerTool"
				PreprocessorDefinitions="_DEBUG"
				Culture="1033"
				AdditionalIncludeDirectories="<?php $_from = $this->_tpl_vars['projIncludes']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?><?php echo $this->_tpl_vars['def']; ?>
;<?php endforeach; endif; unset($_from); ?>"
			/>
			<Tool
				Name="VCPreLinkEventTool"
			/>
			<Tool
				Name="VCLinkerTool"
				AdditionalDependencies="<?php $_from = $this->_tpl_vars['projLibsDebug']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?><?php echo $this->_tpl_vars['def']; ?>
 <?php endforeach; endif; unset($_from); ?>"
				OutputFile="<?php echo $this->_tpl_vars['projectOffset']; ?>
../../<?php echo $this->_tpl_vars['gameFolder']; ?>
/<?php echo $this->_tpl_vars['projOutName']; ?>
_DEBUG.exe"
				LinkIncremental="2"
				SuppressStartupBanner="true"
				AdditionalLibraryDirectories="<?php $_from = $this->_tpl_vars['projLibDirs']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?><?php echo $this->_tpl_vars['def']; ?>
;<?php endforeach; endif; unset($_from); ?><?php echo $this->_tpl_vars['projectOffset']; ?>
../Link/VC2k8.$(ConfigurationName).$(PlatformName);"
				IgnoreDefaultLibraryNames="LIBC,LIBCD<?php $_from = $this->_tpl_vars['projLibsIgnore']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?>,<?php echo $this->_tpl_vars['def']; ?>
<?php endforeach; endif; unset($_from); ?>"
				GenerateDebugInformation="true"
				ProgramDatabaseFile="$(OutDir)/$(ProjectName)_DEBUG.pdb"
				SubSystem="<?php echo $this->_tpl_vars['projSubSystem']; ?>
"
				TargetMachine="1"
				RandomizedBaseAddress="1"
				DataExecutionPrevention="0"        
			/>
			<Tool
				Name="VCALinkTool"
			/>
			<Tool
				Name="VCManifestTool"
			/>
			<Tool
				Name="VCXDCMakeTool"
			/>
			<Tool
				Name="VCBscMakeTool"
			/>
			<Tool
				Name="VCFxCopTool"
			/>
			<Tool
				Name="VCAppVerifierTool"
			/>
			<Tool
				Name="VCWebDeploymentTool"
			/>
			<Tool
				Name="VCPostBuildEventTool"
			/>
		</Configuration>
      <Configuration
			Name="Optimized Debug|Win32"
			OutputDirectory="<?php echo $this->_tpl_vars['projectOffset']; ?>
../Link/VC2k8.$(ConfigurationName).$(PlatformName)"
			IntermediateDirectory="$(OutDir)/$(ProjectName)"
			ConfigurationType="1"
			InheritedPropertySheets="$(VCInstallDir)VCProjectDefaults\UpgradeFromVC71.vsprops"
			UseOfMFC="0"
			ATLMinimizesCRunTimeLibraryUsage="false"
			>
         <Tool
				Name="VCPreBuildEventTool"
			/>
         <Tool
				Name="VCCustomBuildTool"
			/>
         <Tool
				Name="VCXMLDataGeneratorTool"
			/>
         <Tool
				Name="VCWebServiceProxyGeneratorTool"
			/>
         <Tool
				Name="VCMIDLTool"
				TypeLibraryName="$(IntDir)/Torque 3D.tlb"
				HeaderFileName=""
			/>
         <Tool
				Name="VCCLCompilerTool"
				AdditionalOptions="/MP4"
				Optimization="3"
				InlineFunctionExpansion="2"
				EnableIntrinsicFunctions="1"
				AdditionalIncludeDirectories="<?php $_from = $this->_tpl_vars['projIncludes']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?><?php echo $this->_tpl_vars['def']; ?>
;<?php endforeach; endif; unset($_from); ?>"
				PreprocessorDefinitions="<?php $_from = $this->_tpl_vars['projDefines']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?><?php echo $this->_tpl_vars['def']; ?>
;<?php endforeach; endif; unset($_from); ?>TORQUE_DEBUG;TORQUE_DEBUG_GUARD;D3D_DEBUG_INFO;TORQUE_NET_STATS;UNICODE;_CRT_SECURE_NO_DEPRECATE;_CRT_SECURE_NO_WARNINGS"
				ExceptionHandling="1"
				BasicRuntimeChecks="0"
				StringPooling="true"
				RuntimeLibrary = "<?php echo $this->_tpl_vars['projRuntimeDebug']; ?>
"
				BufferSecurityCheck="false"
				EnableFunctionLevelLinking="true"
				TreatWChar_tAsBuiltInType="false"
				RuntimeTypeInfo="true"
				UsePrecompiledHeader="0"
				AssemblerListingLocation="$(OutDir)"
				ProgramDataBaseFileName="$(OutDir)/$(ProjectName)_OPTIMIZEDDEBUG.pdb"
				WarningLevel="4"
				SuppressStartupBanner="true"
				DebugInformationFormat="3"
				CompileAs="0"
				DisableSpecificWarnings="<?php $_from = $this->_tpl_vars['projDisabledWarnings']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?><?php echo $this->_tpl_vars['def']; ?>
;<?php endforeach; endif; unset($_from); ?>4018;4100;4121;4127;4130;4244;4245;4389;4511;4512;4800"
			/>
         <Tool
				Name="VCManagedResourceCompilerTool"
			/>
         <Tool
				Name="VCResourceCompilerTool"
				PreprocessorDefinitions="_DEBUG"
				Culture="1033"
				AdditionalIncludeDirectories="<?php $_from = $this->_tpl_vars['projIncludes']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?><?php echo $this->_tpl_vars['def']; ?>
;<?php endforeach; endif; unset($_from); ?>"
			/>
         <Tool
				Name="VCPreLinkEventTool"
			/>
         <Tool
				Name="VCLinkerTool"
				AdditionalDependencies="<?php $_from = $this->_tpl_vars['projLibsDebug']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?><?php echo $this->_tpl_vars['def']; ?>
 <?php endforeach; endif; unset($_from); ?>"
				OutputFile="<?php echo $this->_tpl_vars['projectOffset']; ?>
../../<?php echo $this->_tpl_vars['gameFolder']; ?>
/<?php echo $this->_tpl_vars['projOutName']; ?>
_OPTIMIZEDDEBUG.exe"
				LinkIncremental="1"
				SuppressStartupBanner="true"
				AdditionalLibraryDirectories="<?php $_from = $this->_tpl_vars['projLibDirs']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?><?php echo $this->_tpl_vars['def']; ?>
;<?php endforeach; endif; unset($_from); ?><?php echo $this->_tpl_vars['projectOffset']; ?>
../Link/VC2k8.$(ConfigurationName).$(PlatformName);"
				IgnoreDefaultLibraryNames="LIBC,LIBCD<?php $_from = $this->_tpl_vars['projLibsIgnore']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?>,<?php echo $this->_tpl_vars['def']; ?>
<?php endforeach; endif; unset($_from); ?>"
				GenerateDebugInformation="true"
				ProgramDatabaseFile="$(OutDir)/$(ProjectName)_OPTIMIZEDDEBUG.pdb"
				SubSystem="<?php echo $this->_tpl_vars['projSubSystem']; ?>
"
				TargetMachine="1"
				RandomizedBaseAddress="1"
				DataExecutionPrevention="0"
			/>
         <Tool
				Name="VCALinkTool"
			/>
         <Tool
				Name="VCManifestTool"
			/>
         <Tool
				Name="VCXDCMakeTool"
			/>
         <Tool
				Name="VCBscMakeTool"
			/>
         <Tool
				Name="VCFxCopTool"
			/>
         <Tool
				Name="VCAppVerifierTool"
			/>
         <Tool
				Name="VCWebDeploymentTool"
			/>
         <Tool
				Name="VCPostBuildEventTool"
			/>
      </Configuration>
		<Configuration
			Name="Release|Win32"
			OutputDirectory="<?php echo $this->_tpl_vars['projectOffset']; ?>
../Link/VC2k8.$(ConfigurationName).$(PlatformName)"
			IntermediateDirectory="$(OutDir)/$(ProjectName)"
			ConfigurationType="1"
			InheritedPropertySheets="$(VCInstallDir)VCProjectDefaults\UpgradeFromVC71.vsprops"
			UseOfMFC="0"
			ATLMinimizesCRunTimeLibraryUsage="false"
			>
			<Tool
				Name="VCPreBuildEventTool"
			/>
			<Tool
				Name="VCCustomBuildTool"
			/>
			<Tool
				Name="VCXMLDataGeneratorTool"
			/>
			<Tool
				Name="VCWebServiceProxyGeneratorTool"
			/>
			<Tool
				Name="VCMIDLTool"
				TypeLibraryName="$(IntDir)/Torque 3D.tlb"
				HeaderFileName=""
			/>
			<Tool
				Name="VCCLCompilerTool"
				AdditionalOptions="/MP4"
				Optimization="3"
				InlineFunctionExpansion="2"
				EnableIntrinsicFunctions="1"
				AdditionalIncludeDirectories="<?php $_from = $this->_tpl_vars['projIncludes']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?><?php echo $this->_tpl_vars['def']; ?>
;<?php endforeach; endif; unset($_from); ?>"
				PreprocessorDefinitions="<?php $_from = $this->_tpl_vars['projDefines']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?><?php echo $this->_tpl_vars['def']; ?>
;<?php endforeach; endif; unset($_from); ?>UNICODE;_CRT_SECURE_NO_DEPRECATE;_CRT_SECURE_NO_WARNINGS"
				ExceptionHandling="1"
				BasicRuntimeChecks="0"
				StringPooling="true"
				RuntimeLibrary="<?php echo $this->_tpl_vars['projRuntimeRelease']; ?>
"
				BufferSecurityCheck="false"
				EnableFunctionLevelLinking="true"
				TreatWChar_tAsBuiltInType="false"
				RuntimeTypeInfo="true"
				UsePrecompiledHeader="0"
				AssemblerListingLocation="$(OutDir)"
				ProgramDataBaseFileName="$(OutDir)/$(ProjectName).pdb"
				WarningLevel="4"
				SuppressStartupBanner="true"
				DebugInformationFormat="3"
				CompileAs="0"
				DisableSpecificWarnings="<?php $_from = $this->_tpl_vars['projDisabledWarnings']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?><?php echo $this->_tpl_vars['def']; ?>
;<?php endforeach; endif; unset($_from); ?>4018;4100;4121;4127;4130;4244;4245;4389;4511;4512;4800"
			/>
			<Tool
				Name="VCManagedResourceCompilerTool"
			/>
			<Tool
				Name="VCResourceCompilerTool"
				PreprocessorDefinitions="NDEBUG"
				Culture="1033"
            AdditionalIncludeDirectories="<?php $_from = $this->_tpl_vars['projIncludes']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?><?php echo $this->_tpl_vars['def']; ?>
;<?php endforeach; endif; unset($_from); ?>"
			/>
			<Tool
				Name="VCPreLinkEventTool"
			/>
			<Tool
				Name="VCLinkerTool"
				AdditionalDependencies="<?php $_from = $this->_tpl_vars['projLibs']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?><?php echo $this->_tpl_vars['def']; ?>
 <?php endforeach; endif; unset($_from); ?>"
				OutputFile="<?php echo $this->_tpl_vars['projectOffset']; ?>
../../<?php echo $this->_tpl_vars['gameFolder']; ?>
/<?php echo $this->_tpl_vars['projOutName']; ?>
.exe"
				LinkIncremental="1"
				SuppressStartupBanner="true"
				AdditionalLibraryDirectories="<?php $_from = $this->_tpl_vars['projLibDirs']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?><?php echo $this->_tpl_vars['def']; ?>
;<?php endforeach; endif; unset($_from); ?><?php echo $this->_tpl_vars['projectOffset']; ?>
../Link/VC2k8.$(ConfigurationName).$(PlatformName);"
				IgnoreDefaultLibraryNames="LIBC<?php $_from = $this->_tpl_vars['projLibsIgnore']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?>,<?php echo $this->_tpl_vars['def']; ?>
<?php endforeach; endif; unset($_from); ?>"
				GenerateDebugInformation="false"
				ProgramDatabaseFile="$(OutDir)/$(ProjectName).pdb"
				SubSystem="<?php echo $this->_tpl_vars['projSubSystem']; ?>
"
				TargetMachine="1"
				RandomizedBaseAddress="1"
				DataExecutionPrevention="0"

			/>
			<Tool
				Name="VCALinkTool"
			/>
			<Tool
				Name="VCManifestTool"
			/>
			<Tool
				Name="VCXDCMakeTool"
			/>
			<Tool
				Name="VCBscMakeTool"
			/>
			<Tool
				Name="VCFxCopTool"
			/>
			<Tool
				Name="VCAppVerifierTool"
			/>
			<Tool
				Name="VCWebDeploymentTool"
			/>
			<Tool
				Name="VCPostBuildEventTool"
			/>
		</Configuration>
	</Configurations>
	<References>
	</References>
	<Files>
		<Filter
			Name="Source Files"
			Filter="cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;cc">
			<File
				RelativePath=".\Torque.rc">
			</File>
<?php $this->assign('dirWalk', $this->_tpl_vars['fileArray']); ?>
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "vc2k8_fileRecurse.tpl", 'smarty_include_vars' => array('dirWalk' => $this->_tpl_vars['dirWalk'],'depth' => 2,'dirPath' => $this->_tpl_vars['projOutput']->base_dir)));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>
		</Filter>
	</Files>
	<Globals>
	</Globals>
</VisualStudioProject>