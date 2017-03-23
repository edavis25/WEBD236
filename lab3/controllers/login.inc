<?php
include_once "include/util.inc";
//include_once "models/users_model.inc";
include_once 'models/User.inc';


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
    
    $validUser = User::isValidUser($username, $password);
    if ($validUser) {
        // Set session variables
        $_SESSION['loggedin'] = true;
        $_SESSION['UserID'] = $validUser->getId();
	$_SESSION['FirstName'] = $validUser->getFirstName();
	$_SESSION['LastName'] = $validUser->getLastName();
	$_SESSION['Email'] = $validUser->getEmail();
		
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