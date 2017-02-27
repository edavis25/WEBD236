<?php
include_once "include/util.inc";
include_once "models/users_model.inc";

// Get view login view
function get_register($params) {
    renderTemplate(
        "views/edit_user_view.inc",
        array(
            'title' => 'Register',
            'form_action' => 'user/register',
            'button_text' => 'Register'
        )
    );
}

function post_register($params) {
	// Get post data
	$inputs['first_name'] = safeParam($_POST, 'first-name', false);
	$inputs['last_name'] = safeParam($_POST, 'last-name', false);
	$inputs['username'] = safeParam($_POST, 'username', false);
	$inputs['password'] = safeParam($_POST, 'password', false);
	
	// Check for all required fields and begin building error string (if necessary)
	$errors = validate_present(array('first-name', 'last-name', 'username', 'password'));
	
	// Check for valid email (doesn't exist in DB already)
	if (isValidEmail($inputs['username'])) {
		$errors .= '&bull; Email address already in use.';
	}
	
	// Errors found, gather any data entered by the user and re-render with errors shown
	if ($errors) {
    	renderTemplate(
       		"views/edit_user_view.inc",
        	array(
    	        'title' => 'Register',
    	        'form_action' => 'user/register',
            	'button_text' => 'Register',
    	        'errors' => $errors,
    	        'inputs' => $inputs
	        )
   		 );
    	die; // Errors found, stop here after re-render
    }
	
	// No errors found: register and log user in
	// Add user to DB
	$id = insertUser($inputs['first_name'], $inputs['last_name'], $inputs['username'], $inputs['password']);
	
	// Log user in and set SESSION variables
	$_SESSION['loggedin'] = true;
	$_SESSION['UserID'] = $id;
	$_SESSION['FirstName'] = $inputs['first_name'];
	$_SESSION['LastName'] = $inputs['last_name'];
	
	redirectRelative("index");
}

