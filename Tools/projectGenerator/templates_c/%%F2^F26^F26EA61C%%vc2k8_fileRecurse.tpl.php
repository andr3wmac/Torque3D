<?php /* Smarty version 2.6.18, created on 2014-09-04 17:02:57
         compiled from vc2k8_fileRecurse.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('modifier', 'indent', 'vc2k8_fileRecurse.tpl', 13, false),array('modifier', 'replace', 'vc2k8_fileRecurse.tpl', 35, false),)), $this); ?>
<?php if (is_array ( $this->_tpl_vars['dirWalk'] )): ?>
<?php if ($this->_tpl_vars['depth'] > 2): ?>
<?php ob_start(); ?>
<Filter
	Name="<?php echo $this->_tpl_vars['dirName']; ?>
"
	Filter=""><?php $this->_smarty_vars['capture']['default'] = ob_get_contents();  $this->assign('dirPrefix', ob_get_contents());ob_end_clean(); ?>
<?php echo ((is_array($_tmp=$this->_tpl_vars['dirPrefix'])) ? $this->_run_mod_handler('indent', true, $_tmp, $this->_tpl_vars['depth'], "\t") : smarty_modifier_indent($_tmp, $this->_tpl_vars['depth'], "\t")); ?>

<?php endif; ?>
<?php $_from = $this->_tpl_vars['dirWalk']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['key'] => $this->_tpl_vars['dir']):
?>
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "vc2k8_fileRecurse.tpl", 'smarty_include_vars' => array('dirWalk' => $this->_tpl_vars['dir'],'dirName' => $this->_tpl_vars['key'],'dirPath' => ($this->_tpl_vars['dirPath']).($this->_tpl_vars['dirName'])."/",'depth' => $this->_tpl_vars['depth']+1)));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>
<?php endforeach; endif; unset($_from); ?>
<?php if ($this->_tpl_vars['depth'] > 2): ?>
<?php ob_start(); ?>
</Filter><?php $this->_smarty_vars['capture']['default'] = ob_get_contents();  $this->assign('dirSuffix', ob_get_contents());ob_end_clean(); ?>
<?php echo ((is_array($_tmp=$this->_tpl_vars['dirSuffix'])) ? $this->_run_mod_handler('indent', true, $_tmp, $this->_tpl_vars['depth'], "\t") : smarty_modifier_indent($_tmp, $this->_tpl_vars['depth'], "\t")); ?>

<?php endif; ?>
<?php else: ?>
<?php ob_start(); ?>
<File
   RelativePath="<?php echo ((is_array($_tmp=((is_array($_tmp=$this->_tpl_vars['dirWalk']->path)) ? $this->_run_mod_handler('replace', true, $_tmp, '//', '/') : smarty_modifier_replace($_tmp, '//', '/')))) ? $this->_run_mod_handler('replace', true, $_tmp, '/', '\\') : smarty_modifier_replace($_tmp, '/', '\\')); ?>
">
<?php if (dontCompile ( $this->_tpl_vars['dirWalk']->path , $this->_tpl_vars['projOutput'] )): ?>
	<FileConfiguration
		Name="Debug|Win32"
		ExcludedFromBuild="true"
		>
		<Tool
			Name="VCCLCompilerTool"
		/>
	</FileConfiguration>
	<FileConfiguration
		Name="Optimized Debug|Win32"
		ExcludedFromBuild="true"
		>
		<Tool
			Name="VCCLCompilerTool"
		/>
	</FileConfiguration>
	<FileConfiguration
		Name="Release|Win32"
		ExcludedFromBuild="true"
		>
		<Tool
			Name="VCCLCompilerTool"
		/>
	</FileConfiguration>
<?php else: ?>
<?php if (substr ( $this->_tpl_vars['dirWalk']->path , -4 , 4 ) == ".asm"): ?>
	<FileConfiguration
		Name="Debug|Win32">
		<Tool
			Name="VCCustomBuildTool"
			CommandLine="&quot;<?php echo ((is_array($_tmp=((is_array($_tmp=$this->_tpl_vars['binDir'])) ? $this->_run_mod_handler('replace', true, $_tmp, '//', '/') : smarty_modifier_replace($_tmp, '//', '/')))) ? $this->_run_mod_handler('replace', true, $_tmp, '/', '\\') : smarty_modifier_replace($_tmp, '/', '\\')); ?>
nasm\nasm.exe&quot; -f win32 &quot;$(InputPath)&quot; -o &quot;$(IntDir)/$(InputName).obj&quot;"
			Outputs="$(IntDir)/$(InputName).obj"/>
	</FileConfiguration>
	<FileConfiguration
		Name="Optimized Debug|Win32">
		<Tool
			Name="VCCustomBuildTool"
			CommandLine="&quot;<?php echo ((is_array($_tmp=((is_array($_tmp=$this->_tpl_vars['binDir'])) ? $this->_run_mod_handler('replace', true, $_tmp, '//', '/') : smarty_modifier_replace($_tmp, '//', '/')))) ? $this->_run_mod_handler('replace', true, $_tmp, '/', '\\') : smarty_modifier_replace($_tmp, '/', '\\')); ?>
nasm\nasm.exe&quot; -f win32 &quot;$(InputPath)&quot; -o &quot;$(IntDir)/$(InputName).obj&quot;"
			Outputs="$(IntDir)/$(InputName).obj"/>
	</FileConfiguration>
	<FileConfiguration
		Name="Release|Win32">
		<Tool
			Name="VCCustomBuildTool"
         CommandLine="&quot;<?php echo ((is_array($_tmp=((is_array($_tmp=$this->_tpl_vars['binDir'])) ? $this->_run_mod_handler('replace', true, $_tmp, '//', '/') : smarty_modifier_replace($_tmp, '//', '/')))) ? $this->_run_mod_handler('replace', true, $_tmp, '/', '\\') : smarty_modifier_replace($_tmp, '/', '\\')); ?>
nasm\nasm.exe&quot; -f win32 &quot;$(InputPath)&quot; -o &quot;$(IntDir)/$(InputName).obj&quot;"
			Outputs="$(IntDir)/$(InputName).obj"/>
	</FileConfiguration>
<?php endif; ?><?php endif; ?></File><?php $this->_smarty_vars['capture']['default'] = ob_get_contents();  $this->assign('itemOut', ob_get_contents());ob_end_clean(); ?>
<?php echo ((is_array($_tmp=$this->_tpl_vars['itemOut'])) ? $this->_run_mod_handler('indent', true, $_tmp, $this->_tpl_vars['depth'], "\t") : smarty_modifier_indent($_tmp, $this->_tpl_vars['depth'], "\t")); ?>

<?php endif; ?>