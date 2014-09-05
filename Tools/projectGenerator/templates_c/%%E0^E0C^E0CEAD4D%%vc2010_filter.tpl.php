<?php /* Smarty version 2.6.18, created on 2014-09-04 17:02:57
         compiled from vc2010_filter.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'gen_uuid', 'vc2010_filter.tpl', 7, false),)), $this); ?>
<?php echo '<?xml'; ?>
 version="1.0" encoding="utf-8"<?php echo '?>'; ?>

<Project ToolsVersion="4.0" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
   <ItemGroup>
      <Filter Include="Source Files">
         <UniqueIdentifier><?php echo gen_uuid(array(), $this);?>
</UniqueIdentifier>
         <Extensions>cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;cc</Extensions>
      </Filter>
<?php $_from = $this->_tpl_vars['Folders']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['folder']):
?>
      <Filter Include="Source Files\<?php echo $this->_tpl_vars['folder']; ?>
">
         <UniqueIdentifier><?php echo gen_uuid(array(), $this);?>
</UniqueIdentifier>
      </Filter>
<?php endforeach; endif; unset($_from); ?>
   </ItemGroup>
  <ItemGroup>
    <ResourceCompile Include="Torque.rc">
      <Filter>Source Files</Filter>
    </ResourceCompile>
  </ItemGroup>
   <ItemGroup>
<?php $_from = $this->_tpl_vars['SrcFiles']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['path'] => $this->_tpl_vars['dir']):
?>
      <ClCompile Include="<?php echo $this->_tpl_vars['path']; ?>
">
         <Filter>Source Files\<?php echo $this->_tpl_vars['dir']; ?>
</Filter>
      </ClCompile>
<?php endforeach; endif; unset($_from); ?>
   </ItemGroup>
   <ItemGroup>
<?php $_from = $this->_tpl_vars['IncFiles']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['path'] => $this->_tpl_vars['dir']):
?>
      <ClInclude Include="<?php echo $this->_tpl_vars['path']; ?>
">
         <Filter>Source Files\<?php echo $this->_tpl_vars['dir']; ?>
</Filter>
      </ClInclude>
<?php endforeach; endif; unset($_from); ?>
   </ItemGroup>
   <ItemGroup>
<?php $_from = $this->_tpl_vars['OtherFiles']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['path'] => $this->_tpl_vars['dir']):
?>
      <CustomBuild Include="<?php echo $this->_tpl_vars['path']; ?>
">
         <Filter>Source Files\<?php echo $this->_tpl_vars['dir']; ?>
</Filter>
      </CustomBuild>
<?php endforeach; endif; unset($_from); ?>
   </ItemGroup>
</Project>