<?php
include_once 'include/util.inc';
include_once 'include/Authenticator.inc';

function get_index($params) {
    Authenticator::instance() -> ensure('admin_page');
    
    renderTemplate(
        "views/admin_tools_view.inc", 
        array(
            'title' => 'Administrative Tools'
        )
    );
}
