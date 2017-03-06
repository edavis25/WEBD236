<?php
include_once "include/util.inc";
include_once "models/users_model.inc";
include_once "models/questions_model.inc";


// View user
function get_view_user($params) {
	// Get userID and retreive user info
	$id = safeParam($params, 0, false);
	$data = retrieveUserById($id);
	if (!$data) {
		die("Error: user not found.");
	}
	
	// Get user's questions
	$questions = retrieveQuestionsByUserId($id);
	
	// Flag for account owner (show the edit/delete account links)
	$ownsAccount = (isLoggedIn() && $_SESSION['UserID'] == $data['UserID']);
	
	renderTemplate(
		"views/view_user_view.inc",
		array(
			'title' => 'View User',
			'data' => $data,
			'questions' => $questions,
			'ownsAccount' => $ownsAccount
		)
	);		
}


/*
 *  Display user registration page
 */
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

/*
 * Register user into the database (POST registration submit event)
 */
function post_register($params) {
	// Get post data
	$inputs['FirstName'] = safeParam($_POST, 'first-name', false);
	$inputs['LastName'] = safeParam($_POST, 'last-name', false);
	$inputs['Email'] = safeParam($_POST, 'username', false);
	$inputs['Password'] = safeParam($_POST, 'password', false);
	
	// Check for all required fields and begin building error string (if necessary)
	$errors = validate_present(array('first-name', 'last-name', 'username', 'password'));
	
	// Check for valid email (doesn't exist in DB already)
	if (isValidEmail($inputs['Email'])) {
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
	$id = insertUser($inputs['FirstName'], $inputs['LastName'], $inputs['Email'], $inputs['Password']);
	
	// Log user in and set SESSION variables
	$_SESSION['loggedin'] = true;
	$_SESSION['UserID'] = $id;
	$_SESSION['FirstName'] = $inputs['FirstName'];
	$_SESSION['LastName'] = $inputs['LastName'];
	$_SESSION['Email'] = $inputs['Email'];
	
	redirectRelative("index");
}

/**
 * Edit existing user information
 */
function get_edit_user($params) {
	ensureLoggedIn();
	
	// Use the user's ID from SESSION to prohibit any URL fishing edits
	$id = safeParam($_SESSION, 'UserID', false);
	
	$inputs = retrieveUserById($id);
	if (!$inputs) {
		die("Error. User not found.");
	}
	
	renderTemplate(
        "views/edit_user_view.inc",
        array(
            'title' => 'Edit User',
            'form_action' => 'user/edit_user',
            'button_text' => 'Save Changes',
            'inputs' => $inputs
        )
    );
}

/**
 * Save edit user changes (edit user form POST submit event)
 */
function post_edit_user($params) {
	ensureLoggedIn();
	
	// Get post data
	$inputs['FirstName'] = safeParam($_POST, 'first-name', false);
	$inputs['LastName'] = safeParam($_POST, 'last-name', false);
	$inputs['Email'] = safeParam($_POST, 'username', false);
	$inputs['Password'] = safeParam($_POST, 'password', false);
	
	// Check for all required fields and begin building error string (if necessary)
	$errors = validate_present(array('first-name', 'last-name', 'username', 'password'));
	
	// Check for valid email ONLY if the user changed it
	if ($_SESSION['Email'] != $inputs['Email']) {	
		if (isValidEmail($inputs['Email'])) {
			$errors .= '&bull; Email address already in use.';
		}
	}
	
	// Errors found, gather any data entered by the user and re-render with errors shown
	if ($errors) {
    	renderTemplate(
       		"views/edit_user_view.inc",
        	array(
    	        'title' => 'Edit User',
    	        'form_action' => 'user/edit_user',
            	'button_text' => 'Save Changes',
    	        'errors' => $errors,
    	        'inputs' => $inputs
	        )
   		 );
    	die; // Errors found, stop here after re-render
    }
	
	// Update user information in the DB
	$id = safeParam($_SESSION, 'UserID', false); 
	updateUserById($inputs['FirstName'], $inputs['LastName'], $inputs['Email'], $inputs['Password'], $id);
	
	// Update SESSION variables
	$_SESSION['FirstName'] = $inputs['FirstName'];
	$_SESSION['LastName'] = $inputs['LastName'];
	$_SESSION['Email'] = $inputs['Email'];
	
	redirectRelative("user/view_user/$id");	
}

/**
 * Delete user and all their questions from the database
 */
function get_delete_user($params) {
	ensureLoggedIn();
	
	// Use the user's ID from SESSION to prohibit any URL fishing deletes
	$id = safeParam($_SESSION, 'UserID', false);
	
	deleteQuestionByUserId($id);
	deleteUserById($id);
	
	redirectRelative("logout");
}
