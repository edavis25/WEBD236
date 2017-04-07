<?php
include_once 'include/util.inc';
include_once 'include/Authenticator.inc';
include_once 'models/Group.inc';

function get_manage_groups($params) {
    Authenticator::instance() -> ensure('admin_page');
    
    $groups = Group::findAll();
    
    renderTemplate(
        "views/group_manage_view.inc", 
        array(
            'title' => 'Manage Groups',
            'groups' => $groups
        )
    );
}