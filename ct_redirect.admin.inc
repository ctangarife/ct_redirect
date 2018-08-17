<?php
/**
 * @file
 * Admin functions
 *
 */
/**
 * Admin form builder
 */
 
 function ct_redirect_admin_form($form,$form_state){
     $form = array(
         'ct_path_origin' => array(
             '#type'   => 'textfield',
             '#title'  => t("Path to be redirect"),
             '#description'  => t("This field is for the path to be redirect to other path"),
             '#attributes' => array(
                 ' required' => 'required'),
             '#required' => TRUE,
         ),
         'ct_path_dest' => array(
             '#type'   => 'textfield',
             '#title'  => t("Path redirect destination"),
             '#description'  => t("This field is for the path destination redirect"),
            '#attributes' => array(
                ' required' => 'required'),
             '#required' => TRUE,
         ),
         'submit' => array(
             '#type' => 'submit', //field type
             '#value'=> t('Save'), //set submit button value. Edit record on edit and Add record on add.  
      )  
     );
     //return system_settings_form($form);
     return $form;
 }
// this function is invoked on form submit 
function ct_redirect_admin_form_submit($form, $form_state) {
    //Gets and sets the form fields value upon submission
    $path_org = $form_state['values']['ct_path_origin'];
    $path_dest = $form_state['values']['ct_path_dest'];
    
    //The data normalize to strolower
   // $path_org=strtolower($path_org);
    //$path_dest=strtolower($path_dest);
    //set data array for insert new record
    $data = array(
        'ct_url_org' => $path_org,
        'ct_url_dest' => $path_dest,
        'created' => date('Y-m-d H:i:s')
    );
    if(!empty($path_org) && $path_org!='' ){
        $datax=array();
        $query=db_select('ct_url_redirect','cr');
        $record=$query->fields('cr',array('id'))
            ->condition('cr.ct_url_org',$data['ct_url_org'],'=')
            ->orderBy('cr.id','DESC')
            ->range(0, 1)
            ->execute()
            ->fetchObject();
        
    }
    if (isset($record->id) && $record->id > 0) {
        $query = db_update('ct_url_redirect')
            ->fields(array(  
                'ct_url_org' => $data['ct_url_org'],
                'ct_url_dest' => $data['ct_url_dest'],
                'modificate' => date('Y-m-d H:i:s'),
            ))
            ->condition('id', $record->id)
            ->execute();
        drupal_set_message(t('The url '.$data['ct_url_org'].' going to be redirect to '.$data['ct_url_dest']));
        drupal_goto('admin/config/search/ct-config-path');
    }else {
        $query = db_insert('ct_url_redirect')->fields($data);
        $insert_url = $query->execute();
        if($insert_url) {
            drupal_set_message('New url gonna be to redirect '.$data['ct_url_org'].' to '.$data['ct_url_dest']);
            drupal_goto('admin/config/search/ct-config-path');
        }else{
            drupal_set_message(t('Error while inserting data into database'), 'error');
        }
    }
}