<?php
include_once "include/util.inc";
include_once 'models/User.inc';


// Get view login view
function get_index($params) {
    // @formatter: off
    renderTemplate(
        "views/login_view.inc",
        array(
            'title' => 'Login',
        )
    );
    // @formatter: on
}

function post_index($params) {
    $username = safeParam($_POST, 'username', false);
    $password = safeParam($_POST, 'password', false);
    
    $validUser = User::isValidUser($username, $password);
    if ($validUser) {
        updateSession($validUser);
		
        if (isset($_SESSION['redirect'])) {
            $redirect = $_SESSION['redirect'];
            redirect($redirect);
            exit();
        }
        redirectRelative("index");
    } 
    else {
        // @formatter:off
        renderTemplate(
            "views/login_view.inc",
            array(
                'title' => 'Login',
                'errors' => array("Invalid username/password"),
                'username' => $username,
                'password' => $password
            )
        );
        // @formatter:on
    }
}