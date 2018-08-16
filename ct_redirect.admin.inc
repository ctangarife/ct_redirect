<?php
/**
 * @file
 * Admin functions
 *
 */
/**
 * Admin form builder
 */
 
 function ct_redirect_admin_form(&$form,&$form_state){
     $form = array(
         'ct_path_origin' => array(
             '#type'   => 'textfield',
             '#title'  => t("Path to be redirect"),
             '#description'  => t("This field is for the path to be redirect to other path"),
         ),
         'ct_path_dest' => array(
             '#type'   => 'textfield',
             '#title'  => t("Path redirect destination"),
             '#description'  => t("This field is for the path destination redirect"),
         )
     );
     return system_settings_form($form);
 }