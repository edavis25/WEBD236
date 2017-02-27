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
    
    $validUser = isValidUser($username, $password);
	if ($validUser) {
    //if (isValidUser($username, $password)) {
        	
        // Set session variables
        $_SESSION['loggedin'] = true;
		$_SESSION['UserID'] = $validUser['UserID'];
		$_SESSION['FirstName'] = $validUser['FirstName'];
		$_SESSION['LastName'] = $validUser['LastName'];
		
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