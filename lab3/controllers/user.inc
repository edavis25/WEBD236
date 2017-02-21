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
	
	// TODO: if test for testing duplicate email
	if ($_POST['username'] == 'admin') {
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
	
	// TODO: Add user to DB
	$id = insertUser($inputs['first_name'], $inputs['last_name'], $inputs['username'], $inputs['password']);
	// TODO: Log user in
	redirectRelative("index");
}

