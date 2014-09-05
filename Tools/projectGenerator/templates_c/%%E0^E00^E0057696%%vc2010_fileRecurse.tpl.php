<?php /* Smarty version 2.6.18, created on 2014-09-04 17:02:57
         compiled from vc2010_fileRecurse.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('modifier', 'replace', 'vc2010_fileRecurse.tpl', 22, false),array('modifier', 'indent', 'vc2010_fileRecurse.tpl', 46, false),)), $this); ?>
<?php if (is_array ( $this->_tpl_vars['dirWalk'] )): ?>

            <?php $_from = $this->_tpl_vars['dirWalk']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['key'] => $this->_tpl_vars['dir']):
?>
   <?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "vc2010_fileRecurse.tpl", 'smarty_include_vars' => array('dirWalk' => $this->_tpl_vars['dir'],'dirName' => $this->_tpl_vars['key'],'dirPath' => ($this->_tpl_vars['dirPath']).($this->_tpl_vars['dirName'])."/",'depth' => $this->_tpl_vars['depth']+1)));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>
   <?php endforeach; endif; unset($_from); ?>
   
<?php else: ?>

            <?php ob_start(); ?>
      <?php if (dontCompile ( $this->_tpl_vars['dirWalk']->path , $this->_tpl_vars['projOutput'] )): ?>
      <ClCompile Include=
      "<?php echo ((is_array($_tmp=((is_array($_tmp=$this->_tpl_vars['dirWalk']->path)) ? $this->_run_mod_handler('replace', true, $_tmp, '//', '/') : smarty_modifier_replace($_tmp, '//', '/')))) ? $this->_run_mod_handler('replace', true, $_tmp, '/', '\\') : smarty_modifier_replace($_tmp, '/', '\\')); ?>
">
            <ExcludedFromBuild Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'">true</ExcludedFromBuild>
            <ExcludedFromBuild Condition="'$(Configuration)|$(Platform)'=='Optimized Debug|Win32'">true</ExcludedFromBuild>
            <ExcludedFromBuild Condition="'$(Configuration)|$(Platform)'=='Release|Win32'">true</ExcludedFromBuild>
      </ClCompile>
   <?php else: ?>
      <?php if (substr ( $this->_tpl_vars['dirWalk']->path , -4 , 4 ) == ".asm"): ?>
         <CustomBuild Include="<?php echo ((is_array($_tmp=((is_array($_tmp=$this->_tpl_vars['dirWalk']->path)) ? $this->_run_mod_handler('replace', true, $_tmp, '//', '/') : smarty_modifier_replace($_tmp, '//', '/')))) ? $this->_run_mod_handler('replace', true, $_tmp, '/', '\\') : smarty_modifier_replace($_tmp, '/', '\\')); ?>
">
            <Command Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'">"<?php echo ((is_array($_tmp=((is_array($_tmp=$this->_tpl_vars['binDir'])) ? $this->_run_mod_handler('replace', true, $_tmp, '//', '/') : smarty_modifier_replace($_tmp, '//', '/')))) ? $this->_run_mod_handler('replace', true, $_tmp, '/', '\\') : smarty_modifier_replace($_tmp, '/', '\\')); ?>
nasm\nasm.exe" -f win32 "%(FullPath)" -o "$(IntDir)%(Filename).obj"</Command>
            <Outputs Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'">$(IntDir)%(Filename).obj;%(Outputs)</Outputs>
            <Command Condition="'$(Configuration)|$(Platform)'=='Optimized Debug|Win32'">"<?php echo ((is_array($_tmp=((is_array($_tmp=$this->_tpl_vars['binDir'])) ? $this->_run_mod_handler('replace', true, $_tmp, '//', '/') : smarty_modifier_replace($_tmp, '//', '/')))) ? $this->_run_mod_handler('replace', true, $_tmp, '/', '\\') : smarty_modifier_replace($_tmp, '/', '\\')); ?>
nasm\nasm.exe" -f win32 "%(FullPath)" -o "$(IntDir)%(Filename).obj"</Command>
            <Outputs Condition="'$(Configuration)|$(Platform)'=='Optimized Debug|Win32'">$(IntDir)%(Filename).obj;%(Outputs)</Outputs>
            <Command Condition="'$(Configuration)|$(Platform)'=='Release|Win32'">"<?php echo ((is_array($_tmp=((is_array($_tmp=$this->_tpl_vars['binDir'])) ? $this->_run_mod_handler('replace', true, $_tmp, '//', '/') : smarty_modifier_replace($_tmp, '//', '/')))) ? $this->_run_mod_handler('replace', true, $_tmp, '/', '\\') : smarty_modifier_replace($_tmp, '/', '\\')); ?>
nasm\nasm.exe" -f win32 "%(FullPath)" -o "$(IntDir)%(Filename).obj"</Command>
            <Outputs Condition="'$(Configuration)|$(Platform)'=='Release|Win32'">$(IntDir)%(Filename).obj;%(Outputs)</Outputs>
         </CustomBuild>
      <?php elseif ($this->_tpl_vars['projOutput']->isSourceFile ( $this->_tpl_vars['dirWalk']->path )): ?>
         <ClCompile Include="<?php echo ((is_array($_tmp=((is_array($_tmp=$this->_tpl_vars['dirWalk']->path)) ? $this->_run_mod_handler('replace', true, $_tmp, '//', '/') : smarty_modifier_replace($_tmp, '//', '/')))) ? $this->_run_mod_handler('replace', true, $_tmp, '/', '\\') : smarty_modifier_replace($_tmp, '/', '\\')); ?>
" />      
      <?php elseif ($this->_tpl_vars['projOutput']->isResourceFile ( $this->_tpl_vars['dirWalk']->path )): ?>
         <ResourceCompile Include="<?php echo ((is_array($_tmp=((is_array($_tmp=$this->_tpl_vars['dirWalk']->path)) ? $this->_run_mod_handler('replace', true, $_tmp, '//', '/') : smarty_modifier_replace($_tmp, '//', '/')))) ? $this->_run_mod_handler('replace', true, $_tmp, '/', '\\') : smarty_modifier_replace($_tmp, '/', '\\')); ?>
" />      
      <?php else: ?>
         <ClInclude Include="<?php echo ((is_array($_tmp=((is_array($_tmp=$this->_tpl_vars['dirWalk']->path)) ? $this->_run_mod_handler('replace', true, $_tmp, '//', '/') : smarty_modifier_replace($_tmp, '//', '/')))) ? $this->_run_mod_handler('replace', true, $_tmp, '/', '\\') : smarty_modifier_replace($_tmp, '/', '\\')); ?>
" />      
      <?php endif; ?>   
   <?php endif; ?>   <?php $this->_smarty_vars['capture']['default'] = ob_get_contents();  $this->assign('itemOut', ob_get_contents());ob_end_clean(); ?>
   <?php echo ((is_array($_tmp=$this->_tpl_vars['itemOut'])) ? $this->_run_mod_handler('indent', true, $_tmp, $this->_tpl_vars['depth'], "\t") : smarty_modifier_indent($_tmp, $this->_tpl_vars['depth'], "\t")); ?>

   
<?php endif; ?>