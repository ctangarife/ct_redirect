<?php
/**
 * @file
 * Admin functions
 *
 */
/**
 * Admin form builder
 */
 
 function ct_redirect_admin_form(){
     var_dump(base_path());
     $output="<form method='POST' name='ct_redirect'>";
 }

function ct_redirect_admin_form_alter($form, $form_state, $form_id) {
  $form['#submit'] = 'ct_redirect_save';
}

function ct_redirect_save(){
    var_dump('Hola');
}