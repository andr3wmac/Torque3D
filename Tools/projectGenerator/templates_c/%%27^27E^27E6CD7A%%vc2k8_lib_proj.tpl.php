<?php /* Smarty version 2.6.18, created on 2014-09-04 17:02:57
         compiled from vc2k8_lib_proj.tpl */ ?>
<?php echo '<?xml'; ?>
 version="1.0" encoding="Windows-1252"<?php echo '?>'; ?>

<VisualStudioProject
	ProjectType="Visual C++"
	Version="9.00"
	Name="<?php echo $this->_tpl_vars['projName']; ?>
"
	ProjectGUID="<?php echo $this->_tpl_vars['GUID']; ?>
"
  TargetFrameworkVersion="131072">
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
			OutputDirectory="<?php echo $this->_tpl_vars['libDir']; ?>
/compiled/$(ConfigurationName).$(PlatformName)"
			IntermediateDirectory="<?php echo $this->_tpl_vars['projectOffset']; ?>
../Link/Vc2k8.$(ConfigurationName).$(PlatformName)/$(ProjectName)"
			ConfigurationType="4"
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
			/>
			<Tool
				Name="VCCLCompilerTool"
				AdditionalOptions="/MP"
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
				ExceptionHandling="0"
				BasicRuntimeChecks="0"
				StringPooling="true"
				RuntimeLibrary="<?php echo $this->_tpl_vars['projRuntimeDebug']; ?>
"
				BufferSecurityCheck="false"
				EnableFunctionLevelLinking="true"
				TreatWChar_tAsBuiltInType="false"
				RuntimeTypeInfo="true"
				UsePrecompiledHeader="0"
				PrecompiledHeaderFile="$(OutDir)/$(ProjectName)_DEBUG.pch"
				AssemblerListingLocation="$(OutDir)"
				ProgramDataBaseFileName="$(OutDir)/$(ProjectName)_DEBUG.pdb"
				WarningLevel="3"
				SuppressStartupBanner="true"
				DebugInformationFormat="4"
				CompileAs="0"
                DisableSpecificWarnings="<?php $_from = $this->_tpl_vars['projDisabledWarnings']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?><?php echo $this->_tpl_vars['def']; ?>
;<?php endforeach; endif; unset($_from); ?>4244;4305;4530;4355"
			/>
			<Tool
				Name="VCManagedResourceCompilerTool"
			/>
			<Tool
				Name="VCResourceCompilerTool"
				PreprocessorDefinitions="_DEBUG"
				Culture="1033"
			/>
			<Tool
				Name="VCPreLinkEventTool"
			/>
			<Tool
				Name="VCLibrarianTool"
				OutputFile="$(OutDir)/<?php echo $this->_tpl_vars['projOutName']; ?>
_DEBUG.lib"
				SuppressStartupBanner="true"
			/>
			<Tool
				Name="VCALinkTool"
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
				Name="VCPostBuildEventTool"
			/>
		</Configuration>
      <Configuration
			Name="Optimized Debug|Win32"
			OutputDirectory="<?php echo $this->_tpl_vars['libDir']; ?>
/compiled/$(ConfigurationName).$(PlatformName)"
			IntermediateDirectory="<?php echo $this->_tpl_vars['projectOffset']; ?>
../Link/Vc2k8.$(ConfigurationName).$(PlatformName)/$(ProjectName)"
			ConfigurationType="4"
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
			/>
         <Tool
				Name="VCCLCompilerTool"
				AdditionalOptions="/MP"
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
				ExceptionHandling="0"
				BasicRuntimeChecks="0"
				StringPooling="true"
				RuntimeLibrary="<?php echo $this->_tpl_vars['projRuntimeDebug']; ?>
"
				BufferSecurityCheck="false"
				EnableFunctionLevelLinking="true"
				TreatWChar_tAsBuiltInType="false"
				RuntimeTypeInfo="true"
				UsePrecompiledHeader="0"
				PrecompiledHeaderFile="$(OutDir)/$(ProjectName)_OPTIMIZEDDEBUG.pch"
				AssemblerListingLocation="$(OutDir)"
				ProgramDataBaseFileName="$(OutDir)/$(ProjectName)_OPTIMIZEDDEBUG.pdb"
				WarningLevel="3"
				SuppressStartupBanner="true"
				DebugInformationFormat="3"
				CompileAs="0"
            	                DisableSpecificWarnings="<?php $_from = $this->_tpl_vars['projDisabledWarnings']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?><?php echo $this->_tpl_vars['def']; ?>
;<?php endforeach; endif; unset($_from); ?>4244;4305;4530;4355"
			/>
         <Tool
				Name="VCManagedResourceCompilerTool"
			/>
         <Tool
				Name="VCResourceCompilerTool"
				PreprocessorDefinitions="_DEBUG"
				Culture="1033"
			/>
         <Tool
				Name="VCPreLinkEventTool"
			/>
         <Tool
				Name="VCLibrarianTool"
				OutputFile="$(OutDir)/<?php echo $this->_tpl_vars['projOutName']; ?>
_OPTIMIZEDDEBUG.lib"
				SuppressStartupBanner="true"
			/>
         <Tool
				Name="VCALinkTool"
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
				Name="VCPostBuildEventTool"
			/>
      </Configuration>
		<Configuration
			Name="Release|Win32"
			OutputDirectory="<?php echo $this->_tpl_vars['libDir']; ?>
/compiled/$(ConfigurationName).$(PlatformName)"
			IntermediateDirectory="<?php echo $this->_tpl_vars['projectOffset']; ?>
../Link/Vc2k8.$(ConfigurationName).$(PlatformName)/$(ProjectName)"
			ConfigurationType="4"
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
			/>
			<Tool
				Name="VCCLCompilerTool"
				AdditionalOptions="/MP"
				Optimization="3"
				InlineFunctionExpansion="2"
				AdditionalIncludeDirectories="<?php $_from = $this->_tpl_vars['projIncludes']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?><?php echo $this->_tpl_vars['def']; ?>
;<?php endforeach; endif; unset($_from); ?>"
				PreprocessorDefinitions="<?php $_from = $this->_tpl_vars['projDefines']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?><?php echo $this->_tpl_vars['def']; ?>
;<?php endforeach; endif; unset($_from); ?>UNICODE;_CRT_SECURE_NO_DEPRECATE;_CRT_SECURE_NO_WARNINGS"
				ExceptionHandling="0"
				BasicRuntimeChecks="0"
				StringPooling="true"
				RuntimeLibrary="<?php echo $this->_tpl_vars['projRuntimeRelease']; ?>
"
				BufferSecurityCheck="false"
				EnableFunctionLevelLinking="true"
				TreatWChar_tAsBuiltInType="false"
				RuntimeTypeInfo="true"
				UsePrecompiledHeader="0"
				PrecompiledHeaderFile="$(OutDir)/$(ProjectName).pch"
				AssemblerListingLocation="$(OutDir)"
				ProgramDataBaseFileName="$(OutDir)/$(ProjectName).pdb"
				WarningLevel="3"
				SuppressStartupBanner="true"
				CompileAs="0"
            	                DisableSpecificWarnings="<?php $_from = $this->_tpl_vars['projDisabledWarnings']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['def']):
?><?php echo $this->_tpl_vars['def']; ?>
;<?php endforeach; endif; unset($_from); ?>4244;4305;4530;4355"
			/>
			<Tool
				Name="VCManagedResourceCompilerTool"
			/>
			<Tool
				Name="VCResourceCompilerTool"
				PreprocessorDefinitions="NDEBUG"
			/>
			<Tool
				Name="VCPreLinkEventTool"
			/>
			<Tool
				Name="VCLibrarianTool"
				OutputFile="$(OutDir)/<?php echo $this->_tpl_vars['projOutName']; ?>
.lib"
				SuppressStartupBanner="true"
			/>
			<Tool
				Name="VCALinkTool"
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
				Name="VCPostBuildEventTool"
			/>
		</Configuration>
	</Configurations>
	<References>
	</References>
	<Files>
		<Filter
			Name="Source Files"
			Filter="cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
			>
<?php $this->assign('dirWalk', $this->_tpl_vars['fileArray']); ?>
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "vc2k8_fileRecurse.tpl", 'smarty_include_vars' => array('dirWalk' => $this->_tpl_vars['dirWalk'],'depth' => 1,'dirPath' => $this->_tpl_vars['projOutput']->base_dir)));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>
		</Filter>
	</Files>
	<Globals>
	</Globals>
</VisualStudioProject>