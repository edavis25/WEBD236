<?php
include_once "include/util.inc";
include_once "models/users_model.inc";


// Get view login view
function get_index($params) {
    renderTemplate(
        "views/login_view.inc",
        array(
            'title' => 'Login',
        )
    );
}

function post_index($params) {
    $username = safeParam($_POST, 'username', false);
    $password = safeParam($_POST, 'password', false);
    if (isValidUser($username, $password)) {
        $_SESSION['loggedin'] = true;
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
            'errors' => "Invalid username/password",
            'username' => $username,
            'password' => $password
        )
    );
    // @formatter:on
    }
}